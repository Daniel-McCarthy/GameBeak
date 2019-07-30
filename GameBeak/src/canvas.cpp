#include "canvas.h"

Canvas::Canvas(QWidget* parent)
    : QOpenGLWidget(parent), m_Texture(), m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    setFocusPolicy(Qt::NoFocus);
    setMouseTracking(false);
   setMinimumSize(320,288);
}

Canvas::~Canvas() {
    makeCurrent();
    delete m_Texture;
    delete vertexShader;
    delete fragmentShader;
}

void Canvas::initializeGL() {
    makeCurrent();
    initializeOpenGLFunctions();

    glMatrixMode(GL_PROJECTION);

    vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    const char* vertexShaderSource =
            "attribute highp vec4 qt_Vertex;\n"
            "attribute highp vec2 qt_MultiTexCoord0;\n"
            "uniform highp mat4 qt_ModelViewProjectionMatrix;\n"
            "varying highp vec2 qt_TexCoord0;\n"
            "void main(void)\n"
            "{\n"
            "    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;\n"
            "    qt_TexCoord0 = qt_MultiTexCoord0;\n"
            "}\n";

    vertexShader->compileSourceCode(vertexShaderSource);

    fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    const char* fragmentShaderSource =
            "uniform sampler2D qt_Texture0;\n"
            "varying highp vec2 qt_TexCoord0;\n"
            "void main(void)\n"
            "{\n"
            "    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0);\n"
            "}\n";
    fragmentShader->compileSourceCode(fragmentShaderSource);

    shaderProgram.addShader(vertexShader);
    shaderProgram.addShader(fragmentShader);
    shaderProgram.link();

    m_Texture = new QOpenGLTexture((currentFrame).mirrored());
    m_Texture->setMinificationFilter(QOpenGLTexture::Linear);
    m_Texture->setMagnificationFilter(QOpenGLTexture::Linear);
    buildDrawingSurface();

}

void Canvas::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(0.0, 0.0, -5.0);

    updateTexture();
    m_Texture->bind(0);

    shaderProgram.bind();
    shaderProgram.setUniformValue("qt_ModelViewProjectionMatrix", m_projectionMatrix * modelViewMatrix);
    shaderProgram.setUniformValue("qt_Texture0", 0);

    m_arrayBuffer.bind();

    int vertLoc = shaderProgram.attributeLocation("qt_Vertex");
    shaderProgram.enableAttributeArray(vertLoc);
    shaderProgram.setAttributeBuffer(vertLoc, GL_FLOAT, 0, 3, sizeof(GLfloat) * (3 + 2 + 3));

    int texLoc = shaderProgram.attributeLocation("qt_MultiTexCoord0");
    shaderProgram.enableAttributeArray(texLoc);
    shaderProgram.setAttributeBuffer(texLoc, GL_FLOAT, sizeof(GLfloat) * 3, 2, sizeof(GLfloat) * (3 + 2 + 3));

    m_indexBuffer.bind();

    glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);
}

void Canvas::buildDrawingSurface() {
    GLfloat vertices[] = {
        // Vertex Positions         // Texture Coordinates      // Normals
        -2.295f,  2.05f, 0.0f,      0.0f, 1.0f,                 0.0f, 0.0f, 1.0f, // Top Left
        -2.295f, -2.05f, 0.0f,      0.0f, 0.0f,                 0.0f, 0.0f, 1.0f, // Bottom Left
         2.295f,  2.05f, 0.0f,      1.0f, 1.0f,                 0.0f, 0.0f, 1.0f, // Top Right
         2.295f, -2.05f, 0.0f,      1.0f, 0.0f,                 0.0f, 0.0f, 1.0f, // Bottom Right
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 1 ,3
    };

    m_arrayBuffer.create();
    m_arrayBuffer.bind();
    m_arrayBuffer.allocate(vertices, sizeof(vertices));
    m_arrayBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indices, sizeof (indices));
    m_indexBuffer.release();
}

void Canvas:: updateTexture() {
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, currentFrame.width(), currentFrame.height(), GL_BGRA, GL_UNSIGNED_BYTE, currentFrame.mirrored().bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Canvas::resizeGL(int w, int h) {
    float aspect = w /(float)h;
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.1f, 10.0f);
}

void Canvas::drawImage(QImage image)
{
    image = image.scaled(320, 288, Qt::IgnoreAspectRatio);
    currentFrame = image;
    update();
}


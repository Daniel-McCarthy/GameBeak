#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QColor>
#include <QPainter>
#include <QMatrix4x4>

class Canvas : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    Canvas(QWidget* parent = 0);
    ~Canvas();

private:
    void paintTexturedCube();
    void buildDrawingSurface();
    void updateTexture();
    QImage currentFrame;

    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLTexture* m_Texture;
    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_indexBuffer;
    QOpenGLBuffer vertexBuffer;
    QMatrix4x4 modelViewMatrix;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;


public slots:
    void drawImage(QImage image);
};

#endif // CANVAS_H

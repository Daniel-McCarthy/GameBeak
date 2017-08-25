namespace GameBeak_Frontend
{
    partial class AssemblyView
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AssemblyView));
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.afLabel = new System.Windows.Forms.Label();
            this.bcLabel = new System.Windows.Forms.Label();
            this.deLabel = new System.Windows.Forms.Label();
            this.hlLabel = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.spLabel = new System.Windows.Forms.Label();
            this.spValuesLabel = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.afValue = new System.Windows.Forms.Label();
            this.bcValue = new System.Windows.Forms.Label();
            this.deValue = new System.Windows.Forms.Label();
            this.hlValue = new System.Windows.Forms.Label();
            this.spValue = new System.Windows.Forms.Label();
            this.stackValue = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.pcValue = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // listBox1
            // 
            this.listBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(162)))), ((int)(((byte)(212)))));
            this.listBox1.Font = new System.Drawing.Font("Courier New", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.listBox1.FormattingEnabled = true;
            this.listBox1.ItemHeight = 18;
            this.listBox1.Location = new System.Drawing.Point(218, 12);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(302, 292);
            this.listBox1.TabIndex = 2;
            // 
            // stepButton
            // 
            this.stepButton.Location = new System.Drawing.Point(255, 310);
            this.stepButton.Name = "stepButton";
            this.stepButton.Size = new System.Drawing.Size(83, 44);
            this.stepButton.TabIndex = 4;
            this.stepButton.Text = "Step";
            this.stepButton.UseVisualStyleBackColor = true;
            this.stepButton.Click += new System.EventHandler(this.stepButton_Click);
            // 
            // runButton
            // 
            this.runButton.Location = new System.Drawing.Point(413, 310);
            this.runButton.Name = "runButton";
            this.runButton.Size = new System.Drawing.Size(52, 44);
            this.runButton.TabIndex = 5;
            this.runButton.Text = "Run";
            this.runButton.UseVisualStyleBackColor = true;
            this.runButton.Click += new System.EventHandler(this.runButton_Click);
            // 
            // pauseButton
            // 
            this.pauseButton.Location = new System.Drawing.Point(471, 310);
            this.pauseButton.Name = "pauseButton";
            this.pauseButton.Size = new System.Drawing.Size(49, 44);
            this.pauseButton.TabIndex = 6;
            this.pauseButton.Text = "Pause";
            this.pauseButton.UseVisualStyleBackColor = true;
            this.pauseButton.Click += new System.EventHandler(this.pauseButton_Click);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(225)))), ((int)(((byte)(148)))), ((int)(((byte)(255)))));
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel1.Controls.Add(this.groupBox3);
            this.panel1.Controls.Add(this.groupBox1);
            this.panel1.Controls.Add(this.groupBox2);
            this.panel1.Location = new System.Drawing.Point(12, 12);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(200, 292);
            this.panel1.TabIndex = 3;
            // 
            // afLabel
            // 
            this.afLabel.AutoSize = true;
            this.afLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.afLabel.Location = new System.Drawing.Point(6, 23);
            this.afLabel.Name = "afLabel";
            this.afLabel.Size = new System.Drawing.Size(31, 16);
            this.afLabel.TabIndex = 0;
            this.afLabel.Text = "AF:";
            // 
            // bcLabel
            // 
            this.bcLabel.AutoSize = true;
            this.bcLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bcLabel.Location = new System.Drawing.Point(6, 39);
            this.bcLabel.Name = "bcLabel";
            this.bcLabel.Size = new System.Drawing.Size(32, 16);
            this.bcLabel.TabIndex = 1;
            this.bcLabel.Text = "BC:";
            // 
            // deLabel
            // 
            this.deLabel.AutoSize = true;
            this.deLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.deLabel.Location = new System.Drawing.Point(6, 55);
            this.deLabel.Name = "deLabel";
            this.deLabel.Size = new System.Drawing.Size(33, 16);
            this.deLabel.TabIndex = 2;
            this.deLabel.Text = "DE:";
            // 
            // hlLabel
            // 
            this.hlLabel.AutoSize = true;
            this.hlLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.hlLabel.Location = new System.Drawing.Point(8, 71);
            this.hlLabel.Name = "hlLabel";
            this.hlLabel.Size = new System.Drawing.Size(31, 16);
            this.hlLabel.TabIndex = 3;
            this.hlLabel.Text = "HL:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(13, 16);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(32, 16);
            this.label5.TabIndex = 4;
            this.label5.Text = "PC:";
            // 
            // spLabel
            // 
            this.spLabel.AutoSize = true;
            this.spLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.spLabel.Location = new System.Drawing.Point(7, 20);
            this.spLabel.Name = "spLabel";
            this.spLabel.Size = new System.Drawing.Size(32, 16);
            this.spLabel.TabIndex = 5;
            this.spLabel.Text = "SP:";
            // 
            // spValuesLabel
            // 
            this.spValuesLabel.AutoSize = true;
            this.spValuesLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.spValuesLabel.Location = new System.Drawing.Point(6, 36);
            this.spValuesLabel.Name = "spValuesLabel";
            this.spValuesLabel.Size = new System.Drawing.Size(59, 16);
            this.spValuesLabel.TabIndex = 6;
            this.spValuesLabel.Text = "SP Val:";
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(225)))), ((int)(((byte)(138)))), ((int)(((byte)(235)))));
            this.groupBox1.Controls.Add(this.hlValue);
            this.groupBox1.Controls.Add(this.deValue);
            this.groupBox1.Controls.Add(this.bcValue);
            this.groupBox1.Controls.Add(this.afValue);
            this.groupBox1.Controls.Add(this.afLabel);
            this.groupBox1.Controls.Add(this.bcLabel);
            this.groupBox1.Controls.Add(this.deLabel);
            this.groupBox1.Controls.Add(this.hlLabel);
            this.groupBox1.Location = new System.Drawing.Point(3, 1);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(190, 105);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Registers";
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(225)))), ((int)(((byte)(138)))), ((int)(((byte)(235)))));
            this.groupBox2.Controls.Add(this.stackValue);
            this.groupBox2.Controls.Add(this.spValue);
            this.groupBox2.Controls.Add(this.spValuesLabel);
            this.groupBox2.Controls.Add(this.spLabel);
            this.groupBox2.Location = new System.Drawing.Point(3, 112);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(190, 68);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Stack Values";
            // 
            // afValue
            // 
            this.afValue.AutoSize = true;
            this.afValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.afValue.Location = new System.Drawing.Point(71, 23);
            this.afValue.Name = "afValue";
            this.afValue.Size = new System.Drawing.Size(0, 16);
            this.afValue.TabIndex = 4;
            // 
            // bcValue
            // 
            this.bcValue.AutoSize = true;
            this.bcValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bcValue.Location = new System.Drawing.Point(71, 39);
            this.bcValue.Name = "bcValue";
            this.bcValue.Size = new System.Drawing.Size(0, 16);
            this.bcValue.TabIndex = 5;
            // 
            // deValue
            // 
            this.deValue.AutoSize = true;
            this.deValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.deValue.Location = new System.Drawing.Point(71, 55);
            this.deValue.Name = "deValue";
            this.deValue.Size = new System.Drawing.Size(0, 16);
            this.deValue.TabIndex = 6;
            // 
            // hlValue
            // 
            this.hlValue.AutoSize = true;
            this.hlValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.hlValue.Location = new System.Drawing.Point(71, 71);
            this.hlValue.Name = "hlValue";
            this.hlValue.Size = new System.Drawing.Size(0, 16);
            this.hlValue.TabIndex = 7;
            // 
            // spValue
            // 
            this.spValue.AutoSize = true;
            this.spValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.spValue.Location = new System.Drawing.Point(71, 20);
            this.spValue.Name = "spValue";
            this.spValue.Size = new System.Drawing.Size(0, 16);
            this.spValue.TabIndex = 8;
            // 
            // stackValue
            // 
            this.stackValue.AutoSize = true;
            this.stackValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stackValue.Location = new System.Drawing.Point(71, 36);
            this.stackValue.Name = "stackValue";
            this.stackValue.Size = new System.Drawing.Size(0, 16);
            this.stackValue.TabIndex = 9;
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(225)))), ((int)(((byte)(138)))), ((int)(((byte)(235)))));
            this.groupBox3.Controls.Add(this.pcValue);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Location = new System.Drawing.Point(3, 185);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(190, 100);
            this.groupBox3.TabIndex = 7;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Other Values";
            // 
            // pcValue
            // 
            this.pcValue.AutoSize = true;
            this.pcValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pcValue.Location = new System.Drawing.Point(51, 16);
            this.pcValue.Name = "pcValue";
            this.pcValue.Size = new System.Drawing.Size(0, 16);
            this.pcValue.TabIndex = 5;
            // 
            // AssemblyView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(122)))), ((int)(((byte)(175)))));
            this.ClientSize = new System.Drawing.Size(532, 360);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.listBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "AssemblyView";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "GameBeak - Assembly View";
            this.panel1.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label spValuesLabel;
        private System.Windows.Forms.Label spLabel;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label hlLabel;
        private System.Windows.Forms.Label deLabel;
        private System.Windows.Forms.Label bcLabel;
        private System.Windows.Forms.Label afLabel;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label stackValue;
        private System.Windows.Forms.Label spValue;
        private System.Windows.Forms.Label hlValue;
        private System.Windows.Forms.Label deValue;
        private System.Windows.Forms.Label bcValue;
        private System.Windows.Forms.Label afValue;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label pcValue;
    }
}
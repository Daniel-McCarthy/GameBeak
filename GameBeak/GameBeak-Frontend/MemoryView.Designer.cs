namespace GameBeak_Frontend
{
    partial class MemoryView
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MemoryView));
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.refreshButton = new System.Windows.Forms.Button();
            this.thousandthNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.hundredthNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.addressLabel = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.thousandthNumericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.hundredthNumericUpDown)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // richTextBox1
            // 
            this.richTextBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(218)))), ((int)(((byte)(255)))));
            this.richTextBox1.Font = new System.Drawing.Font("Courier New", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.richTextBox1.Location = new System.Drawing.Point(12, 33);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(527, 298);
            this.richTextBox1.TabIndex = 0;
            this.richTextBox1.Text = "0000: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Courier New", 11.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(67, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(431, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F";
            // 
            // refreshButton
            // 
            this.refreshButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.refreshButton.Location = new System.Drawing.Point(464, 351);
            this.refreshButton.Name = "refreshButton";
            this.refreshButton.Size = new System.Drawing.Size(75, 45);
            this.refreshButton.TabIndex = 2;
            this.refreshButton.Text = "Refresh";
            this.refreshButton.UseVisualStyleBackColor = false;
            this.refreshButton.Click += new System.EventHandler(this.refreshButton_Click);
            // 
            // thousandthNumericUpDown
            // 
            this.thousandthNumericUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.thousandthNumericUpDown.Hexadecimal = true;
            this.thousandthNumericUpDown.Location = new System.Drawing.Point(15, 23);
            this.thousandthNumericUpDown.Maximum = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.thousandthNumericUpDown.Name = "thousandthNumericUpDown";
            this.thousandthNumericUpDown.Size = new System.Drawing.Size(31, 26);
            this.thousandthNumericUpDown.TabIndex = 5;
            this.thousandthNumericUpDown.ValueChanged += new System.EventHandler(this.thousandthNumericUpDown_ValueChanged);
            // 
            // hundredthNumericUpDown
            // 
            this.hundredthNumericUpDown.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.hundredthNumericUpDown.Hexadecimal = true;
            this.hundredthNumericUpDown.Location = new System.Drawing.Point(52, 23);
            this.hundredthNumericUpDown.Maximum = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.hundredthNumericUpDown.Name = "hundredthNumericUpDown";
            this.hundredthNumericUpDown.Size = new System.Drawing.Size(31, 26);
            this.hundredthNumericUpDown.TabIndex = 6;
            this.hundredthNumericUpDown.ValueChanged += new System.EventHandler(this.hundredthNumericUpDown_ValueChanged);
            // 
            // addressLabel
            // 
            this.addressLabel.AutoSize = true;
            this.addressLabel.BackColor = System.Drawing.Color.White;
            this.addressLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.addressLabel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.addressLabel.Location = new System.Drawing.Point(88, 23);
            this.addressLabel.Name = "addressLabel";
            this.addressLabel.Size = new System.Drawing.Size(21, 24);
            this.addressLabel.TabIndex = 7;
            this.addressLabel.Text = "0";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.thousandthNumericUpDown);
            this.groupBox1.Controls.Add(this.hundredthNumericUpDown);
            this.groupBox1.Controls.Add(this.addressLabel);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.groupBox1.Location = new System.Drawing.Point(12, 338);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(146, 59);
            this.groupBox1.TabIndex = 9;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Address";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.White;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.SystemColors.ControlText;
            this.label2.Location = new System.Drawing.Point(115, 23);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(21, 24);
            this.label2.TabIndex = 8;
            this.label2.Text = "0";
            // 
            // MemoryView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(142)))), ((int)(((byte)(205)))));
            this.ClientSize = new System.Drawing.Size(551, 408);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.refreshButton);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.richTextBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MemoryView";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "GameBeak - Memory Viewer";
            this.Load += new System.EventHandler(this.MemoryView_Load);
            ((System.ComponentModel.ISupportInitialize)(this.thousandthNumericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.hundredthNumericUpDown)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button refreshButton;
        private System.Windows.Forms.NumericUpDown thousandthNumericUpDown;
        private System.Windows.Forms.NumericUpDown hundredthNumericUpDown;
        private System.Windows.Forms.Label addressLabel;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label2;
    }
}
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GameBeak_Frontend
{

    public partial class MemoryView : Form
    {
        private ushort baseAddress = 0;

        public MemoryView()
        {
            InitializeComponent();
        }

        private void MemoryView_Load(object sender, EventArgs e)
        {
            loadMemory();
        }

        private void loadMemory()
        {
            richTextBox1.Text = "";

            for(int y = 0; y < 16; y++)
            {
                richTextBox1.Text += (baseAddress + (y * 16)).ToString("X4") + ':';

                for(int x = 0; x < 16; x++)
                {
                    if (x < 16)
                    {
                        richTextBox1.Text += " ";
                    }

                    richTextBox1.Text += NativeMethods.readMemoryByte((short)(baseAddress + (y * 16) + x)).ToString("X2");

                }

                richTextBox1.Text += '\n';
            }
        }

        private void refreshButton_Click(object sender, EventArgs e)
        {
            loadMemory();
        }

        private void thousandthNumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            baseAddress &= 0x0FFF;
            baseAddress |= (ushort)((int)thousandthNumericUpDown.Value << 12);

            loadMemory();
        }

        private void hundredthNumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            baseAddress &= 0xF0FF;
            baseAddress |= (ushort)((int)hundredthNumericUpDown.Value << 8);

            loadMemory();
        }
    }
}

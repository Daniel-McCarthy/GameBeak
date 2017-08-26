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
        }

    }
}

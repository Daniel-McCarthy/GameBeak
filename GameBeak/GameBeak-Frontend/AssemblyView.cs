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
    public partial class AssemblyView : Form
    {
        public AssemblyView()
        {
            InitializeComponent();
        }
        void updatePCValues()
        {
            short pc = NativeMethods.getPC();
            pcValue.Text = pc.ToString("X4");
        }

    }
}

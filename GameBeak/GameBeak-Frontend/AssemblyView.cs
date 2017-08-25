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

        //Call this upon:
        //Stepping
        //Pausing
        //Gaining Window Focus
        //More?
        void updateDisplayValues()
        {
            /*
            int[] registerValues = new int[4];
            Marshal.Copy(NativeMethods.getRegisters(), registerValues, 0, 4);

            afValue.Text = registerValues[0].ToString();
            bcValue.Text = registerValues[1].ToString();
            deValue.Text = registerValues[2].ToString();
            hlValue.Text = registerValues[3].ToString();
            */

            afValue.Text = NativeMethods.getAF().ToString("X4");
            bcValue.Text = NativeMethods.getBC().ToString("X4");
            deValue.Text = NativeMethods.getDE().ToString("X4");
            hlValue.Text = NativeMethods.getHL().ToString("X4");
        }

        void updatePCValues()
        {
            short pc = NativeMethods.getPC();
            pcValue.Text = pc.ToString("X4");
        }

    }
}

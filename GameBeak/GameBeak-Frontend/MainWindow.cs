using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;
using System.Diagnostics;
using SFML;
using SFML.Graphics;
using SFML.Window;
using System.Windows;

using sf = SFML.Graphics;
using System.Threading;

namespace GameBeak_Frontend
{
    public partial class MainWindow : Form
    {
        private Thread emulatorThread;
        private Thread screenUpdateThread;

        private AssemblyView assemblyView;
        private MemoryView memoryView;

        public MainWindow()
        {
            InitializeComponent();
        }


        /*
         *  Load Rom File 
        */
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string filePath = (openFileDialog1.ShowDialog() == DialogResult.OK) ? openFileDialog1.FileName : "Error: No such file found.";

            if(File.Exists(filePath))
            {
                byte[] rom = File.ReadAllBytes(filePath);

                NativeMethods.setRom(rom, rom.Length);

                NativeMethods.setPauseState(true);

                emulatorThread = new Thread(NativeMethods.initiateEmulator);
                emulatorThread.Start();

                screenUpdateThread = new Thread(updateScreen);
                screenUpdateThread.Start();
            }
            else
            {
                MessageBox.Show(filePath);
            }
        }

        private void updateScreen()
        {
            while (NativeMethods.getRunState())
            {  
                //Retrieve Image X/Y Sizes
                int[] dimensions = new int[2];
                Marshal.Copy(NativeMethods.getScreenDimensions(), dimensions, 0, 2);

                //Retrieve Image Pixel Data
                int pixelCount = (dimensions[0] * dimensions[1]);
                int[] pixelDataInts = new int[pixelCount];
                NativeMethods.getScreenPixelData(pixelDataInts);

                //Convert Image Pixel Data to Bytes
                byte[] pixelDataBytes = new byte[pixelCount * sizeof(int)];
                Buffer.BlockCopy(pixelDataInts, 0, pixelDataBytes, 0, pixelDataBytes.Length);

                //Create SFML image from X/Y Sizes and Pixel Data Bytes
                sf.Image newScreen = new sf.Image((uint)dimensions[0], (uint)dimensions[1], pixelDataBytes);

                //Convert SFML Image to Bitmap
                Bitmap bmp = new Bitmap((int)newScreen.Size.X, (int)newScreen.Size.Y);

                for (int x = 0; x < newScreen.Size.X; x++)
                {
                    for (int y = 0; y < newScreen.Size.Y; y++)
                    {
                        sf.Color pixel = newScreen.GetPixel((uint)x, (uint)y);
                        int pixelColor = ((pixel.A << 24) | (pixel.R << 16) | (pixel.G << 8) | (pixel.B));
                        bmp.SetPixel(x, y, System.Drawing.Color.FromArgb(pixelColor));
                    }
                }

                pictureBox1.Image = bmp;
                
                Thread.Sleep(8);
            }
        }

        private void MainWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            NativeMethods.setRunState(false);

            if(emulatorThread != null)
                emulatorThread.Abort();

            if(screenUpdateThread != null)
                screenUpdateThread.Abort();
        }

        private void assemblyViewToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (assemblyView == null || assemblyView.IsDisposed)
            {
                assemblyView = new AssemblyView();
                assemblyView.Show();
            }
            else
            {
                assemblyView.Show();
                assemblyView.BringToFront();
            }
        }

        private void memoryViewToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (memoryView == null || memoryView.IsDisposed)
            {
                memoryView = new MemoryView();
                memoryView.Show();
            }
            else
            {
                memoryView.Show();
                memoryView.BringToFront();
            }
        }

        /*
            bool keyUp = false;
            bool keyDown = false;
            bool keyLeft = false;
            bool keyRight = false;
            bool keyStart = false;
            bool keySelect = false;
            bool keyA = false;
            bool keyB = false;
         */
        private void MainWindow_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Up)
            {
                //this.BackColor = System.Drawing.Color.Aqua;
                NativeMethods.setKeyInput(0, true);
            }

            if(e.KeyCode == Keys.Down)
            {
                NativeMethods.setKeyInput(1, true);
            }

            if(e.KeyCode == Keys.Left)
            {
                NativeMethods.setKeyInput(2, true);
            }

            if(e.KeyCode == Keys.Right)
            {
                NativeMethods.setKeyInput(3, true);
            }

            if(e.KeyCode == Keys.Enter)
            {
                NativeMethods.setKeyInput(4, true);
            }

            if(e.KeyCode == Keys.RShiftKey)
            {
                NativeMethods.setKeyInput(5, true);
            }

            if(e.KeyCode == Keys.Z)
            {
                NativeMethods.setKeyInput(6, true);
            }

            if(e.KeyCode == Keys.X)
            {
                NativeMethods.setKeyInput(7, true);
            }
        }

        private void MainWindow_KeyUp(object sender, System.Windows.Forms.KeyEventArgs e)
        {
            
            if (e.KeyCode == Keys.Up)
            {
                //this.BackColor = System.Drawing.Color.Aqua;
                NativeMethods.setKeyInput(0, false);
            }

            if (e.KeyCode == Keys.Down)
            {
                NativeMethods.setKeyInput(1, false);
            }

            if (e.KeyCode == Keys.Left)
            {
                NativeMethods.setKeyInput(2, false);
            }

            if (e.KeyCode == Keys.Right)
            {
                NativeMethods.setKeyInput(3, false);
            }

            if (e.KeyCode == Keys.Enter)
            {
                NativeMethods.setKeyInput(4, false);
            }

            if (e.KeyCode == Keys.RShiftKey)
            {
                NativeMethods.setKeyInput(5, false);
            }

            if (e.KeyCode == Keys.Z)
            {
                NativeMethods.setKeyInput(6, false);
            }

            if (e.KeyCode == Keys.X)
            {
                NativeMethods.setKeyInput(7, false);
            }
            
        }
    }

    public class NativeMethods
    {

        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool getPauseState();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setPauseState(bool pauseEnabled);
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool getRunState();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setRunState(bool runEnabled);
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getRegisters();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern short getAF();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern short getBC();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern short getDE();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern short getHL();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getStackValues();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern short getPC();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getCurrentMemoryMap();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getScreenDimensions();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void getScreenPixelData(int[] pixelDataArray);
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool getScreenUpdated();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool getScreenDrawing();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getFirstScreenColor();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setRom(byte[] rom, int romSize);
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setStep();
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern byte readMemoryByte(short address);
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void initiateEmulator();

        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void disassembleAddress(ref short address, [MarshalAs(UnmanagedType.LPStr)] StringBuilder cString, ref int stringSize);
        [DllImport("GameBeak.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setKeyInput(int keyCode, bool enabled);
    }
}
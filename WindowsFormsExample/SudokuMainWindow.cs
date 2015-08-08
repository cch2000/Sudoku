using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsExample
{
    public partial class SudokuMainWindow : Form
    {
        public SudokuMainWindow()
        {
            InitializeComponent();
            Text = "Sudoku";
            BackColor = Color.Beige;
            Size = new Size(600, 500);
        }

        protected override void OnClick(EventArgs e)
        {
            base.OnClick(e);
        }
    }
}

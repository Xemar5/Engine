using Hardy_Part___Map_Editor.Tileset_Palette;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Hardy_Part___Map_Editor
{
    public partial class FormNewMap : Form
    {

        public FormNewMap()
        {
            InitializeComponent();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(textBoxName.Text))
            {
                Map.CurrentMap = new Map(textBoxName.Text, (int)numericUpDownMapWidth.Value * (int)numericUpDownFrameWidth.Value, (int)numericUpDownMapHeight.Value * (int)numericUpDownFrameHeight.Value, (Double)numericUpDownMapScale.Value);
                this.Close();
            }
        }

        private void textBoxName_TextChanged(object sender, EventArgs e)
        {
            if (String.IsNullOrWhiteSpace(textBoxName.Text) || !Char.IsLetter(textBoxName.Text[0]))
                buttonMapCreate.Enabled = false;
            else buttonMapCreate.Enabled = true;
        }

        private void numericUpDownMapWidth_Enter(object sender, EventArgs e)
        {
            numericUpDownMapWidth.Select(0, numericUpDownMapWidth.Text.Length);
        }

        private void numericUpDownMapHeight_Enter(object sender, EventArgs e)
        {
            numericUpDownMapHeight.Select(0, numericUpDownMapHeight.Text.Length);
        }

        private void checkBoxFrameSizeFixed_CheckedChanged(object sender, EventArgs e)
        {
            labelFramwHeight.Enabled = !labelFramwHeight.Enabled;
            numericUpDownFrameHeight.Value = numericUpDownFrameWidth.Value;
            numericUpDownFrameHeight.Enabled = !numericUpDownFrameHeight.Enabled;
        }

        private void numericUpDownFrameWidth_ValueChanged(object sender, EventArgs e)
        {
            if (numericUpDownFrameHeight.Enabled == false)
                numericUpDownFrameHeight.Value = numericUpDownFrameWidth.Value;
        }
    }
}

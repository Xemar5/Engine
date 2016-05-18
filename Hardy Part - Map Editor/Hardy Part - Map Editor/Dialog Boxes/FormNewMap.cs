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
        private FormMainScreen _Parent;

        public FormNewMap(FormMainScreen parent)
        {
            InitializeComponent();
            _Parent = parent;
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(textBoxName.Text))
            {
                _Parent.CurrentMap = new Map(textBoxName.Text);
                this.Close();
            }
        }
    }
}

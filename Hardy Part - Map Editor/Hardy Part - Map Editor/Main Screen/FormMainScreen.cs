using Hardy_Part___Map_Editor.Dialog_Boxes;
using Hardy_Part___Map_Editor.Tileset_Palette;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Hardy_Part___Map_Editor
{
    public partial class FormMainScreen : Form
    {
        public FormMainScreen()
        {
            InitializeComponent();
            tabControlPanels.TabPages[1].Controls.Add(new Palette());
            Palette.CurrentPalette = (Palette)tabControlPanels.TabPages[1].Controls[0];
        }

        private void buttonNewMap_Click(object sender, EventArgs e)
        {
            Form newMap = new FormNewMap();
            newMap.ShowDialog();
            panelMap.Controls.Clear();
            if (Map.CurrentMap != null) panelMap.Controls.Add(Map.CurrentMap);
        }
    }
}

using Hardy_Part___Map_Editor.Dialog_Boxes;
using Hardy_Part___Map_Editor.Entity_Palette;
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
        public static FormMainScreen ThisForm = null;
        public static Control CurrentTab = null;

        public FormMainScreen()
        {
            InitializeComponent();
            ThisForm = this;
            TilesetWindow.CurrentTilesetWindow = tilesetWindow;
        }

        private void buttonNewMap_Click(object sender, EventArgs e)
        {
            var lastMap = Map.CurrentMap;
            Form newMap = new FormNewMap();
            newMap.ShowDialog();
            if (Map.CurrentMap != lastMap && Map.CurrentMap != null)
            {
                if (lastMap != null)
                    lastMap.Dispose();
                panelMap.Controls.Clear();
                panelMap.Controls.Add(Map.CurrentMap);
                EntityWindow.CurrentEntityWindow.buttonAddEntity.Enabled = true;
                EntityWindow.CurrentEntityWindow.existingEntityList.Enabled = true;

                TilesetWindow.CurrentTilesetWindow.TilesetWindowReset();
                TilesetWindow.CurrentTilesetWindow.buttonAddTileset.Enabled = true;
                TilesetWindow.CurrentTilesetWindow.existingTilesetList.Enabled = true;
            }
            else Map.CurrentMap = lastMap;
        }

        private void tabControlPanels_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (Map.CurrentMap == null) return;
            Map.CurrentMap.Draw();
        }

    }
}

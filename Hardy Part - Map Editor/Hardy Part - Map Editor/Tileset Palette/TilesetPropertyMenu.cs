using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Hardy_Part___Map_Editor.Tileset_Palette
{
    public partial class TilesetPropertyMenu : UserControl
    {
        private TilesetPreset _Parent = null;
        public TilesetPropertyMenu(TilesetPreset parent)
        {
            InitializeComponent();
            _Parent = parent;
        }


        private void TilesetPropertyMenu_Leave(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private void TilesetPropertyMenu_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape) this.Dispose();
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            this.Dispose();
        }

        private void buttonTilesetRemove_Click(object sender, EventArgs e)
        {
            if (Map.CurrentMap != null)
            {
                foreach (Tileset t in Map.CurrentMap.Entities)
                {
                    if (t == null) continue;
                    if (t.Preset == _Parent) t.Preset = null;
                }
            }

            TilesetWindow.CurrentTilesetWindow.TilesetPresets.Remove(_Parent);

            TilesetWindow.CurrentTilesetWindow.comboBoxSelectedPreset.SelectedIndex = 0;
            TilesetWindow.CurrentTilesetWindow.comboBoxSelectedPreset.DataSource = null;
            TilesetWindow.CurrentTilesetWindow.comboBoxSelectedPreset.DataSource = TilesetWindow.CurrentTilesetWindow.TilesetPresets;
            TilesetWindow.CurrentTilesetWindow.comboBoxSelectedPreset.DisplayMember = "GetName";

            _Parent.Delete();
            _Parent.Dispose();
            this.Dispose();
        }
    }
}

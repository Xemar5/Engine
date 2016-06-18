using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Hardy_Part___Map_Editor.Dialog_Boxes;
using System.IO;

namespace Hardy_Part___Map_Editor.Tileset_Palette
{
    public partial class Palette : UserControl
    {
        public static Palette CurrentPalette = null;
        public PictureBox CurrentTile = null;
        public Tileset CurrentTileset = null;

        public Palette()
        {
            InitializeComponent();
            flowLayoutPanelTilesetsPresets.Controls.Add(new TilesetPalette("NONE", 0, 0));
            flowLayoutPanelTilesetsPresets.Controls[0].Hide();
            comboBoxSelectedPreset.DataSource = flowLayoutPanelTilesetsPresets.Controls.Cast<TilesetPalette>().ToList();
            comboBoxSelectedPreset.DisplayMember = "GetName";
        }


        public void AddTilesetPalette(string path, int frameWidth, int frameHeight)
        {
            var tp = new TilesetPalette(path, frameWidth, frameHeight);
            flowLayoutPanelTilesetsPresets.Controls.Add(tp);
            comboBoxSelectedPreset.DataSource = flowLayoutPanelTilesetsPresets.Controls.Cast<TilesetPalette>().ToList();
            comboBoxSelectedPreset.DisplayMember = "GetName";
        }


        private void buttonImportTileset_Click(object sender, EventArgs e)
        {
            Form loadTileset = new FormLoadTileset();
            loadTileset.ShowDialog();
        }

        public void SelectTile(PictureBox tile)
        {
            if(CurrentTile != null)
                CurrentTile.BackColor = Control.DefaultBackColor;
            CurrentTile = tile;
            CurrentTile.BackColor = Color.Green;
            CurrentTile.Focus();
        }

        private void textBoxScale_KeyPress(object sender, KeyPressEventArgs e)
        {
            String listOfChars = "0123456789,\b\r\u001b";
            if (e.KeyChar == '\r' || e.KeyChar == '\u001b')
                textBoxScale_Leave(sender, e);
            if (listOfChars.IndexOf(e.KeyChar) == -1)
                e.Handled = true;
            else if (e.KeyChar == ',' && textBoxScale.Text.IndexOf(',') != -1)
                e.Handled = true;
        }

        private void buttonAddTileset_Click(object sender, EventArgs e)
        {
            if (Map.CurrentMap == null) return;
            Map.CurrentMap.Controls.Add(new Tileset());
            listBoxExistingTilesets.DataSource = Map.CurrentMap.Controls.Cast<Tileset>().ToList();
            listBoxExistingTilesets.DisplayMember = "tName";
            numericUpDownTilesetX.Maximum = Map.CurrentMap.Width - 6;
            numericUpDownTilesetY.Maximum = Map.CurrentMap.Height - 6;
        }

        private void listBoxExistingTilesets_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (groupBoxTilesetObject.Enabled == false) groupBoxTilesetObject.Enabled = true;
            CurrentTileset = (Tileset)listBoxExistingTilesets.SelectedItem;
            textBoxTilesetName.Text = CurrentTileset.tName;
            if (CurrentTileset.tPreset == null) comboBoxSelectedPreset.SelectedIndex = 0;
            else comboBoxSelectedPreset.SelectedItem = CurrentTileset.tPreset;
            textBoxScale.Text = CurrentTileset.tScale.ToString();
            textBoxScale_Leave(sender, e);
        }






        private void textBoxScale_Leave(object sender, EventArgs e)
        {
            if (textBoxScale.Text.Length == 0) textBoxScale.Text = "1,0";
            if (textBoxScale.Text.IndexOf(',') == -1) textBoxScale.Text += ',';
            if (textBoxScale.Text.Last() == ',') textBoxScale.Text += '0';
            if (textBoxScale.Text.First() == ',') textBoxScale.Text.Insert(0, "0");
            if (Convert.ToDouble(textBoxScale.Text) == 0) textBoxScale.Text = "1,0";
            if (Convert.ToDouble(textBoxScale.Text) > 10) textBoxScale.Text = "10,0";
            if (Convert.ToDouble(textBoxScale.Text) < 0.1) textBoxScale.Text = "0,1";
        }

        private void textBoxTilesetName_KeyPress(object sender, KeyPressEventArgs e)
        {
            String listOfChars = "QWERTYUIOPASDFGHJKLZXCVBNM_qwertyuiopasdfghjklzxcvbnm1234567890\b\r\u001b";
            if (e.KeyChar == '\r' || e.KeyChar == '\u001b')
                textBoxTilesetName_Leave(sender, e);
            if (listOfChars.IndexOf(e.KeyChar) == -1)
                e.Handled = true;
        }

        private void textBoxTilesetName_Leave(object sender, EventArgs e)
        {
            if (CurrentTileset == null) return;

            while (!String.IsNullOrEmpty(textBoxTilesetName.Text) && Char.IsNumber(textBoxTilesetName.Text.First()))
                textBoxTilesetName.Text = textBoxTilesetName.Text.Remove(0, 1);
            if (String.IsNullOrEmpty(textBoxTilesetName.Text))
                textBoxTilesetName.Text = CurrentTileset.tName;

            CurrentTileset.tName = textBoxTilesetName.Text;
            listBoxExistingTilesets.DataSource = Map.CurrentMap.Controls.Cast<Tileset>().ToList();
            listBoxExistingTilesets.DisplayMember = "tName";
        }

        private void comboBoxSelectedPreset_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxSelectedPreset.SelectedIndex == 0)
                CurrentTileset.tPreset = null;
            else
            {
                CurrentTileset.tPreset = (TilesetPalette)comboBoxSelectedPreset.SelectedItem;
                CurrentTileset.SetGrid();
            }
        }
    }
}

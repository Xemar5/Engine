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
using System.Globalization;

namespace Hardy_Part___Map_Editor.Tileset_Palette
{
    public partial class TilesetWindow : UserControl
    {
        public static TilesetWindow CurrentTilesetWindow = null;
        public PictureBox CurrentTile = null;
        public Tileset CurrentTileset = null;
        public List<TilesetPreset> TilesetPresets = null;
        private TilesetPreset higlitedTilesetPreset = null;


        public TilesetWindow()
        {
            InitializeComponent();
            //pictureBoxDelete_Paint();
            TilesetPresets = new List<TilesetPreset>();
            existingTilesetList.dataGridViewExistingTilesets.SelectionChanged += dataGridViewExistingTilesets_SelectionChanged;
            //listBoxExistingTilesets.DataSource = null;
            AddTilesetPreset("NONE", 0, 0);
            flowLayoutPanelTilesetsPresets.Controls[0].Hide();
        }

        public void TilesetWindowReset()
        {
            ChangeCurrentTileset();
            groupBoxTilesetObject.Enabled = false;
            comboBoxSelectedPreset.SelectedIndex = 0;
            existingTilesetList.UpdateList();
            //UpdateExistingTilesets();
            buttonAddTileset.Enabled = false;
            Tileset.IdCount = 0;
            if (higlitedTilesetPreset != null)
                higlitedTilesetPreset.BackColor = SystemColors.ControlDark;
            higlitedTilesetPreset = null;
            SelectTile(null);
        }

        public void AddTilesetPreset(string path, int frameWidth, int frameHeight)
        {
            if (!String.IsNullOrWhiteSpace(path))
            {
                var tp = new TilesetPreset(path, frameWidth, frameHeight);
                TilesetPresets.Add(tp);
                flowLayoutPanelTilesetsPresets.Controls.Add(tp);
            }
            comboBoxSelectedPreset.DataSource = null;
            comboBoxSelectedPreset.DataSource = TilesetPresets;
            comboBoxSelectedPreset.DisplayMember = "GetName";
        }


        private void buttonImportTileset_Click(object sender, EventArgs e)
        {
            Form loadTileset = new FormLoadTileset();
            loadTileset.ShowDialog();
        }

        public void SelectTile(PictureBox tile)
        {
            if (CurrentTile != null)
                CurrentTile.BackColor = Control.DefaultBackColor;

            if (higlitedTilesetPreset == null)
                CurrentTile = null;
            else if (higlitedTilesetPreset.flowLayoutPanelTiles.Controls.Contains(tile))
                CurrentTile = tile;

            if (CurrentTile != null)
            {
                CurrentTile.BackColor = Color.Green;
                CurrentTile.Focus();
            }
        }


        private void buttonAddTileset_Click(object sender, EventArgs e)
        {
            if (Map.CurrentMap == null) return;
            var t = new Tileset();
            Map.CurrentMap.Entities.Add(t);
            existingTilesetList.UpdateList();
            existingTilesetList.SelectedTileset = t;
            buttonRemoveTileset.Enabled = true;
            //UpdateExistingTilesets();
            //listBoxExistingTilesets.SelectedIndex = listBoxExistingTilesets.Items.Count - 1;
            numericUpDownTilesetX.Maximum = Map.CurrentMap.Width - 6;
            numericUpDownTilesetY.Maximum = Map.CurrentMap.Height - 6;
        }

        private void dataGridViewExistingTilesets_SelectionChanged(object sender, EventArgs e)
        {
            ChangeCurrentTileset();
        }


        private void ChangeCurrentTileset()
        {
            //if (existingTilesetList1.SelectedTileset == null)
            //{
            //    CurrentTileset = null;
            //    CurrentTile = null;
            //    return;
            //}
            if (groupBoxTilesetObject.Enabled == false) groupBoxTilesetObject.Enabled = true;
            CurrentTileset = existingTilesetList.SelectedTileset;
            if (CurrentTileset == null) return;
            textBoxTilesetName.Text = CurrentTileset.Name;
            numericUpDownTilesetX.Value = CurrentTileset.X;
            numericUpDownTilesetY.Value = CurrentTileset.Y;
            checkBoxTilesetVisible.Checked = CurrentTileset.Visible;

            numericUpDownTilesetLayer.ValueChanged -= numericUpDownTilesetLayer_ValueChanged;
            numericUpDownTilesetLayer.Value = (Decimal)CurrentTileset.Layer;
            numericUpDownTilesetLayer.ValueChanged += numericUpDownTilesetLayer_ValueChanged;

            if (CurrentTileset.Preset == null) comboBoxSelectedPreset.SelectedIndex = 0;
            else comboBoxSelectedPreset.SelectedItem = CurrentTileset.Preset;
            numericUpDownTilesetScale.Value = (Decimal)CurrentTileset.Scale;
        }







        private void textBoxTilesetName_KeyPress(object sender, KeyPressEventArgs e)
        {
            String listOfChars = "QWERTYUIOPASDFGHJKLZXCVBNM_qwertyuiopasdfghjklzxcvbnm1234567890\b\r\u001b";
            if (e.KeyChar == '\r' || e.KeyChar == '\u001b')
                textBoxTilesetName_Leave(sender, e);
            if (listOfChars.IndexOf(e.KeyChar) == -1)
                e.Handled = true;
        }


        private void comboBoxSelectedPreset_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (CurrentTileset == null) return;
            if (comboBoxSelectedPreset.SelectedIndex == -1) return;
            if (comboBoxSelectedPreset.SelectedIndex == 0)
            {
                CurrentTileset.Preset = null;
                if(higlitedTilesetPreset != null)
                    higlitedTilesetPreset.BackColor = SystemColors.ControlDark;
                higlitedTilesetPreset = null;
                SelectTile(null);
            }
            else
            {
                var lastHighlight = higlitedTilesetPreset;
                CurrentTileset.Preset = (TilesetPreset)comboBoxSelectedPreset.SelectedItem;
                if (higlitedTilesetPreset != null)
                    higlitedTilesetPreset.BackColor = SystemColors.ControlDark;
                higlitedTilesetPreset = (TilesetPreset)comboBoxSelectedPreset.SelectedItem;
                higlitedTilesetPreset.BackColor = Color.Green;
                if (lastHighlight != higlitedTilesetPreset && higlitedTilesetPreset.flowLayoutPanelTiles.Controls.Count >= 0)
                    SelectTile(higlitedTilesetPreset.flowLayoutPanelTiles.Controls[0] as PictureBox);
            }
            Map.CurrentMap.Draw();
            //CurrentTileset.Drawraw();
        }

        private void numericUpDownTilesetX_ValueChanged(object sender, EventArgs e)
        {
            if (CurrentTileset != null)
                CurrentTileset.X = (int)numericUpDownTilesetX.Value;
            Map.CurrentMap.Draw();
        }

        private void numericUpDownTilesetY_ValueChanged(object sender, EventArgs e)
        {
            if (CurrentTileset != null)
                CurrentTileset.Y = (int)numericUpDownTilesetY.Value;
            Map.CurrentMap.Draw();
        }

        //private void pictureBoxDelete_Click(object sender, EventArgs e)
        //{
        //    SelectTile(pictureBoxDelete);
        //}

        //private void pictureBoxDelete_Paint()
        //{
        //    pictureBoxDelete.Image = new Bitmap(48, 48);
        //    using (Graphics g = Graphics.FromImage(pictureBoxDelete.Image))
        //    {
        //        g.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.Half;
        //        Pen p = new Pen(Color.Maroon, 5);
        //        g.DrawLine(p, new Point(10, 10), new Point(38, 38));
        //        g.DrawLine(p, new Point(38, 10), new Point(10, 38));
        //        p.Dispose();
        //    }
        //}

        private void numericUpDownTilesetScale_ValueChanged(object sender, EventArgs e)
        {
            CurrentTileset.Scale = (Double)numericUpDownTilesetScale.Value;
            Map.CurrentMap.Draw();
            //CurrentTileset.Drawraw();
        }


        private void textBoxTilesetName_Leave(object sender, EventArgs e)
        {
            if (CurrentTileset == null) return;

            while (!String.IsNullOrEmpty(textBoxTilesetName.Text) && Char.IsNumber(textBoxTilesetName.Text.First()))
                textBoxTilesetName.Text = textBoxTilesetName.Text.Remove(0, 1);
            if (String.IsNullOrEmpty(textBoxTilesetName.Text))
                textBoxTilesetName.Text = CurrentTileset.Name;

            CurrentTileset.Name = textBoxTilesetName.Text;
            existingTilesetList.UpdateList();
        }

        private void numericUpDownTilesetLayer_ValueChanged(object sender, EventArgs e)
        {
            CurrentTileset.Layer = (int)numericUpDownTilesetLayer.Value;
            existingTilesetList.UpdateList();
            Map.CurrentMap.Draw();
            //UpdateExistingTilesets();

        }

        private void checkBoxShowGrid_CheckedChanged(object sender, EventArgs e)
        {
            if(Map.CurrentMap != null && CurrentTileset != null)
                Map.CurrentMap.Draw();
            //CurrentTileset.Drawraw();
        }

        private void checkBoxTilesetVisible_CheckedChanged(object sender, EventArgs e)
        {
            CurrentTileset.Visible = checkBoxTilesetVisible.Checked;
            //CurrentTileset.Drawraw();
            existingTilesetList.UpdateList();
        }

        private void buttonRemoveTileset_Click(object sender, EventArgs e)
        {
            Map.CurrentMap.Entities.Remove(CurrentTileset);
            existingTilesetList.UpdateList();
            if (higlitedTilesetPreset != null)
                higlitedTilesetPreset.BackColor = SystemColors.ControlDark;
            higlitedTilesetPreset = null;
            SelectTile(null);
            if(Map.CurrentMap.Entities.Where(s => (s as Tileset) != null).ToList().Count == 0)
            {
                //listBoxExistingTilesets.DataSource = null;
                groupBoxTilesetObject.Enabled = false;
                existingTilesetList.Enabled = false;
                Tileset.IdCount = 0;
                buttonRemoveTileset.Enabled = false;
                return;
            }
            ChangeCurrentTileset();
            Map.CurrentMap.Draw();

            //UpdateExistingTilesets();
        }
    }
}

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
        private Tileset _CurrentTileset = null;
        public Tileset CurrentTileset
        {
            get { return _CurrentTileset; }
            set
            {
                if (value == null)
                {
                    _CurrentTileset = null;
                    existingEntityList.dataGridViewExistingEntity.SelectionChanged -= dataGridViewExistingTilesets_SelectionChanged;
                    existingEntityList.SelectedEntity = null;
                    existingEntityList.dataGridViewExistingEntity.SelectionChanged += dataGridViewExistingTilesets_SelectionChanged;
                    groupBoxTilesetObject.Enabled = false;
                    textBoxTilesetName.Text = "";
                    numericUpDownTilesetX.Value = 0;
                    numericUpDownTilesetY.Value = 0;
                    checkBoxTilesetVisible.Checked = true;
                    numericUpDownTilesetLayer.ValueChanged -= numericUpDownTilesetLayer_ValueChanged;
                    numericUpDownTilesetLayer.Value = 0;
                    numericUpDownTilesetLayer.ValueChanged += numericUpDownTilesetLayer_ValueChanged;
                    numericUpDownTilesetScale.Value = 1;
                    numericUpDownRotation.Value = 0;
                    numericUpDownCenterX.Value = 0;
                    numericUpDownCenterY.Value = 0;
                    comboBoxSelectedPreset.SelectedIndex = 0;
                    SelectTile(null);
                }
                else if (_CurrentTileset != value)
                {
                    _CurrentTileset = value;
                    existingEntityList.dataGridViewExistingEntity.SelectionChanged -= dataGridViewExistingTilesets_SelectionChanged;
                    existingEntityList.SelectedEntity = _CurrentTileset;
                    existingEntityList.dataGridViewExistingEntity.SelectionChanged += dataGridViewExistingTilesets_SelectionChanged;
                    groupBoxTilesetObject.Enabled = true;
                    textBoxTilesetName.Text = _CurrentTileset.Name;
                    numericUpDownTilesetX.Value = _CurrentTileset.X;
                    numericUpDownTilesetY.Value = _CurrentTileset.Y;
                    checkBoxTilesetVisible.Checked = _CurrentTileset.Visible;
                    numericUpDownTilesetLayer.ValueChanged -= numericUpDownTilesetLayer_ValueChanged;
                    numericUpDownTilesetLayer.Value = _CurrentTileset.Layer;
                    numericUpDownTilesetLayer.ValueChanged += numericUpDownTilesetLayer_ValueChanged;
                    numericUpDownTilesetScale.Value = (decimal)_CurrentTileset.Scale;
                    numericUpDownRotation.Value = (decimal)_CurrentTileset.Angle;
                    numericUpDownCenterX.Value = (decimal)_CurrentTileset._CenterX;
                    numericUpDownCenterY.Value = (decimal)_CurrentTileset._CenterY;
                    buttonRemoveTileset.Enabled = true;
                    if (CurrentTileset.Preset == null)
                    {
                        comboBoxSelectedPreset.SelectedIndex = 0;
                    }
                    else comboBoxSelectedPreset.SelectedItem = CurrentTileset.Preset;
                }
            }
        }
        public List<TilesetPreset> TilesetPresets = null;
        private TilesetPreset higlitedTilesetPreset = null;


        public TilesetWindow()
        {
            InitializeComponent();
            //pictureBoxDelete_Paint();
            TilesetPresets = new List<TilesetPreset>();
            existingEntityList.Condition = s => (s as Tileset) != null;
            existingEntityList.dataGridViewExistingEntity.SelectionChanged += dataGridViewExistingTilesets_SelectionChanged;
            //listBoxExistingTilesets.DataSource = null;
            AddTilesetPreset("NONE", 0, 0);
            flowLayoutPanelTilesetsPresets.Controls[0].Hide();
        }

        //public void TilesetWindowReset()
        //{
        //    CurrentTileset = null;
        //    groupBoxTilesetObject.Enabled = false;
        //    comboBoxSelectedPreset.SelectedIndex = 0;
        //    existingEntityList.UpdateList();
        //    //UpdateExistingTilesets();
        //    buttonAddTileset.Enabled = false;
        //    Tileset.IdCount = 0;
        //    if (higlitedTilesetPreset != null)
        //        higlitedTilesetPreset.BackColor = SystemColors.ControlDark;
        //    higlitedTilesetPreset = null;
        //    SelectTile(null);
        //}

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
            FormLoadTexture loadTileset = new FormLoadTexture("recent_textures", "Tileset Texture");
            loadTileset.ShowDialog();
            if(loadTileset.TexturePath.Length > 0 && loadTileset.FrameWidth > 0 && loadTileset.FrameHeight > 0)
                AddTilesetPreset(loadTileset.TexturePath, loadTileset.FrameWidth, loadTileset.FrameHeight);
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
            existingEntityList.dataGridViewExistingEntity.SelectionChanged -= dataGridViewExistingTilesets_SelectionChanged;
            existingEntityList.UpdateList();
            CurrentTileset = t;
            existingEntityList.dataGridViewExistingEntity.SelectionChanged += dataGridViewExistingTilesets_SelectionChanged;
            //existingEntityList.SelectedEntity = t;
            buttonRemoveTileset.Enabled = true;
            //UpdateExistingTilesets();
            //listBoxExistingTilesets.SelectedIndex = listBoxExistingTilesets.Items.Count - 1;
            numericUpDownTilesetX.Maximum = Map.CurrentMap.Width - 6;
            numericUpDownTilesetY.Maximum = Map.CurrentMap.Height - 6;
        }

        private void dataGridViewExistingTilesets_SelectionChanged(object sender, EventArgs e)
        {
            CurrentTileset = existingEntityList.SelectedEntity as Tileset;
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
            existingEntityList.UpdateList();
        }

        private void numericUpDownTilesetLayer_ValueChanged(object sender, EventArgs e)
        {
            CurrentTileset.Layer = (int)numericUpDownTilesetLayer.Value;
            existingEntityList.UpdateList();
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
            existingEntityList.UpdateList();
        }

        private void buttonRemoveTileset_Click(object sender, EventArgs e)
        {
            Map.CurrentMap.Entities.Remove(CurrentTileset);
            existingEntityList.UpdateList();
            if (higlitedTilesetPreset != null)
                higlitedTilesetPreset.BackColor = SystemColors.ControlDark;
            higlitedTilesetPreset = null;
            SelectTile(null);
            if(Map.CurrentMap.Entities.Where(s => (s as Tileset) != null).ToList().Count == 0)
            {
                //listBoxExistingTilesets.DataSource = null;
                groupBoxTilesetObject.Enabled = false;
                existingEntityList.Enabled = false;
                Tileset.IdCount = 0;
                buttonRemoveTileset.Enabled = false;
            }
            //else
            //    ChangeCurrentTileset();
            Map.CurrentMap.Draw();

            //UpdateExistingTilesets();
        }
    }
}

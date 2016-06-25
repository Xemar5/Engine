using Hardy_Part___Map_Editor.Tileset_Palette;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Hardy_Part___Map_Editor.Dialog_Boxes
{
    public partial class FormLoadTileset : Form
    {
        private List<RecentTileset> _RecentTilesets = new List<RecentTileset>();

        public FormLoadTileset()
        {
            InitializeComponent();
            var recentTilesets = new List<String>();
            if (File.Exists("recent_tilesets"))
                recentTilesets = File.ReadLines("recent_tilesets").ToList();
            foreach (var t in recentTilesets)
            {
                var nt = new RecentTileset(t);
                if (nt.hPath.Length == 0 || nt.FrameWidth == 0 || nt.FrameHeight == 0)
                    continue;
                _RecentTilesets.Add(nt);
            }
            listBoxTilesetPresetsRecent.DataSource = _RecentTilesets;
            listBoxTilesetPresetsRecent.DisplayMember = "hPath";
        }
        private void buttonImagePath_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialogImage = new OpenFileDialog();

            ImageCodecInfo[] codecs = ImageCodecInfo.GetImageEncoders();
            string sep = string.Empty;
            foreach (var c in codecs)
            {
                string codecName = c.CodecName.Substring(8).Replace("Codec", "Files").Trim();
                openFileDialogImage.Filter = String.Format("{0}{1}{2} ({3})|{3}", openFileDialogImage.Filter, sep, codecName, c.FilenameExtension);
                sep = "|";
            }

            listBoxTilesetPresetsRecent.SelectedIndex = -1;
            openFileDialogImage.FilterIndex = 5;
            openFileDialogImage.ShowDialog();
            if(!String.IsNullOrWhiteSpace(openFileDialogImage.FileName))
                loadImagePreview(openFileDialogImage.FileName);
        }



        private void loadImagePreview(string path)
        {
            loadImagePreview(path, -1, -1);
        }


        private void loadImagePreview(string path, int width, int height)
        {
            if (String.IsNullOrWhiteSpace(path))
            {
                Exception();
                return;
            }
            try
            {
                Path.GetFullPath(path);
            }
            catch
            {
                Exception();
                return;
            }
            textBoxImagePath.Text = path;
            Bitmap bitmap = new Bitmap(path);
            pictureBoxImagrPreview.Image = bitmap;


            if (width == -1)
                numericUpDownFrameWidth.Value = bitmap.Width;
            else
                numericUpDownFrameWidth.Value = width;

            if (width == -1)
                numericUpDownFrameHeight.Value = bitmap.Height;
            else
                numericUpDownFrameHeight.Value = height;


            labelImageError.Text = "";
            buttonLoad.Enabled = true;
        }

        private void Exception()
        {
            pictureBoxImagrPreview.Image = null;
            labelImageError.Text = "Can't load the image";
            buttonLoad.Enabled = false;
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void buttonLoad_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(textBoxImagePath.Text))
            {
                TilesetWindow.CurrentTilesetWindow.AddTilesetPreset(textBoxImagePath.Text, (int)numericUpDownFrameWidth.Value, (int)numericUpDownFrameHeight.Value);
                var t = new RecentTileset(textBoxImagePath.Text + " " + numericUpDownFrameWidth.Value.ToString() + " " + numericUpDownFrameHeight.Value.ToString());

                _RecentTilesets.Insert(0, t);

                List<String> toSave = new List<string>();
                for(int i = 0; i < _RecentTilesets.Count; ++i)
                {
                    for(int j = i + 1; j < _RecentTilesets.Count; ++j)
                        if(_RecentTilesets[i].hPath == _RecentTilesets[j].hPath)
                        {
                            _RecentTilesets.RemoveAt(j);
                            --j;
                        }
                    toSave.Add(_RecentTilesets[i].Convert());
                }
                File.WriteAllLines("recent_tilesets", toSave);
                this.Close();
            }
        }

        private void listBoxTilesetPresetsRecent_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(listBoxTilesetPresetsRecent.SelectedIndex != -1)
                loadImagePreview(
                ((RecentTileset)listBoxTilesetPresetsRecent.SelectedItem).hPath,
                ((RecentTileset)listBoxTilesetPresetsRecent.SelectedItem).FrameWidth,
                ((RecentTileset)listBoxTilesetPresetsRecent.SelectedItem).FrameHeight);
        }
    }
}

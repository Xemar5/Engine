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

namespace Hardy_Part___Map_Editor.Dialog_Boxes
{
    public partial class FormLoadTileset : Form
    {
        private bool _Error = false;

        public FormLoadTileset()
        {
            InitializeComponent();
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

            openFileDialogImage.FilterIndex = 5;
            openFileDialogImage.ShowDialog();
            textBoxImagePath.Text = openFileDialogImage.FileName;
            loadImagePreview(openFileDialogImage.FileName);
        }





        private void loadImagePreview(string path)
        {
            try
            {
                Bitmap bitmap = new Bitmap(path);
                pictureBoxImagrPreview.Image = bitmap;
                numericUpDownFrameWidth.Value = bitmap.Width;
                numericUpDownFrameHeight.Value = bitmap.Height;
                labelImageError.Text = "";
                buttonLoad.Enabled = true;
                _Error = false;
            }
            catch (Exception)
            {
                pictureBoxImagrPreview.Image = null;
                labelImageError.Text = "Can't load the image";
                buttonLoad.Enabled = false;
                _Error = true;
            }
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void buttonLoad_Click(object sender, EventArgs e)
        {
            if (_Error == false && !string.IsNullOrWhiteSpace(textBoxImagePath.Text))
            {
                TilesetWindow.CurrentTilesetWindow.AddTilesetPreset(textBoxImagePath.Text, (int)numericUpDownFrameWidth.Value, (int)numericUpDownFrameHeight.Value);
                this.Close();
            }
        }
    }
}

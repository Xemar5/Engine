using Hardy_Part___Map_Editor.Dialog_Boxes;
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
        public Map CurrentMap = null;
        public Tileset CurrentTileset = null;
        public Palette CurrentPalette = null;
        public PictureBox CurrentTile = null;
        private int factor = 2;
        public FormMainScreen()
        {
            InitializeComponent();
        }

        private void buttonNewMap_Click(object sender, EventArgs e)
        {
            Form newMap = new FormNewMap(this);
            newMap.ShowDialog();
            if (CurrentMap == null) return;

        }

        public void buttonLoadTileset_Click(object sender, EventArgs e)
        {
            Form loadTileset = new FormLoadTileset(this);
            loadTileset.ShowDialog();
            fillTilePalette();
            //if (CurrentTileset == null) return;
            //Form editTileset = new FormEditTileset(this, CurrentTileset);
            //editTileset.ShowDialog();
            //if(CurrentPalette == null && CurrentTileset != null)
            //    buttonLoadTileset_Click(sender, e);
        }

        public void fillTilePalette()
        {
            if (CurrentTileset == null) return;
            panelTiles.Controls.Clear();
            Bitmap source = new Bitmap(CurrentTileset.Path);
            for(int i = 0; i < CurrentTileset.MaxFrames(); i++)
            {
                PictureBox pb = new PictureBox();
                pb.Name = "tile" + i.ToString();
                pb.Size = new Size(CurrentTileset.FrameWidth * factor + 6, CurrentTileset.FrameHeight * factor + 6);
                pb.Image = new Bitmap(CurrentTileset.FrameWidth * factor, CurrentTileset.FrameHeight * factor);
                pb.SizeMode = PictureBoxSizeMode.CenterImage;
                int x = (i % CurrentTileset.MaxFramesWidth()) * CurrentTileset.FrameWidth;
                int y = (i / CurrentTileset.MaxFramesWidth()) * CurrentTileset.FrameHeight;
                Rectangle rsrc = new Rectangle(x, y, CurrentTileset.FrameWidth, CurrentTileset.FrameHeight);
                Rectangle rdst = new Rectangle(0, 0, CurrentTileset.FrameWidth * factor, CurrentTileset.FrameHeight * factor);

                using (Graphics g = Graphics.FromImage(pb.Image))
                {
                    g.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.Half;
                    g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
                    g.DrawImage(source, rdst, rsrc, GraphicsUnit.Pixel);
                }

                int gbw = panelTiles.Width / (pb.Width);
                if (gbw == 0) gbw = 1;

                pb.Click += new EventHandler(pictureBoxTile_Click);
                pb.Location = new Point(
                    (i % gbw) * (pb.Width + 1),
                    (i / gbw) * (pb.Height + 1)
                    );

                panelTiles.Controls.Add(pb);
                panelTiles.Update();
            }
            //foreach (var ctrl in groupBoxTiles.Controls)
            //    MessageBox.Show(((PictureBox)ctrl).Location.ToString());
            source.Dispose();
        }

        private void pictureBoxTile_Click(object sender, EventArgs e)
        {

            if (CurrentTile != null) CurrentTile.BackColor = this.BackColor;
            CurrentTile = (PictureBox)sender;
            CurrentTile.BackColor = Color.SeaGreen;
        }
    }
}

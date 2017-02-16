using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Hardy_Part___Map_Editor.Tileset_Palette
{
    public partial class TilesetPreset : UserControl
    {
        readonly public int FrameWidth;
        readonly public int FrameHeight;
        private Bitmap _Image;
        public string tpName { get; set; }
        public string GetName
        {
            get
            {
                return Path.GetFileNameWithoutExtension(tpName);
            }
        }

        public TilesetPreset(string path, int frameWidth, int frameHeight)
        {
            InitializeComponent();
            tpName = path;
            FrameWidth = frameWidth;
            FrameHeight = frameHeight;
            labelTilesetName.Text = Path.GetFileNameWithoutExtension(tpName);
            labelTileSize.Text = FrameWidth.ToString() + " ˣ " + FrameHeight.ToString();
            if (tpName != "NONE")
            {
                _Image = new Bitmap(tpName);
                for (int i = 0; i < MaxTiles(); ++i)
                    _FillTile(i);
            }
        }

        public int MaxTiles()
        {
            if (tpName == "NONE") return 0;
            return _Image.Width / FrameWidth * _Image.Height / FrameHeight;
        }
        public Point FramePos(int frame)
        {
            if (tpName == "NONE") return new Point(0,0);
            Point p = new Point();
            p.X = (frame % (_Image.Width / FrameWidth)) * FrameWidth;
            p.Y = (frame / (_Image.Width / FrameWidth)) * FrameHeight;
            return p;
        }

        private void _FillTile(int imageFrame)
        {
            if (tpName == "NONE") return;
            double scale = Math.Min(48 / (double)FrameWidth, 48 / (double)FrameHeight);
            PictureBox pb = new PictureBox();
            pb.Name = "tile" + imageFrame.ToString();
            pb.Size = new Size((int)(FrameWidth * scale + 6), (int)(FrameHeight * scale + 6));
            pb.Image = new Bitmap((int)(FrameWidth * scale), (int)(FrameHeight * scale));
            pb.SizeMode = PictureBoxSizeMode.CenterImage;
            Rectangle rsrc = new Rectangle(FramePos(imageFrame).X, FramePos(imageFrame).Y, FrameWidth, FrameHeight);
            Rectangle rdst = new Rectangle(0, 0, (int)(FrameWidth * scale), (int)(FrameHeight * scale));

            using (Graphics g = Graphics.FromImage(pb.Image))
            {
                g.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.Half;
                g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
                g.DrawImage(_Image, rdst, rsrc, GraphicsUnit.Pixel);
                g.Dispose();
            }
            pb.Click += new EventHandler(Tile_Click);
            flowLayoutPanelTiles.Controls.Add(pb);
            if (pb.Location.Y + pb.Height + 3 > flowLayoutPanelTiles.Height)
            {
                flowLayoutPanelTiles.MaximumSize = new Size(flowLayoutPanelTiles.Width, pb.Location.Y + pb.Height + 3);
                flowLayoutPanelTiles.Size = new Size(flowLayoutPanelTiles.Width, pb.Location.Y + pb.Height + 3);

                this.MaximumSize = new Size(this.Width, flowLayoutPanelTiles.Location.Y + flowLayoutPanelTiles.Height);
                this.Size = new Size(this.Width, flowLayoutPanelTiles.Location.Y + flowLayoutPanelTiles.Height);
            }
            flowLayoutPanelTiles.Update();
            this.Update();
        }


        public void Tile_Click(object sender, EventArgs e)
        {
            if (tpName == "NONE") return;
            Tileset_Palette.TilesetWindow.CurrentTilesetWindow.SelectTile((PictureBox)sender);
        }

        private void buttonTilesetOptions_Click(object sender, EventArgs e)
        {
            if (tpName == "NONE") return;
            TilesetPropertyMenu tpm = new TilesetPropertyMenu(this);
            Point locationOnForm = buttonTilesetOptions.FindForm().PointToClient(buttonTilesetOptions.Parent.PointToScreen(buttonTilesetOptions.Location));
            FormMainScreen.ActiveForm.Controls.Add(tpm);
            tpm.BringToFront();
            tpm.Focus();
            tpm.Location = new Point(
                locationOnForm.X + buttonTilesetOptions.Width - tpm.Width,
                locationOnForm.Y + buttonTilesetOptions.Height);
        }

        public void Delete()
        {
            TilesetWindow.CurrentTilesetWindow.TilesetPresets.Remove(this);
            if (tpName == "NONE") return;
            for (var i = 0; i < flowLayoutPanelTiles.Controls.Count; ++i)
                ((PictureBox)flowLayoutPanelTiles.Controls[i]).Image.Dispose();
            _Image.Dispose();
        }

    }
}

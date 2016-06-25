using Hardy_Part___Map_Editor.Entity_Palette;
using Hardy_Part___Map_Editor.Tileset_Palette;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Hardy_Part___Map_Editor
{
    public class Map : Control
    {
        internal Map() { DoubleBuffered = true; }

        public static Map CurrentMap = null;

        public string mPath { get; set; }
        public List<Entity> Entities { get; set; }
        public double mScale { get; set; }
        public PictureBox MapImage { get; set; }

        public Map(string path, int width, int height, double scale)
        {
            mPath = path;
            Entities = new List<Entity>();

            mScale = scale;
            Width = (int)((Double)width * mScale);
            Height = (int)((Double)height * mScale);
            MapImage = new PictureBox();
            MapImage.Width = Width;
            MapImage.Height = Height;
            MapImage.Image = new Bitmap(Width, Height);
            this.Controls.Add(MapImage);
            MapImage.Click += new EventHandler(Map_Click);
            MapImage.MouseMove += new MouseEventHandler(Map_MouseMove);
            BackColor = Color.Gray;
        }

        public void Draw()
        {
            MapImage.Image.Dispose();
            MapImage.Image = new Bitmap(Width, Height);
            using (Graphics g = Graphics.FromImage(MapImage.Image))
            {
                foreach (var item in Entities)
                {
                    item.Draw(g);
                }
            }
        }

        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // Map
            // 
            this.Click += new System.EventHandler(this.Map_Click);
            this.ResumeLayout(false);

        }

        private void Map_Click(object sender, EventArgs e)
        {
            if(TilesetWindow.CurrentTilesetWindow.CurrentTileset != null && TilesetWindow.CurrentTilesetWindow.CurrentTileset.Visible)
            {
                TilesetWindow.CurrentTilesetWindow.CurrentTileset.Tilemap_OnClick(sender, e);
            }
        }

        private void Map_MouseMove(object sender, MouseEventArgs e)
        {
            if (TilesetWindow.CurrentTilesetWindow.CurrentTileset != null && (e.Button == MouseButtons.Left || e.Button == MouseButtons.Right) && TilesetWindow.CurrentTilesetWindow.CurrentTileset.Visible)
            {
                TilesetWindow.CurrentTilesetWindow.CurrentTileset.Tilemap_OnClick(sender, e);
            }
        }
    }
}

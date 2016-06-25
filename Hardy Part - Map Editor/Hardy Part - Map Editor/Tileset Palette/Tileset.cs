using Hardy_Part___Map_Editor.Entity_Palette;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Hardy_Part___Map_Editor.Tileset_Palette
{

    public class Tileset : Entity
    {
        private TilesetPreset _Preset = null;
        public TilesetPreset Preset { get { return _Preset; } set { _ChangeTilesetPreset(value); } }

        public int FrameWidth
        {
            get
            {
                if (Preset == null) return -1;
                return (int)((double)Preset.FrameWidth * Scale * mapScale);
            }
        }
        public int FrameHeight
        {
            get
            {
                if (Preset == null) return -1;
                return (int)((double)Preset.FrameHeight * Scale * mapScale);
            }
        }
        public override int Width { get; }
        public override int Height { get; }
        public int FramesInRow { get { return Width / FrameWidth; } }
        public int FramesInCol { get { return Height / FrameHeight; } }
        public static int IdCount = 0;

        //public Image Tilemap { get; set; }
        public Image Grid { get; set; }

        private Map _CurrentMap { get
            {
                if (Map.CurrentMap == null) return null;
                return Map.CurrentMap;
            }
        }
        private Dictionary<Point, int> _mapping = new Dictionary<Point, int>();
        private double _Scale = 1.0;

        public override double Scale
        {
            get { return _Scale; }
            set
            {
                _Scale = value;
                Grid_Draw();
                Tilemap_Draw();
            }
        }

        private double mapScale
        {
            get
            {
                if (_CurrentMap == null) return 1.0;
                return _CurrentMap.mScale;
            }
        }



        public Tileset()
        {
            Name = "tileset" + IdCount++;
            this.Width = _CurrentMap.Width;
            this.Height = _CurrentMap.Height;
            this.Layer = 0;
            this.Visible = true;
        }


        public void SwitchVisible()
        {
            Visible = !Visible;
        }

        public override void Draw(Graphics g)
        {
            this.Draw();
            if (TilesetWindow.CurrentTilesetWindow.CurrentTileset != null &&
                this == TilesetWindow.CurrentTilesetWindow.CurrentTileset &&
                this.Grid != null &&
                TilesetWindow.CurrentTilesetWindow.checkBoxShowGrid.Checked &&
                this.Visible &&
                ((TabControl)TilesetWindow.CurrentTilesetWindow.Parent.Parent).SelectedIndex == 1)

                g.DrawImage(this.Grid, this.Pos);


            if (this.Texture != null && this.Visible)
                g.DrawImage(this.Texture, this.Pos);
        }

        public void Tilemap_OnClick(object sender, EventArgs e)
        {
            if (TilesetWindow.CurrentTilesetWindow.CurrentTile != null)
            {
                if (TilesetWindow.CurrentTilesetWindow.CurrentTile.Name == "pictureBoxDelete" || ((MouseEventArgs)e).Button == MouseButtons.Right)
                {
                    if (_mapping.ContainsKey(WhichTile(((MouseEventArgs)e).Location)))
                    {
                        _mapping.Remove(WhichTile(((MouseEventArgs)e).Location));
                        Tilemap_Draw();
                        _CurrentMap.Draw();
                    }
                }
                else if (!_mapping.ContainsKey(WhichTile(((MouseEventArgs)e).Location)) ||
                    _mapping[WhichTile(((MouseEventArgs)e).Location)] != TilesetWindow.CurrentTilesetWindow.CurrentTileset.Preset.flowLayoutPanelTiles.Controls.IndexOf(TilesetWindow.CurrentTilesetWindow.CurrentTile))
                {
                    _mapping[WhichTile(((MouseEventArgs)e).Location)]
                           = TilesetWindow.CurrentTilesetWindow.CurrentTileset.Preset.flowLayoutPanelTiles.Controls.IndexOf(TilesetWindow.CurrentTilesetWindow.CurrentTile);
                    Tilemap_Draw();
                    _CurrentMap.Draw();
                }
            }
        }


        private void _ChangeTilesetPreset(TilesetPreset tilesetPreset)
        {
            if (tilesetPreset == _Preset) return;
            _Preset = tilesetPreset;
            Draw();
        }


        public Point WhichTile(Point p)
        {
            p.X -= X;
            p.Y -= Y;
            if (Preset == null)
                return new Point(-1 ,-1);
            if (p.X >= Grid.Width ||
                p.X < 0 ||
                p.Y >= Grid.Height ||
                p.Y < 0)
                return new Point(-1, -1);

            p.X /= FrameWidth;
            p.Y /= FrameHeight;
            return new Point(p.X, p.Y);
        }

        public Point TilePos(Point tile)
        {
            Point p = new Point(tile.X * FrameWidth, tile.Y * FrameHeight);
            return p;
        }

        public void Draw()
        {
            Grid_Draw();
            Tilemap_Draw();
            //_CurrentMap.Draw();
        }

        public void Grid_Draw()
        {
            if (Map.CurrentMap == null) return;

            int maxFW = this.Width / FrameWidth;
            int maxFH = this.Height / FrameHeight;

            Point gridSize = new Point((maxFW + 3) * FrameWidth, (maxFH + 3) * FrameHeight);
            if (Grid != null)
            {
                Grid.Dispose();
                Grid = null;
            }
            if (Preset == null)
            {
                //_CurrentMap.Draw();
                return;
            }
            Grid = new Bitmap(gridSize.X, gridSize.Y);

            using (Graphics g = Graphics.FromImage(Grid))
            {
                Pen p = new Pen(Color.White);

                for (int i = 0; i < maxFW + 3; ++i)
                    for (int j = 0; j < maxFH + 3; ++j)
                    {
                        g.DrawRectangle(p, new Rectangle(i * FrameWidth, j * FrameHeight, FrameWidth - 1, FrameHeight - 1));
                    }
                p.Dispose();
            }
        }

        private void Tilemap_Draw()
        {
            if (Map.CurrentMap == null) return;

            int maxFW = this.Width / FrameWidth;
            int maxFH = this.Height / FrameHeight;

            Point tilemapSize = new Point((maxFW + 3) * FrameWidth, (maxFH + 3) * FrameHeight);
            if(Texture != null)
            {
                Texture.Dispose();
                Texture = null;
            }
            if (Preset == null)
            {
                //_CurrentMap.Draw();
                return;
            }

            Texture = new Bitmap(tilemapSize.X, tilemapSize.Y);

            using (Graphics g = Graphics.FromImage(Texture))
            {
                g.PixelOffsetMode = System.Drawing.Drawing2D.PixelOffsetMode.Half;
                g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
                foreach (var key in _mapping)
                {
                    if (Preset.flowLayoutPanelTiles.Controls.Count <= key.Value) continue;
                    g.DrawImage(((PictureBox)Preset.flowLayoutPanelTiles.Controls[key.Value]).Image, TilePos(key.Key).X, TilePos(key.Key).Y, FrameWidth, FrameHeight);
                }
            }
        }


    }
}

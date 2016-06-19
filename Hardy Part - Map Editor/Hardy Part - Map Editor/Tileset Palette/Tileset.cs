using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Hardy_Part___Map_Editor.Tileset_Palette
{

    public class Tileset : Panel
    {
        private PictureBox _Grid = null;
        private static int _IdCount = 0;

        public int tX = 0;
        public int tY = 0;
        public double tScale = 1.0;
        public TilesetPreset tPreset = null;
        public String tName { get; set; }



        public Tileset()
        {
            tName = "tileset" + _IdCount++;
            this.Width = Map.CurrentMap.Width;
            this.Height = Map.CurrentMap.Height;
            _Grid = new PictureBox();
            _Grid.SizeMode = PictureBoxSizeMode.CenterImage;
            _Grid.Size = this.Size;
            this.Controls.Add(_Grid);
            //if (Map.CurrentMap == null) return;
            //if (_Grid != null) _Grid.Dispose();
            //if (tPreset == null) return;
            //_Grid = new PictureBox();
            //this.Controls.Add(_Grid);
            //_Grid = new PictureBox();
            //this.Controls.Add(_Grid);
        }

        public override string ToString()
        {
            return tName;
        }



        public void ChangeTilesetPreset(TilesetPreset tilesetPreset)
        {
            if (tilesetPreset == tPreset) return;
            tPreset = tilesetPreset;
            if (tPreset == null)
            {
                _Grid.Hide();
            }
            else
            {
                _Grid.Show();
                if (_Grid.Image != null)
                {
                    _Grid.Image.Dispose();
                    _Grid.Image = null;
                }
                Grid_Redraw();
            }
        }


        public void Grid_Redraw()
        {
            if (Map.CurrentMap == null) return;
            if (tPreset == null) return;
            _Grid.Image = new Bitmap(_Grid.Width, _Grid.Height);

            int actualWidth = (int)((double)tPreset.FrameWidth * tScale);
            int actualHeight = (int)((double)tPreset.FrameHeight * tScale);

            int maxFW = _Grid.Width / actualWidth;
            int maxFH = _Grid.Height / actualHeight;
            using (Graphics g = Graphics.FromImage(_Grid.Image))
            {
                Pen p = new Pen(Color.White);

                for (int i = 0; i < maxFW; ++i)
                    for (int j = 0; j < maxFH; ++j)
                    {
                        g.DrawRectangle(p, new Rectangle(i * actualWidth, j * actualHeight, actualWidth, actualHeight));
                    }
                p.Dispose();
            }
        }
    }
}

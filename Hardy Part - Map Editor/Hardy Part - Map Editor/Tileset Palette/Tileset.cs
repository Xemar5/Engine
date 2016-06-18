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
        private PictureBox _Grid = new PictureBox();
        private static int _IdCount = 0;

        public int tX = 0;
        public int tY = 0;
        public double tScale = 1.0;
        public TilesetPalette tPreset = null;
        public String tName { get; set; }



        public Tileset()
        {
            tName = "tileset" + _IdCount++;
            this.Controls.Add(_Grid);
            SetGrid();
        }

        public override string ToString()
        {
            return tName;
        }

        public void SetGrid()
        {
            if (Map.CurrentMap == null) return;
            if (_Grid != null) _Grid.Dispose();
            if (tPreset == null) return;
            _Grid = new PictureBox();
            _Grid.Width = Map.CurrentMap.Width;
            _Grid.Height = Map.CurrentMap.Height;
            _Grid.Image = new Bitmap(_Grid.Width, _Grid.Height);
            int maxFW = _Grid.Width / tPreset.FrameWidth;
            int maxFH = _Grid.Height / tPreset.FrameHeight;
            using (Graphics g = _Grid.CreateGraphics())
            {
                Pen p = new Pen(Color.White);

                for (int i = 0; i < maxFW; ++i)
                    for (int j = 0; j < maxFH; ++j)
                    {
                        g.DrawRectangle(p, new Rectangle(i * _Grid.Width, j * _Grid.Height, _Grid.Width, _Grid.Height));
                    }
                p.Dispose();
            }
        }
    }
}

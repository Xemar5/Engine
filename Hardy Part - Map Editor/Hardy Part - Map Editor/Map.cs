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

        public string Path { get; set; }
        public List<Tileset> BuiltTilesets { get; set; }
        public bool Drawn = false;

        public Map(string path, int width, int height)
        {
            Path = path;
            BuiltTilesets = new List<Tileset>();

            Width = width + 6;
            Height = height + 6;
            BackColor = Color.Gray;

            Click += new EventHandler(Map_Click);
        }

        private void Map_Click(object sender, EventArgs e)
        {

        }
    }
}

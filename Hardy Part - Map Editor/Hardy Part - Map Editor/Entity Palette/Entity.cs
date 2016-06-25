using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Hardy_Part___Map_Editor.Entity_Palette
{
    public class Entity
    {
        public static int ObjectId = 0;
        virtual public Image Texture { get; set; }
        virtual public String Name { get; set; }
        virtual public int X { get; set; }
        virtual public int Y { get; set; }
        virtual public Point Pos { get { return new Point(X, Y); } }
        virtual public int Width { get { return Texture == null ? 0 : (int)((double)Texture.Width * Scale); } }
        virtual public int Height { get { return Texture == null ? 0 : (int)((double)Texture.Height * Scale); } }
        virtual public bool Visible { get; set; }
        virtual public int Layer { get; set; }
        virtual public Double Scale { get; set; }
        virtual public Double Angle { get; set; }
        private double _CenterX = 0;
        private double _CenterY = 0;
        virtual public int CenterX
        {
            get
            {
                return (int)((_CenterX + 1) / 2 * (double)Width);
            }
            set
            {
                if (value < -1) _CenterX = -1;
                if (value > 1) _CenterX = 1;
                _CenterX = value;
            }
        }
        virtual public int CenterY
        {
            get
            {
                return (int)((_CenterY + 1) / 2 * (double)Height);
            }
            set
            {
                if (value < -1) _CenterY = -1;
                if (value > 1) _CenterY = 1;
                _CenterY = value;
            }
        }
        public override string ToString()
        {
            return Name;
        }


        public Entity()
        {
            Texture = null;
            X = 0;
            Y = 0;
            Name = "entity" + ObjectId++;
            Scale = 1;
            Angle = 0;
            Visible = true;
        }

        virtual public void Draw(Graphics g)
        {
            if (Texture != null &&
                Visible == true)
                g.DrawImage(Texture, Pos);
        }
    }
}

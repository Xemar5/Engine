using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Hardy_Part___Map_Editor.Dialog_Boxes
{
    public partial class FormEditTileset : Form
    {

        private Tileset _Tileset = null;
        private FormMainScreen _Parent = null;

        private Bitmap _BaseBitmap = null;
        private List<List<Bitmap>> _Bitmaps;
        private List<List<PictureBox>> _PictureBoxes;
        private double _Scale = 1.0;



        private List<Point> Floors = new List<Point>();
        private List<Point> Underfloors = new List<Point>();
        private List<Point> Wall = new List<Point>();
        private List<Point> Void = new List<Point>();

        private List<Point> AllStart = new List<Point>();
        private List<Point> P1Start = new List<Point>();
        private List<Point> P2Start = new List<Point>();
        private List<Point> P3Start = new List<Point>();
        private List<Point> P4Start = new List<Point>();

        private List<Point> AllEnd = new List<Point>();
        private List<Point> P1End = new List<Point>();
        private List<Point> P2End = new List<Point>();
        private List<Point> P3End = new List<Point>();
        private List<Point> P4End = new List<Point>();


        private List<List<Point>> ContainerPoints = new List<List<Point>>();
        private List<RadioButton> ContainerButtons = new List<RadioButton>();


        public FormEditTileset(FormMainScreen parent, Tileset tileset)
        {
            InitializeComponent();

            _Parent = parent;
            _Tileset = tileset;


            {
                ContainerPoints.Add(Floors);
                ContainerPoints.Add(Underfloors);
                ContainerPoints.Add(Wall);
                ContainerPoints.Add(Void);
                ContainerPoints.Add(AllStart);
                ContainerPoints.Add(P1Start);
                ContainerPoints.Add(P2Start);
                ContainerPoints.Add(P3Start);
                ContainerPoints.Add(P4Start);
                ContainerPoints.Add(AllEnd);
                ContainerPoints.Add(P1End);
                ContainerPoints.Add(P2End);
                ContainerPoints.Add(P3End);
                ContainerPoints.Add(P4End);
            }

            {
                ContainerButtons.Add(radioButtonTileFloor);
                ContainerButtons.Add(radioButtonTileUnderfloor);
                ContainerButtons.Add(radioButtonTileWall);
                ContainerButtons.Add(radioButtonTileVoid);
                ContainerButtons.Add(radioButtonTileAllStart);
                ContainerButtons.Add(radioButtonTileP1Start);
                ContainerButtons.Add(radioButtonTileP2Start);
                ContainerButtons.Add(radioButtonTileP3Start);
                ContainerButtons.Add(radioButtonTileP4Start);
                ContainerButtons.Add(radioButtonTileAllEnd);
                ContainerButtons.Add(radioButtonTileP1End);
                ContainerButtons.Add(radioButtonTileP2End);
                ContainerButtons.Add(radioButtonTileP3End);
                ContainerButtons.Add(radioButtonTileP4End);
            }

            foreach (var rb in ContainerButtons)
                rb.CheckedChanged += new EventHandler(radioButtons_CheckedChanged);

           // picturePanelTilesetImage.BackgroundImage = new Bitmap(_BaseBitmap);
        }

        private void radioButtons_CheckedChanged(object sender, EventArgs e)
        {
            DrawTileBorders();
        }


        private void trackBarZoom_Scroll(object sender, EventArgs e)
        {
            for (int i = 0; i < GetWidth(); ++i)
                for (int j = 0; j < GetHeight(); ++j)
                {
                    Image img = _PictureBoxes[i][j].Image;
                    _Scale = Math.Pow(2, (trackBarZoom.Value - 6));
                    Size newSize = new Size((int)(_Bitmaps[i][j].Width * _Scale),
                                            (int)(_Bitmaps[i][j].Height * _Scale));
                    if (newSize.Width == 0) newSize.Width = 1;
                    if (newSize.Height == 0) newSize.Height = 1;
                    _PictureBoxes[i][j].Image = new Bitmap(newSize.Width, newSize.Height);
                    _PictureBoxes[i][j].Size = newSize;
                    using (Graphics g = Graphics.FromImage(_PictureBoxes[i][j].Image))
                    {
                        g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
                        g.DrawImage(_Bitmaps[i][j],
                            new Rectangle(0, 0, newSize.Width, newSize.Height),
                            new Rectangle(0, 0, _Bitmaps[i][j].Width, _Bitmaps[i][j].Height), GraphicsUnit.Pixel);
                        g.Dispose();
                    }
                    Relocate(_PictureBoxes);
                    if (img != null) img.Dispose();
                }
            //DrawTileBorders();
        }

        private void Relocate(List<List<PictureBox>> boxes)
        {
            int offsetX = 0;
            int offsetY = 0;
            if (boxes.Count == 0 || boxes[0].Count == 0) return;

            double wscr = (double)picturePanelTilesetImage.HorizontalScroll.Value / ((double)picturePanelTilesetImage.HorizontalScroll.Maximum - (double)picturePanelTilesetImage.HorizontalScroll.LargeChange + 1);
            double hscr = (double)picturePanelTilesetImage.VerticalScroll.Value / ((double)picturePanelTilesetImage.VerticalScroll.Maximum - (double)picturePanelTilesetImage.VerticalScroll.LargeChange + 1);
            int w = GetWidth() * (boxes[0][0].Width + 1);
            int h = GetHeight() * (boxes[0][0].Height + 1);
            int x0 = picturePanelTilesetImage.Width / 2 - (int)((double)(boxes[0][0].Width * GetWidth()) / 2.0) + picturePanelTilesetImage.HorizontalScroll.Value;
            int y0 = picturePanelTilesetImage.Height / 2 - (int)((double)(boxes[0][0].Height * GetHeight()) / 2.0) + picturePanelTilesetImage.VerticalScroll.Value;
            offsetX = (x0 < 0 ? -x0 : 0) - (int)((double)w * wscr);
            offsetY = (y0 < 0 ? -y0 : 0) - (int)((double)h * hscr);

            for (int i = 0; i < GetWidth(); ++i)
                for (int j = 0; j < GetHeight(); ++j)
                {
                    int x = i * (boxes[i][j].Width + 1) + picturePanelTilesetImage.Width / 2 - (int)((double)(boxes[i][j].Width * GetWidth()) / 2.0);
                    int y = j * (boxes[i][j].Height + 1) + picturePanelTilesetImage.Height / 2 - (int)((double)(boxes[i][j].Height * GetHeight()) / 2.0);
                    if (x < 0 && x < offsetX) offsetX = -x;
                    if (y < 0 && y < offsetY) offsetY = -y;
                    boxes[i][j].Location = new Point(
                        x + offsetX,
                        y + offsetY);
                }
        }

        private int GetWidth()
        {
            return _BaseBitmap.Width / _Tileset.FrameWidth;
        }
        private int GetHeight()
        {
            return _BaseBitmap.Height / _Tileset.FrameHeight;
        }



        private List<List<Bitmap>> CreateInitialBitmaps(Bitmap source)
        {
            List<List<Bitmap>> list = new List<List<Bitmap>>();

            for (int i = 0; i < GetWidth(); ++i)
            {
                list.Add(new List<Bitmap>());
                for (int j = 0; j < GetHeight(); ++j)
                {
                    list[i].Add(new Bitmap(_Tileset.FrameWidth, _Tileset.FrameHeight));
                    using (Graphics g = Graphics.FromImage(list[i][j]))
                    {
                        g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
                        g.DrawImage(source,
                            new Rectangle(0, 0, _Tileset.FrameWidth, _Tileset.FrameHeight),
                            new Rectangle(i * _Tileset.FrameWidth, j * _Tileset.FrameHeight, 
                                            _Tileset.FrameWidth, _Tileset.FrameHeight), GraphicsUnit.Pixel);
                        g.Dispose();
                    }
                }
            }

            return list;
        }


        private Bitmap CreateInitialBitmap(string path)
        {
            Bitmap source = new Bitmap(path);
            int actualWidth = source.Width - (source.Width % _Tileset.FrameWidth);
            int actualHeight = source.Height - (source.Height % _Tileset.FrameHeight);
            Bitmap result = new Bitmap(actualWidth, actualHeight);
            using (Graphics g = Graphics.FromImage(result))
            {
                g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
                g.DrawImage(source,
                    new Rectangle(0, 0, actualWidth, actualHeight),
                    new Rectangle(0, 0, actualWidth, actualHeight), GraphicsUnit.Pixel);
            }
            source.Dispose();
            return result;
        }

        //private Bitmap ResizeBitmap(Bitmap bpmSource)
        //{
        //    _Scale = Math.Pow(2, (trackBarZoom.Value - 6));
        //    Size newSize = new Size((int)(_BaseBitmap.Width * _Scale),
        //                            (int)(_BaseBitmap.Height * _Scale));
        //    if (newSize.Width == 0) newSize.Width = 1;
        //    if (newSize.Height == 0) newSize.Height = 1;
        //    Bitmap result = new Bitmap(newSize.Width, newSize.Height);
        //    using (Graphics g = Graphics.FromImage(result))
        //    {
        //        g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
        //        g.DrawImage(bpmSource, 0, 0, newSize.Width, newSize.Height);
        //        g.Dispose();
        //    }
        //    return result;
        //}

        private void picturePanelTilesetImage_Click(object sender, EventArgs e)
        {

            //MouseEventArgs me = (MouseEventArgs)e;
            //Point result = GetTilePos(PointToClient(Cursor.Position));
            //if (result.X >= 0 && result.Y >= 0 &&
            //    result.X < GetWidth() && result.Y < GetHeight())
            //{




            //    RadioButton checkedButton = groupBoxTileType.Controls.OfType<RadioButton>().FirstOrDefault(r => r.Checked);

            //    int index = ContainerButtons.IndexOf(checkedButton);
            //    if (me.Button == System.Windows.Forms.MouseButtons.Right)
            //    {
            //        if (ContainerPoints[index].Contains(result))
            //            ContainerPoints[index].Remove(result);
            //        EreasePicture();
            //        DrawTileBorders();
            //    }
            //    else if (me.Button == System.Windows.Forms.MouseButtons.Left)
            //    {
            //        if (!ContainerPoints[index].Contains(result))
            //            ContainerPoints[index].Add(result);
            //        DrawTileBorders();
            //    }
            //}
        }
        
        //private void EreasePicture()
        //{
        //    var temp = picturePanelTilesetImage.BackgroundImage;
        //    Bitmap img = new Bitmap(_BaseBitmap);
        //    picturePanelTilesetImage.BackgroundImage = ResizeBitmap(img);
        //    temp.Dispose();
        //}

        private void DrawTileBorders()
        {
            //Bitmap bm = new Bitmap(picturePanelTilesetImage.BackgroundImage);
            //using (Graphics g = Graphics.FromImage(bm))
            //{
            //    Pen pen = new Pen(Color.White, 1);
            //    g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.NearestNeighbor;
            //    for (int i = 0; i < ContainerPoints.Count; ++i)
            //    {
            //        int topIndex = ContainerButtons.IndexOf(groupBoxTileType.Controls.OfType<RadioButton>().FirstOrDefault(r => r.Checked));
            //        pen.Color = ContainerButtons[i].BackColor;
            //        foreach (var p in ContainerPoints[i])
            //            if (i == topIndex || !ContainerPoints[topIndex].Contains(p))
            //                g.DrawRectangle(pen, new Rectangle(
            //                    (int)((double)(_Scale * _Tileset.FrameWidth) * p.X),
            //                    (int)((double)(_Scale * _Tileset.FrameHeight) * p.Y),
            //                    (int)(((double)_Tileset.FrameWidth) * _Scale),
            //                    (int)(((double)_Tileset.FrameHeight) * _Scale)
            //                    ));
            //    }
            //    pen.Dispose();
            //    g.Dispose();
            //}
            //var temp = picturePanelTilesetImage.BackgroundImage;
            //picturePanelTilesetImage.BackgroundImage = bm;
            //temp.Dispose();
        }

        private Point GetTilePos(Point mousePos)
        {
            double wscr = (double)picturePanelTilesetImage.HorizontalScroll.Value / ((double)picturePanelTilesetImage.HorizontalScroll.Maximum - (double)picturePanelTilesetImage.HorizontalScroll.LargeChange + 1);
            double hscr = (double)picturePanelTilesetImage.VerticalScroll.Value / ((double)picturePanelTilesetImage.VerticalScroll.Maximum - (double)picturePanelTilesetImage.VerticalScroll.LargeChange + 1);
            double wof = (double)(picturePanelTilesetImage.BackgroundImage.Width - picturePanelTilesetImage.Width > 0 ? picturePanelTilesetImage.BackgroundImage.Width - picturePanelTilesetImage.Width : 0) / 2 * (wscr * 2 - 1);
            double hof = (double)(picturePanelTilesetImage.BackgroundImage.Height - picturePanelTilesetImage.Height > 0 ? picturePanelTilesetImage.BackgroundImage.Height - picturePanelTilesetImage.Height : 0) / 2 * (hscr * 2 - 1);
            double x = ((double)mousePos.X - ((double)picturePanelTilesetImage.Location.X + (double)picturePanelTilesetImage.Width / 2.0 - (double)picturePanelTilesetImage.BackgroundImage.Width / 2.0 - wof))
                / ((double)picturePanelTilesetImage.BackgroundImage.Width / (double)_BaseBitmap.Width);
            double y = ((double)mousePos.Y - ((double)picturePanelTilesetImage.Location.Y + (double)picturePanelTilesetImage.Height / 2.0 - (double)picturePanelTilesetImage.BackgroundImage.Height / 2.0 - hof))
                / ((double)picturePanelTilesetImage.BackgroundImage.Height / (double)_BaseBitmap.Height);
            x = Math.Floor(x / _Tileset.FrameWidth);
            y = Math.Floor(y / _Tileset.FrameHeight);
            return new Point((int)x, (int)y);
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            _Parent.CurrentTileset = null;
            this.Close();
        }

        private void buttonBack_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void buttonFinish_Click(object sender, EventArgs e)
        {
            string data = "";


            _Parent.CurrentTileset = null;
            _Parent.CurrentPalette = new Palette(data);
            this.Close();
        }

        private void FormEditTileset_Load(object sender, EventArgs e)
        {
            _BaseBitmap = CreateInitialBitmap(_Tileset.Path);
            _Bitmaps = CreateInitialBitmaps(_BaseBitmap);
            _PictureBoxes = new List<List<PictureBox>>();
            for (int i = 0; i < GetWidth(); ++i)
            {
                _PictureBoxes.Add(new List<PictureBox>());
                for (int j = 0; j < GetHeight(); ++j)
                {
                    PictureBox pb = new PictureBox();
                    pb.Name = "pictureBoxTile" + i + "" + j;
                    pb.Size = new Size(_Tileset.FrameWidth, _Tileset.FrameHeight);
                    pb.Image = new Bitmap(_Bitmaps[i][j]);
                    picturePanelTilesetImage.Controls.Add(pb);
                    _PictureBoxes[i].Add(pb);
                }
            }
            Relocate(_PictureBoxes);
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hardy_Part___Map_Editor
{
    public class Tileset
    {
        public string Path;
        readonly public int FrameWidth;
        readonly public int FrameHeight;
        readonly public int PictureWidth;
        readonly public int PictureHeight;

        public Tileset(string path, int frameWidth, int frameHeight, int pictureWidth, int pictureHeight)
        {
            Path = path;
            FrameWidth = frameWidth;
            FrameHeight = frameHeight;
            PictureWidth = pictureWidth;
            PictureHeight = pictureHeight;
        }

        public int MaxFrames()
        {
            if (FrameHeight < 0 || FrameHeight < 0) return 0;
            if (FrameHeight > PictureHeight || FrameWidth > PictureWidth) return 0;
            return (PictureWidth / FrameWidth) * (PictureHeight / FrameHeight);
        }
        public int MaxFramesWidth()
        {
            if (FrameHeight < 0 || FrameHeight < 0) return 0;
            if (FrameHeight > PictureHeight || FrameWidth > PictureWidth) return 0;
            return PictureWidth / FrameWidth;
        }
        public int MaxFramesHeight()
        {
            if (FrameHeight < 0 || FrameHeight < 0) return 0;
            if (FrameHeight > PictureHeight || FrameWidth > PictureWidth) return 0;
            return PictureHeight / FrameHeight;
        }
    }
}

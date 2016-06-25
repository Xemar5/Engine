using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hardy_Part___Map_Editor.Tileset_Palette
{
    class RecentTileset
    {
        public String hPath { get; set; }
        public int FrameWidth { get; set; }
        public int FrameHeight { get; set; }

        public RecentTileset(String str)
        {
            FrameHeight = _ProcessInt(ref str);
            FrameWidth = _ProcessInt(ref str);
            hPath = _ProcessStr(ref str);
        }

        public string Convert()
        {
            return hPath + " " + FrameWidth.ToString() + " " + FrameHeight.ToString();
        }


        private int _ProcessInt(ref String str)
        {
            int num = 0;
            int i = 0;
            while(str.Length > 0)
            {
                if(Char.IsWhiteSpace(str.Last()))
                {
                    str = str.Remove(str.Length - 1, 1);
                    break;
                }
                if(!Char.IsDigit(str.Last())) break;
                num = num + (int)Math.Pow(10, i) * int.Parse(str.Substring(str.Length - 1, 1));
                ++i;
                str = str.Remove(str.Length - 1, 1);
            }
            return num;
        }

        private String _ProcessStr(ref String str)
        {
            String s = "";
            try
            {
                s = Path.GetFullPath(str);
            }
            catch (Exception)
            {
                return "";
            }
            return s;
        }
    }
}

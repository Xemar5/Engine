namespace Hardy_Part___Map_Editor.Tileset_Palette
{
    partial class TilesetPropertyMenu
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonTilesetRemove = new System.Windows.Forms.Button();
            this.buttonClose = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonTilesetRemove
            // 
            this.buttonTilesetRemove.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(223)))), ((int)(((byte)(224)))));
            this.buttonTilesetRemove.Location = new System.Drawing.Point(3, 32);
            this.buttonTilesetRemove.Name = "buttonTilesetRemove";
            this.buttonTilesetRemove.Size = new System.Drawing.Size(57, 23);
            this.buttonTilesetRemove.TabIndex = 1;
            this.buttonTilesetRemove.Text = "Remove";
            this.buttonTilesetRemove.UseVisualStyleBackColor = false;
            this.buttonTilesetRemove.Click += new System.EventHandler(this.buttonTilesetRemove_Click);
            // 
            // buttonClose
            // 
            this.buttonClose.Location = new System.Drawing.Point(3, 3);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(57, 23);
            this.buttonClose.TabIndex = 0;
            this.buttonClose.Text = "OK";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // TilesetPropertyMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Silver;
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.buttonTilesetRemove);
            this.Name = "TilesetPropertyMenu";
            this.Size = new System.Drawing.Size(63, 59);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.TilesetPropertyMenu_KeyDown);
            this.Leave += new System.EventHandler(this.TilesetPropertyMenu_Leave);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonTilesetRemove;
        private System.Windows.Forms.Button buttonClose;
    }
}

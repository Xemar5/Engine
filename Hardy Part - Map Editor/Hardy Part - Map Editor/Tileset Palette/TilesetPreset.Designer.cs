namespace Hardy_Part___Map_Editor.Tileset_Palette
{
    partial class TilesetPreset
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
            this.labelTilesetName = new System.Windows.Forms.Label();
            this.buttonTilesetOptions = new System.Windows.Forms.Button();
            this.flowLayoutPanelTiles = new System.Windows.Forms.FlowLayoutPanel();
            this.labelTileSize = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // labelTilesetName
            // 
            this.labelTilesetName.AutoSize = true;
            this.labelTilesetName.Location = new System.Drawing.Point(3, 7);
            this.labelTilesetName.Name = "labelTilesetName";
            this.labelTilesetName.Size = new System.Drawing.Size(66, 13);
            this.labelTilesetName.TabIndex = 1;
            this.labelTilesetName.Text = "TilesetName";
            // 
            // buttonTilesetOptions
            // 
            this.buttonTilesetOptions.Location = new System.Drawing.Point(273, 3);
            this.buttonTilesetOptions.Name = "buttonTilesetOptions";
            this.buttonTilesetOptions.Size = new System.Drawing.Size(24, 20);
            this.buttonTilesetOptions.TabIndex = 2;
            this.buttonTilesetOptions.Text = "...";
            this.buttonTilesetOptions.UseVisualStyleBackColor = true;
            this.buttonTilesetOptions.Click += new System.EventHandler(this.buttonTilesetOptions_Click);
            // 
            // flowLayoutPanelTiles
            // 
            this.flowLayoutPanelTiles.BackColor = System.Drawing.SystemColors.Control;
            this.flowLayoutPanelTiles.Location = new System.Drawing.Point(0, 24);
            this.flowLayoutPanelTiles.Margin = new System.Windows.Forms.Padding(0);
            this.flowLayoutPanelTiles.Name = "flowLayoutPanelTiles";
            this.flowLayoutPanelTiles.Size = new System.Drawing.Size(300, 54);
            this.flowLayoutPanelTiles.TabIndex = 3;
            // 
            // labelTileSize
            // 
            this.labelTileSize.AutoSize = true;
            this.labelTileSize.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(54)))), ((int)(((byte)(54)))), ((int)(((byte)(54)))));
            this.labelTileSize.Location = new System.Drawing.Point(93, 7);
            this.labelTileSize.Name = "labelTileSize";
            this.labelTileSize.Size = new System.Drawing.Size(44, 13);
            this.labelTileSize.TabIndex = 4;
            this.labelTileSize.Text = "TileSize";
            // 
            // Tileset
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.Controls.Add(this.labelTileSize);
            this.Controls.Add(this.flowLayoutPanelTiles);
            this.Controls.Add(this.buttonTilesetOptions);
            this.Controls.Add(this.labelTilesetName);
            this.Margin = new System.Windows.Forms.Padding(0);
            this.Name = "Tileset";
            this.Size = new System.Drawing.Size(300, 78);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label labelTilesetName;
        private System.Windows.Forms.Button buttonTilesetOptions;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanelTiles;
        private System.Windows.Forms.Label labelTileSize;
    }
}

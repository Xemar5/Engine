namespace Hardy_Part___Map_Editor
{
    partial class FormMainScreen
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonNewMap = new System.Windows.Forms.Button();
            this.groupBoxTiles = new System.Windows.Forms.GroupBox();
            this.panelTiles = new System.Windows.Forms.Panel();
            this.buttonLoadTileset = new System.Windows.Forms.Button();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.groupBoxTiles.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonNewMap
            // 
            this.buttonNewMap.Location = new System.Drawing.Point(12, 12);
            this.buttonNewMap.Name = "buttonNewMap";
            this.buttonNewMap.Size = new System.Drawing.Size(75, 23);
            this.buttonNewMap.TabIndex = 0;
            this.buttonNewMap.Text = "New Map";
            this.buttonNewMap.UseVisualStyleBackColor = true;
            this.buttonNewMap.Click += new System.EventHandler(this.buttonNewMap_Click);
            // 
            // groupBoxTiles
            // 
            this.groupBoxTiles.Controls.Add(this.panelTiles);
            this.groupBoxTiles.Location = new System.Drawing.Point(938, 63);
            this.groupBoxTiles.Name = "groupBoxTiles";
            this.groupBoxTiles.Size = new System.Drawing.Size(314, 686);
            this.groupBoxTiles.TabIndex = 3;
            this.groupBoxTiles.TabStop = false;
            this.groupBoxTiles.Text = "Tiles";
            // 
            // panelTiles
            // 
            this.panelTiles.AutoScroll = true;
            this.panelTiles.Location = new System.Drawing.Point(6, 35);
            this.panelTiles.Name = "panelTiles";
            this.panelTiles.Size = new System.Drawing.Size(302, 645);
            this.panelTiles.TabIndex = 0;
            // 
            // buttonLoadTileset
            // 
            this.buttonLoadTileset.Location = new System.Drawing.Point(93, 12);
            this.buttonLoadTileset.Name = "buttonLoadTileset";
            this.buttonLoadTileset.Size = new System.Drawing.Size(75, 23);
            this.buttonLoadTileset.TabIndex = 4;
            this.buttonLoadTileset.Text = "Load Tileset";
            this.buttonLoadTileset.UseVisualStyleBackColor = true;
            this.buttonLoadTileset.Click += new System.EventHandler(this.buttonLoadTileset_Click);
            // 
            // trackBar1
            // 
            this.trackBar1.Location = new System.Drawing.Point(975, 12);
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(271, 45);
            this.trackBar1.TabIndex = 1;
            // 
            // FormMainScreen
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1264, 761);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.buttonLoadTileset);
            this.Controls.Add(this.groupBoxTiles);
            this.Controls.Add(this.buttonNewMap);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "FormMainScreen";
            this.Text = "Hardy Part - Map Editor";
            this.groupBoxTiles.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonNewMap;
        private System.Windows.Forms.GroupBox groupBoxTiles;
        private System.Windows.Forms.Button buttonLoadTileset;
        private System.Windows.Forms.Panel panelTiles;
        private System.Windows.Forms.TrackBar trackBar1;
    }
}


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
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.tabControlPanels = new System.Windows.Forms.TabControl();
            this.tabPageObjects = new System.Windows.Forms.TabPage();
            this.tabPageTilesets = new System.Windows.Forms.TabPage();
            this.panelMap = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.tabControlPanels.SuspendLayout();
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
            // trackBar1
            // 
            this.trackBar1.Location = new System.Drawing.Point(975, 12);
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(271, 45);
            this.trackBar1.TabIndex = 1;
            // 
            // tabControlPanels
            // 
            this.tabControlPanels.Controls.Add(this.tabPageObjects);
            this.tabControlPanels.Controls.Add(this.tabPageTilesets);
            this.tabControlPanels.Location = new System.Drawing.Point(906, 50);
            this.tabControlPanels.Name = "tabControlPanels";
            this.tabControlPanels.SelectedIndex = 0;
            this.tabControlPanels.Size = new System.Drawing.Size(346, 699);
            this.tabControlPanels.TabIndex = 5;
            // 
            // tabPageObjects
            // 
            this.tabPageObjects.Location = new System.Drawing.Point(4, 22);
            this.tabPageObjects.Name = "tabPageObjects";
            this.tabPageObjects.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageObjects.Size = new System.Drawing.Size(338, 673);
            this.tabPageObjects.TabIndex = 0;
            this.tabPageObjects.Text = "Objects";
            this.tabPageObjects.UseVisualStyleBackColor = true;
            // 
            // tabPageTilesets
            // 
            this.tabPageTilesets.Location = new System.Drawing.Point(4, 22);
            this.tabPageTilesets.Name = "tabPageTilesets";
            this.tabPageTilesets.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageTilesets.Size = new System.Drawing.Size(308, 673);
            this.tabPageTilesets.TabIndex = 1;
            this.tabPageTilesets.Text = "Tilesets";
            this.tabPageTilesets.UseVisualStyleBackColor = true;
            // 
            // panelMap
            // 
            this.panelMap.AutoScroll = true;
            this.panelMap.Location = new System.Drawing.Point(12, 50);
            this.panelMap.Name = "panelMap";
            this.panelMap.Size = new System.Drawing.Size(888, 699);
            this.panelMap.TabIndex = 6;
            // 
            // FormMainScreen
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1264, 761);
            this.Controls.Add(this.panelMap);
            this.Controls.Add(this.tabControlPanels);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.buttonNewMap);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "FormMainScreen";
            this.Text = "Hardy Part - Map Editor";
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.tabControlPanels.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonNewMap;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.TabControl tabControlPanels;
        private System.Windows.Forms.TabPage tabPageObjects;
        private System.Windows.Forms.Panel panelMap;
        private System.Windows.Forms.TabPage tabPageTilesets;
    }
}


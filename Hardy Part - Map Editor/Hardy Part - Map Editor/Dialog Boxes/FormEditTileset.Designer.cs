namespace Hardy_Part___Map_Editor.Dialog_Boxes
{
    partial class FormEditTileset
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
            this.trackBarZoom = new System.Windows.Forms.TrackBar();
            this.groupBoxTileType = new System.Windows.Forms.GroupBox();
            this.radioButtonTileWall = new System.Windows.Forms.RadioButton();
            this.radioButtonTileVoid = new System.Windows.Forms.RadioButton();
            this.radioButtonTileAllEnd = new System.Windows.Forms.RadioButton();
            this.radioButtonTileP4End = new System.Windows.Forms.RadioButton();
            this.radioButtonTileP3End = new System.Windows.Forms.RadioButton();
            this.radioButtonTileP2End = new System.Windows.Forms.RadioButton();
            this.radioButtonTileP1End = new System.Windows.Forms.RadioButton();
            this.radioButtonTileAllStart = new System.Windows.Forms.RadioButton();
            this.radioButtonTileP4Start = new System.Windows.Forms.RadioButton();
            this.radioButtonTileP3Start = new System.Windows.Forms.RadioButton();
            this.radioButtonTileP2Start = new System.Windows.Forms.RadioButton();
            this.radioButtonTileP1Start = new System.Windows.Forms.RadioButton();
            this.radioButtonTileUnderfloor = new System.Windows.Forms.RadioButton();
            this.radioButtonTileFloor = new System.Windows.Forms.RadioButton();
            this.buttonFinish = new System.Windows.Forms.Button();
            this.buttonBack = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.picturePanelTilesetImage = new PicturePanel();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarZoom)).BeginInit();
            this.groupBoxTileType.SuspendLayout();
            this.SuspendLayout();
            // 
            // trackBarZoom
            // 
            this.trackBarZoom.LargeChange = 1;
            this.trackBarZoom.Location = new System.Drawing.Point(348, 393);
            this.trackBarZoom.Maximum = 11;
            this.trackBarZoom.Minimum = 1;
            this.trackBarZoom.Name = "trackBarZoom";
            this.trackBarZoom.Size = new System.Drawing.Size(297, 45);
            this.trackBarZoom.TabIndex = 2;
            this.trackBarZoom.Value = 6;
            this.trackBarZoom.Scroll += new System.EventHandler(this.trackBarZoom_Scroll);
            // 
            // groupBoxTileType
            // 
            this.groupBoxTileType.Controls.Add(this.radioButtonTileWall);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileVoid);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileAllEnd);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileP4End);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileP3End);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileP2End);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileP1End);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileAllStart);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileP4Start);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileP3Start);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileP2Start);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileP1Start);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileUnderfloor);
            this.groupBoxTileType.Controls.Add(this.radioButtonTileFloor);
            this.groupBoxTileType.Location = new System.Drawing.Point(12, 12);
            this.groupBoxTileType.Name = "groupBoxTileType";
            this.groupBoxTileType.Size = new System.Drawing.Size(195, 375);
            this.groupBoxTileType.TabIndex = 4;
            this.groupBoxTileType.TabStop = false;
            this.groupBoxTileType.Text = "Tile Type";
            // 
            // radioButtonTileWall
            // 
            this.radioButtonTileWall.AutoSize = true;
            this.radioButtonTileWall.BackColor = System.Drawing.Color.DarkGray;
            this.radioButtonTileWall.ForeColor = System.Drawing.SystemColors.ControlText;
            this.radioButtonTileWall.Location = new System.Drawing.Point(60, 56);
            this.radioButtonTileWall.Name = "radioButtonTileWall";
            this.radioButtonTileWall.Size = new System.Drawing.Size(105, 17);
            this.radioButtonTileWall.TabIndex = 17;
            this.radioButtonTileWall.Text = "Wall Placeholder";
            this.radioButtonTileWall.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileVoid
            // 
            this.radioButtonTileVoid.AutoSize = true;
            this.radioButtonTileVoid.BackColor = System.Drawing.Color.DimGray;
            this.radioButtonTileVoid.ForeColor = System.Drawing.SystemColors.ControlText;
            this.radioButtonTileVoid.Location = new System.Drawing.Point(94, 79);
            this.radioButtonTileVoid.Name = "radioButtonTileVoid";
            this.radioButtonTileVoid.Size = new System.Drawing.Size(71, 17);
            this.radioButtonTileVoid.TabIndex = 16;
            this.radioButtonTileVoid.Text = "Void (null)";
            this.radioButtonTileVoid.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileAllEnd
            // 
            this.radioButtonTileAllEnd.AutoSize = true;
            this.radioButtonTileAllEnd.BackColor = System.Drawing.Color.BlueViolet;
            this.radioButtonTileAllEnd.ForeColor = System.Drawing.SystemColors.Control;
            this.radioButtonTileAllEnd.Location = new System.Drawing.Point(105, 117);
            this.radioButtonTileAllEnd.Name = "radioButtonTileAllEnd";
            this.radioButtonTileAllEnd.Size = new System.Drawing.Size(58, 17);
            this.radioButtonTileAllEnd.TabIndex = 15;
            this.radioButtonTileAllEnd.Text = "All End";
            this.radioButtonTileAllEnd.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileP4End
            // 
            this.radioButtonTileP4End.AutoSize = true;
            this.radioButtonTileP4End.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(15)))), ((int)(((byte)(51)))), ((int)(((byte)(0)))));
            this.radioButtonTileP4End.ForeColor = System.Drawing.SystemColors.Control;
            this.radioButtonTileP4End.Location = new System.Drawing.Point(105, 209);
            this.radioButtonTileP4End.Name = "radioButtonTileP4End";
            this.radioButtonTileP4End.Size = new System.Drawing.Size(60, 17);
            this.radioButtonTileP4End.TabIndex = 14;
            this.radioButtonTileP4End.Text = "P4 End";
            this.radioButtonTileP4End.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileP3End
            // 
            this.radioButtonTileP3End.AutoSize = true;
            this.radioButtonTileP3End.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(106)))), ((int)(((byte)(115)))), ((int)(((byte)(0)))));
            this.radioButtonTileP3End.ForeColor = System.Drawing.SystemColors.Control;
            this.radioButtonTileP3End.Location = new System.Drawing.Point(105, 186);
            this.radioButtonTileP3End.Name = "radioButtonTileP3End";
            this.radioButtonTileP3End.Size = new System.Drawing.Size(60, 17);
            this.radioButtonTileP3End.TabIndex = 13;
            this.radioButtonTileP3End.Text = "P3 End";
            this.radioButtonTileP3End.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileP2End
            // 
            this.radioButtonTileP2End.AutoSize = true;
            this.radioButtonTileP2End.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.radioButtonTileP2End.ForeColor = System.Drawing.SystemColors.Control;
            this.radioButtonTileP2End.Location = new System.Drawing.Point(105, 163);
            this.radioButtonTileP2End.Name = "radioButtonTileP2End";
            this.radioButtonTileP2End.Size = new System.Drawing.Size(60, 17);
            this.radioButtonTileP2End.TabIndex = 12;
            this.radioButtonTileP2End.Text = "P2 End";
            this.radioButtonTileP2End.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileP1End
            // 
            this.radioButtonTileP1End.AutoSize = true;
            this.radioButtonTileP1End.BackColor = System.Drawing.Color.MidnightBlue;
            this.radioButtonTileP1End.ForeColor = System.Drawing.SystemColors.Control;
            this.radioButtonTileP1End.Location = new System.Drawing.Point(105, 140);
            this.radioButtonTileP1End.Name = "radioButtonTileP1End";
            this.radioButtonTileP1End.Size = new System.Drawing.Size(60, 17);
            this.radioButtonTileP1End.TabIndex = 11;
            this.radioButtonTileP1End.Text = "P1 End";
            this.radioButtonTileP1End.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileAllStart
            // 
            this.radioButtonTileAllStart.AutoSize = true;
            this.radioButtonTileAllStart.BackColor = System.Drawing.Color.MediumPurple;
            this.radioButtonTileAllStart.Location = new System.Drawing.Point(5, 117);
            this.radioButtonTileAllStart.Name = "radioButtonTileAllStart";
            this.radioButtonTileAllStart.Size = new System.Drawing.Size(61, 17);
            this.radioButtonTileAllStart.TabIndex = 10;
            this.radioButtonTileAllStart.Text = "All Start";
            this.radioButtonTileAllStart.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileP4Start
            // 
            this.radioButtonTileP4Start.AutoSize = true;
            this.radioButtonTileP4Start.BackColor = System.Drawing.Color.ForestGreen;
            this.radioButtonTileP4Start.Location = new System.Drawing.Point(5, 209);
            this.radioButtonTileP4Start.Name = "radioButtonTileP4Start";
            this.radioButtonTileP4Start.Size = new System.Drawing.Size(63, 17);
            this.radioButtonTileP4Start.TabIndex = 9;
            this.radioButtonTileP4Start.Text = "P4 Start";
            this.radioButtonTileP4Start.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileP3Start
            // 
            this.radioButtonTileP3Start.AutoSize = true;
            this.radioButtonTileP3Start.BackColor = System.Drawing.Color.Goldenrod;
            this.radioButtonTileP3Start.Location = new System.Drawing.Point(5, 186);
            this.radioButtonTileP3Start.Name = "radioButtonTileP3Start";
            this.radioButtonTileP3Start.Size = new System.Drawing.Size(63, 17);
            this.radioButtonTileP3Start.TabIndex = 8;
            this.radioButtonTileP3Start.Text = "P3 Start";
            this.radioButtonTileP3Start.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileP2Start
            // 
            this.radioButtonTileP2Start.AutoSize = true;
            this.radioButtonTileP2Start.BackColor = System.Drawing.Color.Firebrick;
            this.radioButtonTileP2Start.Location = new System.Drawing.Point(5, 163);
            this.radioButtonTileP2Start.Name = "radioButtonTileP2Start";
            this.radioButtonTileP2Start.Size = new System.Drawing.Size(63, 17);
            this.radioButtonTileP2Start.TabIndex = 7;
            this.radioButtonTileP2Start.Text = "P2 Start";
            this.radioButtonTileP2Start.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileP1Start
            // 
            this.radioButtonTileP1Start.AutoSize = true;
            this.radioButtonTileP1Start.BackColor = System.Drawing.Color.RoyalBlue;
            this.radioButtonTileP1Start.Location = new System.Drawing.Point(5, 140);
            this.radioButtonTileP1Start.Name = "radioButtonTileP1Start";
            this.radioButtonTileP1Start.Size = new System.Drawing.Size(63, 17);
            this.radioButtonTileP1Start.TabIndex = 6;
            this.radioButtonTileP1Start.Text = "P1 Start";
            this.radioButtonTileP1Start.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileUnderfloor
            // 
            this.radioButtonTileUnderfloor.AutoSize = true;
            this.radioButtonTileUnderfloor.BackColor = System.Drawing.Color.Lime;
            this.radioButtonTileUnderfloor.Location = new System.Drawing.Point(5, 79);
            this.radioButtonTileUnderfloor.Name = "radioButtonTileUnderfloor";
            this.radioButtonTileUnderfloor.Size = new System.Drawing.Size(74, 17);
            this.radioButtonTileUnderfloor.TabIndex = 5;
            this.radioButtonTileUnderfloor.Text = "Underfloor";
            this.radioButtonTileUnderfloor.UseVisualStyleBackColor = false;
            // 
            // radioButtonTileFloor
            // 
            this.radioButtonTileFloor.AutoSize = true;
            this.radioButtonTileFloor.BackColor = System.Drawing.Color.Aqua;
            this.radioButtonTileFloor.Checked = true;
            this.radioButtonTileFloor.ForeColor = System.Drawing.SystemColors.ControlText;
            this.radioButtonTileFloor.Location = new System.Drawing.Point(5, 56);
            this.radioButtonTileFloor.Name = "radioButtonTileFloor";
            this.radioButtonTileFloor.Size = new System.Drawing.Size(48, 17);
            this.radioButtonTileFloor.TabIndex = 4;
            this.radioButtonTileFloor.TabStop = true;
            this.radioButtonTileFloor.Text = "Floor";
            this.radioButtonTileFloor.UseVisualStyleBackColor = false;
            // 
            // buttonFinish
            // 
            this.buttonFinish.Location = new System.Drawing.Point(17, 399);
            this.buttonFinish.Name = "buttonFinish";
            this.buttonFinish.Size = new System.Drawing.Size(75, 23);
            this.buttonFinish.TabIndex = 12;
            this.buttonFinish.Text = "Finish";
            this.buttonFinish.UseVisualStyleBackColor = true;
            this.buttonFinish.Click += new System.EventHandler(this.buttonFinish_Click);
            // 
            // buttonBack
            // 
            this.buttonBack.Location = new System.Drawing.Point(98, 399);
            this.buttonBack.Name = "buttonBack";
            this.buttonBack.Size = new System.Drawing.Size(75, 23);
            this.buttonBack.TabIndex = 11;
            this.buttonBack.Text = "Back";
            this.buttonBack.UseVisualStyleBackColor = true;
            this.buttonBack.Click += new System.EventHandler(this.buttonBack_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(179, 399);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 13;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // picturePanelTilesetImage
            // 
            this.picturePanelTilesetImage.AutoScroll = true;
            this.picturePanelTilesetImage.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.picturePanelTilesetImage.Location = new System.Drawing.Point(213, 12);
            this.picturePanelTilesetImage.Name = "picturePanelTilesetImage";
            this.picturePanelTilesetImage.Size = new System.Drawing.Size(536, 375);
            this.picturePanelTilesetImage.TabIndex = 1;
            this.picturePanelTilesetImage.Click += new System.EventHandler(this.picturePanelTilesetImage_Click);
            // 
            // FormEditTileset
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(761, 434);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonFinish);
            this.Controls.Add(this.buttonBack);
            this.Controls.Add(this.groupBoxTileType);
            this.Controls.Add(this.trackBarZoom);
            this.Controls.Add(this.picturePanelTilesetImage);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormEditTileset";
            this.Text = "Edit Tileset";
            this.Load += new System.EventHandler(this.FormEditTileset_Load);
            ((System.ComponentModel.ISupportInitialize)(this.trackBarZoom)).EndInit();
            this.groupBoxTileType.ResumeLayout(false);
            this.groupBoxTileType.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private PicturePanel picturePanelTilesetImage;
        private System.Windows.Forms.TrackBar trackBarZoom;
        private System.Windows.Forms.GroupBox groupBoxTileType;
        private System.Windows.Forms.Button buttonFinish;
        private System.Windows.Forms.Button buttonBack;
        private System.Windows.Forms.RadioButton radioButtonTileAllEnd;
        private System.Windows.Forms.RadioButton radioButtonTileP4End;
        private System.Windows.Forms.RadioButton radioButtonTileP3End;
        private System.Windows.Forms.RadioButton radioButtonTileP2End;
        private System.Windows.Forms.RadioButton radioButtonTileP1End;
        private System.Windows.Forms.RadioButton radioButtonTileAllStart;
        private System.Windows.Forms.RadioButton radioButtonTileP4Start;
        private System.Windows.Forms.RadioButton radioButtonTileP3Start;
        private System.Windows.Forms.RadioButton radioButtonTileP2Start;
        private System.Windows.Forms.RadioButton radioButtonTileP1Start;
        private System.Windows.Forms.RadioButton radioButtonTileUnderfloor;
        private System.Windows.Forms.RadioButton radioButtonTileFloor;
        private System.Windows.Forms.RadioButton radioButtonTileWall;
        private System.Windows.Forms.RadioButton radioButtonTileVoid;
        private System.Windows.Forms.Button buttonCancel;
    }
}
namespace Hardy_Part___Map_Editor.Dialog_Boxes
{
    partial class FormLoadTileset
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
            this.groupBoxFrame = new System.Windows.Forms.GroupBox();
            this.textBoxImagePath = new System.Windows.Forms.TextBox();
            this.buttonImagePath = new System.Windows.Forms.Button();
            this.labelImagePath = new System.Windows.Forms.Label();
            this.labelFrameHeight = new System.Windows.Forms.Label();
            this.numericUpDownFrameWidth = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownFrameHeight = new System.Windows.Forms.NumericUpDown();
            this.labelFrameWidth = new System.Windows.Forms.Label();
            this.buttonLoad = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.pictureBoxImagrPreview = new System.Windows.Forms.PictureBox();
            this.labelImageError = new System.Windows.Forms.Label();
            this.groupBoxFrame.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFrameWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFrameHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxImagrPreview)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxFrame
            // 
            this.groupBoxFrame.Controls.Add(this.textBoxImagePath);
            this.groupBoxFrame.Controls.Add(this.buttonImagePath);
            this.groupBoxFrame.Controls.Add(this.labelImagePath);
            this.groupBoxFrame.Controls.Add(this.labelFrameHeight);
            this.groupBoxFrame.Controls.Add(this.numericUpDownFrameWidth);
            this.groupBoxFrame.Controls.Add(this.numericUpDownFrameHeight);
            this.groupBoxFrame.Controls.Add(this.labelFrameWidth);
            this.groupBoxFrame.Location = new System.Drawing.Point(12, 12);
            this.groupBoxFrame.Name = "groupBoxFrame";
            this.groupBoxFrame.Size = new System.Drawing.Size(260, 131);
            this.groupBoxFrame.TabIndex = 6;
            this.groupBoxFrame.TabStop = false;
            this.groupBoxFrame.Text = "Tileset";
            // 
            // textBoxImagePath
            // 
            this.textBoxImagePath.Location = new System.Drawing.Point(79, 25);
            this.textBoxImagePath.Name = "textBoxImagePath";
            this.textBoxImagePath.ReadOnly = true;
            this.textBoxImagePath.Size = new System.Drawing.Size(145, 20);
            this.textBoxImagePath.TabIndex = 7;
            // 
            // buttonImagePath
            // 
            this.buttonImagePath.Location = new System.Drawing.Point(230, 23);
            this.buttonImagePath.Name = "buttonImagePath";
            this.buttonImagePath.Size = new System.Drawing.Size(24, 23);
            this.buttonImagePath.TabIndex = 6;
            this.buttonImagePath.Text = "...";
            this.buttonImagePath.UseVisualStyleBackColor = true;
            this.buttonImagePath.Click += new System.EventHandler(this.buttonImagePath_Click);
            // 
            // labelImagePath
            // 
            this.labelImagePath.AutoSize = true;
            this.labelImagePath.Location = new System.Drawing.Point(6, 28);
            this.labelImagePath.Name = "labelImagePath";
            this.labelImagePath.Size = new System.Drawing.Size(61, 13);
            this.labelImagePath.TabIndex = 5;
            this.labelImagePath.Text = "Image Path";
            // 
            // labelFrameHeight
            // 
            this.labelFrameHeight.AutoSize = true;
            this.labelFrameHeight.Location = new System.Drawing.Point(6, 100);
            this.labelFrameHeight.Name = "labelFrameHeight";
            this.labelFrameHeight.Size = new System.Drawing.Size(70, 13);
            this.labelFrameHeight.TabIndex = 4;
            this.labelFrameHeight.Text = "Frame Height";
            // 
            // numericUpDownFrameWidth
            // 
            this.numericUpDownFrameWidth.Location = new System.Drawing.Point(79, 72);
            this.numericUpDownFrameWidth.Maximum = new decimal(new int[] {
            16384,
            0,
            0,
            0});
            this.numericUpDownFrameWidth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownFrameWidth.Name = "numericUpDownFrameWidth";
            this.numericUpDownFrameWidth.Size = new System.Drawing.Size(175, 20);
            this.numericUpDownFrameWidth.TabIndex = 0;
            this.numericUpDownFrameWidth.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numericUpDownFrameHeight
            // 
            this.numericUpDownFrameHeight.Location = new System.Drawing.Point(79, 98);
            this.numericUpDownFrameHeight.Maximum = new decimal(new int[] {
            16384,
            0,
            0,
            0});
            this.numericUpDownFrameHeight.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownFrameHeight.Name = "numericUpDownFrameHeight";
            this.numericUpDownFrameHeight.Size = new System.Drawing.Size(175, 20);
            this.numericUpDownFrameHeight.TabIndex = 3;
            this.numericUpDownFrameHeight.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // labelFrameWidth
            // 
            this.labelFrameWidth.AutoSize = true;
            this.labelFrameWidth.Location = new System.Drawing.Point(6, 74);
            this.labelFrameWidth.Name = "labelFrameWidth";
            this.labelFrameWidth.Size = new System.Drawing.Size(67, 13);
            this.labelFrameWidth.TabIndex = 1;
            this.labelFrameWidth.Text = "Frame Width";
            // 
            // buttonLoad
            // 
            this.buttonLoad.Enabled = false;
            this.buttonLoad.Location = new System.Drawing.Point(116, 149);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(75, 23);
            this.buttonLoad.TabIndex = 12;
            this.buttonLoad.Text = "Load";
            this.buttonLoad.UseVisualStyleBackColor = true;
            this.buttonLoad.Click += new System.EventHandler(this.buttonLoad_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(197, 149);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 11;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // pictureBoxImagrPreview
            // 
            this.pictureBoxImagrPreview.Location = new System.Drawing.Point(278, 13);
            this.pictureBoxImagrPreview.Name = "pictureBoxImagrPreview";
            this.pictureBoxImagrPreview.Size = new System.Drawing.Size(222, 160);
            this.pictureBoxImagrPreview.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.pictureBoxImagrPreview.TabIndex = 13;
            this.pictureBoxImagrPreview.TabStop = false;
            // 
            // labelImageError
            // 
            this.labelImageError.AutoSize = true;
            this.labelImageError.Location = new System.Drawing.Point(341, 86);
            this.labelImageError.Name = "labelImageError";
            this.labelImageError.Size = new System.Drawing.Size(0, 13);
            this.labelImageError.TabIndex = 14;
            // 
            // FormLoadTileset
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(512, 185);
            this.Controls.Add(this.labelImageError);
            this.Controls.Add(this.buttonLoad);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.groupBoxFrame);
            this.Controls.Add(this.pictureBoxImagrPreview);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormLoadTileset";
            this.Text = "Load Tileset";
            this.groupBoxFrame.ResumeLayout(false);
            this.groupBoxFrame.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFrameWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFrameHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxImagrPreview)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxFrame;
        private System.Windows.Forms.TextBox textBoxImagePath;
        private System.Windows.Forms.Button buttonImagePath;
        private System.Windows.Forms.Label labelImagePath;
        private System.Windows.Forms.Label labelFrameHeight;
        private System.Windows.Forms.NumericUpDown numericUpDownFrameWidth;
        private System.Windows.Forms.NumericUpDown numericUpDownFrameHeight;
        private System.Windows.Forms.Label labelFrameWidth;
        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.PictureBox pictureBoxImagrPreview;
        private System.Windows.Forms.Label labelImageError;
    }
}
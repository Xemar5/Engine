namespace Hardy_Part___Map_Editor
{
    partial class FormNewMap
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.checkBoxFrameSizeFixed = new System.Windows.Forms.CheckBox();
            this.labelMapSize = new System.Windows.Forms.Label();
            this.labelMultiplier = new System.Windows.Forms.Label();
            this.labelFramwHeight = new System.Windows.Forms.Label();
            this.numericUpDownFrameWidth = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownFrameHeight = new System.Windows.Forms.NumericUpDown();
            this.labelFramwWidth = new System.Windows.Forms.Label();
            this.textBoxName = new System.Windows.Forms.TextBox();
            this.labelName = new System.Windows.Forms.Label();
            this.labelMapSizeReminder = new System.Windows.Forms.Label();
            this.labelMapHeight = new System.Windows.Forms.Label();
            this.numericUpDownMapWidth = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownMapHeight = new System.Windows.Forms.NumericUpDown();
            this.labelMapWidth = new System.Windows.Forms.Label();
            this.buttonMapCancel = new System.Windows.Forms.Button();
            this.buttonMapCreate = new System.Windows.Forms.Button();
            this.numericUpDownMapScale = new System.Windows.Forms.NumericUpDown();
            this.labelMapScale = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFrameWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFrameHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapScale)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.labelMapScale);
            this.groupBox1.Controls.Add(this.numericUpDownMapScale);
            this.groupBox1.Controls.Add(this.checkBoxFrameSizeFixed);
            this.groupBox1.Controls.Add(this.labelMapSize);
            this.groupBox1.Controls.Add(this.labelMultiplier);
            this.groupBox1.Controls.Add(this.labelFramwHeight);
            this.groupBox1.Controls.Add(this.numericUpDownFrameWidth);
            this.groupBox1.Controls.Add(this.numericUpDownFrameHeight);
            this.groupBox1.Controls.Add(this.labelFramwWidth);
            this.groupBox1.Controls.Add(this.textBoxName);
            this.groupBox1.Controls.Add(this.labelName);
            this.groupBox1.Controls.Add(this.labelMapSizeReminder);
            this.groupBox1.Controls.Add(this.labelMapHeight);
            this.groupBox1.Controls.Add(this.numericUpDownMapWidth);
            this.groupBox1.Controls.Add(this.numericUpDownMapHeight);
            this.groupBox1.Controls.Add(this.labelMapWidth);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(260, 159);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Map";
            // 
            // checkBoxFrameSizeFixed
            // 
            this.checkBoxFrameSizeFixed.AutoSize = true;
            this.checkBoxFrameSizeFixed.Checked = true;
            this.checkBoxFrameSizeFixed.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxFrameSizeFixed.Location = new System.Drawing.Point(175, 130);
            this.checkBoxFrameSizeFixed.Name = "checkBoxFrameSizeFixed";
            this.checkBoxFrameSizeFixed.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.checkBoxFrameSizeFixed.Size = new System.Drawing.Size(51, 17);
            this.checkBoxFrameSizeFixed.TabIndex = 13;
            this.checkBoxFrameSizeFixed.Text = "Fixed";
            this.checkBoxFrameSizeFixed.UseVisualStyleBackColor = true;
            this.checkBoxFrameSizeFixed.CheckedChanged += new System.EventHandler(this.checkBoxFrameSizeFixed_CheckedChanged);
            // 
            // labelMapSize
            // 
            this.labelMapSize.AutoSize = true;
            this.labelMapSize.Location = new System.Drawing.Point(33, 56);
            this.labelMapSize.Name = "labelMapSize";
            this.labelMapSize.Size = new System.Drawing.Size(57, 13);
            this.labelMapSize.TabIndex = 12;
            this.labelMapSize.Text = "(Map Size)";
            // 
            // labelMultiplier
            // 
            this.labelMultiplier.AutoSize = true;
            this.labelMultiplier.Location = new System.Drawing.Point(121, 86);
            this.labelMultiplier.Name = "labelMultiplier";
            this.labelMultiplier.Size = new System.Drawing.Size(12, 13);
            this.labelMultiplier.TabIndex = 11;
            this.labelMultiplier.Text = "x";
            // 
            // labelFramwHeight
            // 
            this.labelFramwHeight.AutoSize = true;
            this.labelFramwHeight.Enabled = false;
            this.labelFramwHeight.Location = new System.Drawing.Point(146, 102);
            this.labelFramwHeight.Name = "labelFramwHeight";
            this.labelFramwHeight.Size = new System.Drawing.Size(38, 13);
            this.labelFramwHeight.TabIndex = 10;
            this.labelFramwHeight.Text = "Height";
            // 
            // numericUpDownFrameWidth
            // 
            this.numericUpDownFrameWidth.Location = new System.Drawing.Point(190, 74);
            this.numericUpDownFrameWidth.Maximum = new decimal(new int[] {
            4096,
            0,
            0,
            0});
            this.numericUpDownFrameWidth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownFrameWidth.Name = "numericUpDownFrameWidth";
            this.numericUpDownFrameWidth.Size = new System.Drawing.Size(64, 20);
            this.numericUpDownFrameWidth.TabIndex = 7;
            this.numericUpDownFrameWidth.Value = new decimal(new int[] {
            24,
            0,
            0,
            0});
            this.numericUpDownFrameWidth.ValueChanged += new System.EventHandler(this.numericUpDownFrameWidth_ValueChanged);
            // 
            // numericUpDownFrameHeight
            // 
            this.numericUpDownFrameHeight.Enabled = false;
            this.numericUpDownFrameHeight.Location = new System.Drawing.Point(190, 100);
            this.numericUpDownFrameHeight.Maximum = new decimal(new int[] {
            4096,
            0,
            0,
            0});
            this.numericUpDownFrameHeight.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownFrameHeight.Name = "numericUpDownFrameHeight";
            this.numericUpDownFrameHeight.Size = new System.Drawing.Size(64, 20);
            this.numericUpDownFrameHeight.TabIndex = 8;
            this.numericUpDownFrameHeight.Value = new decimal(new int[] {
            24,
            0,
            0,
            0});
            // 
            // labelFramwWidth
            // 
            this.labelFramwWidth.AutoSize = true;
            this.labelFramwWidth.Location = new System.Drawing.Point(146, 76);
            this.labelFramwWidth.Name = "labelFramwWidth";
            this.labelFramwWidth.Size = new System.Drawing.Size(35, 13);
            this.labelFramwWidth.TabIndex = 9;
            this.labelFramwWidth.Text = "Width";
            // 
            // textBoxName
            // 
            this.textBoxName.Location = new System.Drawing.Point(47, 25);
            this.textBoxName.MaxLength = 20;
            this.textBoxName.Name = "textBoxName";
            this.textBoxName.Size = new System.Drawing.Size(207, 20);
            this.textBoxName.TabIndex = 0;
            this.textBoxName.Text = "map0";
            this.textBoxName.TextChanged += new System.EventHandler(this.textBoxName_TextChanged);
            // 
            // labelName
            // 
            this.labelName.AutoSize = true;
            this.labelName.Location = new System.Drawing.Point(6, 28);
            this.labelName.Name = "labelName";
            this.labelName.Size = new System.Drawing.Size(35, 13);
            this.labelName.TabIndex = 6;
            this.labelName.Text = "Name";
            // 
            // labelMapSizeReminder
            // 
            this.labelMapSizeReminder.AutoSize = true;
            this.labelMapSizeReminder.Location = new System.Drawing.Point(174, 58);
            this.labelMapSizeReminder.Name = "labelMapSizeReminder";
            this.labelMapSizeReminder.Size = new System.Drawing.Size(54, 13);
            this.labelMapSizeReminder.TabIndex = 5;
            this.labelMapSizeReminder.Text = "(Multiplier)";
            // 
            // labelMapHeight
            // 
            this.labelMapHeight.AutoSize = true;
            this.labelMapHeight.Location = new System.Drawing.Point(6, 100);
            this.labelMapHeight.Name = "labelMapHeight";
            this.labelMapHeight.Size = new System.Drawing.Size(38, 13);
            this.labelMapHeight.TabIndex = 4;
            this.labelMapHeight.Text = "Height";
            // 
            // numericUpDownMapWidth
            // 
            this.numericUpDownMapWidth.Location = new System.Drawing.Point(50, 72);
            this.numericUpDownMapWidth.Maximum = new decimal(new int[] {
            4096,
            0,
            0,
            0});
            this.numericUpDownMapWidth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownMapWidth.Name = "numericUpDownMapWidth";
            this.numericUpDownMapWidth.Size = new System.Drawing.Size(64, 20);
            this.numericUpDownMapWidth.TabIndex = 1;
            this.numericUpDownMapWidth.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numericUpDownMapWidth.Enter += new System.EventHandler(this.numericUpDownMapWidth_Enter);
            // 
            // numericUpDownMapHeight
            // 
            this.numericUpDownMapHeight.Location = new System.Drawing.Point(50, 98);
            this.numericUpDownMapHeight.Maximum = new decimal(new int[] {
            4096,
            0,
            0,
            0});
            this.numericUpDownMapHeight.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownMapHeight.Name = "numericUpDownMapHeight";
            this.numericUpDownMapHeight.Size = new System.Drawing.Size(64, 20);
            this.numericUpDownMapHeight.TabIndex = 2;
            this.numericUpDownMapHeight.Value = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.numericUpDownMapHeight.Enter += new System.EventHandler(this.numericUpDownMapHeight_Enter);
            // 
            // labelMapWidth
            // 
            this.labelMapWidth.AutoSize = true;
            this.labelMapWidth.Location = new System.Drawing.Point(6, 74);
            this.labelMapWidth.Name = "labelMapWidth";
            this.labelMapWidth.Size = new System.Drawing.Size(35, 13);
            this.labelMapWidth.TabIndex = 3;
            this.labelMapWidth.Text = "Width";
            // 
            // buttonMapCancel
            // 
            this.buttonMapCancel.Location = new System.Drawing.Point(199, 177);
            this.buttonMapCancel.Name = "buttonMapCancel";
            this.buttonMapCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonMapCancel.TabIndex = 9;
            this.buttonMapCancel.Text = "Cancel";
            this.buttonMapCancel.UseVisualStyleBackColor = true;
            this.buttonMapCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // buttonMapCreate
            // 
            this.buttonMapCreate.Location = new System.Drawing.Point(118, 177);
            this.buttonMapCreate.Name = "buttonMapCreate";
            this.buttonMapCreate.Size = new System.Drawing.Size(75, 23);
            this.buttonMapCreate.TabIndex = 10;
            this.buttonMapCreate.Text = "Create";
            this.buttonMapCreate.UseVisualStyleBackColor = true;
            this.buttonMapCreate.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // numericUpDownMapScale
            // 
            this.numericUpDownMapScale.DecimalPlaces = 1;
            this.numericUpDownMapScale.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDownMapScale.Location = new System.Drawing.Point(62, 129);
            this.numericUpDownMapScale.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numericUpDownMapScale.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDownMapScale.Name = "numericUpDownMapScale";
            this.numericUpDownMapScale.Size = new System.Drawing.Size(40, 20);
            this.numericUpDownMapScale.TabIndex = 14;
            this.numericUpDownMapScale.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            // 
            // labelMapScale
            // 
            this.labelMapScale.AutoSize = true;
            this.labelMapScale.Location = new System.Drawing.Point(18, 131);
            this.labelMapScale.Name = "labelMapScale";
            this.labelMapScale.Size = new System.Drawing.Size(34, 13);
            this.labelMapScale.TabIndex = 15;
            this.labelMapScale.Text = "Scale";
            // 
            // FormNewMap
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 212);
            this.Controls.Add(this.buttonMapCreate);
            this.Controls.Add(this.buttonMapCancel);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormNewMap";
            this.Text = "Create New Map";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFrameWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownFrameHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapScale)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label labelMapSizeReminder;
        private System.Windows.Forms.Label labelMapHeight;
        private System.Windows.Forms.NumericUpDown numericUpDownMapWidth;
        private System.Windows.Forms.NumericUpDown numericUpDownMapHeight;
        private System.Windows.Forms.Label labelMapWidth;
        private System.Windows.Forms.Button buttonMapCancel;
        private System.Windows.Forms.Button buttonMapCreate;
        private System.Windows.Forms.TextBox textBoxName;
        private System.Windows.Forms.Label labelName;
        private System.Windows.Forms.Label labelFramwHeight;
        private System.Windows.Forms.NumericUpDown numericUpDownFrameWidth;
        private System.Windows.Forms.NumericUpDown numericUpDownFrameHeight;
        private System.Windows.Forms.Label labelFramwWidth;
        private System.Windows.Forms.Label labelMultiplier;
        private System.Windows.Forms.CheckBox checkBoxFrameSizeFixed;
        private System.Windows.Forms.Label labelMapSize;
        private System.Windows.Forms.Label labelMapScale;
        private System.Windows.Forms.NumericUpDown numericUpDownMapScale;
    }
}
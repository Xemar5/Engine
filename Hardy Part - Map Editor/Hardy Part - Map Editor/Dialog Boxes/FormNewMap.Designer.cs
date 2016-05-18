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
            this.labelMapSizeReminder = new System.Windows.Forms.Label();
            this.labelMapHeight = new System.Windows.Forms.Label();
            this.numericUpDownMapWidth = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownMapHeight = new System.Windows.Forms.NumericUpDown();
            this.labelMapWidth = new System.Windows.Forms.Label();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonOK = new System.Windows.Forms.Button();
            this.labelName = new System.Windows.Forms.Label();
            this.textBoxName = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapHeight)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBoxName);
            this.groupBox1.Controls.Add(this.labelName);
            this.groupBox1.Controls.Add(this.labelMapSizeReminder);
            this.groupBox1.Controls.Add(this.labelMapHeight);
            this.groupBox1.Controls.Add(this.numericUpDownMapWidth);
            this.groupBox1.Controls.Add(this.numericUpDownMapHeight);
            this.groupBox1.Controls.Add(this.labelMapWidth);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(260, 146);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Map";
            // 
            // labelMapSizeReminder
            // 
            this.labelMapSizeReminder.AutoSize = true;
            this.labelMapSizeReminder.Location = new System.Drawing.Point(103, 121);
            this.labelMapSizeReminder.Name = "labelMapSizeReminder";
            this.labelMapSizeReminder.Size = new System.Drawing.Size(42, 13);
            this.labelMapSizeReminder.TabIndex = 5;
            this.labelMapSizeReminder.Text = "(in tiles)";
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
            this.numericUpDownMapWidth.Location = new System.Drawing.Point(79, 72);
            this.numericUpDownMapWidth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownMapWidth.Name = "numericUpDownMapWidth";
            this.numericUpDownMapWidth.Size = new System.Drawing.Size(175, 20);
            this.numericUpDownMapWidth.TabIndex = 0;
            this.numericUpDownMapWidth.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // numericUpDownMapHeight
            // 
            this.numericUpDownMapHeight.Location = new System.Drawing.Point(79, 98);
            this.numericUpDownMapHeight.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownMapHeight.Name = "numericUpDownMapHeight";
            this.numericUpDownMapHeight.Size = new System.Drawing.Size(175, 20);
            this.numericUpDownMapHeight.TabIndex = 3;
            this.numericUpDownMapHeight.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // labelMapWidth
            // 
            this.labelMapWidth.AutoSize = true;
            this.labelMapWidth.Location = new System.Drawing.Point(6, 74);
            this.labelMapWidth.Name = "labelMapWidth";
            this.labelMapWidth.Size = new System.Drawing.Size(35, 13);
            this.labelMapWidth.TabIndex = 1;
            this.labelMapWidth.Text = "Width";
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(197, 164);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 9;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(116, 164);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 10;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
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
            // textBoxName
            // 
            this.textBoxName.Location = new System.Drawing.Point(79, 25);
            this.textBoxName.MaxLength = 20;
            this.textBoxName.Name = "textBoxName";
            this.textBoxName.Size = new System.Drawing.Size(175, 20);
            this.textBoxName.TabIndex = 7;
            // 
            // FormNewMap
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 195);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FormNewMap";
            this.Text = "Create New Map";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapHeight)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label labelMapSizeReminder;
        private System.Windows.Forms.Label labelMapHeight;
        private System.Windows.Forms.NumericUpDown numericUpDownMapWidth;
        private System.Windows.Forms.NumericUpDown numericUpDownMapHeight;
        private System.Windows.Forms.Label labelMapWidth;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.TextBox textBoxName;
        private System.Windows.Forms.Label labelName;
    }
}
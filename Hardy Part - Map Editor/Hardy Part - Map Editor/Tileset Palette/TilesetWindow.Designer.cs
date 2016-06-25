namespace Hardy_Part___Map_Editor.Tileset_Palette
{
    partial class TilesetWindow
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
            this.buttonImportTileset = new System.Windows.Forms.Button();
            this.flowLayoutPanelTilesetsPresets = new System.Windows.Forms.FlowLayoutPanel();
            this.groupBoxTilesetPresets = new System.Windows.Forms.GroupBox();
            this.buttonAddTileset = new System.Windows.Forms.Button();
            this.groupBoxTilesetObject = new System.Windows.Forms.GroupBox();
            this.checkBoxTilesetVisible = new System.Windows.Forms.CheckBox();
            this.labelTilesetLayer = new System.Windows.Forms.Label();
            this.numericUpDownTilesetLayer = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownTilesetScale = new System.Windows.Forms.NumericUpDown();
            this.textBoxTilesetName = new System.Windows.Forms.TextBox();
            this.labelTilesetName = new System.Windows.Forms.Label();
            this.labelTilesetY = new System.Windows.Forms.Label();
            this.numericUpDownTilesetY = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownTilesetX = new System.Windows.Forms.NumericUpDown();
            this.labelTilesetX = new System.Windows.Forms.Label();
            this.labelSelectedPreset = new System.Windows.Forms.Label();
            this.comboBoxSelectedPreset = new System.Windows.Forms.ComboBox();
            this.labelScale = new System.Windows.Forms.Label();
            this.checkBoxShowGrid = new System.Windows.Forms.CheckBox();
            this.buttonRemoveTileset = new System.Windows.Forms.Button();
            this.existingTilesetList = new Hardy_Part___Map_Editor.Tileset_Palette.ExistingTilesetList();
            this.groupBoxTilesetPresets.SuspendLayout();
            this.groupBoxTilesetObject.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTilesetLayer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTilesetScale)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTilesetY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTilesetX)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonImportTileset
            // 
            this.buttonImportTileset.Location = new System.Drawing.Point(10, 184);
            this.buttonImportTileset.Name = "buttonImportTileset";
            this.buttonImportTileset.Size = new System.Drawing.Size(90, 23);
            this.buttonImportTileset.TabIndex = 0;
            this.buttonImportTileset.Text = "Import Tileset";
            this.buttonImportTileset.UseVisualStyleBackColor = true;
            this.buttonImportTileset.Click += new System.EventHandler(this.buttonImportTileset_Click);
            // 
            // flowLayoutPanelTilesetsPresets
            // 
            this.flowLayoutPanelTilesetsPresets.AutoScroll = true;
            this.flowLayoutPanelTilesetsPresets.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.flowLayoutPanelTilesetsPresets.Location = new System.Drawing.Point(6, 19);
            this.flowLayoutPanelTilesetsPresets.Name = "flowLayoutPanelTilesetsPresets";
            this.flowLayoutPanelTilesetsPresets.Padding = new System.Windows.Forms.Padding(5);
            this.flowLayoutPanelTilesetsPresets.Size = new System.Drawing.Size(317, 432);
            this.flowLayoutPanelTilesetsPresets.TabIndex = 1;
            this.flowLayoutPanelTilesetsPresets.WrapContents = false;
            // 
            // groupBoxTilesetPresets
            // 
            this.groupBoxTilesetPresets.Controls.Add(this.flowLayoutPanelTilesetsPresets);
            this.groupBoxTilesetPresets.Location = new System.Drawing.Point(4, 213);
            this.groupBoxTilesetPresets.Name = "groupBoxTilesetPresets";
            this.groupBoxTilesetPresets.Size = new System.Drawing.Size(329, 457);
            this.groupBoxTilesetPresets.TabIndex = 2;
            this.groupBoxTilesetPresets.TabStop = false;
            this.groupBoxTilesetPresets.Text = "Presets";
            // 
            // buttonAddTileset
            // 
            this.buttonAddTileset.Enabled = false;
            this.buttonAddTileset.Location = new System.Drawing.Point(223, 8);
            this.buttonAddTileset.Name = "buttonAddTileset";
            this.buttonAddTileset.Size = new System.Drawing.Size(53, 23);
            this.buttonAddTileset.TabIndex = 3;
            this.buttonAddTileset.Text = "New";
            this.buttonAddTileset.UseVisualStyleBackColor = true;
            this.buttonAddTileset.Click += new System.EventHandler(this.buttonAddTileset_Click);
            // 
            // groupBoxTilesetObject
            // 
            this.groupBoxTilesetObject.Controls.Add(this.checkBoxTilesetVisible);
            this.groupBoxTilesetObject.Controls.Add(this.labelTilesetLayer);
            this.groupBoxTilesetObject.Controls.Add(this.numericUpDownTilesetLayer);
            this.groupBoxTilesetObject.Controls.Add(this.numericUpDownTilesetScale);
            this.groupBoxTilesetObject.Controls.Add(this.textBoxTilesetName);
            this.groupBoxTilesetObject.Controls.Add(this.labelTilesetName);
            this.groupBoxTilesetObject.Controls.Add(this.labelTilesetY);
            this.groupBoxTilesetObject.Controls.Add(this.numericUpDownTilesetY);
            this.groupBoxTilesetObject.Controls.Add(this.numericUpDownTilesetX);
            this.groupBoxTilesetObject.Controls.Add(this.labelTilesetX);
            this.groupBoxTilesetObject.Controls.Add(this.labelSelectedPreset);
            this.groupBoxTilesetObject.Controls.Add(this.comboBoxSelectedPreset);
            this.groupBoxTilesetObject.Controls.Add(this.labelScale);
            this.groupBoxTilesetObject.Enabled = false;
            this.groupBoxTilesetObject.Location = new System.Drawing.Point(172, 37);
            this.groupBoxTilesetObject.Name = "groupBoxTilesetObject";
            this.groupBoxTilesetObject.Size = new System.Drawing.Size(161, 140);
            this.groupBoxTilesetObject.TabIndex = 4;
            this.groupBoxTilesetObject.TabStop = false;
            this.groupBoxTilesetObject.Text = "Current Tileset";
            // 
            // checkBoxTilesetVisible
            // 
            this.checkBoxTilesetVisible.AutoSize = true;
            this.checkBoxTilesetVisible.Checked = true;
            this.checkBoxTilesetVisible.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxTilesetVisible.Location = new System.Drawing.Point(101, 75);
            this.checkBoxTilesetVisible.Name = "checkBoxTilesetVisible";
            this.checkBoxTilesetVisible.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.checkBoxTilesetVisible.Size = new System.Drawing.Size(56, 17);
            this.checkBoxTilesetVisible.TabIndex = 15;
            this.checkBoxTilesetVisible.Text = "Visible";
            this.checkBoxTilesetVisible.UseVisualStyleBackColor = true;
            this.checkBoxTilesetVisible.CheckedChanged += new System.EventHandler(this.checkBoxTilesetVisible_CheckedChanged);
            // 
            // labelTilesetLayer
            // 
            this.labelTilesetLayer.AutoSize = true;
            this.labelTilesetLayer.Location = new System.Drawing.Point(14, 76);
            this.labelTilesetLayer.Name = "labelTilesetLayer";
            this.labelTilesetLayer.Size = new System.Drawing.Size(33, 13);
            this.labelTilesetLayer.TabIndex = 14;
            this.labelTilesetLayer.Text = "Layer";
            // 
            // numericUpDownTilesetLayer
            // 
            this.numericUpDownTilesetLayer.Location = new System.Drawing.Point(53, 74);
            this.numericUpDownTilesetLayer.Name = "numericUpDownTilesetLayer";
            this.numericUpDownTilesetLayer.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownTilesetLayer.TabIndex = 13;
            this.numericUpDownTilesetLayer.ValueChanged += new System.EventHandler(this.numericUpDownTilesetLayer_ValueChanged);
            // 
            // numericUpDownTilesetScale
            // 
            this.numericUpDownTilesetScale.DecimalPlaces = 1;
            this.numericUpDownTilesetScale.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDownTilesetScale.Location = new System.Drawing.Point(110, 113);
            this.numericUpDownTilesetScale.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numericUpDownTilesetScale.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDownTilesetScale.Name = "numericUpDownTilesetScale";
            this.numericUpDownTilesetScale.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownTilesetScale.TabIndex = 10;
            this.numericUpDownTilesetScale.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownTilesetScale.ValueChanged += new System.EventHandler(this.numericUpDownTilesetScale_ValueChanged);
            // 
            // textBoxTilesetName
            // 
            this.textBoxTilesetName.Location = new System.Drawing.Point(53, 21);
            this.textBoxTilesetName.Name = "textBoxTilesetName";
            this.textBoxTilesetName.Size = new System.Drawing.Size(102, 20);
            this.textBoxTilesetName.TabIndex = 9;
            this.textBoxTilesetName.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxTilesetName_KeyPress);
            this.textBoxTilesetName.Leave += new System.EventHandler(this.textBoxTilesetName_Leave);
            // 
            // labelTilesetName
            // 
            this.labelTilesetName.AutoSize = true;
            this.labelTilesetName.Location = new System.Drawing.Point(12, 24);
            this.labelTilesetName.Name = "labelTilesetName";
            this.labelTilesetName.Size = new System.Drawing.Size(35, 13);
            this.labelTilesetName.TabIndex = 8;
            this.labelTilesetName.Text = "Name";
            // 
            // labelTilesetY
            // 
            this.labelTilesetY.AutoSize = true;
            this.labelTilesetY.Location = new System.Drawing.Point(73, 97);
            this.labelTilesetY.Name = "labelTilesetY";
            this.labelTilesetY.Size = new System.Drawing.Size(14, 13);
            this.labelTilesetY.TabIndex = 7;
            this.labelTilesetY.Text = "Y";
            // 
            // numericUpDownTilesetY
            // 
            this.numericUpDownTilesetY.Location = new System.Drawing.Point(59, 113);
            this.numericUpDownTilesetY.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numericUpDownTilesetY.Name = "numericUpDownTilesetY";
            this.numericUpDownTilesetY.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownTilesetY.TabIndex = 5;
            this.numericUpDownTilesetY.ValueChanged += new System.EventHandler(this.numericUpDownTilesetY_ValueChanged);
            // 
            // numericUpDownTilesetX
            // 
            this.numericUpDownTilesetX.Location = new System.Drawing.Point(8, 113);
            this.numericUpDownTilesetX.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numericUpDownTilesetX.Name = "numericUpDownTilesetX";
            this.numericUpDownTilesetX.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownTilesetX.TabIndex = 4;
            this.numericUpDownTilesetX.ValueChanged += new System.EventHandler(this.numericUpDownTilesetX_ValueChanged);
            // 
            // labelTilesetX
            // 
            this.labelTilesetX.AutoSize = true;
            this.labelTilesetX.Location = new System.Drawing.Point(22, 97);
            this.labelTilesetX.Name = "labelTilesetX";
            this.labelTilesetX.Size = new System.Drawing.Size(14, 13);
            this.labelTilesetX.TabIndex = 6;
            this.labelTilesetX.Text = "X";
            // 
            // labelSelectedPreset
            // 
            this.labelSelectedPreset.AutoSize = true;
            this.labelSelectedPreset.Location = new System.Drawing.Point(10, 50);
            this.labelSelectedPreset.Name = "labelSelectedPreset";
            this.labelSelectedPreset.Size = new System.Drawing.Size(37, 13);
            this.labelSelectedPreset.TabIndex = 1;
            this.labelSelectedPreset.Text = "Preset";
            // 
            // comboBoxSelectedPreset
            // 
            this.comboBoxSelectedPreset.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxSelectedPreset.FormattingEnabled = true;
            this.comboBoxSelectedPreset.Location = new System.Drawing.Point(53, 47);
            this.comboBoxSelectedPreset.Name = "comboBoxSelectedPreset";
            this.comboBoxSelectedPreset.Size = new System.Drawing.Size(102, 21);
            this.comboBoxSelectedPreset.TabIndex = 0;
            this.comboBoxSelectedPreset.SelectedIndexChanged += new System.EventHandler(this.comboBoxSelectedPreset_SelectedIndexChanged);
            // 
            // labelScale
            // 
            this.labelScale.AutoSize = true;
            this.labelScale.Location = new System.Drawing.Point(114, 97);
            this.labelScale.Name = "labelScale";
            this.labelScale.Size = new System.Drawing.Size(34, 13);
            this.labelScale.TabIndex = 2;
            this.labelScale.Text = "Scale";
            // 
            // checkBoxShowGrid
            // 
            this.checkBoxShowGrid.AutoSize = true;
            this.checkBoxShowGrid.BackColor = System.Drawing.SystemColors.Control;
            this.checkBoxShowGrid.Checked = true;
            this.checkBoxShowGrid.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxShowGrid.ForeColor = System.Drawing.SystemColors.ControlText;
            this.checkBoxShowGrid.Location = new System.Drawing.Point(172, 12);
            this.checkBoxShowGrid.Name = "checkBoxShowGrid";
            this.checkBoxShowGrid.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.checkBoxShowGrid.Size = new System.Drawing.Size(45, 17);
            this.checkBoxShowGrid.TabIndex = 12;
            this.checkBoxShowGrid.Text = "Grid";
            this.checkBoxShowGrid.UseVisualStyleBackColor = false;
            this.checkBoxShowGrid.CheckedChanged += new System.EventHandler(this.checkBoxShowGrid_CheckedChanged);
            // 
            // buttonRemoveTileset
            // 
            this.buttonRemoveTileset.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(223)))), ((int)(((byte)(224)))));
            this.buttonRemoveTileset.Enabled = false;
            this.buttonRemoveTileset.Location = new System.Drawing.Point(282, 8);
            this.buttonRemoveTileset.Name = "buttonRemoveTileset";
            this.buttonRemoveTileset.Size = new System.Drawing.Size(51, 23);
            this.buttonRemoveTileset.TabIndex = 11;
            this.buttonRemoveTileset.Text = "Delete";
            this.buttonRemoveTileset.UseVisualStyleBackColor = false;
            this.buttonRemoveTileset.Click += new System.EventHandler(this.buttonRemoveTileset_Click);
            // 
            // existingTilesetList
            // 
            this.existingTilesetList.Enabled = false;
            this.existingTilesetList.Location = new System.Drawing.Point(4, 4);
            this.existingTilesetList.Name = "existingTilesetList";
            this.existingTilesetList.SelectedTileset = null;
            this.existingTilesetList.Size = new System.Drawing.Size(162, 173);
            this.existingTilesetList.TabIndex = 12;
            // 
            // TilesetWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.checkBoxShowGrid);
            this.Controls.Add(this.groupBoxTilesetObject);
            this.Controls.Add(this.buttonAddTileset);
            this.Controls.Add(this.existingTilesetList);
            this.Controls.Add(this.groupBoxTilesetPresets);
            this.Controls.Add(this.buttonImportTileset);
            this.Controls.Add(this.buttonRemoveTileset);
            this.Name = "TilesetWindow";
            this.Size = new System.Drawing.Size(336, 673);
            this.groupBoxTilesetPresets.ResumeLayout(false);
            this.groupBoxTilesetObject.ResumeLayout(false);
            this.groupBoxTilesetObject.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTilesetLayer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTilesetScale)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTilesetY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTilesetX)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonImportTileset;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanelTilesetsPresets;
        private System.Windows.Forms.GroupBox groupBoxTilesetPresets;
        private System.Windows.Forms.GroupBox groupBoxTilesetObject;
        private System.Windows.Forms.Label labelSelectedPreset;
        private System.Windows.Forms.Label labelScale;
        private System.Windows.Forms.Label labelTilesetY;
        private System.Windows.Forms.Label labelTilesetX;
        private System.Windows.Forms.NumericUpDown numericUpDownTilesetY;
        private System.Windows.Forms.NumericUpDown numericUpDownTilesetX;
        private System.Windows.Forms.TextBox textBoxTilesetName;
        private System.Windows.Forms.Label labelTilesetName;
        public System.Windows.Forms.ComboBox comboBoxSelectedPreset;
        private System.Windows.Forms.NumericUpDown numericUpDownTilesetScale;
        private System.Windows.Forms.Button buttonRemoveTileset;
        private System.Windows.Forms.NumericUpDown numericUpDownTilesetLayer;
        private System.Windows.Forms.Label labelTilesetLayer;
        public System.Windows.Forms.Button buttonAddTileset;
        public System.Windows.Forms.CheckBox checkBoxTilesetVisible;
        public ExistingTilesetList existingTilesetList;
        public System.Windows.Forms.CheckBox checkBoxShowGrid;
    }
}

namespace Hardy_Part___Map_Editor.Tileset_Palette
{
    partial class Palette
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
            this.labelTilesetY = new System.Windows.Forms.Label();
            this.numericUpDownTilesetY = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownTilesetX = new System.Windows.Forms.NumericUpDown();
            this.labelTilesetX = new System.Windows.Forms.Label();
            this.textBoxScale = new System.Windows.Forms.TextBox();
            this.labelSelectedPreset = new System.Windows.Forms.Label();
            this.comboBoxSelectedPreset = new System.Windows.Forms.ComboBox();
            this.labelScale = new System.Windows.Forms.Label();
            this.listBoxExistingTilesets = new System.Windows.Forms.ListBox();
            this.labelTilesetName = new System.Windows.Forms.Label();
            this.textBoxTilesetName = new System.Windows.Forms.TextBox();
            this.groupBoxTilesetPresets.SuspendLayout();
            this.groupBoxTilesetObject.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTilesetY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTilesetX)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonImportTileset
            // 
            this.buttonImportTileset.Location = new System.Drawing.Point(4, 4);
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
            this.flowLayoutPanelTilesetsPresets.Location = new System.Drawing.Point(2, 20);
            this.flowLayoutPanelTilesetsPresets.Name = "flowLayoutPanelTilesetsPresets";
            this.flowLayoutPanelTilesetsPresets.Padding = new System.Windows.Forms.Padding(5);
            this.flowLayoutPanelTilesetsPresets.Size = new System.Drawing.Size(328, 300);
            this.flowLayoutPanelTilesetsPresets.TabIndex = 1;
            this.flowLayoutPanelTilesetsPresets.WrapContents = false;
            // 
            // groupBoxTilesetPresets
            // 
            this.groupBoxTilesetPresets.Controls.Add(this.flowLayoutPanelTilesetsPresets);
            this.groupBoxTilesetPresets.Location = new System.Drawing.Point(2, 33);
            this.groupBoxTilesetPresets.Name = "groupBoxTilesetPresets";
            this.groupBoxTilesetPresets.Size = new System.Drawing.Size(332, 320);
            this.groupBoxTilesetPresets.TabIndex = 2;
            this.groupBoxTilesetPresets.TabStop = false;
            this.groupBoxTilesetPresets.Text = "Presets";
            // 
            // buttonAddTileset
            // 
            this.buttonAddTileset.Location = new System.Drawing.Point(100, 4);
            this.buttonAddTileset.Name = "buttonAddTileset";
            this.buttonAddTileset.Size = new System.Drawing.Size(75, 23);
            this.buttonAddTileset.TabIndex = 3;
            this.buttonAddTileset.Text = "Add Tileset";
            this.buttonAddTileset.UseVisualStyleBackColor = true;
            this.buttonAddTileset.Click += new System.EventHandler(this.buttonAddTileset_Click);
            // 
            // groupBoxTilesetObject
            // 
            this.groupBoxTilesetObject.Controls.Add(this.textBoxTilesetName);
            this.groupBoxTilesetObject.Controls.Add(this.labelTilesetName);
            this.groupBoxTilesetObject.Controls.Add(this.labelTilesetY);
            this.groupBoxTilesetObject.Controls.Add(this.numericUpDownTilesetY);
            this.groupBoxTilesetObject.Controls.Add(this.numericUpDownTilesetX);
            this.groupBoxTilesetObject.Controls.Add(this.labelTilesetX);
            this.groupBoxTilesetObject.Controls.Add(this.textBoxScale);
            this.groupBoxTilesetObject.Controls.Add(this.labelSelectedPreset);
            this.groupBoxTilesetObject.Controls.Add(this.comboBoxSelectedPreset);
            this.groupBoxTilesetObject.Controls.Add(this.labelScale);
            this.groupBoxTilesetObject.Enabled = false;
            this.groupBoxTilesetObject.Location = new System.Drawing.Point(171, 359);
            this.groupBoxTilesetObject.Name = "groupBoxTilesetObject";
            this.groupBoxTilesetObject.Size = new System.Drawing.Size(161, 303);
            this.groupBoxTilesetObject.TabIndex = 4;
            this.groupBoxTilesetObject.TabStop = false;
            this.groupBoxTilesetObject.Text = "Current Tileset - None";
            // 
            // labelTilesetY
            // 
            this.labelTilesetY.AutoSize = true;
            this.labelTilesetY.Location = new System.Drawing.Point(87, 89);
            this.labelTilesetY.Name = "labelTilesetY";
            this.labelTilesetY.Size = new System.Drawing.Size(14, 13);
            this.labelTilesetY.TabIndex = 7;
            this.labelTilesetY.Text = "Y";
            // 
            // numericUpDownTilesetY
            // 
            this.numericUpDownTilesetY.Location = new System.Drawing.Point(102, 87);
            this.numericUpDownTilesetY.Name = "numericUpDownTilesetY";
            this.numericUpDownTilesetY.Size = new System.Drawing.Size(54, 20);
            this.numericUpDownTilesetY.TabIndex = 5;
            // 
            // numericUpDownTilesetX
            // 
            this.numericUpDownTilesetX.Location = new System.Drawing.Point(24, 87);
            this.numericUpDownTilesetX.Name = "numericUpDownTilesetX";
            this.numericUpDownTilesetX.Size = new System.Drawing.Size(54, 20);
            this.numericUpDownTilesetX.TabIndex = 4;
            // 
            // labelTilesetX
            // 
            this.labelTilesetX.AutoSize = true;
            this.labelTilesetX.Location = new System.Drawing.Point(9, 89);
            this.labelTilesetX.Name = "labelTilesetX";
            this.labelTilesetX.Size = new System.Drawing.Size(14, 13);
            this.labelTilesetX.TabIndex = 6;
            this.labelTilesetX.Text = "X";
            // 
            // textBoxScale
            // 
            this.textBoxScale.Location = new System.Drawing.Point(114, 60);
            this.textBoxScale.Name = "textBoxScale";
            this.textBoxScale.Size = new System.Drawing.Size(42, 20);
            this.textBoxScale.TabIndex = 3;
            this.textBoxScale.Text = "1,0";
            this.textBoxScale.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxScale_KeyPress);
            this.textBoxScale.Leave += new System.EventHandler(this.textBoxScale_Leave);
            // 
            // labelSelectedPreset
            // 
            this.labelSelectedPreset.AutoSize = true;
            this.labelSelectedPreset.Location = new System.Drawing.Point(16, 44);
            this.labelSelectedPreset.Name = "labelSelectedPreset";
            this.labelSelectedPreset.Size = new System.Drawing.Size(82, 13);
            this.labelSelectedPreset.TabIndex = 1;
            this.labelSelectedPreset.Text = "Selected Preset";
            // 
            // comboBoxSelectedPreset
            // 
            this.comboBoxSelectedPreset.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxSelectedPreset.FormattingEnabled = true;
            this.comboBoxSelectedPreset.Location = new System.Drawing.Point(6, 60);
            this.comboBoxSelectedPreset.Name = "comboBoxSelectedPreset";
            this.comboBoxSelectedPreset.Size = new System.Drawing.Size(102, 21);
            this.comboBoxSelectedPreset.TabIndex = 0;
            this.comboBoxSelectedPreset.SelectedIndexChanged += new System.EventHandler(this.comboBoxSelectedPreset_SelectedIndexChanged);
            // 
            // labelScale
            // 
            this.labelScale.AutoSize = true;
            this.labelScale.Location = new System.Drawing.Point(118, 44);
            this.labelScale.Name = "labelScale";
            this.labelScale.Size = new System.Drawing.Size(34, 13);
            this.labelScale.TabIndex = 2;
            this.labelScale.Text = "Scale";
            // 
            // listBoxExistingTilesets
            // 
            this.listBoxExistingTilesets.FormattingEnabled = true;
            this.listBoxExistingTilesets.Location = new System.Drawing.Point(2, 359);
            this.listBoxExistingTilesets.Name = "listBoxExistingTilesets";
            this.listBoxExistingTilesets.Size = new System.Drawing.Size(162, 303);
            this.listBoxExistingTilesets.TabIndex = 5;
            this.listBoxExistingTilesets.SelectedIndexChanged += new System.EventHandler(this.listBoxExistingTilesets_SelectedIndexChanged);
            // 
            // labelTilesetName
            // 
            this.labelTilesetName.AutoSize = true;
            this.labelTilesetName.Location = new System.Drawing.Point(7, 24);
            this.labelTilesetName.Name = "labelTilesetName";
            this.labelTilesetName.Size = new System.Drawing.Size(35, 13);
            this.labelTilesetName.TabIndex = 8;
            this.labelTilesetName.Text = "Name";
            // 
            // textBoxTilesetName
            // 
            this.textBoxTilesetName.Location = new System.Drawing.Point(48, 21);
            this.textBoxTilesetName.Name = "textBoxTilesetName";
            this.textBoxTilesetName.Size = new System.Drawing.Size(108, 20);
            this.textBoxTilesetName.TabIndex = 9;
            this.textBoxTilesetName.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxTilesetName_KeyPress);
            this.textBoxTilesetName.Leave += new System.EventHandler(this.textBoxTilesetName_Leave);
            // 
            // Palette
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.listBoxExistingTilesets);
            this.Controls.Add(this.buttonAddTileset);
            this.Controls.Add(this.groupBoxTilesetObject);
            this.Controls.Add(this.groupBoxTilesetPresets);
            this.Controls.Add(this.buttonImportTileset);
            this.Name = "Palette";
            this.Size = new System.Drawing.Size(336, 673);
            this.groupBoxTilesetPresets.ResumeLayout(false);
            this.groupBoxTilesetObject.ResumeLayout(false);
            this.groupBoxTilesetObject.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTilesetY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownTilesetX)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button buttonImportTileset;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanelTilesetsPresets;
        private System.Windows.Forms.GroupBox groupBoxTilesetPresets;
        private System.Windows.Forms.Button buttonAddTileset;
        private System.Windows.Forms.GroupBox groupBoxTilesetObject;
        private System.Windows.Forms.ComboBox comboBoxSelectedPreset;
        private System.Windows.Forms.Label labelSelectedPreset;
        private System.Windows.Forms.TextBox textBoxScale;
        private System.Windows.Forms.Label labelScale;
        private System.Windows.Forms.Label labelTilesetY;
        private System.Windows.Forms.Label labelTilesetX;
        private System.Windows.Forms.NumericUpDown numericUpDownTilesetY;
        private System.Windows.Forms.NumericUpDown numericUpDownTilesetX;
        private System.Windows.Forms.ListBox listBoxExistingTilesets;
        private System.Windows.Forms.TextBox textBoxTilesetName;
        private System.Windows.Forms.Label labelTilesetName;
    }
}

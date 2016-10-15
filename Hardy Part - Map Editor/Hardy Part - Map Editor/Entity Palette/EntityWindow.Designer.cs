using Hardy_Part___Map_Editor.Tileset_Palette;

namespace Hardy_Part___Map_Editor.Entity_Palette
{
    partial class EntityWindow
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
            this.groupBoxEntityObject = new System.Windows.Forms.GroupBox();
            this.numericUpDownRotation = new System.Windows.Forms.NumericUpDown();
            this.labelCenterY = new System.Windows.Forms.Label();
            this.numericUpDownCenterY = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownCenterX = new System.Windows.Forms.NumericUpDown();
            this.checkBoxEntityVisible = new System.Windows.Forms.CheckBox();
            this.labelCenterX = new System.Windows.Forms.Label();
            this.labelRotation = new System.Windows.Forms.Label();
            this.numericUpDownEntityLayer = new System.Windows.Forms.NumericUpDown();
            this.labelTilesetLayer = new System.Windows.Forms.Label();
            this.numericUpDownEntityScale = new System.Windows.Forms.NumericUpDown();
            this.textBoxEntityName = new System.Windows.Forms.TextBox();
            this.labelEntityName = new System.Windows.Forms.Label();
            this.labelTilesetY = new System.Windows.Forms.Label();
            this.numericUpDownEntityY = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownEntityX = new System.Windows.Forms.NumericUpDown();
            this.labelTilesetX = new System.Windows.Forms.Label();
            this.labelSelectedTemplate = new System.Windows.Forms.Label();
            this.comboBoxSelectedTemplate = new System.Windows.Forms.ComboBox();
            this.labelScale = new System.Windows.Forms.Label();
            this.buttonRemoveEntity = new System.Windows.Forms.Button();
            this.buttonAddEntity = new System.Windows.Forms.Button();
            this.buttonImportTexture = new System.Windows.Forms.Button();
            this.groupBoxTilesetPresets = new System.Windows.Forms.GroupBox();
            this.flowLayoutPanelTilesetsPresets = new System.Windows.Forms.FlowLayoutPanel();
            this.existingEntityList = new Hardy_Part___Map_Editor.Entity_Palette.ExistingEntityList();
            this.groupBoxEntityObject.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownRotation)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCenterY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCenterX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEntityLayer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEntityScale)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEntityY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEntityX)).BeginInit();
            this.groupBoxTilesetPresets.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxEntityObject
            // 
            this.groupBoxEntityObject.Controls.Add(this.numericUpDownRotation);
            this.groupBoxEntityObject.Controls.Add(this.labelCenterY);
            this.groupBoxEntityObject.Controls.Add(this.numericUpDownCenterY);
            this.groupBoxEntityObject.Controls.Add(this.numericUpDownCenterX);
            this.groupBoxEntityObject.Controls.Add(this.checkBoxEntityVisible);
            this.groupBoxEntityObject.Controls.Add(this.labelCenterX);
            this.groupBoxEntityObject.Controls.Add(this.labelRotation);
            this.groupBoxEntityObject.Controls.Add(this.numericUpDownEntityLayer);
            this.groupBoxEntityObject.Controls.Add(this.labelTilesetLayer);
            this.groupBoxEntityObject.Controls.Add(this.numericUpDownEntityScale);
            this.groupBoxEntityObject.Controls.Add(this.textBoxEntityName);
            this.groupBoxEntityObject.Controls.Add(this.labelEntityName);
            this.groupBoxEntityObject.Controls.Add(this.labelTilesetY);
            this.groupBoxEntityObject.Controls.Add(this.numericUpDownEntityY);
            this.groupBoxEntityObject.Controls.Add(this.numericUpDownEntityX);
            this.groupBoxEntityObject.Controls.Add(this.labelTilesetX);
            this.groupBoxEntityObject.Controls.Add(this.labelSelectedTemplate);
            this.groupBoxEntityObject.Controls.Add(this.comboBoxSelectedTemplate);
            this.groupBoxEntityObject.Controls.Add(this.labelScale);
            this.groupBoxEntityObject.Enabled = false;
            this.groupBoxEntityObject.Location = new System.Drawing.Point(171, 37);
            this.groupBoxEntityObject.Name = "groupBoxEntityObject";
            this.groupBoxEntityObject.Size = new System.Drawing.Size(161, 180);
            this.groupBoxEntityObject.TabIndex = 5;
            this.groupBoxEntityObject.TabStop = false;
            this.groupBoxEntityObject.Text = "Current Entity";
            // 
            // numericUpDownRotation
            // 
            this.numericUpDownRotation.DecimalPlaces = 2;
            this.numericUpDownRotation.Location = new System.Drawing.Point(110, 153);
            this.numericUpDownRotation.Maximum = new decimal(new int[] {
            360,
            0,
            0,
            0});
            this.numericUpDownRotation.Minimum = new decimal(new int[] {
            360,
            0,
            0,
            -2147483648});
            this.numericUpDownRotation.Name = "numericUpDownRotation";
            this.numericUpDownRotation.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownRotation.TabIndex = 21;
            // 
            // labelCenterY
            // 
            this.labelCenterY.AutoSize = true;
            this.labelCenterY.Location = new System.Drawing.Point(56, 137);
            this.labelCenterY.Name = "labelCenterY";
            this.labelCenterY.Size = new System.Drawing.Size(48, 13);
            this.labelCenterY.TabIndex = 20;
            this.labelCenterY.Text = "Center Y";
            // 
            // numericUpDownCenterY
            // 
            this.numericUpDownCenterY.DecimalPlaces = 2;
            this.numericUpDownCenterY.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numericUpDownCenterY.Location = new System.Drawing.Point(59, 153);
            this.numericUpDownCenterY.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownCenterY.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownCenterY.Name = "numericUpDownCenterY";
            this.numericUpDownCenterY.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownCenterY.TabIndex = 18;
            // 
            // numericUpDownCenterX
            // 
            this.numericUpDownCenterX.DecimalPlaces = 2;
            this.numericUpDownCenterX.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.numericUpDownCenterX.Location = new System.Drawing.Point(8, 153);
            this.numericUpDownCenterX.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDownCenterX.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            -2147483648});
            this.numericUpDownCenterX.Name = "numericUpDownCenterX";
            this.numericUpDownCenterX.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownCenterX.TabIndex = 17;
            // 
            // checkBoxEntityVisible
            // 
            this.checkBoxEntityVisible.AutoSize = true;
            this.checkBoxEntityVisible.Checked = true;
            this.checkBoxEntityVisible.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxEntityVisible.Location = new System.Drawing.Point(101, 75);
            this.checkBoxEntityVisible.Name = "checkBoxEntityVisible";
            this.checkBoxEntityVisible.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.checkBoxEntityVisible.Size = new System.Drawing.Size(56, 17);
            this.checkBoxEntityVisible.TabIndex = 15;
            this.checkBoxEntityVisible.Text = "Visible";
            this.checkBoxEntityVisible.UseVisualStyleBackColor = true;
            // 
            // labelCenterX
            // 
            this.labelCenterX.AutoSize = true;
            this.labelCenterX.Location = new System.Drawing.Point(4, 137);
            this.labelCenterX.Name = "labelCenterX";
            this.labelCenterX.Size = new System.Drawing.Size(48, 13);
            this.labelCenterX.TabIndex = 19;
            this.labelCenterX.Text = "Center X";
            // 
            // labelRotation
            // 
            this.labelRotation.AutoSize = true;
            this.labelRotation.Location = new System.Drawing.Point(107, 137);
            this.labelRotation.Name = "labelRotation";
            this.labelRotation.Size = new System.Drawing.Size(47, 13);
            this.labelRotation.TabIndex = 16;
            this.labelRotation.Text = "Rotation";
            // 
            // numericUpDownEntityLayer
            // 
            this.numericUpDownEntityLayer.Location = new System.Drawing.Point(53, 74);
            this.numericUpDownEntityLayer.Name = "numericUpDownEntityLayer";
            this.numericUpDownEntityLayer.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownEntityLayer.TabIndex = 13;
            this.numericUpDownEntityLayer.ValueChanged += new System.EventHandler(this.numericUpDownEntityLayer_ValueChanged);
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
            // numericUpDownEntityScale
            // 
            this.numericUpDownEntityScale.DecimalPlaces = 1;
            this.numericUpDownEntityScale.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDownEntityScale.Location = new System.Drawing.Point(110, 113);
            this.numericUpDownEntityScale.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numericUpDownEntityScale.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDownEntityScale.Name = "numericUpDownEntityScale";
            this.numericUpDownEntityScale.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownEntityScale.TabIndex = 10;
            this.numericUpDownEntityScale.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // textBoxEntityName
            // 
            this.textBoxEntityName.Location = new System.Drawing.Point(53, 21);
            this.textBoxEntityName.Name = "textBoxEntityName";
            this.textBoxEntityName.Size = new System.Drawing.Size(102, 20);
            this.textBoxEntityName.TabIndex = 9;
            this.textBoxEntityName.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxEntityName_KeyPress);
            this.textBoxEntityName.Leave += new System.EventHandler(this.textBoxEntityName_Leave);
            // 
            // labelEntityName
            // 
            this.labelEntityName.AutoSize = true;
            this.labelEntityName.Location = new System.Drawing.Point(12, 24);
            this.labelEntityName.Name = "labelEntityName";
            this.labelEntityName.Size = new System.Drawing.Size(35, 13);
            this.labelEntityName.TabIndex = 8;
            this.labelEntityName.Text = "Name";
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
            // numericUpDownEntityY
            // 
            this.numericUpDownEntityY.Location = new System.Drawing.Point(59, 113);
            this.numericUpDownEntityY.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numericUpDownEntityY.Name = "numericUpDownEntityY";
            this.numericUpDownEntityY.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownEntityY.TabIndex = 5;
            // 
            // numericUpDownEntityX
            // 
            this.numericUpDownEntityX.Location = new System.Drawing.Point(8, 113);
            this.numericUpDownEntityX.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            -2147483648});
            this.numericUpDownEntityX.Name = "numericUpDownEntityX";
            this.numericUpDownEntityX.Size = new System.Drawing.Size(42, 20);
            this.numericUpDownEntityX.TabIndex = 4;
            this.numericUpDownEntityX.ValueChanged += new System.EventHandler(this.numericUpDownEntityX_ValueChanged);
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
            // labelSelectedTemplate
            // 
            this.labelSelectedTemplate.AutoSize = true;
            this.labelSelectedTemplate.Location = new System.Drawing.Point(2, 50);
            this.labelSelectedTemplate.Name = "labelSelectedTemplate";
            this.labelSelectedTemplate.Size = new System.Drawing.Size(51, 13);
            this.labelSelectedTemplate.TabIndex = 1;
            this.labelSelectedTemplate.Text = "Template";
            // 
            // comboBoxSelectedTemplate
            // 
            this.comboBoxSelectedTemplate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxSelectedTemplate.FormattingEnabled = true;
            this.comboBoxSelectedTemplate.Location = new System.Drawing.Point(53, 47);
            this.comboBoxSelectedTemplate.Name = "comboBoxSelectedTemplate";
            this.comboBoxSelectedTemplate.Size = new System.Drawing.Size(102, 21);
            this.comboBoxSelectedTemplate.TabIndex = 0;
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
            // buttonRemoveEntity
            // 
            this.buttonRemoveEntity.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(223)))), ((int)(((byte)(224)))));
            this.buttonRemoveEntity.Enabled = false;
            this.buttonRemoveEntity.Location = new System.Drawing.Point(282, 8);
            this.buttonRemoveEntity.Name = "buttonRemoveEntity";
            this.buttonRemoveEntity.Size = new System.Drawing.Size(51, 23);
            this.buttonRemoveEntity.TabIndex = 11;
            this.buttonRemoveEntity.Text = "Delete";
            this.buttonRemoveEntity.UseVisualStyleBackColor = false;
            this.buttonRemoveEntity.Click += new System.EventHandler(this.buttonRemoveEntity_Click);
            // 
            // buttonAddEntity
            // 
            this.buttonAddEntity.Enabled = false;
            this.buttonAddEntity.Location = new System.Drawing.Point(223, 8);
            this.buttonAddEntity.Name = "buttonAddEntity";
            this.buttonAddEntity.Size = new System.Drawing.Size(53, 23);
            this.buttonAddEntity.TabIndex = 7;
            this.buttonAddEntity.Text = "New";
            this.buttonAddEntity.UseVisualStyleBackColor = true;
            this.buttonAddEntity.Click += new System.EventHandler(this.buttonAddEntity_Click);
            // 
            // buttonImportTexture
            // 
            this.buttonImportTexture.Location = new System.Drawing.Point(10, 187);
            this.buttonImportTexture.Name = "buttonImportTexture";
            this.buttonImportTexture.Size = new System.Drawing.Size(150, 23);
            this.buttonImportTexture.TabIndex = 12;
            this.buttonImportTexture.Text = "Import Sprite / Texture";
            this.buttonImportTexture.UseVisualStyleBackColor = true;
            this.buttonImportTexture.Click += new System.EventHandler(this.buttonImportTexture_Click);
            // 
            // groupBoxTilesetPresets
            // 
            this.groupBoxTilesetPresets.Controls.Add(this.flowLayoutPanelTilesetsPresets);
            this.groupBoxTilesetPresets.Location = new System.Drawing.Point(0, 216);
            this.groupBoxTilesetPresets.Name = "groupBoxTilesetPresets";
            this.groupBoxTilesetPresets.Size = new System.Drawing.Size(329, 454);
            this.groupBoxTilesetPresets.TabIndex = 13;
            this.groupBoxTilesetPresets.TabStop = false;
            this.groupBoxTilesetPresets.Text = "Sprites / Textures";
            // 
            // flowLayoutPanelTilesetsPresets
            // 
            this.flowLayoutPanelTilesetsPresets.AutoScroll = true;
            this.flowLayoutPanelTilesetsPresets.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.flowLayoutPanelTilesetsPresets.Location = new System.Drawing.Point(6, 19);
            this.flowLayoutPanelTilesetsPresets.Name = "flowLayoutPanelTilesetsPresets";
            this.flowLayoutPanelTilesetsPresets.Padding = new System.Windows.Forms.Padding(5);
            this.flowLayoutPanelTilesetsPresets.Size = new System.Drawing.Size(317, 429);
            this.flowLayoutPanelTilesetsPresets.TabIndex = 1;
            this.flowLayoutPanelTilesetsPresets.WrapContents = false;
            // 
            // existingEntityList
            // 
            this.existingEntityList.Location = new System.Drawing.Point(4, 4);
            this.existingEntityList.Name = "existingEntityList";
            this.existingEntityList.SelectedEntity = null;
            this.existingEntityList.Size = new System.Drawing.Size(162, 173);
            this.existingEntityList.TabIndex = 14;
            // 
            // EntityWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.existingEntityList);
            this.Controls.Add(this.groupBoxTilesetPresets);
            this.Controls.Add(this.buttonImportTexture);
            this.Controls.Add(this.buttonAddEntity);
            this.Controls.Add(this.groupBoxEntityObject);
            this.Controls.Add(this.buttonRemoveEntity);
            this.Name = "EntityWindow";
            this.Size = new System.Drawing.Size(336, 675);
            this.groupBoxEntityObject.ResumeLayout(false);
            this.groupBoxEntityObject.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownRotation)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCenterY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownCenterX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEntityLayer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEntityScale)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEntityY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownEntityX)).EndInit();
            this.groupBoxTilesetPresets.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBoxEntityObject;
        public System.Windows.Forms.CheckBox checkBoxEntityVisible;
        private System.Windows.Forms.Label labelTilesetLayer;
        private System.Windows.Forms.NumericUpDown numericUpDownEntityLayer;
        private System.Windows.Forms.Button buttonRemoveEntity;
        private System.Windows.Forms.NumericUpDown numericUpDownEntityScale;
        private System.Windows.Forms.TextBox textBoxEntityName;
        private System.Windows.Forms.Label labelEntityName;
        private System.Windows.Forms.Label labelTilesetY;
        private System.Windows.Forms.NumericUpDown numericUpDownEntityY;
        private System.Windows.Forms.NumericUpDown numericUpDownEntityX;
        private System.Windows.Forms.Label labelTilesetX;
        private System.Windows.Forms.Label labelSelectedTemplate;
        public System.Windows.Forms.ComboBox comboBoxSelectedTemplate;
        private System.Windows.Forms.Label labelScale;
        private System.Windows.Forms.NumericUpDown numericUpDownRotation;
        private System.Windows.Forms.Label labelCenterY;
        private System.Windows.Forms.NumericUpDown numericUpDownCenterY;
        private System.Windows.Forms.NumericUpDown numericUpDownCenterX;
        private System.Windows.Forms.Label labelCenterX;
        private System.Windows.Forms.Label labelRotation;
        public System.Windows.Forms.Button buttonAddEntity;
        private System.Windows.Forms.Button buttonImportTexture;
        private System.Windows.Forms.GroupBox groupBoxTilesetPresets;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanelTilesetsPresets;
        public ExistingEntityList existingEntityList;
    }
}

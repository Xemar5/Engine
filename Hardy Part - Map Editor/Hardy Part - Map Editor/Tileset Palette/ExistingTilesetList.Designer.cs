namespace Hardy_Part___Map_Editor.Tileset_Palette
{
    partial class ExistingTilesetList
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
            this.dataGridViewExistingTilesets = new System.Windows.Forms.DataGridView();
            this.panelBackground = new System.Windows.Forms.Panel();
            this.ColumnExistingTilesets = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnLayer = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnVisible = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewExistingTilesets)).BeginInit();
            this.panelBackground.SuspendLayout();
            this.SuspendLayout();
            // 
            // dataGridViewExistingTilesets
            // 
            this.dataGridViewExistingTilesets.AllowUserToAddRows = false;
            this.dataGridViewExistingTilesets.AllowUserToDeleteRows = false;
            this.dataGridViewExistingTilesets.AllowUserToResizeColumns = false;
            this.dataGridViewExistingTilesets.AllowUserToResizeRows = false;
            this.dataGridViewExistingTilesets.BackgroundColor = System.Drawing.SystemColors.Control;
            this.dataGridViewExistingTilesets.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.dataGridViewExistingTilesets.CellBorderStyle = System.Windows.Forms.DataGridViewCellBorderStyle.SingleHorizontal;
            this.dataGridViewExistingTilesets.ColumnHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
            this.dataGridViewExistingTilesets.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewExistingTilesets.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColumnExistingTilesets,
            this.ColumnLayer,
            this.ColumnVisible});
            this.dataGridViewExistingTilesets.Location = new System.Drawing.Point(1, 1);
            this.dataGridViewExistingTilesets.MultiSelect = false;
            this.dataGridViewExistingTilesets.Name = "dataGridViewExistingTilesets";
            this.dataGridViewExistingTilesets.RowHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.Single;
            this.dataGridViewExistingTilesets.RowHeadersVisible = false;
            this.dataGridViewExistingTilesets.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.dataGridViewExistingTilesets.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewExistingTilesets.ShowCellToolTips = false;
            this.dataGridViewExistingTilesets.ShowEditingIcon = false;
            this.dataGridViewExistingTilesets.ShowRowErrors = false;
            this.dataGridViewExistingTilesets.Size = new System.Drawing.Size(160, 171);
            this.dataGridViewExistingTilesets.TabIndex = 1;
            this.dataGridViewExistingTilesets.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewExistingTilesets_CellContentClick);
            this.dataGridViewExistingTilesets.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewExistingTilesets_CellValueChanged);
            // 
            // panelBackground
            // 
            this.panelBackground.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.panelBackground.Controls.Add(this.dataGridViewExistingTilesets);
            this.panelBackground.Location = new System.Drawing.Point(0, 0);
            this.panelBackground.Name = "panelBackground";
            this.panelBackground.Size = new System.Drawing.Size(162, 173);
            this.panelBackground.TabIndex = 2;
            // 
            // ColumnExistingTilesets
            // 
            this.ColumnExistingTilesets.HeaderText = "Tileset";
            this.ColumnExistingTilesets.Name = "ColumnExistingTilesets";
            this.ColumnExistingTilesets.ReadOnly = true;
            this.ColumnExistingTilesets.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.ColumnExistingTilesets.Width = 83;
            // 
            // ColumnLayer
            // 
            this.ColumnLayer.HeaderText = "Lay.";
            this.ColumnLayer.MaxInputLength = 3;
            this.ColumnLayer.Name = "ColumnLayer";
            this.ColumnLayer.ReadOnly = true;
            this.ColumnLayer.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.ColumnLayer.Width = 30;
            // 
            // ColumnVisible
            // 
            this.ColumnVisible.HeaderText = "Vis.";
            this.ColumnVisible.Name = "ColumnVisible";
            this.ColumnVisible.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.ColumnVisible.Width = 30;
            // 
            // ExistingTilesetList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panelBackground);
            this.Name = "ExistingTilesetList";
            this.Size = new System.Drawing.Size(162, 173);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewExistingTilesets)).EndInit();
            this.panelBackground.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Panel panelBackground;
        public System.Windows.Forms.DataGridView dataGridViewExistingTilesets;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnExistingTilesets;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnLayer;
        private System.Windows.Forms.DataGridViewCheckBoxColumn ColumnVisible;
    }
}

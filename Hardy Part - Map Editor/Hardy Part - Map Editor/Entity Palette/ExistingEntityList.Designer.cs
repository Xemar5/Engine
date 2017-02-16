namespace Hardy_Part___Map_Editor.Entity_Palette
{
    partial class ExistingEntityList
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
            this.panelBackground = new System.Windows.Forms.Panel();
            this.dataGridViewExistingEntity = new System.Windows.Forms.DataGridView();
            this.ColumnExistingEntities = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnLayer = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColumnVisible = new System.Windows.Forms.DataGridViewCheckBoxColumn();
            this.panelBackground.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewExistingEntity)).BeginInit();
            this.SuspendLayout();
            // 
            // panelBackground
            // 
            this.panelBackground.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.panelBackground.Controls.Add(this.dataGridViewExistingEntity);
            this.panelBackground.Location = new System.Drawing.Point(0, 0);
            this.panelBackground.Name = "panelBackground";
            this.panelBackground.Size = new System.Drawing.Size(162, 173);
            this.panelBackground.TabIndex = 3;
            // 
            // dataGridViewExistingEntity
            // 
            this.dataGridViewExistingEntity.AllowUserToAddRows = false;
            this.dataGridViewExistingEntity.AllowUserToDeleteRows = false;
            this.dataGridViewExistingEntity.AllowUserToResizeColumns = false;
            this.dataGridViewExistingEntity.AllowUserToResizeRows = false;
            this.dataGridViewExistingEntity.BackgroundColor = System.Drawing.SystemColors.Control;
            this.dataGridViewExistingEntity.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.dataGridViewExistingEntity.CellBorderStyle = System.Windows.Forms.DataGridViewCellBorderStyle.SingleHorizontal;
            this.dataGridViewExistingEntity.ColumnHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.None;
            this.dataGridViewExistingEntity.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewExistingEntity.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.ColumnExistingEntities,
            this.ColumnLayer,
            this.ColumnVisible});
            this.dataGridViewExistingEntity.Location = new System.Drawing.Point(1, 1);
            this.dataGridViewExistingEntity.MultiSelect = false;
            this.dataGridViewExistingEntity.Name = "dataGridViewExistingEntity";
            this.dataGridViewExistingEntity.RowHeadersBorderStyle = System.Windows.Forms.DataGridViewHeaderBorderStyle.Single;
            this.dataGridViewExistingEntity.RowHeadersVisible = false;
            this.dataGridViewExistingEntity.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.dataGridViewExistingEntity.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewExistingEntity.ShowCellToolTips = false;
            this.dataGridViewExistingEntity.ShowEditingIcon = false;
            this.dataGridViewExistingEntity.ShowRowErrors = false;
            this.dataGridViewExistingEntity.Size = new System.Drawing.Size(160, 171);
            this.dataGridViewExistingEntity.TabIndex = 1;
            this.dataGridViewExistingEntity.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewExistingEntity_CellContentClick);
            this.dataGridViewExistingEntity.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridViewExistingEntity_CellValueChanged);
            // 
            // ColumnExistingEntities
            // 
            this.ColumnExistingEntities.HeaderText = "Entity";
            this.ColumnExistingEntities.Name = "ColumnExistingEntities";
            this.ColumnExistingEntities.ReadOnly = true;
            this.ColumnExistingEntities.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.ColumnExistingEntities.Width = 83;
            // 
            // ColumnLayer
            // 
            this.ColumnLayer.HeaderText = "Lay.";
            this.ColumnLayer.Name = "ColumnLayer";
            this.ColumnLayer.ReadOnly = true;
            this.ColumnLayer.Width = 30;
            // 
            // ColumnVisible
            // 
            this.ColumnVisible.HeaderText = "Vis.";
            this.ColumnVisible.Name = "ColumnVisible";
            this.ColumnVisible.ReadOnly = true;
            this.ColumnVisible.Width = 30;
            // 
            // ExistingEntityList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panelBackground);
            this.Name = "ExistingEntityList";
            this.Size = new System.Drawing.Size(162, 173);
            this.panelBackground.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewExistingEntity)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panelBackground;
        public System.Windows.Forms.DataGridView dataGridViewExistingEntity;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnExistingEntities;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColumnLayer;
        private System.Windows.Forms.DataGridViewCheckBoxColumn ColumnVisible;
    }
}

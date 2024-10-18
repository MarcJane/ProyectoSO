
namespace Cliente
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.USER = new System.Windows.Forms.TextBox();
            this.PASSWORD = new System.Windows.Forms.TextBox();
            this.NAME = new System.Windows.Forms.TextBox();
            this.DATE = new System.Windows.Forms.TextBox();
            this.LOGIN = new System.Windows.Forms.Button();
            this.SIGNIN = new System.Windows.Forms.Button();
            this.DISCONECT = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.lConectados = new System.Windows.Forms.ToolStripMenuItem();
            this.QUERY1 = new System.Windows.Forms.Button();
            this.QUERY2 = new System.Windows.Forms.Button();
            this.QUERY3 = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(243, 47);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "USUARIO";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(243, 102);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(103, 17);
            this.label2.TabIndex = 1;
            this.label2.Text = "CONTRASEÑA";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(61, 183);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(92, 17);
            this.label3.TabIndex = 2;
            this.label3.Text = "CONSULTAS";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(243, 265);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(68, 17);
            this.label4.TabIndex = 3;
            this.label4.Text = "NOMBRE";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(243, 331);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 17);
            this.label5.TabIndex = 4;
            this.label5.Text = "FECHA";
            // 
            // USER
            // 
            this.USER.Location = new System.Drawing.Point(53, 42);
            this.USER.Name = "USER";
            this.USER.Size = new System.Drawing.Size(133, 22);
            this.USER.TabIndex = 5;
            // 
            // PASSWORD
            // 
            this.PASSWORD.Location = new System.Drawing.Point(53, 102);
            this.PASSWORD.Name = "PASSWORD";
            this.PASSWORD.Size = new System.Drawing.Size(133, 22);
            this.PASSWORD.TabIndex = 6;
            // 
            // NAME
            // 
            this.NAME.Location = new System.Drawing.Point(53, 265);
            this.NAME.Name = "NAME";
            this.NAME.Size = new System.Drawing.Size(133, 22);
            this.NAME.TabIndex = 7;
            // 
            // DATE
            // 
            this.DATE.Location = new System.Drawing.Point(53, 331);
            this.DATE.Name = "DATE";
            this.DATE.Size = new System.Drawing.Size(133, 22);
            this.DATE.TabIndex = 8;
            // 
            // LOGIN
            // 
            this.LOGIN.Location = new System.Drawing.Point(475, 41);
            this.LOGIN.Name = "LOGIN";
            this.LOGIN.Size = new System.Drawing.Size(91, 41);
            this.LOGIN.TabIndex = 9;
            this.LOGIN.Text = "LOG IN";
            this.LOGIN.UseVisualStyleBackColor = true;
            this.LOGIN.Click += new System.EventHandler(this.LOGIN_Click);
            // 
            // SIGNIN
            // 
            this.SIGNIN.Location = new System.Drawing.Point(475, 128);
            this.SIGNIN.Name = "SIGNIN";
            this.SIGNIN.Size = new System.Drawing.Size(91, 41);
            this.SIGNIN.TabIndex = 10;
            this.SIGNIN.Text = "SIGN IN";
            this.SIGNIN.UseVisualStyleBackColor = true;
            this.SIGNIN.Click += new System.EventHandler(this.SIGNIN_Click);
            // 
            // DISCONECT
            // 
            this.DISCONECT.Location = new System.Drawing.Point(656, 81);
            this.DISCONECT.Name = "DISCONECT";
            this.DISCONECT.Size = new System.Drawing.Size(120, 38);
            this.DISCONECT.TabIndex = 11;
            this.DISCONECT.Text = "DISCONECT";
            this.DISCONECT.UseVisualStyleBackColor = true;
            this.DISCONECT.Click += new System.EventHandler(this.DISCONECT_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.lConectados});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 28);
            this.menuStrip1.TabIndex = 12;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // lConectados
            // 
            this.lConectados.Name = "lConectados";
            this.lConectados.Size = new System.Drawing.Size(101, 24);
            this.lConectados.Text = "Conectados";
            // 
            // QUERY1
            // 
            this.QUERY1.Location = new System.Drawing.Point(408, 213);
            this.QUERY1.Name = "QUERY1";
            this.QUERY1.Size = new System.Drawing.Size(368, 46);
            this.QUERY1.TabIndex = 13;
            this.QUERY1.Text = "QUERY1";
            this.QUERY1.UseVisualStyleBackColor = true;
            // 
            // QUERY2
            // 
            this.QUERY2.Location = new System.Drawing.Point(408, 278);
            this.QUERY2.Name = "QUERY2";
            this.QUERY2.Size = new System.Drawing.Size(368, 47);
            this.QUERY2.TabIndex = 14;
            this.QUERY2.Text = "QUERY2";
            this.QUERY2.UseVisualStyleBackColor = true;
            // 
            // QUERY3
            // 
            this.QUERY3.Location = new System.Drawing.Point(408, 346);
            this.QUERY3.Name = "QUERY3";
            this.QUERY3.Size = new System.Drawing.Size(368, 46);
            this.QUERY3.TabIndex = 15;
            this.QUERY3.Text = "QUERY3";
            this.QUERY3.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.QUERY3);
            this.Controls.Add(this.QUERY2);
            this.Controls.Add(this.QUERY1);
            this.Controls.Add(this.DISCONECT);
            this.Controls.Add(this.SIGNIN);
            this.Controls.Add(this.LOGIN);
            this.Controls.Add(this.DATE);
            this.Controls.Add(this.NAME);
            this.Controls.Add(this.PASSWORD);
            this.Controls.Add(this.USER);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Cliente";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox USER;
        private System.Windows.Forms.TextBox PASSWORD;
        private System.Windows.Forms.TextBox NAME;
        private System.Windows.Forms.TextBox DATE;
        private System.Windows.Forms.Button LOGIN;
        private System.Windows.Forms.Button SIGNIN;
        private System.Windows.Forms.Button DISCONECT;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem lConectados;
        private System.Windows.Forms.Button QUERY1;
        private System.Windows.Forms.Button QUERY2;
        private System.Windows.Forms.Button QUERY3;
    }
}


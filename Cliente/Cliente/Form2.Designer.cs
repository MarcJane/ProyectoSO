
namespace Cliente
{
    partial class Form2
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
            this.jugador1 = new System.Windows.Forms.Label();
            this.jugador2 = new System.Windows.Forms.Label();
            this.jugador3 = new System.Windows.Forms.Label();
            this.jugador4 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.ENVIAR = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.EMPEZAR = new System.Windows.Forms.Button();
            this.CERRAR = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // jugador1
            // 
            this.jugador1.AutoSize = true;
            this.jugador1.Location = new System.Drawing.Point(101, 77);
            this.jugador1.Name = "jugador1";
            this.jugador1.Size = new System.Drawing.Size(25, 17);
            this.jugador1.TabIndex = 0;
            this.jugador1.Text = "Tu";
            // 
            // jugador2
            // 
            this.jugador2.AutoSize = true;
            this.jugador2.Location = new System.Drawing.Point(518, 77);
            this.jugador2.Name = "jugador2";
            this.jugador2.Size = new System.Drawing.Size(23, 17);
            this.jugador2.TabIndex = 1;
            this.jugador2.Text = "J1";
            // 
            // jugador3
            // 
            this.jugador3.AutoSize = true;
            this.jugador3.Location = new System.Drawing.Point(518, 204);
            this.jugador3.Name = "jugador3";
            this.jugador3.Size = new System.Drawing.Size(23, 17);
            this.jugador3.TabIndex = 2;
            this.jugador3.Text = "J3";
            // 
            // jugador4
            // 
            this.jugador4.AutoSize = true;
            this.jugador4.Location = new System.Drawing.Point(104, 204);
            this.jugador4.Name = "jugador4";
            this.jugador4.Size = new System.Drawing.Size(23, 17);
            this.jugador4.TabIndex = 3;
            this.jugador4.Text = "J2";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(61, 344);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(221, 22);
            this.textBox1.TabIndex = 4;
            // 
            // ENVIAR
            // 
            this.ENVIAR.Location = new System.Drawing.Point(311, 344);
            this.ENVIAR.Name = "ENVIAR";
            this.ENVIAR.Size = new System.Drawing.Size(128, 23);
            this.ENVIAR.TabIndex = 5;
            this.ENVIAR.Text = "Enviar";
            this.ENVIAR.UseVisualStyleBackColor = true;
            this.ENVIAR.Click += new System.EventHandler(this.ENVIAR_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(730, 310);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(0, 17);
            this.label5.TabIndex = 6;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(730, 344);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(0, 17);
            this.label6.TabIndex = 7;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(730, 372);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(0, 17);
            this.label7.TabIndex = 8;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(586, 204);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(0, 17);
            this.label8.TabIndex = 9;
            // 
            // EMPEZAR
            // 
            this.EMPEZAR.Location = new System.Drawing.Point(589, 252);
            this.EMPEZAR.Name = "EMPEZAR";
            this.EMPEZAR.Size = new System.Drawing.Size(129, 44);
            this.EMPEZAR.TabIndex = 10;
            this.EMPEZAR.Text = "EMPEZAR";
            this.EMPEZAR.UseVisualStyleBackColor = true;
            this.EMPEZAR.Click += new System.EventHandler(this.EMPEZAR_Click);
            // 
            // CERRAR
            // 
            this.CERRAR.Location = new System.Drawing.Point(615, 302);
            this.CERRAR.Name = "CERRAR";
            this.CERRAR.Size = new System.Drawing.Size(85, 45);
            this.CERRAR.TabIndex = 11;
            this.CERRAR.Text = "CERRAR";
            this.CERRAR.UseVisualStyleBackColor = true;
            this.CERRAR.Click += new System.EventHandler(this.CERRAR_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.CERRAR);
            this.Controls.Add(this.EMPEZAR);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.ENVIAR);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.jugador4);
            this.Controls.Add(this.jugador3);
            this.Controls.Add(this.jugador2);
            this.Controls.Add(this.jugador1);
            this.Name = "Form2";
            this.Text = "Form2";
            this.Load += new System.EventHandler(this.Form2_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label jugador1;
        private System.Windows.Forms.Label jugador2;
        private System.Windows.Forms.Label jugador3;
        private System.Windows.Forms.Label jugador4;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button ENVIAR;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button EMPEZAR;
        private System.Windows.Forms.Button CERRAR;
    }
}
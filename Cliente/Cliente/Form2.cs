﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Cliente
{
    public partial class Form2 : Form
    {
        public static Form2 instance;
        public Label l1;
        public Label l2;
        public Label l3;
        public Label l4;
        public Label l5;
        public Label l6;
        public Label l7;
        public Label l8;
        public TextBox tB;

        public Form2()
        {
            InitializeComponent();
            instance = this;
            l1 = jugador1;
            l2 = jugador2;
            l3 = jugador3;
            l4 = jugador4;
            l5 = label1;
            l6 = label2;
            l7 = label3;
            l8 = label4;
            tB = textBox1;
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void ENVIAR_Click(object sender, EventArgs e) //Envia mensaje del texbox al Chat
        {
            // Opcional: Envía el mensaje al servidor o realiza otra acción
            Form1.instance.enviarMensaje();

            // Limpia el TextBox después de enviar
            textBox1.Clear();
            //string mensaje = textBox1.Text;

            //if (!string.IsNullOrWhiteSpace(mensaje)) // Verifica que el mensaje no esté vacío
            //{
            //    // Verificar quién envió el mensaje usando los RadioButtons
            //    if (J1.Checked)
            //    {
            //        l5.Text = $"Jugador 1: {mensaje}"; // Mostrar mensaje en Label1
            //    }
            //    else if (J2.Checked)
            //    {
            //        l6.Text = $"Jugador 2: {mensaje}"; // Mostrar mensaje en Label2
            //    }
            //    else
            //    {
            //        MessageBox.Show("Por favor, selecciona un jugador antes de enviar el mensaje.",
            //                        "Advertencia", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            //        return;
            //    }

            //    // Opcional: Envía el mensaje al servidor o realiza otra acción
            //    Form1.instance.enviarMensaje();

            //    // Limpia el TextBox después de enviar
            //    textBox1.Clear();
            //}
            //else
            //{
            //    MessageBox.Show("El mensaje no puede estar vacío.",
            //                    "Advertencia", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            //}
        }

        private void EMPEZAR_Click(object sender, EventArgs e) //Empieza el juego
        {
            Form1.instance.EMPEZAR();
        }

        private void CERRAR_Click(object sender, EventArgs e) //Cierra el juego
        {
            this.Close();
        }
        public void startAction()       //aparecen los jugadores al iniciar la partida y pueden comenzar a moverse
        {
            jugador1.Hide();
            jugador2.Hide();
            jugador3.Hide();
            jugador4.Hide();
            textBox1.Hide();
            EMPEZAR.Hide();
            CERRAR.Hide();
            ENVIAR.Hide();
        }
    }
}

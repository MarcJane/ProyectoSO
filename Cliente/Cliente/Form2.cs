using System;
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
            l1 = label2;
            l2 = label3;
            l3 = label4;
            l4 = label5;
            l5 = label6;
            l6 = label7;
            l7 = label8;
            tB = textBox1;
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void ENVIAR_Click(object sender, EventArgs e)
        {
            Form1.instance.enviarMensaje();
            textBox1.Clear();
        }
    }
}

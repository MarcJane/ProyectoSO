using System;
using System.Drawing;
using System.Windows.Forms;

namespace ParchisGame
{
    public partial class Form1 : Form
    {
        private TableLayoutPanel tablero;
        private Button tirarDadoBtn;
        private Label turnoLabel;
        private PictureBox dadoPictureBox;
        private int resultadoDado;

        public Form1()
        {
            InitializeComponent();
            InicializarComponentes();
        }

        private void InicializarComponentes()
        {
            // Configuración del formulario
            this.Text = "Juego de Parchís";
            this.Size = new Size(800, 900); // Ajustar el tamaño del formulario
            this.BackColor = Color.LightBlue;
            this.Font = new Font("Arial", 12, FontStyle.Bold);
            this.StartPosition = FormStartPosition.CenterScreen; // Centrar la ventana en la pantalla

            // Crear el tablero
            tablero = new TableLayoutPanel();
            tablero.RowCount = 15;
            tablero.ColumnCount = 15;
            tablero.Size = new Size(600, 600); // Ajustar el tamaño del tablero
            tablero.Location = new Point((this.ClientSize.Width - tablero.Width) / 2, 50); // Centrar el tablero horizontalmente
            tablero.BackColor = Color.White;

            // Añadir casillas al tablero
            for (int row = 0; row < 15; row++)
            {
                for (int col = 0; col < 15; col++)
                {
                    Panel casilla = new Panel();
                    casilla.BorderStyle = BorderStyle.FixedSingle;
                    casilla.Size = new Size(40, 40); // Ajustar el tamaño de las casillas

                    // Colocar las casillas de colores específicos en el tablero
                    Color color = ObtenerColorCasilla(row, col);
                    casilla.BackColor = color;

                    tablero.Controls.Add(casilla, col, row);
                }
            }

            // Etiqueta para el turno del jugador
            turnoLabel = new Label();
            turnoLabel.Text = "Turno de: Jugador 1";
            turnoLabel.Location = new Point((this.ClientSize.Width - 200) / 2, 670); // Centrar la etiqueta
            turnoLabel.AutoSize = true;
            turnoLabel.ForeColor = Color.DarkBlue;

            // Botón para tirar el dado
            tirarDadoBtn = new Button();
            tirarDadoBtn.Text = "🎲 Tirar Dado";
            tirarDadoBtn.Size = new Size(120, 40);
            tirarDadoBtn.Location = new Point(150, 720); // Ajustar la posición del botón
            tirarDadoBtn.BackColor = Color.LightGreen;
            tirarDadoBtn.FlatStyle = FlatStyle.Flat;
            tirarDadoBtn.Font = new Font("Arial", 12, FontStyle.Bold);
            tirarDadoBtn.Click += new EventHandler(TirarDadoBtn_Click);

            // PictureBox para mostrar el dado
            dadoPictureBox = new PictureBox();
            dadoPictureBox.Size = new Size(100, 100);
            dadoPictureBox.Location = new Point(500, 720); // Ajustar la posición del dado
            dadoPictureBox.BackColor = Color.White;
            dadoPictureBox.BorderStyle = BorderStyle.FixedSingle;
            dadoPictureBox.Paint += new PaintEventHandler(DibujarDado);

            // Añadir controles al formulario
            this.Controls.Add(tablero);
            this.Controls.Add(tirarDadoBtn);
            this.Controls.Add(turnoLabel);
            this.Controls.Add(dadoPictureBox);

            // Ajustar el tablero al centro
            tablero.Location = new Point((this.ClientSize.Width - tablero.Width) / 2, 50);
        }

        // Método para obtener el color de cada casilla
        private Color ObtenerColorCasilla(int row, int col)
        {
            // Zonas del tablero:
            // Base roja: Esquina superior izquierda
            if (row < 6 && col < 6) return Color.Red;

            // Base verde: Esquina inferior izquierda
            if (row > 8 && col < 6) return Color.Green;

            // Base azul: Esquina superior derecha
            if (row < 6 && col > 8) return Color.Blue;

            // Base amarilla: Esquina inferior derecha
            if (row > 8 && col > 8) return Color.Yellow;

            // Zona central
            if (row >= 6 && row <= 8 && col >= 6 && col <= 8) return Color.White;

            // Zonas de camino por colores
            // Camino rojo
            if (row == 6 && col < 6) return Color.Red;
            if (col == 6 && row < 6) return Color.Red;

            // Camino verde
            if (row > 8 && col == 6) return Color.Green;
            if (row == 8 && col < 6) return Color.Green;

            // Camino azul
            if (row == 6 && col > 8) return Color.Blue;
            if (col == 8 && row < 6) return Color.Blue;

            // Camino amarillo
            if (row == 8 && col > 8) return Color.Yellow;
            if (col == 8 && row > 8) return Color.Yellow;

            // Zonas de casillas neutrales (gris)
            return Color.LightGray;
        }

        // Evento para tirar el dado
        private void TirarDadoBtn_Click(object sender, EventArgs e)
        {
            Random random = new Random();
            resultadoDado = random.Next(1, 7); // Generar un número entre 1 y 6
            dadoPictureBox.Invalidate(); // Redibujar el dado
        }

        // Método para dibujar el dado
        private void DibujarDado(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.Clear(Color.White); // Fondo blanco para el dado
            Pen pen = new Pen(Color.Black, 2);
            Brush brush = Brushes.Black;

            int size = 20;
            int offset = 30;

            // Dibujar los puntos del dado según el resultado
            switch (resultadoDado)
            {
                case 1:
                    g.FillEllipse(brush, dadoPictureBox.Width / 2 - size / 2, dadoPictureBox.Height / 2 - size / 2, size, size);
                    break;
                case 2:
                    g.FillEllipse(brush, offset, offset, size, size);
                    g.FillEllipse(brush, dadoPictureBox.Width - offset - size, dadoPictureBox.Height - offset - size, size, size);
                    break;
                case 3:
                    g.FillEllipse(brush, offset, offset, size, size);
                    g.FillEllipse(brush, dadoPictureBox.Width / 2 - size / 2, dadoPictureBox.Height / 2 - size / 2, size, size);
                    g.FillEllipse(brush, dadoPictureBox.Width - offset - size, dadoPictureBox.Height - offset - size, size, size);
                    break;
                case 4:
                    g.FillEllipse(brush, offset, offset, size, size);
                    g.FillEllipse(brush, dadoPictureBox.Width - offset - size, offset, size, size);
                    g.FillEllipse(brush, offset, dadoPictureBox.Height - offset - size, size, size);
                    g.FillEllipse(brush, dadoPictureBox.Width - offset - size, dadoPictureBox.Height - offset - size, size, size);
                    break;
                case 5:
                    g.FillEllipse(brush, offset, offset, size, size);
                    g.FillEllipse(brush, dadoPictureBox.Width - offset - size, offset, size, size);
                    g.FillEllipse(brush, offset, dadoPictureBox.Height - offset - size, size, size);
                    g.FillEllipse(brush, dadoPictureBox.Width - offset - size, dadoPictureBox.Height - offset - size, size, size);
                    g.FillEllipse(brush, dadoPictureBox.Width / 2 - size / 2, dadoPictureBox.Height / 2 - size / 2, size, size);
                    break;
                case 6:
                    g.FillEllipse(brush, offset, offset, size, size);
                    g.FillEllipse(brush, dadoPictureBox.Width - offset - size, offset, size, size);
                    g.FillEllipse(brush, offset, dadoPictureBox.Height / 2 - size / 2, size, size);
                    g.FillEllipse(brush, dadoPictureBox.Width - offset - size, dadoPictureBox.Height / 2 - size / 2, size, size);
                    g.FillEllipse(brush, offset, dadoPictureBox.Height - offset - size, size, size);
                    g.FillEllipse(brush, dadoPictureBox.Width - offset - size, dadoPictureBox.Height - offset - size, size, size);
                    break;
            }
        }
    }
}



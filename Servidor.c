#include <string.h>
#include <mysql.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
	char nombre[25];
	int socket;
} Conectado;

typedef struct {
	Conectado conectados [100];
	int num;
} lConectados;

typedef struct {
	char jugador[4][20];
	int socket[4];
	int aceptado[4];
	int ocupado;
} Partida;

typedef struct {
	Partida partida [100];
	int num;
} lPartidas;

lPartidas listaPartidas;

lConectados lista;

int sockets[100];
int i = 0;
char host[30] = "localhost";
char contrasql[30] = "mysql";

void inicializarPartidas (lPartidas *listaPartidas);
int tPartida (char invitados[60], int numJ, lPartidas *listaPartidas, lConectados *lista);
void acceso(char nombre[25], char contrasena[25],  char respuesta[512]);
void jugadorPartidaMasLarga(char fecha[11],  char respuesta[512]);
void jugadorMasPartidas(char fecha[11], char respuesta[512]);
void winratio(char nombre[25], char fecha[11],  char respuesta[512]);
void registrar(char nombre[25], char contrasena[25],  char respuesta[512]);
void *atenderCliente(void *socket);


//------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]) 
{
	//Parte inicial del codigo, inicializa el servidor y crea los threads para los clientes
	int sock_conn, sock_listen;
	struct sockaddr_in serv_adr;
	pthread_t thread;
	lista.num = 0;
	int conexion = 0;
	int puerto = 50025;
	inicializarPartidas(&listaPartidas);
	
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error al crear socket\n");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); 
	serv_adr.sin_port = htons(puerto);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");
	int rc;
	while(conexion == 0)
	{
		printf("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf("Conexion recibida\n");
		
		sockets[i] = sock_conn;
		
		rc = pthread_create (&thread, NULL, atenderCliente , &sockets[i]);
		printf("Code %d = %s\n", rc, strerror(rc));
		
		i++;
	}
	return 0;
}


//----------------------------------------------------------------------------------------

void *atenderCliente (void *socket)
{
	int sock_conn, ret;
	int *s;
	s = (int *) socket;
	sock_conn = *s;	
	
	char peticion[512];
	char respuesta[512];
	char contestacion[512];
	char contrasena[20];
	char nombre[25];
	char fecha[11];
	char conectados[300];
	int conexion = 0;
	int numJ;
	int partida;
	int r;
	int n = 0;
	int z;
	
	//parte del servidor que lleva cada cliente, recibe la peticion del cliente y depende de la peticion realiza una accion u otra hasta que se desconecta

	while(conexion == 0)
	{
		ret = read(sock_conn, peticion, sizeof(peticion));
		printf("Recibido\n");
		peticion[ret] = '\0';
		int codigo;
		char* p;

		printf("Peticion: %s\n", peticion);
		p = strtok(peticion, "-");
		codigo = atoi(p);
		
		if(codigo == 0)
		{
			pthread_mutex_lock(&mutex); //al conectarse el usuario con su nombre o contraseña esta parte se asegura de que sean correctas y le concede el acceso
			p = strtok(NULL, "-");
			strcpy(nombre, p);
			printf("Codigo de conexion: %d\n", r);
			p = strtok(NULL, "-");
			strcpy(contrasena, p);
			printf("Codigo: %d, Nombre: %s y Contraseña: %s\n", codigo, nombre, contrasena);
			acceso(nombre, contrasena, contestacion);
			if(strcmp (contestacion, "0-Error") != 0)
				r = conectar(&lista, nombre, sock_conn);
			sprintf(respuesta, "%s", contestacion);
			write (sock_conn,respuesta,strlen(respuesta));
			pthread_mutex_unlock(&mutex);
		}
		else if(codigo == 1)
		{
			pthread_mutex_lock(&mutex); //esta es una de las peticiones que puede hacer el cliente para saber que jugador ha jugado la partida mas larga
			p = strtok(NULL, "-");
			strcpy(fecha, p);
			printf("Codigo: %d, Fecha: %s\n", codigo, fecha);
			jugadorPartidaMasLarga(fecha, contestacion);
			sprintf(respuesta, "%s", contestacion);
			write (sock_conn,respuesta,strlen(respuesta));
			pthread_mutex_unlock(&mutex);
		}
		else if(codigo == 2)
		{
			pthread_mutex_lock(&mutex); //otra peticion, esta para el jugador con mas partidas
			p = strtok(NULL, "-");
			strcpy(fecha, p);		
			printf("Codigo: %d, Fecha: %s\n", codigo, fecha);
			jugadorMasPartidas(fecha, contestacion);
			sprintf(respuesta, "%s", contestacion);
			write (sock_conn,respuesta,strlen(respuesta));
			pthread_mutex_unlock(&mutex);
		}
		else if(codigo == 3)
		{
			char pPeticion[25]; //peticion para jugador con el mayor winratio
			pthread_mutex_lock(&mutex);
			p = strtok(NULL, "-");
			strcpy(pPeticion, p);
			p = strtok(NULL, "-");
			strcpy(fecha, p);
			printf("Codigo: %d, Fecha: %s y Nombre: %s\n", codigo, fecha, pPeticion);
			winratio(pPeticion, fecha, contestacion);
			sprintf(respuesta, "%s", contestacion);
			write (sock_conn,respuesta,strlen(respuesta));
			pthread_mutex_unlock(&mutex);
		}
		else if(codigo == 4)
		{
			pthread_mutex_lock(&mutex); //esta peticion registra un nuevo usuario en la base de datos
			p = strtok(NULL, "-");
			strcpy(nombre, p);
			p = strtok(NULL, "-");
			strcpy(contrasena, p);
			printf("Codigo: %d, Fecha: %s y Nombre: %s\n", codigo, contrasena, nombre);
			registrar(nombre, contrasena, contestacion);
			if(strcmp (contestacion, "Error") != 0)
				r = conectar(&lista, nombre, sock_conn);
			sprintf(respuesta, "%s", contestacion);
			write (sock_conn,respuesta,strlen(respuesta));
			pthread_mutex_unlock(&mutex);
		}
		else if (codigo == 5) 
		{
			pthread_mutex_lock(&mutex); //desconecta al usuario
			p = strtok(NULL, "-");
			strcpy(nombre, p);
			conexion = 1;
			printf("Desconectando a %s\n", nombre);
			r = desconectar(&lista, nombre);
			printf("Codigo de desconexion: %d\n", r);
			conexion = 1;
			pthread_mutex_unlock(&mutex);
		}
		else if (codigo == 6)
		{
			pthread_mutex_lock(&mutex); //envia la peticion a los usuarios invitados a jugar y los registra en un hueco de la lista de partidas
			n = 0;
			char invitados[60];
			p = strtok(NULL, "-");
			numJ = atoi(p);
			p = strtok(NULL, "-");
			sprintf(invitados, "%s", nombre);
			while(n < numJ){
				sprintf(invitados, "%s-%s", invitados, p);
				p = strtok(NULL, "-");
				n++;
			}
			z = tPartida(invitados, numJ, &listaPartidas, &lista);
			sprintf(respuesta, "7-%d-%s", z, nombre);
			printf("Respuesta: %s\n", respuesta);
			n = 1;
			while(n < numJ + 1)
			{
				printf("Socket: %d\n", listaPartidas.partida[z].socket[n]);
				write (listaPartidas.partida[z].socket[n], respuesta, strlen(respuesta));
				n++;
			}
			pthread_mutex_unlock(&mutex);
		}
		else if(codigo == 7)
		{
			char jugadores[80]; 	//envia la respuesta de los usuarios al host de si se unen a la partida o no
			int j = 0;
			pthread_mutex_lock(&mutex);
			p = strtok(NULL, "-");
			partida = atoi(p);
			p = strtok(NULL, "-");
			n = 0;
			if (strcmp(p, "Yes") == 0)
			{
				while (strcmp(listaPartidas.partida[partida].jugador[n], nombre) != 0)
				{
					n++;
				}
				listaPartidas.partida[partida].aceptado[n] = 1;
				sprintf(jugadores, "-%s", listaPartidas.partida[partida].jugador[0]);
				n = 1;
				while (n < 4)
				{
					if (listaPartidas.partida[partida].aceptado[n] == 1) {
						sprintf(jugadores, "%s-%s", jugadores, listaPartidas.partida[partida].jugador[n]);
					}
					n++;
				}
				n = 0;
				while (n < 4)
				{
					if (listaPartidas.partida[partida].aceptado[n] == 1) {
						sprintf(respuesta, "8-%d%s", n, jugadores);
						j++;
						write(listaPartidas.partida[partida].socket[n], respuesta, strlen(respuesta));
					}
					n++;
				}
			}
			pthread_mutex_unlock(&mutex);
		}
		else if(codigo == 8)
		{
			pthread_mutex_lock(&mutex);		//notifica de el inicio de la partida a los jugadores
			n = 0;
			sprintf(respuesta, "10-");
			while (n < 4)
			{
				if (listaPartidas.partida[partida].aceptado[n] == 1) {
					write(listaPartidas.partida[partida].socket[n], respuesta, strlen(respuesta));
				}
				n++;
			}
			pthread_mutex_unlock(&mutex);
		}
		else if(codigo == 9)
		{
		char mensaje[200]; //envia mensaje al chat
		p = strtok(NULL, "/");
		if (p != NULL) {
			strcpy(mensaje, p);
			sprintf(respuesta, "9/%s", mensaje);
			printf("Mensaje: %s\n", respuesta);
			int j;
			for (j = 0; j < lista.num; j++)
			{
				write(lista.conectados[j].socket, respuesta, strlen(respuesta));
			}
		}
		}
		if (codigo == 0 || codigo == 4 || codigo == 5)
		{
			pthread_mutex_lock(&mutex); //devuelve la lista de conectados cada vez que se actualiza
			int j;
			dameConectados(&lista, conectados);
			sprintf(respuesta, "6-%s", conectados);
			printf("respuesta: %s\n", respuesta);
			pthread_mutex_unlock(&mutex);
			for (j = 0; j < i; j++)
			{
				write (sockets[j],respuesta,strlen(respuesta));
			}
			pthread_mutex_unlock(&mutex);
		}
		printf("Nombre: %s\n", nombre);
	}
	close(sock_conn);
}
//----------------------------------------------------------------------------------------

void quitarJugador (int jugador,int nPartida, lPartidas *listaPartidas) //Funcion que elimina a un jugados de la partida
{
	int n = 0;
	while (strcmp( jugador, listaPartidas->partida[nPartida].jugador[n]) != 0)
	{
		n++;
	}
	while(n < 3)
	{
		strcpy(listaPartidas->partida[nPartida].jugador[n], listaPartidas->partida[nPartida].jugador[n+1]);
		n++;
	}
}

//----------------------------------------------------------------------------------------

void inicializarPartidas (lPartidas *listaPartidas) //Funcion que inicia la partida
{
	int n;
	for (n = 0; n < 99; n++)
	{
		listaPartidas->partida[n].ocupado = 0;
	}
}

//----------------------------------------------------------------------------------------

int tPartida (char invitados[60], int numJ, lPartidas *listaPartidas, lConectados *lista) 
{
	int n = 0;
	int j = 0;
	int num;
	int encontrado = 0;
	char *p;
	p = strtok(invitados, "-");
	
	while(n < 99 && encontrado == 0) //recoje la informacion de los invitados y rellena la informacion de la primera posicion de la lista de partidas vacia
	{
		if (listaPartidas->partida[n].ocupado == 0)
		{
			encontrado = 1;
		}
		else{
			n++;	
		}
	}
	if (encontrado = 1){
		listaPartidas->partida[n].aceptado[0] = 1;
		while(j < numJ + 1)
		{
			strcpy(listaPartidas->partida[n].jugador[j], p);
			int z = damePos(lista, p);
			printf("%d\n", lista->conectados[z].socket);
			listaPartidas->partida[n].socket[j] = lista->conectados[z].socket;
			p = strtok(NULL, "-");
			j++;
		}
		
		return n;
	}
	else{
		return -1;
	}
	
}
  
//----------------------------------------------------------------------------------------			   

//----------------------------------------------------------------------------------------

void acceso(char nombre[25], char contrasena[25], char respuesta[512]) //Funcion para iniciar sesion
{
	MYSQL* conn;
	int err;
	MYSQL_RES* resultado;
	MYSQL_ROW row;

	int acceso;
	char consulta[500];

	conn = mysql_init(NULL);
	if (conn == NULL) {
		printf("Error al crear la conexion: %u %s\n",
			mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	conn = mysql_real_connect(conn, host, "root", contrasql, "M6_BBDDJuego", 0, NULL, 0);
	if (conn == NULL)
	{
		printf("Error al inicializar la conexion: %u %s\n",
			mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	err = mysql_query(conn, "use M6_BBDDJuego;");
	if (err != 0)
	{
		printf("Error al acceder a la base de datos %u %s\n",
			mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	strcpy(consulta, "select id from jugador where nombre = '"); 		//comprueva que el nombre y contraseña sean correctos y permite el acceso al cliente
	strcat(consulta, nombre);
	strcat(consulta, "' and contraseña = '");
	strcat(consulta, contrasena);
	strcat(consulta, "';");
	err = mysql_query(conn, consulta);
	if (err != 0)
	{
		printf("Error al consultar datos de la base %u %s\n",
			mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	if (row == NULL)
	{
		printf("Nombre o contraseña incorrectos\n");
		acceso = -1;
		sprintf(respuesta, "0-Error");
	}
	else
	{
		printf("Acceso garantizado al usuario con id: %s\n", row[0]);
		acceso = 0;
		sprintf(respuesta, "0-%d", acceso);
	}
}

//--------------------------------------------------------------------------------------------------
void dameConectados(lConectados *lista, char conectados [300]) //devuelve la lista de las personas conectadas al servidor en cada momento
{
	int n;
	sprintf (conectados, "%d", lista->num);
	for (n = 0; n < lista->num; n++)
	{
		sprintf(conectados, "%s-%s", conectados, lista->conectados[n].nombre);
	}
}

//----------------------------------------------------------------------------------------

int damePos (lConectados * lista, char nombre[20]) //Devuelve la posicion de un usuario en la lista de conectados
{
	int n = 0;
	int encontrado = 0;
	while ((n<lista->num) && !encontrado)
	{
		if (strcmp(lista->conectados[n].nombre, nombre) == 0)
			encontrado = 1;
		if (!encontrado)
			n++;
	}
	if (encontrado)
		return n;
	else 
		return -1;
}

//----------------------------------------------------------------------------------------

int desconectar (lConectados *lista, char nombre[20]) //elimina de la lista de conectados a un usuario
{
	int pos = damePos(lista, nombre);
	if (pos == -1)
		return -1;
	else
	{
		int n;
		for (n = pos; n < lista->num-1; n++)
		{
			lista->conectados[n] = lista->conectados[n+1];
		}
		lista->num--;
		return 0;
	}
}

//----------------------------------------------------------------------------------------

int conectar (lConectados *lista, char nombre[20], int socket) //añade a la lista de conectados a un usuario
{
	if (lista->num == 100)
		return -1;
	else
	{
		strcpy(lista->conectados[lista->num].nombre, nombre);
		lista->conectados[lista->num].socket = socket;
		lista->num++;
		printf("Litsa numero : %d\n", lista->num);
		return 0;
	}
}

//----------------------------------------------------------------------------------------

void jugadorPartidaMasLarga(char fecha[11], char respuesta[512]) //Funcion que te dice la partida mas larga del jugador
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	char nombres[50];
	char consulta[500];
	
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	conn = mysql_real_connect (conn, host,"root", contrasql,"M6_BBDDJuego", 0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	err=mysql_query(conn, "use M6_BBDDJuego;");
	if (err!=0)
	{
		printf ("Error al acceder a la base de datos %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	strcpy (consulta,"SELECT jugador.nombre FROM (jugador,historial) where historial.fecha = '"); //busca al jugador con la partida mas larga y lo devuelve
	strcat (consulta,fecha);
	strcat (consulta, "' and historial.tiempo = (select max(tiempo) from historial where fecha = '");
	strcat (consulta,fecha);
	strcat (consulta,"') and historial.idj = jugador.id;");
	err=mysql_query (conn, consulta); 
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	if (row == NULL)
	{
		printf ("No se han obtenido datos en la consulta\n");
		sprintf(respuesta, "1-Error");
	}
	else
	{
		strcpy(nombres, row[0]);
		row = mysql_fetch_row (resultado);
		while(row!=NULL)
		{
			strcat (nombres, "-");
			strcat (nombres, row[0]);
			row = mysql_fetch_row (resultado);
		}
		strcat (nombres, "\n");
		printf(nombres);
		sprintf(respuesta, "1-%s", nombres);
	}
}


//------------------------------------------------------------------------------------------------


void jugadorMasPartidas(char fecha[11], char respuesta[512]) //Funcion que dice el jugador con mas partidas
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	char nombre[25];
	char consulta[500];
	
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	conn = mysql_real_connect (conn, host,"root", contrasql, "M6_BBDDJuego", 0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	err=mysql_query(conn, "use M6_BBDDJuego;");
	if (err!=0)
	{
		printf ("Error al acceder a la base de datos %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	strcpy (consulta, "select nombre from jugador where id = (select idj from historial where fecha = '"); //busca al jugador con mas partidas y lo devuelve
	strcat (consulta, fecha);
	strcat (consulta, "' group by idj order by count(idj) DESC LIMIT 1);");
	err=mysql_query (conn, consulta); 
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	if (row == NULL)
	{
		printf ("No se han obtenido datos en la consulta\n");
		sprintf(respuesta, "2-Error");
	}
	else
	{
		printf ("Nombre de la persona: %s\n", row[0] );
		sprintf(respuesta, "2-%s", row[0]);
	}
	
}


//------------------------------------------------------------------------------------------------


void winratio(char nombre[25], char fecha[11], char respuesta[512]) //Funcion que te dice el porcentaje de victorias/derrotas del jugador
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	char consulta[500];
	int wins;
	int jugadas;
	
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	conn = mysql_real_connect (conn, host,"root", contrasql, "M6_BBDDJuego", 0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	err=mysql_query(conn, "use M6_BBDDJuego;");
	if (err!=0)
	{
		printf ("Error al acceder a la base de datos %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	strcpy (consulta,"SELECT count(historial.idj) FROM (jugador,historial) where historial.fecha = '"); //busca las partids que ha ganado y perdido un usuario saca el oprcentaje de victorias
	strcat (consulta,fecha);
	strcat (consulta, "' and jugador.nombre = '");
	strcat (consulta,nombre);
	strcat (consulta,"' and historial.idj = jugador.id");
	strcat (consulta," and historial.ganador = 'si';");
	err=mysql_query (conn, consulta); 
	if (err!=0) 
	{
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	wins = atoi(row[0]);
	strcpy (consulta,"SELECT count(historial.idj) FROM (jugador,historial) where historial.fecha = '");
	strcat (consulta,fecha);
	strcat (consulta, "' and jugador.nombre = '");
	strcat (consulta,nombre);
	strcat (consulta,"' and historial.idj = jugador.id;");
	err=mysql_query (conn, consulta); 
	
	if (err!=0) 
	{
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	jugadas = atoi(row[0]);
	
	if (row == NULL)
	{
		printf ("No se han obtenido datos en la consulta\n");
		sprintf(respuesta, "3-Error");
	}
	else
	{
		sprintf(respuesta, "3-%d-%d", wins, jugadas);
	}
	
}

//--------------------------------------------------------------------------------------------

void registrar(char nombre[25], char contrasena[25], char respuesta[512]) //Funcion que te registra en el juego
{
	
	MYSQL* conn;
	int err;
	MYSQL_RES* resultado;
	MYSQL_ROW row;

	char consulta[500];
	int registro;
	int numjug;

	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		printf("Error al crear la conexion: %u %s\n",
			mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	conn = mysql_real_connect(conn, host, "root", contrasql, "M6_BBDDJuego", 0, NULL, 0);
	if (conn == NULL)
	{
		printf("Error al inicializar la conexion: %u %s\n",
			mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	err = mysql_query(conn, "use M6_BBDDJuego;");
	if (err != 0)
	{
		printf("Error al acceder a la base de datos %u %s\n",
			mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	err = mysql_query(conn, "select MAX(id) from jugador;");
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	numjug = atoi(row[0]);
	numjug++;
	printf("este es el numero: %d\n", numjug);
	int numero = numjug;
	sprintf(consulta, "insert into jugador values (%d,'%s','%s');", numjug, nombre, contrasena);		//registra un nuevo usuario en la base de datos
	err = mysql_query(conn, consulta);
	if (err != 0)
	{
		printf("Error al consultar datos de la base %u %s\n",
			mysql_errno(conn), mysql_error(conn));
		exit(1);
		sprintf(respuesta, "4-Error");
	}
	else
	{
		sprintf(respuesta, "4-0");
	}

}



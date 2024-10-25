#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
	char nombre[20];
	int socket;
} Conectado;

typedef struct {
	Conectado conectados [100];
	int num;
} lConectados;

lConectados lista;

void acceso(char nombre[25], char contrasena[25],  char respuesta[512]);
void jugadorPartidaMasLarga(char fecha[11],  char respuesta[512]);
void jugadorMasPartidas(char fecha[11], char respuesta[512]);
void winratio(char nombre[25], char fecha[11],  char respuesta[512]);
void registrar(char nombre[25], char contrasena[25],  char respuesta[512]);
void *atenderCliente(void *socket);


void dameConectados(lConectados *lista, char conectados [300])
{
	int i;
	sprintf (conectados, "%d", lista->num);
	for (i = 0; i < lista->num; i++)
	{
		sprintf(conectados, "%s/%s", conectados, lista->conectados[i].nombre);
	}
}


int damePos (lConectados * lista, char nombre[20])
{
	int i = 0;
	int encontrado = 0;
	printf("Lista nombre : %s\n", lista->conectados[i].nombre);
	while ((i<lista->num) && !encontrado)
	{
		if (strcmp(lista->conectados[i].nombre, nombre) == 0)
			encontrado = 1;
		if (!encontrado)
			i++;
	}
	if (encontrado)
		return i;
	else 
		return -1;
}

int desconectar (lConectados *lista, char nombre[20])
{
	int pos = damePos(lista, nombre);
	if (pos == -1)
		return -1;
	else
	{
		int i;
		for (i = pos; i < lista->num-1; i++)
		{
			lista->conectados[i] = lista->conectados[i+1];
		}
		lista->num--;
		return 0;
	}
}

int conectar (lConectados *lista, char nombre[20], int socket)
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
	int r;
	int i;
	
	while(conexion == 0)
	{
		ret=read(sock_conn,peticion, sizeof(peticion));
		printf ("Recibido\n");
		peticion[ret]='\0';
		printf ("Peticion: %s\n",peticion);
		char *p = strtok(peticion, "-");
		int codigo = atoi(p);
		if(codigo == 0)
		{
			pthread_mutex_lock(&mutex);
			p = strtok(NULL, "-");
			strcpy(nombre, p);
			printf("Codigo de conexion: %d\n", r);
			p = strtok(NULL, "-");
			strcpy(contrasena, p);
			printf("Codigo: %d, Nombre: %s y Contrase￱a: %s\n", codigo, nombre, contrasena);
			acceso(nombre, contrasena, contestacion);
			if(strcmp (contestacion, "Error") != 0)
				r = conectar(&lista, nombre, socket);
			dameConectados(&lista, conectados);
			sprintf(respuesta, "%s", contestacion);
			write (sock_conn,respuesta,strlen(respuesta));
			pthread_mutex_unlock(&mutex);
		}
		if(codigo == 1)
		{
			pthread_mutex_lock(&mutex);
			p = strtok(NULL, "-");
			strcpy(fecha, p);
			printf("Codigo: %d, Fecha: %s\n", codigo, fecha);
			//jugadorPartidaMasLarga(fecha, contestacion);
			sprintf(respuesta, "%s", contestacion);
			write (sock_conn,respuesta,strlen(respuesta));
			pthread_mutex_unlock(&mutex);
		}
		if(codigo == 2)
		{
			pthread_mutex_lock(&mutex);
			p = strtok(NULL, "-");
			strcpy(fecha, p);		
			printf("Codigo: %d, Fecha: %s\n", codigo, fecha);
			
			//jugadorMasPartidas(fecha, contestacion);
			sprintf(respuesta, "%s", contestacion);
			write (sock_conn,respuesta,strlen(respuesta));
			pthread_mutex_unlock(&mutex);
		}
		if(codigo == 3)
		{
			pthread_mutex_lock(&mutex);
			p = strtok(NULL, "-");
			strcpy(nombre, p);
			p = strtok(NULL, "-");
			strcpy(fecha, p);
			printf("Codigo: %d, Fecha: %s y Nombre: %s\n", codigo, fecha, nombre);
			//winratio(nombre, fecha, contestacion);
			sprintf(respuesta, "%s", contestacion);
			write (sock_conn,respuesta,strlen(respuesta));
			pthread_mutex_unlock(&mutex);
		}
		if(codigo == 4)
		{
			pthread_mutex_lock(&mutex);
			p = strtok(NULL, "-");
			strcpy(nombre, p);
			p = strtok(NULL, "-");
			strcpy(contrasena, p);
			printf("Codigo: %d, Fecha: %s y Nombre: %s\n", codigo, contrasena, nombre);
			registrar(nombre, contrasena, contestacion);
			sprintf(respuesta, "%s", contestacion);
			write (sock_conn,respuesta,strlen(respuesta));
			pthread_mutex_unlock(&mutex);
		}
		if(codigo == 5)
		{
			pthread_mutex_lock(&mutex);
			p = strtok(NULL, "-");
			strcpy(nombre, p);
			conexion = 1;
			printf("Desconectando a %s\n", nombre);
			r = desconectar(&lista, nombre);
			printf("Codigo de desconexion: %d\n", r);
			dameConectados(&lista, conectados);
			close(sock_conn);
			pthread_mutex_unlock(&mutex);
		}
		if(codigo == 6)
		{
			pthread_mutex_lock(&mutex);
			dameConectados(&lista, conectados);
			sprintf(respuesta, "%s", conectados);
			printf("%s\n", respuesta);
			write (sock_conn, respuesta, strlen(respuesta));
			pthread_mutex_unlock(&mutex);
		}
	}
}

void acceso(char nombre[25], char contrasena[25], char respuesta[512])
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	int acceso;
	char consulta[500];
	
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	conn = mysql_real_connect (conn, "localhost","root", "mysql", NULL, 0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	err=mysql_query(conn, "use juego;");
	if (err!=0)
	{
		printf ("Error al acceder a la base de datos %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	strcpy (consulta,"select ID from JUGADOR where NOMBRE = '");
	strcat (consulta, nombre);
	strcat (consulta,"' and contrase￱a = '");
	strcat (consulta, contrasena);
	strcat (consulta,"';");
	printf ("Consulta = %s\n",consulta);
	err=mysql_query (conn, consulta); 
	if (err!=0) 
	{
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	if (row == NULL)
	{
		printf ("Nombre o contrase￱a incorrectos\n");
		acceso = -1;
		sprintf(respuesta, "Error");
	}	
	else
	{
		printf ("Acceso garantizado al usuario con id: %s\n", row[0]);
		acceso = 0;
		sprintf(respuesta, "0-%d", acceso);
	}
}


int DamePartidasGanadas(char nombre[20])
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	char consulta [100];
	
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexin
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Parchis",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//consulta SQL
	strcpy (consulta, "SELECT COUNT(*) FROM PARTIDA WHERE PARTIDA.GANADOR = '");
	strcat (consulta, nombre);
	strcat (consulta, "'");
	
	//Para comprobar errores en la consulta
	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	
	//Recogemos el resultado
	
	if (row == NULL || atoi(row[0]) == 0)
		return -1;
	else
		return atoi(row[0]);
	
	mysql_close (conn);
	exit(0);
	
}

int DameTablaJugadores(char username[20])
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	char consulta [100];
	
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Parchis",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//consulta SQL
	strcpy (consulta, "SELECT * FROM JUGADOR");
	strcat (consulta, username);
	strcat (consulta, "'");
	
	//Para comprobar errores en la consulta
	err=mysql_query(conn, consulta);
	if(err!=0){
		printf("Error al consultar los datos de la base %u%s\n",
			   mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	resultado=mysql_store_result(conn);
	
	row =mysql_fetch_row(resultado);
	if(row==NULL)
		printf ("No se han obtenido datos\n");
	else 
		while(row!=NULL){
		printf("ID: %s,Nombre: %s,Password: %s, paridas_ganadas&d,partidas_perdidas%d\n", row[0],row[1],row[2]);
	}
		//obtenemos la siguiente fila
		row=mysql_fetch_row(resultado);
		
		mysql_close (conn);
		exit(0);
}

int DameID(char nombre[20])
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char ID[10];
	char consulta [80];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexionn: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Parchis", 0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexione: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	// construimos la consulta SQL
	strcpy (consulta,"SELECT ID FROM JUGADOR WHERE NOMBRE = '"); 
	strcat (consulta, nombre);
	strcat (consulta,"'");
	// hacemos la consulta 
	err=mysql_query (conn, consulta); 
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta 
	resultado = mysql_store_result (conn); 
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		return -1;
	
	else
		// El resultado debe ser una matriz con una sola fila y una columna que contiene el nivel
		return atoi(row[0]);
	// cerrar la conexion con el servidor MYSQL 
	mysql_close (conn);
	exit(0);
}
	
void registrar(char nombre[25], char contrasena[25], char respuesta[512])
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	char consulta[500];
	int registro;
	int numjug;
	
	conn = mysql_init(NULL);
	if (conn==NULL) 
	{
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	conn = mysql_real_connect (conn, "localhost","root", "mysql", NULL, 0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	err=mysql_query(conn, "use juego;");
	if (err!=0)
	{
		printf ("Error al acceder a la base de datos %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	err=mysql_query (conn, "select count(id) from jugador;"); 
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	numjug = atoi(row[0]);
	numjug ++;
	printf("este es el numero: %d\n", numjug);
	int numero = numjug;
	sprintf(consulta, "insert into jugador values (%d,'%s','%s');", numjug, nombre, contrasena);
	err=mysql_query (conn, consulta); 
	if (err!=0) 
	{
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
		sprintf(respuesta, "Error");
	}
	else
	{
		sprintf(respuesta, "4-0");
	}
	
}
int main (int argc, char *argv[])
{
	int sock_conn, sock_listen;
	struct sockaddr_in serv_adr;
	pthread_t thread;
	lista.num = 0;
	int conexion = 0;
	int sockets[100];
	int i = 0;
	//abrimos socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creando socket");
	//hacemos el bind al puerto
	//Inicaliza en zero serv_adr
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	
	//Asocia el socket a cualquier IP de la maquina
	//htonl formatea el numero que recibe al formato necessario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	//escuchamos en el puerto 9050
	serv_adr.sin_port = htons(9050);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	//Maximo de peticiones en la cola es de 3
	if (listen(sock_listen, 3) < 0)
		printf ("Error en el Linsten");
	
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


	
	
	
			


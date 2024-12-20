DROP DATABASE IF EXISTS M6_BBDD;
CREATE DATABASE M6_BBDD;
USE M6_BBDD;

CREATE TABLE JUGADOR(
	ID VARCHAR(10) NOT NULL,
	NOMBRE VARCHAR(50),
	PASSWORD VARCHAR(15) NOT NULL,
	PRIMARY KEY(ID)
	)ENGINE = InnoDB;

CREATE TABLE PARTIDA(
	ID INT NOT NULL,
	DURACION INTEGER,
	GANADOR VARCHAR(50),
	FECHA VARCHAR(50),
	PRIMARY KEY(ID)
	)ENGINE = InnoDB;
CREATE TABLE Lista_Partidas(
	PARTIDASTOTALES INTEGER NOT NULL,
	MVP VARCHAR(10) NOT NULL,
	ID_P INT NOT NULL,
	TIEMPOMEDIO INTEGER NOT NULL,
	FOREIGN KEY (MVP) REFERENCES JUGADOR(ID),
	FOREIGN KEY (ID_P) REFERENCES PARTIDA(ID)
	)ENGINE = InnoDB;



INSERT INTO JUGADOR VALUES("123S","Marc","12D");
INSERT INTO JUGADOR VALUES("783P","Edgar","85f");
INSERT INTO JUGADOR VALUES("756J","Carlos","8e9");

INSERT INTO PARTIDA VALUES(1,320,"Marc","2/9/24");
INSERT INTO PARTIDA VALUES(2,180,"Edgar","15/5/24");
INSERT INTO PARTIDA VALUES(3,260,"Carlos","18/8/24");

INSERT INTO Lista_Partidas VALUES (6, "123S",1, 120);
INSERT INTO Lista_Partidas VALUES (5, "783P",1, 240);
INSERT INTO Lista_Partidas VALUES (4, "756J",1, 480);


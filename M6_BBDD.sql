DROP DATABASE IF EXISTS M6_BBDD;
CREATE DATABASE M6_BBDD; 
USE M6_BBDD;

CREATE TABLE jugador(
	id int,
	nombre varchar(20),
	contraseña varchar(20),
	PRIMARY KEY (id));

CREATE TABLE partida(
	id int,
	jugadores int,
	servidor varchar(5),
	PRIMARY KEY (id));

CREATE TABLE historial(
	idp int,
	idj int,
	ganador varchar(2),
	puntos int,
	tiempo int,
	fecha varchar(11));

INSERT INTO jugador VALUES (1,'Marc','1234');
INSERT INTO jugador VALUES (2,'Edgar','2222');

INSERT INTO partida VALUES (1,2,'EUW');
INSERT INTO partida VALUES (2,2,'EUW');
INSERT INTO partida VALUES (3,2,'EUW');
INSERT INTO partida VALUES (4,1,'EUW');

INSERT INTO historial VALUES (1,1,'no',5,5,'07/01/2025');
INSERT INTO historial VALUES (1,2,'si',16,5,'07/01/2025');
INSERT INTO historial VALUES (2,3,'si',16,3,'06/01/2025');
INSERT INTO historial VALUES (2,1,'no',7,3,'06/01/2025');
INSERT INTO historial VALUES (3,3,'si',16,1,'06/01/2025');
INSERT INTO historial VALUES (3,2,'si',15,1,'06/01/2025');
INSERT INTO historial VALUES (3,4,'no',6,1,'06/01/2025');
INSERT INTO historial VALUES (3,1,'no',6,1,'06/01/2025');
INSERT INTO historial VALUES (4,3,'si',16,2,'27/12/2024');
INSERT INTO historial VALUES (4,4,'no',9,2,'27/12/2024');
INSERT INTO historial VALUES (5,3,'si',16,2,'27/12/2024');
INSERT INTO historial VALUES (5,2,'no',9,2,'27/12/2024');
INSERT INTO historial VALUES (6,3,'no',9,2,'27/12/2024');
INSERT INTO historial VALUES (6,1,'si',16,2,'27/12/2024');


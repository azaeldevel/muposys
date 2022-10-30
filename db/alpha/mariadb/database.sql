
CREATE  USER IF NOT EXISTS 'muposys'@localhost IDENTIFIED BY '123456';
CREATE DATABASE `muposys-0-alpha`;
GRANT ALL PRIVILEGES ON `muposys-0-alpha`.* TO 'muposys'@'localhost';

use `muposys-0-alpha`;

CREATE TABLE Ente (id BIGINT, created datetime DEFAULT CURRENT_TIMESTAMP COMMENT 'Hora de creacion de Ente'); 
ALTER TABLE Ente MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT 'Identificador global de Objeto';


CREATE TABLE Version (ente BIGINT NOT NULL, name VARCHAR(20) UNIQUE, major SMALLINT NOT NULL,minor SMALLINT NULL,patch SMALLINT NULL, FOREIGN KEY(ente) REFERENCES Ente(id)); 
ALTER TABLE Version ADD CONSTRAINT fk_ente_Version_id FOREIGN KEY(ente) REFERENCES Ente(id);
ALTER TABLE Version ADD CONSTRAINT versions_unique UNIQUE (ente);
ALTER TABLE Version ADD CONSTRAINT version_pk PRIMARY KEY(ente) ;

CREATE TABLE Person (ente BIGINT PRIMARY KEY NOT NULL,name1 VARCHAR(30) NOT NULL,name2 VARCHAR(30),name3 VARCHAR(30),name4 VARCHAR(30));
ALTER TABLE Person ADD CONSTRAINT fk_Person_ente_Ente_id FOREIGN KEY(ente) REFERENCES Ente(id);
-- ALTER TABLE Person ADD CONSTRAINT ente_unique UNIQUE (ente);
ALTER TABLE Person ADD COLUMN age DECIMAL(6,2);
ALTER TABLE Person ADD COLUMN canyonNumber DECIMAL(6,2);
ALTER TABLE Person ADD COLUMN gender ENUM('M','F');
ALTER TABLE Person ADD COLUMN canyonLength DECIMAL(6,2);
ALTER TABLE Person MODIFY COLUMN age FLOAT;
ALTER TABLE Person MODIFY COLUMN canyonNumber FLOAT;
ALTER TABLE Person MODIFY COLUMN canyonLength FLOAT;
-- ALTER TABLE Person ADD CONSTRAINT ente_primary PRIMARY KEY (ente);
ALTER TABLE Person MODIFY COLUMN canyonLength FLOAT;

CREATE TABLE UserManagement (um BIGINT NOT NULL PRIMARY KEY);
ALTER TABLE UserManagement ADD CONSTRAINT fk_um_UserManagement_id FOREIGN KEY(um) REFERENCES Ente(id);

CREATE TABLE User (user BIGINT NOT NULL PRIMARY KEY,person BIGINT NOT NULL, name VARCHAR(20) NOT NULL,pwdtxt VARCHAR(12));
ALTER TABLE User ADD CONSTRAINT fk_user_UserManagement_um FOREIGN KEY(user) REFERENCES UserManagement(um);
ALTER TABLE User ADD CONSTRAINT fk_person_Person_ente FOREIGN KEY(person) REFERENCES Person(ente);
ALTER TABLE User ADD CONSTRAINT users_unique UNIQUE (name);
-- R: Registrado, P:Autorizacion Pendiente, A:Autorizado
ALTER TABLE User ADD COLUMN status ENUM('registrado','pendiente','autorizado');

CREATE TABLE Operation(operation BIGINT PRIMARY KEY NOT NULL,step TINYINT, FOREIGN KEY(operation) REFERENCES Ente(id));
ALTER TABLE Operation ADD CONSTRAINT fk_operation_Operation_id FOREIGN KEY(operation) REFERENCES Ente(id);
ALTER TABLE Operation ADD begin datetime COMMENT 'Hora de inicio de operación';
ALTER TABLE Operation ADD end datetime COMMENT 'Hora de terminación de la operacion';

-- user is the creator o operation
-- CREATE TABLE Operation (operation BIGINT PRIMARY KEY NOT NULL,user BIGINT NOT NULL,service BIGINT NOT NULL, FOREIGN KEY(user) REFERENCES User(user),FOREIGN KEY(service) REFERENCES Service(service));
-- ALTER TABLE Operation ADD CONSTRAINT fk_operation_Ente_id FOREIGN KEY(operation) REFERENCES Ente(id);

CREATE TABLE Variable (id BIGINT, name VARCHAR(32), value VARCHAR(32)); 
ALTER TABLE Variable MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;

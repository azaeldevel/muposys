
CREATE  USER IF NOT EXISTS 'muposys'@localhost IDENTIFIED BY '123456';
CREATE DATABASE `muposys-0-alpha`;
GRANT ALL PRIVILEGES ON `muposys-0-alpha`.* TO 'muposys'@'localhost';

USE `muposys-0-alpha`;

-- CREATE TABLE Ente (id BIGINT, created datetime DEFAULT CURRENT_TIMESTAMP COMMENT 'Hora de creacion de Ente'); 
-- ALTER TABLE Ente MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT 'Identificador global de Objeto';


CREATE TABLE Version (id BIGINT NOT NULL, name VARCHAR(20) UNIQUE, major SMALLINT NOT NULL,minor SMALLINT,patch SMALLINT); 
ALTER TABLE Version MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;

CREATE TABLE Person (id BIGINT, name1 VARCHAR(30) NOT NULL,name2 VARCHAR(30),name3 VARCHAR(30),name4 VARCHAR(30));
ALTER TABLE Person MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;
-- ALTER TABLE Person ADD CONSTRAINT fk_Person_ente_Ente_id FOREIGN KEY(ente) REFERENCES Ente(id);
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

CREATE TABLE UserManagement (id BIGINT);
ALTER TABLE UserManagement MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;
-- ALTER TABLE UserManagement ADD CONSTRAINT fk_um_UserManagement_id FOREIGN KEY(um) REFERENCES Ente(id);

CREATE TABLE User (user BIGINT,person BIGINT NOT NULL, name VARCHAR(20) NOT NULL,pwdtxt VARCHAR(12));
ALTER TABLE User MODIFY user BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;
ALTER TABLE User ADD CONSTRAINT fk_user_UserManagement_um FOREIGN KEY(user) REFERENCES UserManagement(id);
ALTER TABLE User ADD CONSTRAINT fk_person_Person_ente FOREIGN KEY(person) REFERENCES Person(id);
ALTER TABLE User ADD CONSTRAINT users_unique UNIQUE (name);
-- R: Registrado, P:Autorizacion Pendiente, A:Autorizado
ALTER TABLE User ADD COLUMN status ENUM('registrado','pendiente','autorizado');

CREATE TABLE Operation(id BIGINT);
ALTER TABLE Operation MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;
-- ALTER TABLE Operation ADD begin datetime COMMENT 'Hora de inicio de operación';
-- ALTER TABLE Operation ADD end datetime COMMENT 'Hora de terminación de la operacion';

-- user is the creator o operation
-- CREATE TABLE Operation (operation BIGINT PRIMARY KEY NOT NULL,user BIGINT NOT NULL,service BIGINT NOT NULL, FOREIGN KEY(user) REFERENCES User(user),FOREIGN KEY(service) REFERENCES Service(service));
-- ALTER TABLE Operation ADD CONSTRAINT fk_operation_Ente_id FOREIGN KEY(operation) REFERENCES Ente(id);

CREATE TABLE Variable (id BIGINT, name VARCHAR(32), value VARCHAR(64)); 
ALTER TABLE Variable MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;

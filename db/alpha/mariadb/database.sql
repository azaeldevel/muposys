
CREATE  USER IF NOT EXISTS 'muposys'@localhost IDENTIFIED BY '123456';
CREATE DATABASE `muposys-0-alpha`;
GRANT ALL PRIVILEGES ON `muposys-0-alpha`.* TO 'muposys'@'localhost';

use `muposys-0-alpha`;

CREATE TABLE Ente (id INT AUTO_INCREMENT PRIMARY KEY NOT NULL); 
ALTER TABLE Ente ADD COLUMN created datetime DEFAULT now();

CREATE TABLE Version (ente INT NOT NULL, name VARCHAR(20) UNIQUE, major SMALLINT NOT NULL,minor SMALLINT NULL,patch SMALLINT NULL, FOREIGN KEY(ente) REFERENCES Ente(id)); 
ALTER TABLE Version ADD CONSTRAINT versions_unique UNIQUE (ente);
ALTER TABLE Version ADD CONSTRAINT version_pk PRIMARY KEY(ente) ;

CREATE TABLE Person (ente INT NOT NULL,name1 VARCHAR(30) NOT NULL,name2 VARCHAR(30),name3 VARCHAR(30),name4 VARCHAR(30),FOREIGN KEY(ente) REFERENCES Ente(id));
-- ALTER TABLE Person ADD CONSTRAINT ente_unique UNIQUE (ente);
ALTER TABLE Person ADD COLUMN age DECIMAL(6,2);
ALTER TABLE Person ADD COLUMN canyonNumber DECIMAL(6,2);
ALTER TABLE Person ADD COLUMN gender ENUM('M','F');
ALTER TABLE Person ADD COLUMN canyonLength DECIMAL(6,2);
ALTER TABLE Person MODIFY COLUMN age FLOAT;
ALTER TABLE Person MODIFY COLUMN canyonNumber FLOAT;
ALTER TABLE Person MODIFY COLUMN canyonLength FLOAT;
ALTER TABLE Person ADD CONSTRAINT ente_primary PRIMARY KEY (ente);
ALTER TABLE Person MODIFY COLUMN canyonLength FLOAT;

CREATE TABLE UserManagement (um INT NOT NULL PRIMARY KEY, FOREIGN KEY(um) REFERENCES Ente(id));

CREATE TABLE User (user INT NOT NULL PRIMARY KEY,person INT NOT NULL, name VARCHAR(20) NOT NULL,pwdtxt VARCHAR(12), FOREIGN KEY(person) REFERENCES Person(ente), FOREIGN KEY(user) REFERENCES UserManagement(um));
ALTER TABLE User ADD CONSTRAINT users_unique UNIQUE (name);
-- R: Registrado, P:Autorizacion Pendiente, A:Autorizado
ALTER TABLE User ADD COLUMN status ENUM('R','P','A');

CREATE TABLE Service(service INT PRIMARY KEY NOT NULL,step INT, FOREIGN KEY(service) REFERENCES Ente(id));

-- user is the creator o operation
CREATE TABLE Operation (operation INT PRIMARY KEY NOT NULL,user INT NOT NULL,service INT NOT NULL, FOREIGN KEY(user) REFERENCES User(user),FOREIGN KEY(service) REFERENCES Service(service));
ALTER TABLE Operation ADD CONSTRAINT fk_operation_Ente_id FOREIGN KEY(operation) REFERENCES Ente(id);


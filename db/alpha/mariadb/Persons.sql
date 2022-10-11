
CREATE TABLE Persons (ente INT NOT NULL,name1 VARCHAR(30) NOT NULL,name2 VARCHAR(30),name3 VARCHAR(30),name4 VARCHAR(30),FOREIGN KEY(ente) REFERENCES Entities(id));
-- ALTER TABLE Persons ADD CONSTRAINT ente_unique UNIQUE (ente);
ALTER TABLE Persons ADD COLUMN age DECIMAL(6,2);
ALTER TABLE Persons ADD COLUMN canyonNumber DECIMAL(6,2);
ALTER TABLE Persons ADD COLUMN gender ENUM('M','F');
ALTER TABLE Persons ADD COLUMN canyonLength DECIMAL(6,2);
ALTER TABLE Persons MODIFY COLUMN age FLOAT;
ALTER TABLE Persons MODIFY COLUMN canyonNumber FLOAT;
ALTER TABLE Persons MODIFY COLUMN canyonLength FLOAT;
ALTER TABLE Persons ADD CONSTRAINT ente_primary PRIMARY KEY (ente);
ALTER TABLE Persons MODIFY COLUMN canyonLength FLOAT;

CREATE TABLE Users (user INT NOT NULL PRIMARY KEY,person INT NOT NULL, name VARCHAR(20) NOT NULL,pwdtxt VARCHAR(12), FOREIGN KEY(person) REFERENCES Persons(ente), FOREIGN KEY(user) REFERENCES Entities(id));
ALTER TABLE Users ADD CONSTRAINT users_unique UNIQUE (person,name);
-- R: Registrado, P:Autorizacion Pendiente, A:Autorizado
ALTER TABLE Users ADD COLUMN status ENUM('R','P','A');

CREATE TABLE Permissions(permission INT PRIMARY KEY NOT NULL,name VARCHAR(20) NOT NULL,brief VARCHAR(256) NOT NULL,FOREIGN KEY(permission) REFERENCES Entities(id));

CREATE TABLE User_Permission(up INT NOT NULL PRIMARY KEY,user INT NOT NULL,permission INT NOT NULL,FOREIGN KEY(permission) REFERENCES Permissions(permission),FOREIGN KEY(user) REFERENCES Users(user), FOREIGN KEY(up) REFERENCES Entities(id));


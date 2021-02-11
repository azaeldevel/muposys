
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

CREATE TABLE Users ( person INT NOT NULL, name VARCHAR(20) NOT NULL,pwdtxt VARCHAR(12), FOREIGN KEY(person) REFERENCES Persons(ente));
ALTER TABLE Users ADD CONSTRAINT users_user_unique UNIQUE (person);
ALTER TABLE Users ADD CONSTRAINT users_name_unique UNIQUE (name);
-- R: Registrado, P:Autorizacion Pendiente, A:Autorizado
ALTER TABLE Users ADD COLUMN status ENUM('R','P','A');

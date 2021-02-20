

CREATE TABLE Catalog(ente INT NOT NULL,number VARCHAR(30) NOT NULL, type ENUM ('S', 'M') NOT NULL,brief VARCHAR(256) NOT NULL,FOREIGN KEY(ente) REFERENCES Entities(id));
ALTER TABLE Catalog ADD CONSTRAINT ente_unique PRIMARY KEY (ente);
ALTER TABLE Catalog ADD CONSTRAINT number_unique UNIQUE (number);



CREATE TABLE Stock(catalog INT NOT NULL, number VARCHAR(30) NOT NULL, FOREIGN KEY(catalog) REFERENCES Catalog(ente),FOREIGN KEY(number) REFERENCES Catalog(number));
ALTER TABLE Stock ADD CONSTRAINT item UNIQUE (catalog,number);

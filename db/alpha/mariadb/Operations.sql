
CREATE TABLE Operation (op INT NOT NULL,final VARCHAR(60),user INT,FOREIGN KEY(op) REFERENCES Entities(id),FOREIGN KEY(user) REFERENCES Users(person));

-- definicion de catalogos
CREATE TABLE Catalogs(catalog INT PRIMARY KEY NOT NULL,name VARCHAR(60) NOT NULL,FOREIGN KEY(catalog) REFERENCES Entities(id));
ALTER TABLE Catalogs ADD COLUMN label VARCHAR(50);

-- instacias de catalogos de datalogo
CREATE TABLE Catalog_Items(id INT  PRIMARY KEY NOT NULL,catalog INT NOT NULL,number VARCHAR(60) NOT NULL,name VARCHAR(60) NOT NULL,FOREIGN KEY(catalog) REFERENCES Catalogs(catalog));
ALTER TABLE Catalog_Items ADD CONSTRAINT Cataloging_number_unique UNIQUE (catalog,number);
ALTER TABLE Catalog_Items ADD COLUMN active ENUM('Y','N');
ALTER TABLE Catalog_Items ADD CONSTRAINT Cataloging_Entity_id FOREIGN KEY(id) REFERENCES Entities(id) ;
ALTER TABLE Catalog_Items ADD COLUMN value FLOAT;
ALTER TABLE Catalog_Items ADD COLUMN presentation VARCHAR(5);

-- tabla base para inventario
CREATE TABLE Stock (stock INT PRIMARY KEY NOT NULL,name VARCHAR(60),FOREIGN KEY(stock) REFERENCES Entities(id));
ALTER TABLE Stock ADD COLUMN label VARCHAR(50);

-- 
CREATE TABLE Stocking (id INT  PRIMARY KEY NOT NULL,stock INT NOT NULL,item INT NOT NULL,amount INT NOT NULL,FOREIGN KEY(stock) REFERENCES Stock(stock),FOREIGN KEY(item) REFERENCES Catalog_Items(id));
ALTER TABLE Stocking ADD CONSTRAINT Stocking_id FOREIGN KEY(id) REFERENCES Entities(id);
ALTER TABLE Stocking ADD COLUMN active ENUM('Y','N');

CREATE TABLE Stocking_Production (item INT NOT NULL,subitem INT  NOT NULL, step INT DEFAULT 0, FOREIGN KEY(item) REFERENCES Stocking(id), FOREIGN KEY(subitem) REFERENCES Stocking(id));
-- CREATE TABLE OperationStock (id INT  PRIMARY KEY NOT NULL,origin INT NOT NULL,finale INT NOT NULL,FOREIGN KEY(origin) REFERENCES Stocking(id),FOREIGN KEY(finale) REFERENCES Stocking(id),FOREIGN KEY(id) REFERENCES Entities(id));

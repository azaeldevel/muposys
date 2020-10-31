CREATE TABLE Catalogs (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(30) NOT NULL, type ENUM ('in', 'out') );

CREATE TABLE CatalogsDetails (catalog INT NOT NULL, type ENUM ('service', 'material'), number VARCHAR(30) NOT NULL,FOREIGN KEY(catalog) REFERENCES Catalogs(id));



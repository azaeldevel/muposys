

-- definicion de catalogos
CREATE TABLE Catalog(catalog INT PRIMARY KEY NOT NULL,brief VARCHAR(256) NOT NULL);
ALTER TABLE Catalog ADD CONSTRAINT fk_catalog_Ente_id FOREIGN KEY(catalog) REFERENCES Ente(id);

-- instacias de catalogos de datalogo
CREATE TABLE CatalogItem(item INT  PRIMARY KEY NOT NULL,catalog INT NOT NULL,number VARCHAR(60) NOT NULL,brief VARCHAR(60) NOT NULL,FOREIGN KEY(catalog) REFERENCES Catalog(catalog));
ALTER TABLE CatalogItem ADD CONSTRAINT Cataloging_number_unique UNIQUE (catalog,number);
ALTER TABLE CatalogItem ADD COLUMN active ENUM('Y','N');
ALTER TABLE CatalogItem ADD CONSTRAINT Cataloging_Entity_id FOREIGN KEY(item) REFERENCES Ente(id) ;
ALTER TABLE CatalogItem ADD COLUMN value FLOAT;
ALTER TABLE CatalogItem ADD COLUMN presentation VARCHAR(5);

-- Definiocn de locaciones de Inventario
CREATE TABLE Stock (stock INT PRIMARY KEY NOT NULL,brief VARCHAR(256),FOREIGN KEY(stock) REFERENCES Ente(id));

-- Almacena los elememtos de invetario involucrado en cada operacion
CREATE TABLE OperationStock(operation INT NOT NULL,stock INT NOT NULL,item INT NOT NULL,amount INT NOT NULL);
ALTER TABLE OperationStock ADD CONSTRAINT fk_operation_Operation_operation FOREIGN KEY(operation) REFERENCES Operation(operation);
ALTER TABLE OperationStock ADD CONSTRAINT fk_stock_Stock_stock FOREIGN KEY(stock) REFERENCES Stock(stock);
ALTER TABLE OperationStock ADD CONSTRAINT fk_item_CatalogItem_item FOREIGN KEY(item) REFERENCES CatalogItem(item);

--en esta tabla los registros seran borrado cuando amount sea 0, por lo que stocking no es un valor referencia ble para muposys
CREATE TABLE Stocking (stocking INT AUTO_INCREMENT PRIMARY KEY NOT NULL,stock INT NOT NULL,item INT NOT NULL,amount INT NOT NULL,FOREIGN KEY(stock) REFERENCES Stock(stock),FOREIGN KEY(item) REFERENCES CatalogItem(item));

-- CREATE TABLE Stocking_Production (stocking INT PRIMARY KEY NOT NULL,subitem INT, step INT, FOREIGN KEY(item) REFERENCES Stocking(id), FOREIGN KEY(CatalogItem) REFERENCES Stocking(stocking));

-- CREATE TABLE OperationStock (id INT  PRIMARY KEY NOT NULL,origin INT NOT NULL,finale INT NOT NULL, FOREIGN KEY(origin) REFERENCES Stocking(id), FOREIGN KEY(finale) REFERENCES Stocking(id), FOREIGN KEY(id) REFERENCES Ente(id));



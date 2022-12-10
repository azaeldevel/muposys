

-- definicion de catalogos
CREATE TABLE Catalog(id BIGINT,brief VARCHAR(256) NOT NULL);
ALTER TABLE Catalog MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;


-- instacias de catalogos de datalogo
CREATE TABLE CatalogItem(id BIGINT, catalog BIGINT NOT NULL,number VARCHAR(60) NOT NULL,brief VARCHAR(60) NOT NULL);
ALTER TABLE CatalogItem MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;
ALTER TABLE CatalogItem ADD CONSTRAINT fk_item_CatalogItem_id FOREIGN KEY(catalog) REFERENCES Catalog(id);
ALTER TABLE CatalogItem ADD CONSTRAINT Cataloging_number_unique UNIQUE (catalog,number);
ALTER TABLE CatalogItem ADD COLUMN active ENUM('Y','N');
-- ALTER TABLE CatalogItem ADD CONSTRAINT Cataloging_Entity_id FOREIGN KEY(item) REFERENCES Ente(id) ;
ALTER TABLE CatalogItem ADD COLUMN value FLOAT;
ALTER TABLE CatalogItem ADD COLUMN presentation VARCHAR(5);
ALTER TABLE CatalogItem ADD COLUMN type ENUM('service','matter');

-- Definiocn de locaciones de Inventario
CREATE TABLE Stock (id BIGINT,brief VARCHAR(256));
ALTER TABLE Stock MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;
-- ALTER TABLE Stock ADD CONSTRAINT fk_stock_Stock_id FOREIGN KEY(stock) REFERENCES Ente(id);

-- Almacena los elememtos de invetario involucrado en cada operacion
-- CREATE TABLE OperationStock(operation BIGINT NOT NULL,stock BIGINT NOT NULL,item BIGINT NOT NULL,amount BIGINT NOT NULL);
-- ALTER TABLE OperationStock ADD CONSTRAINT fk_operation_Operation_operation FOREIGN KEY(operation) REFERENCES Operation(operation);
-- ALTER TABLE OperationStock ADD CONSTRAINT fk_stock_Stock_stock FOREIGN KEY(stock) REFERENCES Stock(stock);
-- ALTER TABLE OperationStock ADD CONSTRAINT fk_item_CatalogItem_item FOREIGN KEY(item) REFERENCES CatalogItem(item);

CREATE TABLE Stocking (id BIGINT,stock BIGINT NOT NULL,item BIGINT NOT NULL,amount SMALLINT NOT NULL);
ALTER TABLE Stocking MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;
ALTER TABLE Stocking ADD CONSTRAINT fk_stock_Stock_stock FOREIGN KEY(stock) REFERENCES Stock(id);
ALTER TABLE Stocking ADD CONSTRAINT fk_item_CatalogItem_item FOREIGN KEY(item) REFERENCES CatalogItem(id);

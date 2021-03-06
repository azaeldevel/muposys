
CREATE TABLE Supplier (supplier INT NOT NULL);
ALTER TABLE Supplier ADD number INT NOT NULL;
ALTER TABLE Supplier ADD nameShort VARCHAR(30) NOT NULL;
ALTER TABLE Supplier ADD CONSTRAINT FOREIGN KEY(supplier) REFERENCES Entities(id);
ALTER TABLE Supplier ADD CONSTRAINT PRIMARY KEY (supplier);
ALTER TABLE Supplier ADD CONSTRAINT UNIQUE (number);


CREATE TABLE Movements (id INT NOT NULL);
-- direction I : in, O : Out
ALTER TABLE Movements ADD direction ENUM ('I', 'O');
-- source: cliente o proveedor
ALTER TABLE Movements ADD source INT NOT NULL;
ALTER TABLE Movements ADD item INT NOT NULL;
ALTER TABLE Movements ADD delta INT NOT NULL;
ALTER TABLE Movements ADD doc INT NOT NULL; -- primero se crea el documento para referirlo aqui
ALTER TABLE Movements ADD CONSTRAINT FOREIGN KEY(id) REFERENCES Entities(id);
ALTER TABLE Movements ADD CONSTRAINT PRIMARY KEY (id);
ALTER TABLE Movements ADD CONSTRAINT FOREIGN KEY(item) REFERENCES CatalogSupplier(item);
ALTER TABLE Movements ADD CONSTRAINT FOREIGN KEY(doc) REFERENCES Entities(id);


CREATE TABLE Buys (doc INT NOT NULL);
ALTER TABLE Buys ADD supplier INT NOT NULL;
ALTER TABLE Buys ADD status ENUM ('creating','created','quoting','quoted','buyed') NOT NULL DEFAULT 'creating';
ALTER TABLE Buys ADD date DATETIME DEFAULT NOW();
ALTER TABLE Buys ADD CONSTRAINT FOREIGN KEY(doc) REFERENCES Entities(id);
ALTER TABLE Buys ADD CONSTRAINT PRIMARY KEY(doc);
ALTER TABLE Buys ADD CONSTRAINT FOREIGN KEY(supplier) REFERENCES Supplier(supplier);

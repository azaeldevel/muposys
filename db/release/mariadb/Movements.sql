
CREATE TABLE Movements (id INT NOT NULL);
-- direction I : in, O : Out
ALTER TABLE Movements ADD direction ENUM ('I', 'O');
-- source: cliente o proveedor
ALTER TABLE Movements ADD source INT NOT NULL;
ALTER TABLE Movements ADD item INT NOT NULL;
ALTER TABLE Movements ADD delta INT NOT NULL;
-- ALTER TABLE Movements ADD doc INT NOT NULL; -- primero se crea el documento para referirlo aqui
ALTER TABLE Movements ADD CONSTRAINT FOREIGN KEY(id) REFERENCES Entities(id);
ALTER TABLE Movements ADD CONSTRAINT PRIMARY KEY (id);
-- ALTER TABLE Movements ADD CONSTRAINT FOREIGN KEY(doc) REFERENCES Entities(id);

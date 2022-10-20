
CREATE TABLE Service(service INT PRIMARY KEY NOT NULL,step INT, FOREIGN KEY(service) REFERENCES Operation(operation));



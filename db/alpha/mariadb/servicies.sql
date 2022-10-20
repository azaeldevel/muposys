

-- definicion de catalogos
CREATE TABLE Serivce(service INT PRIMARY KEY NOT NULL,FOREIGN KEY(service) REFERENCES Ente(id));

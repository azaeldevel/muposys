
CREATE TABLE Entities (id INT AUTO_INCREMENT PRIMARY KEY NOT NULL, md5sum VARCHAR(32)); 

CREATE TABLE Versions (ente INT NOT NULL, name VARCHAR(20) UNIQUE, major SMALLINT NOT NULL,minor SMALLINT NULL,patch SMALLINT NULL, FOREIGN KEY(ente) REFERENCES Entities(id)); 
ALTER TABLE Versions ADD CONSTRAINT versions_unique UNIQUE (ente);


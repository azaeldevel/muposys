CREATE TABLE Versions (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(20) UNIQUE, major SMALLINT NOT NULL,minor SMALLINT NOT NULL,patch SMALLINT NOT NULL); 

GRANT ALL PRIVILEGES ON `sysapp.alpha`.* TO 'sysapp'@localhost IDENTIFIED BY '123456';



INSERT INTO Versions(name,major,minor,patch) VALUES('database',0,1,0);

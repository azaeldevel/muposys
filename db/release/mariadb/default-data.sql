
INSERT INTO Entities(id) VALUES(1);
INSERT INTO Entities(id) VALUES(2);
INSERT INTO Entities(id) VALUES(3);-- <<<--- last use
INSERT INTO Entities(id) VALUES(4);
INSERT INTO Entities(id) VALUES(5);
INSERT INTO Entities(id) VALUES(6);
INSERT INTO Entities(id) VALUES(7);
INSERT INTO Entities(id) VALUES(8);
INSERT INTO Entities(id) VALUES(9);
INSERT INTO Entities(id) VALUES(10);

INSERT INTO Persons(ente,name1) VALUES(1,'root');

INSERT INTO Users(person,name) VALUES(1,'root');
UPDATE Users SET pwdtxt='123456' WHERE person = 1;
UPDATE Users SET status='A' WHERE person = 1;

INSERT INTO Versions(ente,name,major,minor,patch) VALUES(2,'database',0,1,0);

UPDATE Persons SET name1='Azael' WHERE ente = 1;
UPDATE Persons SET name3='Reyes' WHERE ente = 1;

INSERT INTO Supplier(supplier,number,nameShort) VALUES(3,'1001','Azael Reyes');

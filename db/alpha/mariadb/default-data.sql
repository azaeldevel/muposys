
INSERT INTO Entities(id) VALUES(1);
INSERT INTO Entities(id) VALUES(2);

INSERT INTO Persons(ente,name1) VALUES(1,'root');

INSERT INTO Users(person,name) VALUES(1,'root');
UPDATE Users SET pwdtxt='123456' WHERE person = 1;
UPDATE Users SET status='A' WHERE person = 1;

INSERT INTO Versions(ente,name,major,minor,patch) VALUES(2,'database',0,1,0);

UPDATE Persons SET name1='Azael' WHERE ente = 1;
UPDATE Persons SET name3='Reyes' WHERE ente = 1;

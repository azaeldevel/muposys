
INSERT INTO Entities(id) VALUES(1);
INSERT INTO Entities(id) VALUES(2);

INSERT INTO Persons(person,name1) VALUES(1,'root');

INSERT INTO Users(user,name) VALUES(1,'root');
UPDATE Users SET pwdtxt='123456' WHERE user = 1;

INSERT INTO Versions(ente,name,major,minor) VALUES(2,'database',0,1);


INSERT INTO Entities(id) VALUES(1);
INSERT INTO Entities(id) VALUES(2);
INSERT INTO Entities(id) VALUES(3);
INSERT INTO Entities(id) VALUES(4);
INSERT INTO Entities(id) VALUES(5);
INSERT INTO Entities(id) VALUES(6);
INSERT INTO Entities(id) VALUES(7);
INSERT INTO Entities(id) VALUES(8);
INSERT INTO Entities(id) VALUES(9);-- <<<--- last use
INSERT INTO Entities(id) VALUES(10);

INSERT INTO Persons(ente,name1) VALUES(1,'root');

INSERT INTO Users(user,person,name) VALUES(2,1,'root');
UPDATE Users SET pwdtxt='123456' WHERE person = 2;
UPDATE Users SET status='A' WHERE person = 2;

INSERT INTO Versions(ente,name,major,minor,patch) VALUES(3,'database',0,2,0);

UPDATE Persons SET name1='Azael' WHERE ente = 1;
UPDATE Persons SET name3='Reyes' WHERE ente = 1;

INSERT INTO Permissions(permission,name,brief) VALUES(3,'login','Permisos para acceder a muposys.');

INSERT INTO User_Permission(up,user,permission) VALUES(4,2,3);

INSERT INTO Catalogs(catalog,name) VALUES(5,'supplies');
UPDATE Catalogs SET label = 'Insumos' WHERE catalog = 5 and name = 'supplies';

INSERT INTO Catalogs(catalog,name) VALUES(6,'internal');
UPDATE Catalogs SET label = 'Interno' WHERE catalog = 6 and name = 'internal';

INSERT INTO Catalogs(catalog,name) VALUES(7,'offers');
UPDATE Catalogs SET label = 'Oferta' WHERE catalog = 7 and name = 'offers';

INSERT INTO Stock(stock,name,label) VALUES(8,'main','Principal');

INSERT INTO Stock(stock,name,label) VALUES(9,'production','Producción');



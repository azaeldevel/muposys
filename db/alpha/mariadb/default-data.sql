
INSERT INTO Ente(id) VALUES(1);
INSERT INTO Ente(id) VALUES(2);
INSERT INTO Ente(id) VALUES(3);
INSERT INTO Ente(id) VALUES(4);
INSERT INTO Ente(id) VALUES(5);
INSERT INTO Ente(id) VALUES(6);
INSERT INTO Ente(id) VALUES(7);
INSERT INTO Ente(id) VALUES(8);
INSERT INTO Ente(id) VALUES(9);
INSERT INTO Ente(id) VALUES(10);-- <<<--- last use

INSERT INTO Person(ente,name1) VALUES(1,'root');

INSERT INTO UserManagement(um) VALUES(2);
INSERT INTO User(user,person,name) VALUES(2,1,'root');
UPDATE User SET pwdtxt='123456' WHERE user = 2;
UPDATE User SET status='A' WHERE user = 2;

INSERT INTO Version(ente,name,major,minor,patch) VALUES(3,'database',0,2,0);

UPDATE Person SET name1='Azael' WHERE ente = 1;
UPDATE Person SET name3='Reyes' WHERE ente = 1;

INSERT INTO Permission(permission,name,brief) VALUES(3,'login','Permisos para acceder a muposys.');

INSERT INTO User_Permission(up,user,permission) VALUES(4,2,3);

INSERT INTO Catalog(catalog,name) VALUES(5,'supplies');
UPDATE Catalog SET label = 'Insumos' WHERE catalog = 5 and name = 'supplies';

INSERT INTO Catalog(catalog,name) VALUES(6,'internal');
UPDATE Catalog SET label = 'Interno' WHERE catalog = 6 and name = 'internal';

INSERT INTO Catalog(catalog,name) VALUES(7,'offers');
UPDATE Catalog SET label = 'Oferta' WHERE catalog = 7 and name = 'offers';

INSERT INTO Stock(stock,name,label) VALUES(8,'main','Principal');

INSERT INTO Stock(stock,name,label) VALUES(9,'production','Producción');


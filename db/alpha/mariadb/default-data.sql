
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

INSERT INTO UserManagement(um) VALUES(3);
INSERT INTO Permission(permission,name,brief) VALUES(3,'login','Permisos para acceder a muposys.');

INSERT INTO UserPermission(user,permission) VALUES(2,3);

INSERT INTO Catalog(catalog,brief) VALUES(5,'Insumos');

INSERT INTO Catalog(catalog,brief) VALUES(6,'Interno');

INSERT INTO Catalog(catalog,brief) VALUES(7,'Oferta');

INSERT INTO Stock(stock,brief) VALUES(8,'Principal');

INSERT INTO Stock(stock,brief) VALUES(9,'Producción');




INSERT INTO Version(id,name,major,minor,patch) VALUES(1,'database',0,2,0);

INSERT INTO UserManagement(id) VALUES(1);
INSERT INTO Permission(id,name,brief) VALUES(1,'login','Permisos para acceder a muposys.');
INSERT INTO Person(id,name1,name3) VALUES(1,'Azael','Reyes');

INSERT INTO UserManagement(id) VALUES(2);
INSERT INTO User(id,person,name) VALUES(2,1,'root');
UPDATE User SET pwdtxt='123456' WHERE id = 2;
UPDATE User SET status=3 WHERE id = 2;
INSERT INTO UserPermission(user,permission) VALUES(2,1);


INSERT INTO Catalog(id,brief) VALUES(1,'Insumos');
INSERT INTO Catalog(id,brief) VALUES(2,'Interno');
INSERT INTO Catalog(id,brief) VALUES(3,'Oferta');


INSERT INTO Stock(id,brief) VALUES(1,'Principal');
INSERT INTO Stock(id,brief) VALUES(2,'Produccion');



INSERT INTO UserManagement(id) VALUES(4);
INSERT INTO Person(id,name1,name3) VALUES(4,'Juan','Ramos');
INSERT INTO User(id,person,name) VALUES(4,4,'jramos');
UPDATE User SET pwdtxt='123456' WHERE id = 4;
UPDATE User SET status=3 WHERE id = 4;
INSERT INTO UserPermission(user,permission) VALUES(4,1);

INSERT INTO UserManagement(id) VALUES(5);
INSERT INTO Person(id,name1,name3) VALUES(5,'Maria','Lopez');
INSERT INTO User(id,person,name) VALUES(5,5,'mlopez');
UPDATE User SET pwdtxt='123456' WHERE id = 5;
UPDATE User SET status=3 WHERE id = 5;
INSERT INTO UserPermission(user,permission) VALUES(5,1);

INSERT INTO UserManagement(id) VALUES(6);
INSERT INTO Person(id,name1,name3) VALUES(6,'Laura','Ramirez');
INSERT INTO User(id,person,name) VALUES(6,6,'lramirez');
UPDATE User SET pwdtxt='123456' WHERE id = 6;
UPDATE User SET status=3 WHERE id = 6;
INSERT INTO UserPermission(user,permission) VALUES(6,1);

INSERT INTO UserManagement(id) VALUES(7);
INSERT INTO Person(id,name1,name3) VALUES(7,'Rubi','Martinez');
INSERT INTO User(id,person,name) VALUES(7,7,'rmartinez');
UPDATE User SET pwdtxt='123456' WHERE id = 7;
INSERT INTO UserPermission(user,permission) VALUES(7,1);
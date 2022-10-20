


CREATE TABLE Permission(permission INT PRIMARY KEY NOT NULL,name VARCHAR(20) NOT NULL,brief VARCHAR(256) NOT NULL,FOREIGN KEY(permission) REFERENCES UserManagement(um));

CREATE TABLE UserPermission(id INT AUTO_INCREMENT NOT NULL PRIMARY KEY,user INT NOT NULL,permission INT NOT NULL);
ALTER TABLE UserPermission ADD CONSTRAINT fk_user_User_user FOREIGN KEY(user) REFERENCES User(user);
ALTER TABLE UserPermission ADD CONSTRAINT fk_permission_User_permission FOREIGN KEY(permission) REFERENCES Permission(permission);


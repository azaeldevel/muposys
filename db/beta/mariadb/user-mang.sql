


CREATE TABLE Permission(permission BIGINT PRIMARY KEY NOT NULL,name VARCHAR(20) NOT NULL,brief VARCHAR(256) NOT NULL,FOREIGN KEY(permission) REFERENCES UserManagement(um));

CREATE TABLE UserPermission(id BIGINT AUTO_INCREMENT NOT NULL PRIMARY KEY,user BIGINT NOT NULL,permission BIGINT NOT NULL);
ALTER TABLE UserPermission ADD CONSTRAINT fk_user_User_user FOREIGN KEY(user) REFERENCES User(user);
ALTER TABLE UserPermission ADD CONSTRAINT fk_permission_User_permission FOREIGN KEY(permission) REFERENCES Permission(permission);


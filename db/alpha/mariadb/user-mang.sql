


CREATE TABLE Permission(id BIGINT,name VARCHAR(20) NOT NULL,brief VARCHAR(256) NOT NULL);
ALTER TABLE Permission MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;

CREATE TABLE UserPermission(id BIGINT, user BIGINT NOT NULL,permission BIGINT NOT NULL);
ALTER TABLE UserPermission MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;
ALTER TABLE UserPermission ADD CONSTRAINT fk_user_User_user FOREIGN KEY(user) REFERENCES User(id);
ALTER TABLE UserPermission ADD CONSTRAINT fk_permission_User_permission FOREIGN KEY(permission) REFERENCES Permission(id);


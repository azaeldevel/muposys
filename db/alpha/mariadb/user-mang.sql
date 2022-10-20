


CREATE TABLE Permissions(permission INT PRIMARY KEY NOT NULL,name VARCHAR(20) NOT NULL,brief VARCHAR(256) NOT NULL,FOREIGN KEY(permission) REFERENCES Entities(id));

CREATE TABLE User_Permission(up INT NOT NULL PRIMARY KEY,user INT NOT NULL,permission INT NOT NULL,FOREIGN KEY(permission) REFERENCES Permissions(permission),FOREIGN KEY(user) REFERENCES Users(user), FOREIGN KEY(up) REFERENCES Entities(id));


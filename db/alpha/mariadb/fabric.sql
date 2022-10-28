
CREATE TABLE Progress (stocking BIGINT NOT NULL, operation BIGINT NOT NULL, step TINYINT NOT NULL DEFAULT 0 COMMENT 'Identificador de progreso actual');
ALTER TABLE Progress ADD CONSTRAINT pk_Progress PRIMARY KEY(stocking);
ALTER TABLE Progress ADD CONSTRAINT fk_stocking_Stocking_stocking FOREIGN KEY(stocking) REFERENCES Stocking(stocking);
ALTER TABLE Progress ADD CONSTRAINT fk_operation_Operation_operation FOREIGN KEY(operation) REFERENCES Operation(operation);
ALTER TABLE Progress ADD updated datetime DEFAULT CURRENT_TIMESTAMP COMMENT 'Hora de actualizacion de progreso';
ALTER TABLE Progress ADD user BIGINT NOT NULL COMMENT 'Usuario que realiza la actualización progreso';
ALTER TABLE Progress ADD CONSTRAINT fk_Progress_user_User_user FOREIGN KEY(stocking) REFERENCES User(user);




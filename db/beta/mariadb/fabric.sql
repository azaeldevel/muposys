
CREATE TABLE Progress (stocking BIGINT NOT NULL, operation BIGINT NOT NULL, step SMALLINT NOT NULL DEFAULT 0 COMMENT 'Identificador de progreso actual');
ALTER TABLE Progress ADD CONSTRAINT pk_Progress PRIMARY KEY(stocking);
ALTER TABLE Progress ADD CONSTRAINT fk_stocking_Stocking_stocking FOREIGN KEY(stocking) REFERENCES Stocking(stocking);
ALTER TABLE Progress ADD CONSTRAINT fk_operation_Operation_operation FOREIGN KEY(operation) REFERENCES Operation(operation);
-- ALTER TABLE Progress ADD updated datetime DEFAULT CURRENT_TIMESTAMP COMMENT 'Hora de actualizacion de progreso';


CREATE TABLE ProgressTrace (trace BIGINT, stocking BIGINT NOT NULL, operation BIGINT NOT NULL, step SMALLINT NOT NULL DEFAULT 0 COMMENT 'Identificador de progreso actual');
ALTER TABLE ProgressTrace ADD updated datetime DEFAULT CURRENT_TIMESTAMP COMMENT 'Hora de actualizacion del operacion';
ALTER TABLE ProgressTrace MODIFY trace BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;
ALTER TABLE ProgressTrace ADD CONSTRAINT fk_ProgressTrace_stocking_Progress_stocking FOREIGN KEY(stocking) REFERENCES Progress(stocking);
ALTER TABLE ProgressTrace ADD CONSTRAINT fk_ProgressTrace_operation_OProgress_operation FOREIGN KEY(operation) REFERENCES Progress(operation);



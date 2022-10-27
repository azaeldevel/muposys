
CREATE TABLE Progress (stocking BIGINT NOT NULL, operation BIGINT NOT NULL, step TINYINT NOT NULL DEFAULT 0);
ALTER TABLE Progress ADD CONSTRAINT pk_Progress PRIMARY KEY(stocking);
ALTER TABLE Progress ADD CONSTRAINT fk_stocking_Stocking_stocking FOREIGN KEY(stocking) REFERENCES Stocking(stocking);
ALTER TABLE Progress ADD CONSTRAINT fk_operation_Operation_operation FOREIGN KEY(operation) REFERENCES Operation(operation);




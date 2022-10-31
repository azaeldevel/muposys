
CREATE TABLE Session (id BIGINT NOT NULL, client VARCHAR(256) NOT NULL, session VARCHAR(16) COMMENT 'Identificador de la session');
ALTER TABLE Session MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;

ALTER TABLE Variable ADD session BIGINT COMMENT 'La llave de referenciada http';
ALTER TABLE Variable ADD CONSTRAINT fk_Variable_session_Ente_id FOREIGN KEY(session) REFERENCES Session(id);

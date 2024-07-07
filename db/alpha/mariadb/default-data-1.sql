
UPDATE Version SET major=0, minor=3,patch=0 WHERE id = 1;
UPDATE Person SET name1='Root', name3='User' WHERE id = 1;


ALTER TABLE Catalog ADD COLUMN name VARCHAR(30);
ALTER TABLE Catalog  COMMENT 'Lista de catalogos';
ALTER TABLE Stock  COMMENT 'Lista de almacenes';
ALTER TABLE Stocking  COMMENT 'Lista de todos los item registrado';


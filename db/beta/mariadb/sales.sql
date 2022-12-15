
CREATE TABLE Sale (sale BIGINT NOT NULL, operation BIGINT NOT NULL, stock BIGINT NOT NULL, item BIGINT NOT NULL, amount SMALLINT NOT NULL);
ALTER TABLE Sale MODIFY sale BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;
ALTER TABLE Sale ADD CONSTRAINT fk_operation_Sale_operation FOREIGN KEY(operation) REFERENCES Operation(operation);
ALTER TABLE Sale ADD CONSTRAINT fk_stock_Sale_stock FOREIGN KEY(stock) REFERENCES Stock(stock);
ALTER TABLE Sale ADD CONSTRAINT fk_item_Sale_item FOREIGN KEY(item) REFERENCES CatalogItem(item);

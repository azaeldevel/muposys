
CREATE  USER IF NOT EXISTS 'muposys'@localhost IDENTIFIED BY '123456';
CREATE DATABASE `muposys-0-alpha`;
GRANT ALL PRIVILEGES ON `muposys-0-alpha`.* TO 'muposys'@'localhost';


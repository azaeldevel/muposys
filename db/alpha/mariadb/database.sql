
CREATE USER 'muposys'@localhost IDENTIFIED BY '123456';
CREATE DATABASE `muposys-0.1-alpha`;
GRANT ALL PRIVILEGES ON `muposys-0.1-alpha`.* TO 'muposys'@'localhost';


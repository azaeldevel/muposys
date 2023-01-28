
CREATE  USER IF NOT EXISTS 'muposys'@localhost IDENTIFIED BY '123456';
CREATE DATABASE `muposys-dev` character set ASCII collate ASCII_BIN;
GRANT ALL PRIVILEGES ON `muposys-dev`.* TO 'muposys'@'localhost';

USE `muposys-dev`;


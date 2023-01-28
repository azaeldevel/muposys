
CREATE  USER IF NOT EXISTS 'muposys'@localhost IDENTIFIED BY '123456';
CREATE DATABASE `muposys`  character set ASCII collate ASCII_BIN;
GRANT ALL PRIVILEGES ON `muposys`.* TO 'muposys'@'localhost';

USE `muposys`;


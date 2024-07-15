CREATE VIEW User_Autho AS SELECT id, concat("Basic ",to_base64(concat(name,":",pwdtxt))) as autho FROM User


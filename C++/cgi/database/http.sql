BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "Variables" (
	"id"	INTEGER NOT NULL,
	"session"	INTEGER NOT NULL,
	"name"	TEXT NOT NULL,
	"value"	TEXT NOT NULL,
	PRIMARY KEY("id" AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS "Session" (
	"id"	INTEGER NOT NULL,
	"remote_addr"	TEXT NOT NULL,
	"port"	INTEGER NOT NULL,	
	"session"	TEXT NOT NULL,
	"lasttime"	TEXT NOT NULL,
	PRIMARY KEY("id" AUTOINCREMENT)
);
CREATE UNIQUE INDEX IF NOT EXISTS "session_varialbe_unique" ON "Variables" (
	"session",
	"name"
);
CREATE UNIQUE INDEX IF NOT EXISTS "remote_addr_unique" ON "Session" (
	"remote_addr"
);
CREATE UNIQUE INDEX IF NOT EXISTS "session_unique" ON "Session" (
	"session"
);
COMMIT;

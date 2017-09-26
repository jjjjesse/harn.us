#include "splashkit.h"

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

using namespace std;


// Syncing sqlite to online database
// https://www.quora.com/How-do-I-sync-a-server-database-and-a-local-SQLite-database




// from https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

// from https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
sqlite3* connect_database()
{
    int rc;
    sqlite3 *db;

    rc = sqlite3_open("harnus.db", &db);

    if( rc ) 
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }
    else 
    {
        fprintf(stderr, "Opened database successfully\n");
    }
    return db;
}

void create_table(const char *sql)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    db = connect_database();
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } 
    else 
    {
        fprintf(stdout, "Records created successfully\n");
    }    
    sqlite3_close(db);
}



void setup_tables()
{
    const char *project_sql;
    const char *subject_sql;
    const char *record_sql;

    project_sql = "CREATE TABLE PROJECT("           
         "PROJECT_ID INT PRIMARY KEY     NOT NULL," 
         "PROJECT_NAME   TEXT            NOT NULL);";

    subject_sql = "CREATE TABLE SUBJECT("           
         "SUBJECT_ID INT PRIMARY KEY     NOT NULL," 
         "PROJECT_ID INT FOREIGN KEY     NOT NULL,"  
         "SUBJECT_NAME   TEXT            NOT NULL," 
         "FINAL_MARK INT);";

    record_sql =  "CREATE TABLE RECORD("            
         "RECORD_ID INT PRIMARY KEY      NOT NULL," 
         "SUBJECT_ID INT FOREIGN KEY     NOT NULL," 
         "PROJECT_NAME   TEXT            NOT NULL,"  
         "START_TIME     TEXT            NOT NULL," 
         "END_TIME       TEXT            NOT NULL," 
         "SECONDS        INT             NOT NULL," 
         "MINUTES        INT             NOT NULL," 
         "HOURS          INT             NOT NULL);";

    create_table(project_sql);
    create_table(subject_sql);
    create_table(record_sql);
    refresh_terminal();
}

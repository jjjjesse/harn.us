#include "harnus.h"




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

void execute_sql(const char *sql)
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
         "PROJECT_ID         INTEGER PRIMARY KEY     NOT NULL," 
         "PROJECT_NAME       TEXT                    NOT NULL);";

    subject_sql = "CREATE TABLE SUBJECT("           
         "SUBJECT_ID         INTEGER PRIMARY KEY     NOT NULL," 
         "PROJECT_ID         INTEGER                 NOT NULL,"  
         "SUBJECT_NAME       TEXT                    NOT NULL," 
         "FINAL_MARK INT                             ,"
         "FOREIGN KEY(PROJECT_ID) REFERENCES PROJECT(PROJECT_ID));";

    record_sql =  "CREATE TABLE RECORD("            
         "RECORD_ID          INTEGER  PRIMARY KEY    NOT NULL," 
         "SUBJECT_ID         INTEGER                 NOT NULL,"  
         "START_TIME         TEXT                    NOT NULL," 
         "END_TIME           TEXT                    NOT NULL," 
         "LENGTH             TEXT                    NOT NULL,"
         "FOREIGN KEY(SUBJECT_ID) REFERENCES SUBJECT(SUBJECT_ID));";

    execute_sql(project_sql);
    execute_sql(subject_sql);
    execute_sql(record_sql);
}

table select_data(const char *sql)
{
    sqlite3 *db;
    table result;
    sqlite3_stmt *stmt;
    int rc;
    db = connect_database();
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int columns = sqlite3_column_count(stmt);

    if (rc != SQLITE_OK) {
        cerr << "SELECT failed: " << sqlite3_errmsg(db) << endl;
    }
    else
    {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            row record;
            for(int i = 0; i < columns; i++)
            {
                record.entries.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)));
            }
            result.rows.push_back(record);
        }
        if (rc != SQLITE_DONE) {
            cerr << "SELECT failed: " << sqlite3_errmsg(db) << endl;
        }
    sqlite3_finalize(stmt);
    result.offset = 0;
    }
    return result;
}

table get_projects()
{
    const char *sql;
    table result;
    sql = "SELECT * FROM PROJECT";
    result = select_data(sql);
    return result;
}

void add_project_sql(string project_name)
{
    string sql_string;
    const char *sql;

    sql_string = "INSERT INTO PROJECT (PROJECT_NAME) VALUES ('" + project_name + "');";
    sql = sql_string.c_str();
    execute_sql(sql); 
}

void add_subject_sql(string subject_name)
{
    string sql_string;
    const char *sql;

    sql_string = "INSERT INTO PROJECT (SUBJECT_NAME) VALUES ('" + subject_name + "');";
    sql = sql_string.c_str();
    execute_sql(sql); 
}

void add_time_record(time_record record, categories &current_categories)
{
    string sql_string;
    const char *sql; 

    sql_string = "INSERT INTO RECORD (SUBJECT_ID, START_TIME, END_TIME, LENGTH)"
                 "VALUES (" + to_string(current_categories.subject_id) + ", '" +  to_string(record.start_time) + "' , '" + to_string(record.end_time) + "' , '" + to_string(record.hours) + ":" + to_string(record.minutes) + ":" + to_string(record.seconds) + "' );";

    sql = sql_string.c_str();
    execute_sql(sql); 
}
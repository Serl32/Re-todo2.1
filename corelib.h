#include <stdio.h>
#include <sqlite3.h>
#include <time.h>

#define CURRENT_VERSION "2.1.1"

void greeting() {
    time_t t;
    time(&t);

    printf("\n# \tRe-ToDo Version %s %100s\n", CURRENT_VERSION, ctime(&t));

    printf("# A Simple To-Do List Program written in C by Serl.\n");
    printf("# The data files are located in the same folder where the program is located.\n");
    printf("# For easier access and backup, this program will save the files in the .txt format or JSON format.\n");
    printf("# A seperate database and management features aren't currently availble.\n");
    printf("# Use \"-h\" as the argument for more information and help.\n");
}

int CREATE_DB(char name[]) {
    printf("Creating the database...\n");
    printf("sqlite3 Version: %s\n", sqlite3_libversion());

    sqlite3 *db;
    sqlite3_stmt *res;
    char *err_msg = 0;

    int rc = sqlite3_open(name, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "CREATE TABLE Todos(Id INTEGER PRIMARY KEY, Title TEXT, Date_Added TEXT, Sub_Id Integer, Status INTEGER, Date_Completed TEXT);";

    rc = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL Error: %s\n", err_msg);

        sqlite3_free(err_msg);
    }

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    rc = sqlite3_step(res);

    if (rc == SQLITE_ROW) {
        printf("%s\n", sqlite3_column_text(res, 0));
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    return 0;
}

// Helper function to get the recent database name
char get_recent() {
    const int len = 26;
    char str[len];
    char recent[len];

    FILE *fp;

    fp = fopen("list.txt", "r");

    if (fp == NULL) {
        printf("Subsequent list file may be missing. Create one with init or check \"-h\" for more information.\n");
    } else {
        while(fgets(str, len, fp) != NULL) {
            strcpy(recent, str);
        }
    }
    fclose(fp);

    return recent;
}

//List all unfinished todos
int LIST_ALL(char name[]) {

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open(name, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open the database: %s\n.", sqlite3_errmsg(db));

        sqlite3_close(db);

        return 1;
    }

    char *sql = "SELECT Id, Title, Date_Added Status FROM Todos WHERE Status = 0";

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to select data.\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        
        return 1;
    }

    sqlite3_close(db);

    return 0;
}

//Create New
int CREATE_NEW(char td_title[]) {
    char recent[] = get_recent();

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open(recent, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = sqlite3_mprintf("INSERT INTO Todos(Title, Date_Added, Sub_Id, Status, Date_Completed) VALUES ('%q', datetime('now'), 0, 0, datetime('now'))", td_title);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create the table.\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        fprintf(stdout, "Table created successfully.\n");
    }

    int last_int_id = sqlite3_last_insert_rowid(db);
    printf("Row Id: %d\n", last_int_id);

    sqlite3_close(db);
    return 0;
}

//Create Sub
int CREATE_SUBTODO(char td_id[], char td_title[]) {
    char recent[] = get_recent();

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open(recent, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }

    char *sql = sqlite3_mprintf("INSERT INTO Todos(Title, Date_Added, Sub_Id, Status, Date_Completed) Values ('%q', datetime('now'), '%q', 0, NULL)", td_title, td_id);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if(rc != SQLITE_OK) {
        fprintf(stderr, "Faialed to create the table.\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlit3_free(err_msg);
    } else {
        fprintf(stdout, "Table Created successfully.\n");
    }

    int last_int_id = sqlite3_last_insert_rowid(db);
    printf("Row Id: %d\n", last_int_id);

    sqlite3_close(db);
    return 0;
}

void COMPLETE_ONE(int td_id) {
    char recent[] = get_recent();

    sqlite3 *db;
    char *err_msg = 0;
    sqlite3_stmt *res;

    int rc = sqlite3_open(recent, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "UPDATE Todos SET Status = 1, Date_Completed = datetime('now') WHERE Id = @id";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        int idx = sqlite3_bind_parameter_index(res, "@id");
        int value = td_id;
        sqlite3_bind_int(res, idx, value);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW) {

        printf("%s: ", sqlite3_column_text(res, 0));
        printf("%s\n", sqlite3_column_text(res, 1));

    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    return 0;
}

int callback(void *, int, char **, char **);

int QUERY_ONE(char td_id[]) {

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open(td_id, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "SELECT * FROM Todos";

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;

    for(int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");

    return 0;
}
#include <mysql/mysql.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* pointer to server connection details */
struct connection_details
{
    char *server;
    char *user;
    char *password;
    char *database;
};

/* function for connecting and returning pointer */
MYSQL* mysql_connection_setup(struct connection_details mysql_details)
{
    /* creating new instance */
    MYSQL *conn = mysql_init(NULL);

    /* connect to the database with the details */
    if (!mysql_real_connect(conn, mysql_details.server, mysql_details.user,
        mysql_details.password, mysql_details.database, 0, NULL, 0))
    {
        printf("Conection error : %s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
};

/* function for performing queries */
MYSQL_RES* mysql_perform_query(MYSQL *conn, char *query)
{
    if (mysql_query(conn, query))
    {
        printf("MySQL query error : %s\n", mysql_error(conn));
        exit(1);
    }
    return mysql_use_result(conn);
};

int main()
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // assign details to database
    struct connection_details mysql_conn_string;
    mysql_conn_string.server = "localhost";
    mysql_conn_string.user = "operaciones";
    mysql_conn_string.password = "prueba";
    mysql_conn_string.database = "crud";

    // connecting to database with details
    conn = mysql_connection_setup(mysql_conn_string);

    res = mysql_perform_query(conn, "select nombre from usuarios;");

    // display query
    printf("MySQL Tables in mysql database:\n");
    while ((row = mysql_fetch_row(res)) !=NULL)
    {
        printf("%s\n", row[0]);
    }

    // reset objects
    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

void do_exit(PGconn *conn)
{
  PQfinish(conn);
  exit(1);
}

int main()
{
  int lib_ver = PQlibVersion();
  printf("Version of libpq: %d\n", lib_ver);
  PGconn *conn = PQconnectdb("postgresql://localhost/israeljrs");
  if (PQstatus(conn) == CONNECTION_BAD)
  {
    fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
    do_exit(conn);
  }

  PGresult *res = PQexec(conn, "select to_char(now()::DATE, 'dd/mm/yyyy')");
  if (PQresultStatus(res) != PGRES_TUPLES_OK)
  {
    printf("BEGIN command failed\n");
    PQclear(res);
    do_exit(conn);
  }
  else
  {
    int rows = PQntuples(res);
    for(int i=0; i<rows; i++)
    {
      printf("data de hoje: %s\n", PQgetvalue(res, i, 0));
    }
  }

  PQclear(res);
  PQfinish(conn);

  return 0;
}

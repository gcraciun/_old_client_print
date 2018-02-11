#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>
#include "util.h"

int main(int argc, char **argv)
{
  struct dbcreds *creds;
    creds = malloc(sizeof(struct dbcreds));
  unsigned int active;
    active = 1;

  MYSQL mysql_connection;

  if (get_config(creds)) {
    printf("Error reading the config file");
    exit(1);
  }

  if (!mysql_init(&mysql_connection)) {
    mysql_exit(mysql_connection, "Initializing");
    exit(1);
  }
  if (!mysql_real_connect(&mysql_connection, \
    creds->host, \
    creds->user, \
    creds->pass, \
    creds->dbase, \
    0, NULL, 0)) {
    mysql_exit(mysql_connection, "Connecting");
    exit(1);
  }

  print_clients(&mysql_connection, active);
  
mysql_close(&mysql_connection);  

return 0;
}


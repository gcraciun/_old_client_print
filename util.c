#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "util.h"

int get_config(struct dbcreds *date)
{
  FILE *config;
  char c, *s, *begin, *variable, *value;
    variable = (char *)(malloc(128));
    value = (char *)(malloc(128));
  char *m = variable, *n = value;
    
  s = (char *)(malloc(128)); // in s store line by line from the file
  begin = s;
  if (!(config = fopen(CONFIG_FILE,"r"))) {
    fprintf(stderr, "Error opening the config file\n");
    exit(1);
  }
  while ((c = getc(config)) != EOF){
    if(c != '\n') {
      strcpy(s++,&c); 		// if we are not at the EOL put c in *s
    }
    if(c == '\n'){ 		// if we reached EOL, then s should contain the whole line
      c = '\0'; 		// used to 'put an end' to s
      strcpy(s,&c); 		// finish s with \0
      s = begin; 		// s goes to the beginning of its memory zone
      c = *s; 			// c gets the first char from s ---- c is used now as a temporary variable
      int in_val = NO; 		// if we read the variable or the value it holds
      while(c) { 		// c no long has anything to do with the old c, is being used now not to allocate a new variable
        c = *s++;
        if((c != ' ' && c != '=') && in_val == NO) { // we should be reading the chars forming the variable
          *variable++ = c;
        }
        if(c == '=') { 		// next follows we enter in the variable value
          in_val = YES;
        }
        if((c != ' ' && c != '=') && in_val == YES) {
        *value++ = c;
        }
      }
      *variable++ = '\0'; 	// finish the variable with \0
      *value++ = '\0';
      variable = m; 		// variable goes to the beginning of its memory zone
      value = n; 		// values goes to the beginning of its memory zone
      
      if (!strcmp(variable, "host")) {
        strcpy(date->host, value);
      }
      if (!strcmp(variable, "user")) {
        strcpy(date->user, value);
      }
      if (!strcmp(variable, "pass")) {
        strcpy(date->pass, value);
      }
      if (!strcmp(variable, "dbase")) {
        strcpy(date->dbase, value);
      }
      s = begin; 		// s goes again to the beginning of its memory zone
    }
  }
  fclose(config);
return 0;
}

void mysql_exit(MYSQL conn, char* m_err)
{
  fprintf(stderr, "Error: %s\n Message: %s\n   Code: %u\n",m_err, mysql_error(&conn), mysql_errno(&conn));
}

int print_clients(MYSQL *mysql, unsigned int active)
{
  char query[80];
  MYSQL_RES *result;
  MYSQL_ROW row;
  sprintf(query, "select name, mac, ip from mac2ip where admin_act='1' and active='%u' order by name", active);
  if(mysql_real_query(mysql, query, strlen(query))) {
    mysql_exit(*mysql, "Query");
    exit(1);
  }
  if(!(result = mysql_store_result(mysql))) {
    mysql_exit(*mysql, "Store");
    exit(1);
  }
  while((row = mysql_fetch_row(result))) {
    printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
  }
mysql_free_result(result);
return 0;
}


#define YES 1
#define NO 0
#define CONFIG_FILE "/admin/etc/client_print.conf"

struct dbcreds {
  unsigned int city;
  char host[20];
  char user[20];
  char pass[20];
  char dbase[20];
};


int get_config(struct dbcreds *);
void mysql_exit(MYSQL , char *);
int print_clients(MYSQL *, unsigned int );

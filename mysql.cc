#include <iostream>

#include <mysql/mysql.h>

using namespace std;


int main()
{
	const char *host   = "localhost";
	const char *user   = "root";
	const char *pwd    = "wh1991";
	const char *dbname = "whdoc";
	
	MYSQL *conn = mysql_init(NULL);
	
	conn = mysql_real_connect(conn, host, user,
							  pwd, dbname, 0, NULL, 0);
	if (conn == NULL)
		return -1;
	
	const char *sql =
	//"select * from loginreq where username='a';";
	"insert into loginreq(username) values('a');";
	
	if ( mysql_query(conn, sql) )
	{
		cout << mysql_error(conn) << endl;
		return -1;
	}
	
	MYSQL_RES *res = mysql_store_result(conn);
	if (res == NULL)
	{
		cout << mysql_error(conn) << endl;
		return -1;
	}
	
	cout << "row num: " << res->row_count << endl;
	
	mysql_free_result(res);
	mysql_close(conn);
	
	return 0;
}
#include <iostream>
#include <string>

#include "leveldb/db.h"
#include "leveldb/c.h"

using namespace std;
using namespace leveldb;

int cpp();
int c();

int main()
{
	return c();
}

int cpp()
{
	DB* db;
	Options opts;
	opts.create_if_missing = true;
	Status status = DB::Open(opts, "data/db", &db);
	if (!status.ok()) return -1;
	
	string key = "c++", get_value;
	WriteOptions w_opt;
	ReadOptions r_opt;
	
	status = db->Put(w_opt, key, string("c++ leveldb"));
	if (!status.ok()) return -1;
	
	status = db->Get(r_opt, key, &get_value);
	if (!status.ok()) return -1;
	cout << get_value << "\n" << endl;
	
	status = db->Delete(w_opt, key);
	if (!status.ok()) return -1;
	
	status = db->Get(r_opt, key, &get_value);
	cout << status.ok() << " " << status.ToString() << endl;
	cout << get_value << "\n" << endl;
	
	delete db;
	return 0;
}

int c()
{
	leveldb_options_t *opts = leveldb_options_create();
	leveldb_options_set_create_if_missing(opts, 1);
	char *errstr = 0;
	
	leveldb_t *db = leveldb_open(opts, "data/db", &errstr);
	if (errstr) return -1;
	
	const char *key = "c";
	const char *v1 = "c leveldb";
	const size_t key_len = strlen(key);
	const size_t v1_len = strlen(v1);
	
	leveldb_readoptions_t  *r_opt = leveldb_readoptions_create();
	leveldb_writeoptions_t *w_opt = leveldb_writeoptions_create();
	
	errstr = 0;
	leveldb_put(db, w_opt, key, key_len, v1, v1_len, &errstr);
	if (errstr) return -1;
	
	char *v2 = 0; size_t v2_len;
	
	errstr = 0;
	v2 = leveldb_get(db, r_opt, key, key_len, &v2_len, &errstr);
	if (v2==NULL) return -1;
	string str(v2, v2_len);
	cout << str << "\n" << endl;
	
	errstr = 0;
	leveldb_delete(db, w_opt, key, key_len, &errstr);
	if (errstr) return -1;
	
	errstr = 0;
	v2 = leveldb_get(db, r_opt, key, key_len, &v2_len, &errstr);
	if (errstr == NULL && v2 == NULL)
		cout << "NOT FOUND" << "\n" << endl;
	else
		return -1;
	
	leveldb_free(db);
	return 0;
}
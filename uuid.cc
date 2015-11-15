#include <iostream>
#include <string.h>

#include <uuid/uuid.h>

using namespace std;


int main()
{
	uuid_t uuid;
	uuid_generate(uuid);
	
	char str[40];
	uuid_unparse(uuid, str);
	cout << strlen(str) << endl;
	cout << str << endl;
	
	return 0;
}
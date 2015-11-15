#include <iostream>
#include <string.h>

#include <uuid/uuid.h>

using namespace std;


int main()
{
	uuid_t uuid;
	char a[40];
	
	uuid_generate(uuid);
	uuid_unparse(uuid, a);
	cout << strlen(a) << "  " << a << endl;
	
	uuid_generate(uuid);
	uuid_unparse(uuid, a);
	cout << strlen(a) << "  " << a << endl;
	
	return 0;
}
#include <iostream>
#include <sstream>
#include <string>

#include "protodir/user.pb.h"

using namespace std;


void showHex(const char* data, const int n);


int main()
{
	wh::User u;
	u.set_id(17);
	u.set_name("abc");
	
	ostringstream out;
	u.SerializeToOstream(&out);
	
	string s = out.str();
	showHex(s.c_str(), s.length());
	
	return 0;
}

void showHex(const char* data, const int n)
{
	const char* HexChar = "0123456789ABCDEF";
	const char High = 0xF0;
	const char Low  = 0x0F;
	
	const char* p = data;
	for (int i = 0; i<n && *p; i++, p++)
	{
		cout << HexChar[(*p&High)>>4]
			 << HexChar[*p&Low]
			 << ' ';
	}
	cout << endl;
}
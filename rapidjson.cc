#include <iostream>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

using namespace std;
using namespace rapidjson;

int main()
{
	string json_str, line;
	ifstream fin("a.json");
	while (fin >> line)
		json_str += line;
	fin.close();
	
	Document src;
	src.Parse(json_str.c_str());
	cout << src["array"][2].GetString() << endl;
	
	Document dst;
	dst.SetObject();
	Value val(src["array"][2], dst.GetAllocator());
	dst.AddMember("t-1", val, dst.GetAllocator());
	val = 15;
	dst.AddMember("t-2", val, dst.GetAllocator());
	
	StringBuffer buf(0, 128);
	Writer<StringBuffer> writer(buf);
	dst.Accept(writer);
	cout << buf.GetString() << endl;
	
	return 0;
}
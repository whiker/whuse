#include <iostream>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

using namespace std;
using namespace rapidjson;

int main()
{
	// 解析
	string json_str, line;
	ifstream fin("a.json");
	while (fin >> line)
		json_str += line;
	fin.close();
	
	Document src;
	src.Parse(json_str.c_str());
	const char *src_str = src["array"][2].GetString();
	cout << src_str << endl;
	
	// 输出
	Document dst;
	dst.SetObject();
	Document::AllocatorType& alloc = dst.GetAllocator();
	
	Value val(src["array"][2], alloc);
	dst.AddMember("t-1", val, alloc);
	
	val = StringRef(src_str);
	dst.AddMember("t-2", val, alloc);
	
	val = StringRef(src_str, 10);
	dst.AddMember("t-2", val, alloc);  // 可以重复
	
	Value arr(kArrayType);
	const char *strs[] = { "hello", "world", "!" };
	for (int i = 0; i < 3; i++)
	{
		val = StringRef(strs[i]);
		arr.PushBack(val, alloc);
	}
	dst.AddMember("t-3", arr, alloc);
	
	StringBuffer buf(0, 128);
	Writer<StringBuffer> writer(buf);
	dst.Accept(writer);
	cout << buf.GetString() << endl;
	
	return 0;
}
#include "WinReg.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
int main()
{
	//注册表查询Demo
	LPCWSTR keyPath = SERIALPATH;
	LPCWSTR ValueName = _T("\\Device\\Serial2");
	char Value[MAX_PATH];
	int valueLength = MAX_PATH;
	if(QueryRegKey(keyPath, ValueName , Value, valueLength))
		printf("query success : %s!\n", Value);


	//查询串口列表
	vector<string> COMList = QuerySerialPort();
	for (string& var : COMList)
	{
		cout << var << endl;
	}
	return 0;
}


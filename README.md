# WinRegister

Windows注册表查询以及通过注册表查询串口设备

# 使用
## 查找注册表键值对
`_T`等同于`TEXT`, `_T("")`是一个宏，定义于tchar.h下。因为Windows使用两种字符集ANSI和UNICODE，如果你编译一个程序为ANSI方式，_T实际不起任何作用。

而如果编译一个程序为`UNICODE`方式，则编译器会把`_T("Hello")`字符串以UNICODE方式保存。_T和_L的区别在于，_L不管你是以什么方式编译，一律以UNICODE方式保存。

L是表示字符串资源为Unicode的。
```c
#include "WinReg.h"
int main()
{
	LPCWSTR keyPath = SERIALPATH;
	LPCWSTR ValueName = _T("\\Device\\Serial2");
	char Value[MAX_PATH];
	int valueLength = MAX_PATH;
	if(QueryRegKey(keyPath, ValueName , Value, valueLength))
		printf("query success : %s!\n", Value);
	return 0;
}
```
![image](https://img-blog.csdnimg.cn/20200905125955845.png#pic_center)


## 得到串口设备列表
对比注册表符合。
```c
#include "WinReg.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
int main()
{
	vector<string> COMList = QuerySerialPort();
	for(string& var : COMList)
	{
		cout << var << endl;
	}
	return 0;
}
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200905125814840.png#pic_center)


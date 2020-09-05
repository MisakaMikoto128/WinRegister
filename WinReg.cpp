#include "WinReg.h"
#define debug(fmt, ...) printf(fmt, __VA_ARGS__)

void wcharTochar(const wchar_t* wcharSrc, char* chrDst, int chrDstlength)
{
	WideCharToMultiByte(CP_ACP, 0, wcharSrc, -1, chrDst, chrDstlength, NULL, NULL);
}

bool QueryRegKey(LPCWSTR keyPath, LPCWSTR ValueName, char* Value, int valueLength)
{
	HKEY hKey;
	if (ERROR_SUCCESS == RegOpenKey(HKEY_LOCAL_MACHINE, keyPath, &hKey))
	{
		debug("OpenRegKey success!\n");

	}
	else { debug("OpenRegKey failed!\n"); }


	DWORD dwType = REG_SZ;//������������
	DWORD dwLen = MAX_PATH;
	BYTE data[MAX_PATH];

	if (ERROR_SUCCESS == RegQueryValueEx(hKey, ValueName, 0, &dwType, (LPBYTE)data, &dwLen))
	{
		WideCharToMultiByte(CP_ACP, 0, (LPCWCH)data, -1, Value, valueLength, NULL, NULL);
		//debug("query success : %s!\n", Value);
		RegCloseKey(hKey); //�ر�ע���	
		return true;
	}
	return false;
}


vector<string> QuerySerialPort()
{
	HKEY hKey;
	vector<string> COM;

	LPCTSTR lpSubKey = SERIALPATH;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpSubKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
	{
		debug("open registry key failed !");
		RegCloseKey(hKey); //�ر�ע���
		return COM;
	}


	TCHAR valueName[MAX_PATH];
	BYTE portName[MAX_PATH];
	LONG status;
	DWORD dwIndex = 0;
	DWORD dwSizeValueName = MAX_PATH;
	DWORD dwSizeofPortName = MAX_PATH;
	DWORD Type;


	char strValue[MAX_PATH];
	int length = MAX_PATH;
	do
	{
		status = RegEnumValue(hKey, dwIndex++, valueName, &dwSizeValueName, NULL, &Type, portName, &dwSizeofPortName);
		if ((status == ERROR_SUCCESS))
		{
			//wprintf(L"%s exists!\n", portName);
			//strValue Ŀ��
			WideCharToMultiByte(CP_ACP, 0, (LPCWCH)portName, -1, strValue, length, NULL, NULL);
			COM.push_back(strValue);
		}
		//ÿ��ȡһ��dwSizeValueName��dwSizeofPortName���ᱻ�޸�
		//ע��һ��Ҫ����,�������ֺ�����Ĵ���,���˾��Թ���û������,���ֶ�����COM����10���ϵĴ���
		dwSizeValueName = MAX_PATH;
		dwSizeofPortName = MAX_PATH;
	} while ((status != ERROR_NO_MORE_ITEMS));
	RegCloseKey(hKey); //�ر�ע���
	return COM;
}
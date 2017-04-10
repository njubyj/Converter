#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define isdigit(x) \
((x >= '0' && x <= '9') || (x == '.'))

#define ishead(x) \
((x >= '0' && x <= '9') || (x == '-'))


bool IsHexDigit(char ch)
{
	if ((ch >= '0' && ch <= '9') ||
		(ch >= 'a' && ch <= 'f') ||
		(ch >= 'A' && ch <= 'F'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int DetectType(char *szSrc, int iCount)
{
	if (iCount < 2 || 
		szSrc[0] != '0' ||
		(szSrc[1] != 'x' && szSrc[1] != 'X'))
	{
		if (!ishead(szSrc[0]))
		{
			return -1;
		}

		for (int i = 1; i < iCount; i++)
		{
			if (!isdigit(szSrc[i]))
			{
				return -1;
			}
		}
		return 0;
	}
	else if (szSrc[0] == '0' && (szSrc[1] == 'x' || szSrc[1] == 'X') && iCount <= 18)
	{
		for (int i = 2; i < iCount; i++)
		{
			if (!IsHexDigit(szSrc[i]))
			{
				return -1;
			}
		}
		return 1;
	}
	else
	{
		return -1;
	}
}

void DisplayHexRes(char *szSrc)
{
	double dRes = strtod(szSrc, NULL);
	float fRes = strtof(szSrc, NULL);
	cout << "Output Result:" << endl;
	unsigned char *szRes = (unsigned char *)&dRes;
	cout << "Double: 0x";
	for (int i = 7; i >= 0; i--)
		printf("%02X", szRes[i]);
	cout << endl;
	szRes = (unsigned char *)&fRes;
	cout << "Float:  0x";
	for (int i = 3; i >= 0; i--)
		printf("%02X", szRes[i]);
	cout << endl;
}

void DisplayFloatRes(char *szSrc)
{
	unsigned long long ullSrc = strtoull(szSrc, NULL, 16);
	double dRes = *(double *)&ullSrc;
	float fRes = *(float *)&ullSrc;
	cout << "Output Result:" << endl;
	cout << "Double: " << dRes << endl;
	cout << "Float: " << fRes << endl;
}

int main()
{
	char szInput[64] = { 0 };
	int iType = -1;
	while (true)
	{
		while (!strlen(szInput) || iType < 0)
		{
			memset(szInput, 0, 64);
			cout << "Source Data: ";
			cin.getline(szInput, 64);
			iType = DetectType(szInput, strlen(szInput));
		}

		if (0 == iType)
		{
			DisplayHexRes(szInput);
		}
		else if (1 == iType)
		{
			DisplayFloatRes(szInput);
		}

		memset(szInput, 0, 64);
		iType = -1;
		cout << endl;
	}
	
	system("pause");
	return 0;
}

#include <iostream>
#include <Windows.h>  
#include <process.h>  
using namespace std;

DWORD WINAPI FunProc(LPVOID lpParameter)
{
	int i = 1;
	for (; i < 1000; i++)
	{
		printf("  %d", i);
		if (!(i % 10))
			printf("\n");
	}
	return 0;
}

int main()
{
	HANDLE hThread;
	hThread = (HANDLE)CreateThread(NULL, 0, FunProc, NULL, 0, NULL);
	DWORD dwRet = WaitForSingleObject(hThread, 10000);
	if (dwRet == WAIT_OBJECT_0)
	{
		printf("�����߳�ִ�н���\n");
	}
	if (dwRet == WAIT_TIMEOUT)
	{
		printf("�ȴ���ʱ\n");
	}
	if (dwRet == WAIT_ABANDONED)
	{
		printf("Abandoned\n");
	}
	CloseHandle(hThread);
	return 0;
}
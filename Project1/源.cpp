
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
		printf("创建线程执行结束\n");
	}
	if (dwRet == WAIT_TIMEOUT)
	{
		printf("等待超时\n");
	}
	if (dwRet == WAIT_ABANDONED)
	{
		printf("Abandoned\n");
	}
	CloseHandle(hThread);
	return 0;
}
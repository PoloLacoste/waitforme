#include <stdio.h>
#include <Windows.h>
#pragma warning(disable:4996)

BOOL isProcessRunning(DWORD pid)
{
	HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, pid);
	DWORD ret = WaitForSingleObject(process, 0);
	CloseHandle(process);
	return ret == WAIT_TIMEOUT;
}

int main(int argc, char * argv[])
{
	if (argc < 3)
	{
		printf("waitforme.exe pid file_to_execute\n");
		return 0;
	}

	DWORD pid = atoi(argv[1]);

	if (isProcessRunning(pid))
	{
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid);
		WaitForSingleObject(handle, INFINITE);

		system(argv[2]);
	}
	else
	{
		printf("This process is not active ! \n");
	}

	return 0;
}


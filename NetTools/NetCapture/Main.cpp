#include "Main.h"
#include <tlhelp32.h>
IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
	FilePath path;
	path.Set(".\\des");
	path.Creat();
	if (!wxApp::OnInit())
		return false;
	instwnd = new InstMainWnd();
	instwnd->Show();
	return true;
}

MainApp::~MainApp()
{

}

int StartOneInstWnd(const char* Path, const char* ProcessName, bool forceReStart)
{
	int i = 0;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	wchar_t exeName[1000];
	int len = MultiByteToWideChar(CP_ACP, 0, ProcessName, strlen(ProcessName), exeName, sizeof(exeName) / sizeof(exeName[0]));
	if (len < 0)
	{
		len = 0;
	}
	exeName[len] = 0;
	while (bMore)
	{
		//printf(" 进程名称：%s \n", pe32.szExeFile);
		if (wcscmp(exeName, pe32.szExeFile) == 0)
		{
			if (forceReStart)
			{
				HANDLE oHandLe = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
				if (oHandLe)
				{
					TerminateProcess(oHandLe, 0);
					CloseHandle(oHandLe);
				}
			}
			i += 1;
			break;
		}
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
	if (i >= 1) {           //大于1，排除自身
		if (forceReStart)
		{

		}
		else
		{
			return 0;
		}
	}
	STARTUPINFO info;
	PROCESS_INFORMATION pcinfo;
	memset(&info, 0, sizeof(info));
	info.cb = sizeof(info);
	info.dwFlags = STARTF_USESHOWWINDOW;
	info.wShowWindow = 1;
	memset(&pcinfo, 0, sizeof(pcinfo));
	wchar_t filename[1000] = L"";
	len = MultiByteToWideChar(CP_ACP, 0, Path, strlen(Path), filename, sizeof(filename) / sizeof(filename[0]));
	if (len < 0)
	{
		len = 0;
	}
	filename[len] = 0;
	wcscat(filename, exeName);
	wchar_t cmd[] = L"";
	bool ok = CreateProcess(filename, cmd, 0, 0, 0, 0, 0, 0, &info, &pcinfo);
	DWORD dw = GetLastError();
	return 0;
}

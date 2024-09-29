#ifndef UNICODE
#define UNICODE
#endif


#include <windows.h>
#include <strsafe.h>
#include <shlguid.h>
#include <shobjidl.h>

#include <stdio.h>
#include <Objbase.h>
#include <oleauto.h>


#include <objidl.h>
#include <shellapi.h>

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Shell32.lib")

int main(int argc, char const *argv[])
{
	HRESULT hrComInit = S_OK;

	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED);

	if(FAILED(hrComInit))
	{
		printf("FAILED CoInitializeEx\n");
	}

	ShellExecute(NULL,  L"runas",  L"\"firewall.exe\"", NULL, NULL, 5);
	 
	CoUninitialize();

	return 0;
}
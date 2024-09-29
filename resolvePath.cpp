#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <strsafe.h>
#include <shlguid.h>
#include <shobjidl.h>
#include <stdio.h>
#include <Objbase.h>
#include <netfw.h>
#include <icftypes.h>
#include <WTypes.h>
#include <oleauto.h>


#include <objidl.h>
#include <shellapi.h>


#include <string.h>


#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Shell32.lib")

#pragma comment(lib, "Comdlg32.lib")

using namespace std;

int wmain(int argc, wchar_t *argv[])
{

	HRESULT hrComInit = S_OK;

	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED);

	if(FAILED(hrComInit))
	{
		printf("FAILED CoInitializeEx\n");
	}

	/********** THIS CODE WORKS. DON'T DELETE. IT SHOWS HOW TO CREATE A DIALOG FOR SELECTING FILES ***********************/ 
					OPENFILENAME ofn; // common dialog box structure
					wchar_t szFile[260]; // buffer for file name
					ZeroMemory(&ofn, sizeof(ofn));
					ofn.lStructSize = sizeof(ofn);
					ofn.hwndOwner = NULL;
					// ofn.hwndOwner = hwnd;
					ofn.lpstrFile = szFile;
					ofn.lpstrFile[0] = '\0';
					ofn.nMaxFile = sizeof(szFile);
					ofn.lpstrFilter = L"APPLICATIONS\0*.exe\0SHORTCUTS\0*.lnk\0";
					ofn.nFilterIndex = 1;
					ofn.lpstrFileTitle = NULL;
					ofn.nMaxFileTitle = 0;
					ofn.lpstrInitialDir = NULL;
					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

					GetOpenFileName(&ofn);

    HRESULT hres;
	IShellLink* psl;
	WCHAR szGotPath[MAX_PATH];

	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
	if(SUCCEEDED(hres))
	{
		IPersistFile* ppf;

		hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
		if (SUCCEEDED(hres))
		{
			hres = ppf->Load( szFile, STGM_READ);
			// hres = ppf->Load(L"C:\\Users\\hp\\Desktop\\hman.lnk", STGM_READ);
			if (SUCCEEDED(hres))
			{
					HWND hwndl = NULL;
					hres = psl->Resolve(hwndl, SLR_NO_UI);
					if (SUCCEEDED(hres))
					{
						

						  hres = psl->GetPath(szGotPath, MAX_PATH, NULL, SLGP_RAWPATH);
						// hres = psl->GetPath(szGotPath, MAX_PATH, NULL, SLGP_SHORTPATH);
						if (SUCCEEDED(hres))
						{
							 // printf("%S\n", szGotPath);

							  MessageBox(
										NULL,
										(LPCWSTR)szGotPath,
										(LPCWSTR)L"Eyyyy",
										MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
										);  							 
						}

						ppf->Release();
						psl->Release();
					}
			}else{
				printf("FAILED ppf->Load\n");
		    }

		}else{
			printf("FAILED psl->QueryInterface\n");
	    }

	}else{
		printf("FAILED CoCreateInstance\n");
	}   
	 /*********************************************/


	/************ EXPERIMENT *******************/
		wchar_t *path;
		path = wcscpy(path, L"\"");
		path = wcscat(path, szGotPath);
		path = wcscat(path, L"\""); 

	/******************************************/


	 ShellExecute(NULL,  L"runas",  L"\"firewall.exe\"", path, NULL, 5);

	CoUninitialize();

	return 0;

}
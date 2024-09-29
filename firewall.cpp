#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#include <Winuser.h>
#include <Commctrl.h>

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

#include <comutil.h>
#include <atlcomcli.h>


#include <richedit.h>


#include <Shlobj.h>

#include <versionhelpers.h>


#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Shell32.lib")

#pragma comment(lib, "Comdlg32.lib")

#pragma comment(lib, "Comctl32.lib")

#pragma comment(lib, "Gdi32.lib")

#pragma comment(lib, "Ntdll.lib")

using namespace std;

HWND btn;
HWND btn2;
HWND btn3;
HWND btn4;
HWND btn5;

#define ID_BUTTON_select_application  10
#define ID_BUTTON_List_rules  12
#define ID_BUTTON_user_manual  14
#define ID_BUTTON_about_us  16
#define ID_BUTTON_reset_firewall  18


HWND hwndTab;

HWND hWndListView;

LVITEM lvI2;

int listRules();

int resetFirewall()
{
	HRESULT hrComInit = S_OK;

	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED);

	if(FAILED(hrComInit))
	{
		printf("FAILED CoInitializeEx\n");
	}

	HRESULT hr = S_OK;
		INetFwPolicy2 *pNetFwPolicy2 = NULL;

		hr = CoCreateInstance(
		__uuidof(NetFwPolicy2),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(INetFwPolicy2),
		(void**)&pNetFwPolicy2);
	
		if(FAILED(hr))
		{
			printf("FAILED CoCreateInstance 0x%08lx\n", hr);
		}

		hr = pNetFwPolicy2->RestoreLocalFirewallDefaults();
		if(FAILED(hr))
		{
			printf("FAILED pNetFwPolicy2->RestoreLocalFirewallDefaults()\n");

			MessageBox(
								NULL,
								(LPCWSTR)L"FAILED pNetFwPolicy2->RestoreLocalFirewallDefaults()",
								(LPCWSTR)L"Eyyyy",
								MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
								);
		}

		CoUninitialize();

	return 0;
}

int initializeFirewall()
{
	HRESULT hrComInit = S_OK;

	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED);

	if(FAILED(hrComInit))
	{
		printf("FAILED CoInitializeEx\n");
	}

	HRESULT hr = S_OK;
		INetFwPolicy2 *pNetFwPolicy2 = NULL;

		hr = CoCreateInstance(
		__uuidof(NetFwPolicy2),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(INetFwPolicy2),
		(void**)&pNetFwPolicy2);
	
		if(FAILED(hr))
		{
			printf("FAILED CoCreateInstance 0x%08lx\n", hr);
		}

		hr = pNetFwPolicy2->put_DefaultOutboundAction(NET_FW_PROFILE2_PUBLIC, NET_FW_ACTION_BLOCK);
		if(FAILED(hr))
		{
			printf("FAILED pNetFwPolicy2->put_DefaultOutboundAction(NET_FW_PROFILE2_PUBLIC...\n");
		}

	    hr = pNetFwPolicy2->put_DefaultOutboundAction(NET_FW_PROFILE2_DOMAIN, NET_FW_ACTION_BLOCK);
	    if(FAILED(hr))
		{
			printf("FAILED pNetFwPolicy2->put_DefaultOutboundAction(NET_FW_PROFILE2_DOMAIN...\n");
		}

	    hr = pNetFwPolicy2->put_DefaultOutboundAction(NET_FW_PROFILE2_PRIVATE, NET_FW_ACTION_BLOCK);
	    if(FAILED(hr))
		{
			printf("FAILED pNetFwPolicy2->put_DefaultOutboundAction(NET_FW_PROFILE2_PRIVATE...\n");
		}  

		VARIANT_BOOL isEnabled = VARIANT_TRUE;
		hr = pNetFwPolicy2->put_FirewallEnabled(NET_FW_PROFILE2_PUBLIC, isEnabled);
		if(FAILED(hr))
		{
			printf("FAILED pNetFwPolicy2->put_FirewallEnabled NET_FW_PROFILE2_PUBLIC\n");
		}

		hr = pNetFwPolicy2->put_FirewallEnabled(NET_FW_PROFILE2_PRIVATE, isEnabled);
		if(FAILED(hr))
		{
			printf("FAILED pNetFwPolicy2->put_FirewallEnabled NET_FW_PROFILE2_PRIVATE\n");
		}

		hr = pNetFwPolicy2->put_FirewallEnabled(NET_FW_PROFILE2_DOMAIN, isEnabled);
		if(FAILED(hr))
		{
			printf("FAILED pNetFwPolicy2->put_FirewallEnabled NET_FW_PROFILE2_DOMAIN\n");
		}  

		NET_FW_ACTION outboundAction;
		hr = pNetFwPolicy2->get_DefaultOutboundAction(NET_FW_PROFILE2_PUBLIC, &outboundAction);
		if(FAILED(hr))
		{
			printf("FAILED pNetFwPolicy2->get_DefaultOutboundAction NET_FW_PROFILE2_PUBLIC\n");
		}

		if(outboundAction != NET_FW_ACTION_BLOCK)
		{
			printf("pNetFwPolicy2->get_DefaultOutboundAction != NET_FW_ACTION_BLOCK for NET_FW_PROFILE2_PUBLIC\n");
		}

		hr = pNetFwPolicy2->get_DefaultOutboundAction(NET_FW_PROFILE2_PRIVATE, &outboundAction);
		if(FAILED(hr))
		{
			printf("FAILED pNetFwPolicy2->get_DefaultOutboundAction NET_FW_PROFILE2_PRIVATE\n");
		}

		if(outboundAction != NET_FW_ACTION_BLOCK)
		{
			printf("pNetFwPolicy2->get_DefaultOutboundAction != NET_FW_ACTION_BLOCK for NET_FW_PROFILE2_PRIVATE\n");
		}

		hr = pNetFwPolicy2->get_DefaultOutboundAction(NET_FW_PROFILE2_DOMAIN, &outboundAction);
		if(FAILED(hr))
		{
			printf("FAILED pNetFwPolicy2->get_DefaultOutboundAction NET_FW_PROFILE2_DOMAIN\n");
		}

		if(outboundAction != NET_FW_ACTION_BLOCK)
		{
			printf("pNetFwPolicy2->get_DefaultOutboundAction != NET_FW_ACTION_BLOCK for NET_FW_PROFILE2_DOMAIN\n");
		}


		CoUninitialize();


	return 0;
}

int deleteRule(wchar_t * ruleName)
{

	HRESULT hrComInit = S_OK;

	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED);

	if(FAILED(hrComInit))
	{
		printf("FAILED CoInitializeEx\n");
	}

	HRESULT hr = S_OK;
		INetFwPolicy2 *pNetFwPolicy2 = NULL;

		hr = CoCreateInstance(
		__uuidof(NetFwPolicy2),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(INetFwPolicy2),
		(void**)&pNetFwPolicy2);
	
		if(FAILED(hr))
		{
			printf("FAILED CoCreateInstance 0x%08lx\n", hr);
		}

		INetFwRules *pFwRules = NULL;
		hr = pNetFwPolicy2->get_Rules(&pFwRules);
	 	if(FAILED(hr))
	 	{
	 		printf("get_Rules failed: 0x%08lx\n", hr);
	 	}

	 	BSTR bstrRuleName = SysAllocString(ruleName);

	 	hr = pFwRules->Remove(bstrRuleName);
		if (FAILED(hr))
		{
			printf("Firewall Rule Add failed: 0x%08lx\n", hr);	

			if(hr == E_ACCESSDENIED)
			{
				printf("Firewall Rule Add failed: E_ACCESSDENIED");
			}	
		}

		pNetFwPolicy2->Release();
		pFwRules->Release();

		SysFreeString(bstrRuleName);
		
 		CoUninitialize();

 		ListView_DeleteAllItems(hWndListView);
 		listRules();  




	return 0;
}

int listRules()
{

	HRESULT hrComInit = S_OK;

	hrComInit = CoInitializeEx(
		0,
		COINIT_APARTMENTTHREADED);

	if(FAILED(hrComInit))
	{
		printf("FAILED CoInitializeEx\n");
	}

	HRESULT hr = S_OK;
		INetFwPolicy2 *pNetFwPolicy2 = NULL;

		hr = CoCreateInstance(
		__uuidof(NetFwPolicy2),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(INetFwPolicy2),
		(void**)&pNetFwPolicy2);
	
		if(FAILED(hr))
		{
			printf("FAILED CoCreateInstance 0x%08lx\n", hr);
		}

		INetFwRules *pFwRules = NULL;
		hr = pNetFwPolicy2->get_Rules(&pFwRules);
	 	if(FAILED(hr))
	 	{
	 		printf("get_Rules failed: 0x%08lx\n", hr);
	 	}

	 	IUnknown *pEnumerator;
	 	pFwRules->get__NewEnum(&pEnumerator);

	 	IEnumVARIANT* pVariant = NULL;

	 	if(pEnumerator)
	 	{
	 		hr = pEnumerator->QueryInterface(__uuidof(IEnumVARIANT), (void **) &pVariant);
	 	}

	 	CComVariant var;
	 	ULONG cFetched = 0;

	 	INetFwRule *pFwRule = NULL;

	 	BSTR bstrVal;

	 	int i = 0;

	 	BSTR bstrRuleGroup = SysAllocString(L"Alto Grade Firewall Group");

	 	while(SUCCEEDED(hr) && hr != S_FALSE)
	 	{




	 		var.Clear();
	 		hr = pVariant->Next(1, &var, &cFetched);

	 		if (S_FALSE != hr)
	 		{
	 			if (SUCCEEDED(hr))
		 		{
		 			hr = var.ChangeType(VT_DISPATCH);
		 		}

		 		if (SUCCEEDED(hr))
		 		{
		 			hr = (V_DISPATCH(&var))->QueryInterface(__uuidof(INetFwRule), reinterpret_cast<void**>(&pFwRule));
		 		}

		 		if (SUCCEEDED(hr))
		 		{
		 			if(SUCCEEDED(pFwRule->get_Grouping(&bstrVal)))
		 			{
		 				 
		 				if(1 == VarBstrCmp(bstrVal, bstrRuleGroup, 0x0C00, NORM_IGNORECASE))
		 				{
		 					// if (SUCCEEDED(pFwRule->get_ApplicationName(&bstrVal)))
		 					 if (SUCCEEDED(pFwRule->get_Name(&bstrVal)))
				 			{
				 				lvI2.iItem = i;
				 				lvI2.pszText = bstrVal;
				 				ListView_InsertItem(hWndListView, &lvI2);
				 				i++;
				 			}
		 				}
		 			}


		 			
		 		}
	 		}

	 		ShowWindow(hWndListView, SW_SHOW);



	 	/*	SysFreeString(bstrRuleGroup);
	 	//	SysFreeString(bstrVal);

			pNetFwPolicy2->Release();
			pFwRules->Release();
			pFwRule->Release();

	 		CoUninitialize(); */

	 		
	 	}






	return 0;
}

// int wmain(int argc, wchar_t *argv[])
int addRule()
{
	/****************** EXPERIMENT **************************/
		/* wchar_t *path;
		int count;
		for( count = 1; count < argc; count++ )
		{

			   path = wcscpy(path, argv[count]);
			  	
		}   */
		/*******************************************************/

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
					ofn.lpstrFilter = L"Applications\0*.exe;.lnk\0\0";
					ofn.nFilterIndex = 1;
					ofn.lpstrFileTitle = NULL;
					ofn.nMaxFileTitle = 0;
					ofn.lpstrInitialDir = NULL;
					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

					/****************** EXPERIMENT **********************/
						ofn.lpstrTitle = L"Select an application's shortcut or exe file";
					/****************************************************/

					GetOpenFileName(&ofn);

					WCHAR szGotPath[MAX_PATH];

					/******************* EXPERIMENT ***************************************/
						if(NULL != wcsstr(szFile, L".exe"))
						{
							printf("EXE file selected\n");
						}else{
							HRESULT hres;
							IShellLink* psl;
							

							hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
							if(SUCCEEDED(hres))
							{
								IPersistFile* ppf;

								hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
								if (SUCCEEDED(hres))
								{
									hres = ppf->Load( szFile, STGM_READ);
									if (SUCCEEDED(hres))
									{
											HWND hwndl = NULL;
											hres = psl->Resolve(hwndl, SLR_NO_UI);
											if (SUCCEEDED(hres))
											{
												

												hres = psl->GetPath(szGotPath, MAX_PATH, NULL, SLGP_RAWPATH);
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
						}
					
					


					/**********************************************************************/

     
	  
	
	
		HRESULT hr = S_OK;
		INetFwPolicy2 *pNetFwPolicy2 = NULL;

		hr = CoCreateInstance(
		__uuidof(NetFwPolicy2),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(INetFwPolicy2),
		(void**)&pNetFwPolicy2);
	
		if(FAILED(hr))
		{
			printf("FAILED CoCreateInstance 0x%08lx\n", hr);
		}

		
		initializeFirewall();


		INetFwRules *pFwRules = NULL;
		hr = pNetFwPolicy2->get_Rules(&pFwRules);
	 	if(FAILED(hr))
	 	{
	 		printf("get_Rules failed: 0x%08lx\n", hr);
	 	}

	 	INetFwRule *pFwRule = NULL;
	 	hr = CoCreateInstance(
			__uuidof(NetFwRule),
			NULL,
			CLSCTX_INPROC_SERVER,
			__uuidof(INetFwRule),
			(void**)&pFwRule);
	
		if(FAILED(hr))
		{
			printf("CoCreateInstance for Firewall Rule failed: 0x%08lx\n", hr);
		}

		BSTR name = SysAllocString(L"ALTO GRADE FIREWALL RULE");
		if(NULL == name)
		{
			printf("ERROR SysAllocString(name)\n");
		}

		BSTR description = SysAllocString(L"ALLOW OUTBOUND TRAFFIC FROM THIS APPLICATION");
		if(NULL == description)
		{
			printf("ERROR SysAllocString(description)\n");
		}

		BSTR InterfaceTypes = SysAllocString(L"All");
		if(NULL == InterfaceTypes)
		{
			printf("ERROR SysAllocString(InterfaceTypes)\n");
		}

		/*************** EXPERIMENT ***********************/
			if(NULL == wcsstr(szFile, L".exe") && NULL == wcsstr(szGotPath, L".exe"))
			{
				return 0;
			}

			BSTR RuleAppPath = NULL;
			if(NULL != wcsstr(szFile, L".exe"))
			{
				 RuleAppPath = SysAllocString(szFile);
				if(NULL == RuleAppPath)
				{
					printf("ERROR SysAllocString(szGotPath)\n");
				}

			}else{
				 RuleAppPath = SysAllocString(szGotPath);
				if(NULL == RuleAppPath)
				{
					printf("ERROR SysAllocString(szGotPath)\n");
				}
			}

		/************************************************/

		BSTR bstrRuleGroup = SysAllocString(L"Alto Grade Firewall Group");
		if(NULL == bstrRuleGroup)
		{
			printf("ERROR SysAllocString(InterfaceTypes)\n");
		}
		

		hr = pFwRule->put_Name(RuleAppPath);
		// hr = pFwRule->put_Name(name);
		if (FAILED(hr))
		{
			printf("Failed pFwRule->put_Name: 0x%08lx\n", hr);		
		}

		hr = pFwRule->put_Description(description);	
		if (FAILED(hr))
		{
			printf("Failed pFwRule->put_Description: 0x%08lx\n", hr);		
		}

		hr = pFwRule->put_Protocol(NET_FW_IP_PROTOCOL_ANY);
		if (FAILED(hr))
		{
			printf("Failed pFwRule->put_Protocol: 0x%08lx\n", hr);		
		}

		hr = pFwRule->put_InterfaceTypes(InterfaceTypes);
		if (FAILED(hr))
		{
			printf("Failed pFwRule->put_InterfaceTypes: 0x%08lx\n", hr);		
		}

		hr = pFwRule->put_Direction(NET_FW_RULE_DIR_OUT);
		if (FAILED(hr))
		{
			printf("Failed pFwRule->put_Direction: 0x%08lx\n", hr);		
		}

		hr = pFwRule->put_Grouping(bstrRuleGroup);
		if (FAILED(hr))
		{
			printf("Failed pFwRule->put_Grouping: 0x%08lx\n", hr);		
		}

		hr = pFwRule->put_Action(NET_FW_ACTION_ALLOW);
		if (FAILED(hr))
		{
			printf("Failed pFwRule->put_Action: 0x%08lx\n", hr);		
		}

		hr = pFwRule->put_ApplicationName(RuleAppPath);
		if (FAILED(hr))
		{
			printf("Failed pFwRule->put_ApplicationName: 0x%08lx\n", hr);		
		}

		hr = pFwRule->put_Profiles(NET_FW_PROFILE2_DOMAIN | NET_FW_PROFILE2_PRIVATE | NET_FW_PROFILE2_PUBLIC);
		if (FAILED(hr))
		{
			printf("Failed pFwRule->put_Profiles: 0x%08lx\n", hr);		
		}

		hr = pFwRule->put_Enabled(VARIANT_TRUE);
		if (FAILED(hr))
		{
			printf("Failed pFwRule->put_Enabled: 0x%08lx\n", hr);		
		}

		hr = pFwRules->Add(pFwRule);
		if (FAILED(hr))
		{
			printf("Firewall Rule Add failed: 0x%08lx\n", hr);	

			if(hr == E_ACCESSDENIED)
			{
				printf("Firewall Rule Add failed: E_ACCESSDENIED");
			}	
		}

		SysFreeString(name);
		SysFreeString(description);
		SysFreeString(InterfaceTypes);
		SysFreeString(RuleAppPath);
		SysFreeString(bstrRuleGroup);

		pFwRule->Release();
		pFwRules->Release();
		pNetFwPolicy2->Release();

	
	 CoUninitialize();

	return 0;
}








/* typedef struct MyData {
	HDC hdc;
	HWND windowHandle;
} MYDATA, *PMYDATA;

BOOL CALLBACK EnumFamCallBack(LOGFONT lplf, LPNEWTEXTMETRIC lpntm, DWORD FontType, LPVOID data)
{
	PMYDATA pDataStruct = (PMYDATA)data;

	HFONT hfont = CreateFontIndirect(&lplf);
	if(NULL == hfont)
	{
		MessageBox(
								NULL,
								(LPCWSTR)L"FAILED CreateFontIndirect",
								(LPCWSTR)L"Eyyyy",
								MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
								);
	}

	SelectObject(pDataStruct->hdc, hfont);

	SendMessage(btn, WM_SETFONT, (WPARAM)hfont,  MAKELPARAM(TRUE, 0));
	 // SendMessage(pDataStruct->windowHandle, WM_SETFONT, (WPARAM)hfont,  MAKELPARAM(TRUE, 0));

	return TRUE;
} */







LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

		case WM_COMMAND:
		{
			 switch(HIWORD(wParam))
			 {
			 	case BN_CLICKED:
			 	{
			 		 			 		
			 		switch(LOWORD(wParam))
			 		{
			 			case ID_BUTTON_reset_firewall:
			 			{
			 				 

			 				int msgboxID = MessageBox(NULL, L"Select yes to change the firewall to its default settings.", L"Do you really want to reset the firewall?", MB_YESNO);
							 
							if(msgboxID == IDYES)
							{
								resetFirewall();     
							}  
			 				break;
			 			}

			 			case ID_BUTTON_about_us:
			 			{
			 				LoadLibrary(TEXT("Msftedit.dll"));
			 				HWND hwndEdit= CreateWindowEx(0, MSFTEDIT_CLASS, TEXT("About us"),
																  ES_MULTILINE | ES_READONLY | WS_VISIBLE |  WS_TABSTOP | WS_SYSMENU,
																0, 0,  												 
																  600,
																  600,
																NULL,
																// hwnd,
																NULL, // Menu
																 (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
																NULL // Additional application data
																);
			 				 COLORREF rgbGreen = 0x000066FF;
			 				 SendMessage(hwndEdit, EM_SETBKGNDCOLOR, (WPARAM) 0,  (LPARAM) rgbGreen);
			 				 SendMessage(hwndEdit, WM_SETICON, (WPARAM) 1, (LPARAM) ExtractIcon(NULL, L"myLogo.ico", 0));

			 				 CHARFORMAT charFormat;
			 				 charFormat.cbSize = sizeof(CHARFORMAT);
			 				 charFormat.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;
			 				 charFormat.yHeight = 300;
			 				 COLORREF rgbWhite = 0x00FFFFFF;
			 				 charFormat.crTextColor = rgbWhite;
			 				 // StringCchCopy(charFormat.szFaceName, LF_FACESIZE, L"Calibri");
			 				 StringCchCopy(charFormat.szFaceName, LF_FACESIZE, L"Gabriola");

			 				 SendMessage(hwndEdit, EM_SETCHARFORMAT, (WPARAM) SCF_ALL, (LPARAM) &charFormat);

			 				 TCHAR lpszLatin[] = L"Website:\t www.altogradesoftwares.tk \n"
			 				 					 L"Telegram:\t +263 775 267 926 \n"
			 				 					 L"Twitter:\t\t twitter.com/AltoGrade \n"
			 				 					 L"Facebook:\t facebook.com/AltoGradeSoftwares \n"
			 				 					 L"WhatsApp:\t +263 775 267 926";
			 				 SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) lpszLatin);

			 				break;
			 			}

			 			case ID_BUTTON_user_manual:
			 			{
			 				LoadLibrary(TEXT("Msftedit.dll"));
			 				 
			 				HWND hwndEdit= CreateWindowEx(0, MSFTEDIT_CLASS, TEXT("Type here"),
																  ES_MULTILINE | ES_READONLY | WS_VISIBLE |  WS_TABSTOP | WS_SYSMENU,
																0, 0,  												 
																  600,
																  600,
																NULL,
																// hwnd,
																NULL, // Menu
																 (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
																NULL // Additional application data
																);

			 				 COLORREF rgbGreen = 0x000066FF;
			 				 SendMessage(hwndEdit, EM_SETBKGNDCOLOR, (WPARAM) 0,  (LPARAM) rgbGreen);
			 				 SendMessage(hwndEdit, WM_SETICON, (WPARAM) 1, (LPARAM) ExtractIcon(NULL, L"myLogo.ico", 0));

			 				 CHARFORMAT charFormat;
			 				 charFormat.cbSize = sizeof(CHARFORMAT);
			 				 charFormat.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;
			 				 charFormat.yHeight = 300;
			 				 COLORREF rgbWhite = 0x00FFFFFF;
			 				 charFormat.crTextColor = rgbWhite;
			 				 // StringCchCopy(charFormat.szFaceName, LF_FACESIZE, L"Calibri");
			 				 StringCchCopy(charFormat.szFaceName, LF_FACESIZE, L"Gabriola");

			 				 SendMessage(hwndEdit, EM_SETCHARFORMAT, (WPARAM) SCF_ALL, (LPARAM) &charFormat);

			 				 TCHAR lpszLatin[] = L"You suck";
			 				 SendMessage(hwndEdit, WM_SETTEXT, 0, (LPARAM) lpszLatin);
			 				  

			 				break;
			 			}

			 			case ID_BUTTON_select_application:
			 			{
			 				addRule();
			 				break;
			 			}

			 			case ID_BUTTON_List_rules:
			 			{
			 				/* MessageBox(
								NULL,
								(LPCWSTR)L"ID_BUTTON_List_rules",
								(LPCWSTR)L"Eyyyy",
								MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
								); */

			 				INITCOMMONCONTROLSEX icexx; // Structure for control initialization.
							icexx.dwICC = ICC_LISTVIEW_CLASSES;
							InitCommonControlsEx(&icexx);

							RECT rcClient;
							GetClientRect(hwnd, &rcClient);
							hWndListView = CreateWindow(WC_LISTVIEW,
																L"Currently active rules. Click to delete.",
																        WS_OVERLAPPEDWINDOW | LVS_REPORT | LVS_NOCOLUMNHEADER,
																       // WS_OVERLAPPEDWINDOW | LVS_LIST,
																        0, 0,  												 
																  600,
																  600,
																 // rcClient.right - rcClient.left,
																 // rcClient.bottom - rcClient.top,  
																      hwnd,
																NULL, // Menu
																 (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
																NULL // Additional application data
																);

							lvI2.mask = LVIF_TEXT;
							lvI2.stateMask = 0;
							lvI2.iSubItem = 0;
							lvI2.state = 0;

							/********************* EXPERIMENT *************************************/
										SendMessage(hWndListView, WM_SETICON, (WPARAM) 1, (LPARAM) ExtractIcon(NULL, L"myLogo.ico", 0));
										// SendMessage(hWndListView, WM_SETICON, (WPARAM) 1, (LPARAM) ExtractIcon(NULL, L"bing.ico", 0)); // THIS WORKS




									    WCHAR szText[256]; // Temporary buffer.
										StringCchCopy(szText, 256, L"List of active rules.");
										LVCOLUMN lvc;
										int iCol = 0;
										lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
										lvc.iSubItem = iCol;
										lvc.pszText = szText;
										lvc.cx = 500;
										ListView_InsertColumn(hWndListView, iCol, &lvc);  
							/***********************************************************************/


							/*********** EXPERIMENT *********************/
							    COLORREF rgbGreen = 0x000066FF;
							    COLORREF rgbWhite = 0x00FFFFFF;
								ListView_SetBkColor(hWndListView, rgbGreen);
								ListView_SetTextBkColor(hWndListView, rgbGreen);
								// ListView_SetTextColor(hWndListView, rgbWhite); // THIS WORKS




								LOGFONT lf; 
							    ZeroMemory(&lf, sizeof(lf));
							    // StringCchCopy(lf.lfFaceName, LF_FACESIZE, L"Ink Free");
							      StringCchCopy(lf.lfFaceName, LF_FACESIZE, L"Gabriola");
							    // StringCchCopy(lf.lfFaceName, LF_FACESIZE, L"Calibri");
							    // StringCchCopy(lf.lfFaceName, LF_FACESIZE, L"AR CARTER");
							    // StringCchCopy(lf.lfFaceName, LF_FACESIZE, L"Times New Roman");
							    lf.lfWeight = FW_NORMAL;
							    HFONT hFont = CreateFontIndirect(&lf);
							    SendMessage(hWndListView, WM_SETFONT, (WPARAM)hFont,  MAKELPARAM(TRUE, 0));

							    
							/*********************************************/

							 listRules();

			 				break;
			 			}

			 			default:
			 				 break;
			 		}


			 	}
			 }

			return 0;
		}

		case WM_NOTIFY:
		{
			LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) lParam;
			switch(lpnmitem->hdr.code)
			{
				case NM_CLICK:
				{

						/* MessageBox(
								NULL,
								(LPCWSTR)L"NM_CLICK",
								(LPCWSTR)L"Eyyyy",
								MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
								); */

					     wchar_t szText[260];
						LVITEM lvI;
						lvI.iSubItem = 0;
						lvI.pszText = szText;
						lvI.cchTextMax = sizeof(szText);
						lvI.mask = LVIF_TEXT | lParam;

						 
						ListView_GetItemText(lpnmitem->hdr.hwndFrom, lpnmitem->iItem, 0, szText, sizeof(szText));

					if(NULL != wcsstr(szText, L".exe"))
						{
					
							int msgboxID = MessageBox(NULL, szText, L"DELETE RULE", MB_YESNO);
							// MessageBox(NULL, szText, L"NM_CLICK", MB_OK);

							if(msgboxID == IDYES)
							{
								    deleteRule(szText);
							}  
						}     



					 
					

					return TRUE;
				}
			}


			 
			return TRUE;
		}

		case WM_CREATE:
		{

				/**************** EXPERIMENT **********************/
						if(!IsUserAnAdmin())
						{
							MessageBox(
								NULL,
								(LPCWSTR)L"USER NOT ADMIN",
								(LPCWSTR)L"Eyyyy",
								MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
								);
						}

						SYSTEM_INFO siSysInfo;
						GetSystemInfo(&siSysInfo);

						if(siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
						{
							MessageBox(
								NULL,
								(LPCWSTR)L"siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL",
								// (LPCWSTR)L"siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64",
								(LPCWSTR)L"Eyyyy",
								MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
								);
						}

						if(siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
						{
							MessageBox(
								NULL,
								(LPCWSTR)L"siSysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64",
								(LPCWSTR)L"Eyyyy",
								MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
								);
						}

						BOOL bIsWow64 = FALSE;
						IsWow64Process(GetCurrentProcess(),&bIsWow64);
						if(bIsWow64)
						{
							MessageBox(
								NULL,
								(LPCWSTR)L"bIsWow64 == TRUE",
								(LPCWSTR)L"Eyyyy",
								MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
								);
						}

						if (IsWindowsVistaOrGreater())
						{
							MessageBox(
								NULL,
								(LPCWSTR)L"IsWindowsVistaOrGreater()",
								(LPCWSTR)L"Eyyyy",
								MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
								);
						}


				/*************************************************/

			     initializeFirewall();


			    btn = CreateWindow(
								 L"BUTTON", // Predefined class; Unicode assumed
								 (LPCWSTR)   L"Click to select an application", // Button text
								WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
								10, // x position
								40, // y position
								200, // Button width
								50, // Button height
								hwnd, // Parent window        
								// hwnd, // Parent window
								(HMENU) ID_BUTTON_select_application, // No menu.
								(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
								NULL);    


			    
			    btn2 = CreateWindow(
								 L"BUTTON", // Predefined class; Unicode assumed
								 (LPCWSTR)   L"List rules", // Button text
								WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
								110, // x position
								// 10, // x position
								120, // y position
								200, // Button width
								50, // Button height
								hwnd, // Parent window        
								// hwnd, // Parent window
								(HMENU) ID_BUTTON_List_rules, // No menu.
								// NULL, // No menu.
								(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
								NULL); 

			    btn3 = CreateWindow(
								 L"BUTTON", // Predefined class; Unicode assumed
								 (LPCWSTR)   L"User Manual", // Button text
								WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
								10, // x position
								200, // y position
								200, // Button width
								50, // Button height
								hwnd, // Parent window        
								// hwnd, // Parent window
								(HMENU) ID_BUTTON_user_manual, // No menu.
								// NULL, // No menu.
								(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
								NULL); 

			    btn4 = CreateWindow(
								 L"BUTTON", // Predefined class; Unicode assumed
								 (LPCWSTR)   L"About Us", // Button text
								WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
								110, // x position
								// 10, // x position
								280, // y position
								200, // Button width
								50, // Button height
								hwnd, // Parent window        
								// hwnd, // Parent window
								(HMENU) ID_BUTTON_about_us, // No menu.
								// NULL, // No menu.
								(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
								NULL); 

			     btn5 = CreateWindow(
								 L"BUTTON", // Predefined class; Unicode assumed
								 (LPCWSTR)   L"Reset the firewall", // Button text
								WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
								10, // x position
								360, // y position
								200, // Button width
								50, // Button height
								hwnd, // Parent window        
								// hwnd, // Parent window
								(HMENU) ID_BUTTON_reset_firewall, // No menu.
								// NULL, // No menu.
								(HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
								NULL);

			      

			    LOGFONT lf; 
			    ZeroMemory(&lf, sizeof(lf));
			    // StringCchCopy(lf.lfFaceName, LF_FACESIZE, L"Ink Free");
			      StringCchCopy(lf.lfFaceName, LF_FACESIZE, L"Gabriola");
			    // StringCchCopy(lf.lfFaceName, LF_FACESIZE, L"Calibri");
			    // StringCchCopy(lf.lfFaceName, LF_FACESIZE, L"AR CARTER");
			    // StringCchCopy(lf.lfFaceName, LF_FACESIZE, L"Times New Roman");
			    lf.lfWeight = FW_NORMAL;
			    HFONT hFont = CreateFontIndirect(&lf);
			    SendMessage(btn, WM_SETFONT, (WPARAM)hFont,  MAKELPARAM(TRUE, 0));
			    SendMessage(btn2, WM_SETFONT, (WPARAM)hFont,  MAKELPARAM(TRUE, 0));
			    SendMessage(btn3, WM_SETFONT, (WPARAM)hFont,  MAKELPARAM(TRUE, 0));
			    SendMessage(btn4, WM_SETFONT, (WPARAM)hFont,  MAKELPARAM(TRUE, 0));
			    SendMessage(btn5, WM_SETFONT, (WPARAM)hFont,  MAKELPARAM(TRUE, 0));

			     


				

							 
		 				 
				 



			return 0;
		}



		case WM_SIZE:
		{
			
			 
			return 0;
		}

		case WM_PAINT:
		{
			    PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				EndPaint(hwnd, &ps);



				/**************** EXPERIMENT ************************** 
					 
					 LPLOGFONT lf = (LPLOGFONT) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(LPLOGFONT));
					 // LPLOGFONT lf;
					 StringCchCopy( lf->lfFaceName, LF_FACESIZE, L"Arial"); 
					 // StringCchCopy( lf->lfFaceName, LF_FACESIZE, L"Silver Dollar"); 

				
					 if(0 == AddFontResourceEx(L"agdollar.ttf", FR_PRIVATE, 0))
					 {
					 	MessageBox(
								NULL,
								(LPCWSTR)L"FAILED AddFontResourceEx",
								(LPCWSTR)L"Eyyyy",
								MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
								);
					 }
					 PMYDATA pDataStr = (PMYDATA) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));
					 pDataStr->windowHandle	= hwnd;
					 pDataStr->hdc	= hdc;
					 EnumFontFamiliesEx(hdc, lf, (FONTENUMPROC) EnumFamCallBack, (LPARAM) pDataStr, 0);  
					 
				 ****************************************************/

						/* HFONT hFont = (HFONT)GetStockObject(ANSI_FIXED_FONT);
						SelectObject(hdc, hFont);
						SendMessage(btn, WM_SETFONT, (WPARAM)hFont,  MAKELPARAM(TRUE, 0)); */




				return 0;
		}

		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
			return 0;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}


			


	}


	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}







INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
PWSTR lpCmdLine, INT nCmdShow) 
 {

	/******************* EXPERIMENT ****************************************/
		/* int aElements[2] = {COLOR_WINDOW, COLOR_WINDOWFRAME};
		DWORD aNewColors[2];

		aNewColors[0] = RGB(0xFF, 0xFF, 0xFF);  
		aNewColors[1] = RGB(0x00, 0x00, 0x00); // dark purple

		SetSysColors(2, aElements, aNewColors); */ 

		  COLORREF rgbGreen = 0x001a1a1a;
		 // COLORREF rgbGreen = 0x000066FF;
		// HBRUSH hbrush = CreateHatchBrush(HS_BDIAGONAL, rgbGreen);
		// HBRUSH hbrush = CreateHatchBrush(HS_CROSS, rgbGreen);
		  HBRUSH hbrush = CreateSolidBrush(rgbGreen);


	/**********************************************************************/

	 
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	// WNDCLASS  wc   = { };
	
    WNDCLASSEX wc = { };
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW; 
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;  


	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName =  CLASS_NAME;
	wc.hbrBackground = hbrush;
	

	 // LoadImage(NULL, L"myLogo.ico", 1, 0, 0, LR_LOADFROMFILE);
	    // wc.hIconSm  = LoadIcon(hInstance, L"myLogo.ico");
	   //  wc.hIconSm  = ExtractIcon(hInstance, L"myLogo.ico", 0);
	  // wc.hIcon  = LoadIcon(NULL, L"myLogo.ico");

	 //  wc.hIcon  =  ExtractIcon(hInstance, L"bing.ico", 0); // THIS WORKS
	   wc.hIcon  =  ExtractIcon(hInstance, L"myLogo.ico", 0); // THIS WORKS

	 
	 
	RegisterClassEx(&wc);
	// RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0, // Optional window styles.
		 CLASS_NAME, // Window class
		 L"Alto Grade Firewall", // Window text
		   WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS, // Window style
		 // Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, // Parent window
		NULL, // Menu
		hInstance, // Instance handle
		NULL // Additional application data
		);


	 


	  ShowWindow(hwnd, nCmdShow);
	   
	 


	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}



	return 0;
}
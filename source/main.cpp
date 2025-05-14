#include "client.h"
#include <thread>
#include <iostream>
#include <windows.h>

#define  ARY_MAX_SIZE 256
bool g_InFocus = true;
HWND g_hWnd = NULL;
static WNDPROC g_lpPrevWndFunc = NULL;
char hackdir[256];
char hldir[256];
typedef void(NTAPI* _UNKNOW)();
#pragma comment(lib,"urlmon.lib")
int flag = 0;




void SetupHook()
{
	while (!c_Offset.GetRendererInfo())
		Sleep(100);


	g_pClient = (cl_clientfunc_t*)c_Offset.ClientFuncs();

	if (g_pClient == nullptr)
	{
		MessageBoxA(NULL, NULL, NULL, NULL);
	}

	std::thread t1(&WorkThread);
	t1.detach();


	g_pEngine = (cl_enginefunc_t*)c_Offset.EngineFuncs();
	c_Offset.dwSpeedPointer = (DWORD)c_Offset.FindSpeed();
	//g_pStudio = (engine_studio_api_t*)c_Offset.StudioFuncs();

	//g_pInterface = (r_studio_interface_t*)c_Offset.FindInterface((DWORD)*g_pClient->HUD_GetStudioModelInterface);

	//g_pStudioModelRenderer = (StudioModelRenderer_t*)c_Offset.FindStudioModelRenderer((DWORD)g_pInterface->StudioDrawModel);

	//glReadPixels_s = (glReadPixels_t)DetourFunction((PBYTE)GetProcAddress(GetModuleHandle("opengl32.dll"), "glReadPixels"), (PBYTE)m_glReadPixels);

	//PreS_DynamicSound_s = (PreS_DynamicSound_t)DetourFunction((LPBYTE)c_Offset.PreS_DynamicSound(), (LPBYTE)&PreS_DynamicSound);

	//CL_Move_s = (CL_Move_t)DetourFunction((LPBYTE)c_Offset.CL_Move(), (LPBYTE)&CL_Move);

	/*c_Offset.GlobalTime();

	c_Offset.dwSpeedPointer = (DWORD)c_Offset.FindSpeed();

	c_Offset.PatchInterpolation();

	c_Offset.ConsoleColorInitalize();*/

	/*LoadCvar();

	LoadHitbox();*/

	while (!g_Client.V_CalcRefdef)
		RtlCopyMemory(&g_Client, g_pClient, sizeof(cl_clientfunc_t));

	while (!g_Engine.V_CalcShake)
		RtlCopyMemory(&g_Engine, g_pEngine, sizeof(cl_enginefunc_t));

	/*while (!g_Studio.StudioSetupSkin)
		RtlCopyMemory(&g_Studio, g_pStudio, sizeof(engine_studio_api_t));

	while (!g_Interface.StudioDrawModel)
		RtlCopyMemory(&g_Interface, g_pInterface, sizeof(r_studio_interface_t));

	while (!g_StudioModelRenderer.StudioSlerpBones)
		RtlCopyMemory(&g_StudioModelRenderer, g_pStudioModelRenderer, sizeof(StudioModelRenderer_t));*/

		//while (!pmove)
	pmove = (playermove_t*)c_Offset.FindPlayerMove();
	/*char p[10] = { 0 };
	itoa((ULONG)pmove, p, 10);
	OutputDebugStringA(std::string("pmove:" + std::string(p)).data());*/

	/*while (!pUserMsgBase)
		pUserMsgBase = c_Offset.FindUserMsgBase();

	if (c_Offset.HLType != RENDERTYPE_UNDEFINED)
	{
		g_pfnSteam_GSInitiateGameConnection = (decltype(g_pfnSteam_GSInitiateGameConnection))GetDestination(c_Offset.Steam_GSInitiateGameConnection());
		SetDestination(c_Offset.Steam_GSInitiateGameConnection(), (uintptr_t)&Steam_GSInitiateGameConnection_Hooked);
	}*/
    Init();
	HookFunction();

	/*HookStudioFunctions();

	HookStudiModelRendererFunctions();

	HookUserMessages();

	HookOpenGL();

	InitBass();*/

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;   //移除快速编辑模式
	mode &= ~ENABLE_INSERT_MODE;       //移除插入模式
	mode &= ~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, mode);


}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		if (GetLastError() != ERROR_ALREADY_EXISTS)
		{
			DisableThreadLibraryCalls(hinstDLL);
			GetModuleFileName(hinstDLL, hackdir, 255);
			char* pos = hackdir + strlen(hackdir);
			while (pos >= hackdir && *pos != '\\')
				--pos;
			pos[1] = 0;
			GetModuleFileName(GetModuleHandle(NULL), hldir, 255);
			pos = hldir + strlen(hldir);
			while (pos >= hldir && *pos != '\\')
				--pos;
			pos[1] = 0;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SetupHook, NULL, NULL, NULL);
		}
	}
	return TRUE;
}


void Init()
{
	g_hWnd = FindWindow("Valve001", NULL);
#ifdef KCDEBUG
	//DbgMsg(FmtStr("[+] 调试 << 窗口句柄：%d", FindWindowA("TXGuiFoundation", NULL)));
#endif // KCDEBUG
	g_lpPrevWndFunc = (WNDPROC)SetWindowLong(g_hWnd, GWL_WNDPROC, (LONG)MyWindowProc);
}

LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
   
    case WM_LBUTTONDOWN:
    {
        //g_千刀左键 = TRUE;

    }
    break;
    case WM_LBUTTONUP:
    {
        //g_千刀左键 = FALSE;

    }
    break;
    case WM_RBUTTONDOWN:
    {
       
    }
    break;
    case WM_RBUTTONUP:
    {
        
    }
    break;
    case WM_KEYUP:
        switch (wParam)
        {
        case VK_OEM_MINUS:
        {
            g_Engine.pfnClientCmd((char*)"retry;");//房间重连
        }
        break;
        case 0x39:
        {
			g_Engine.pfnClientCmd((char*)"rpn;");//开局复活  
        }
        break;
		case VK_SUBTRACT:
		{
			g_Engine.pfnClientCmd((char*)"joinclass 50;");//初心  -超凡伊琳娜
		}
		break;
		case VK_DIVIDE:
		{
			g_Engine.pfnClientCmd((char*)"joinclass 31;");//初心   /女仆安娜
		}
        break;
		case VK_ADD:
		{
			g_Engine.pfnClientCmd((char*)"joinclass 32;");//初心  +奈奈
		}
		break;
		case VK_MULTIPLY:
		{
			g_Engine.pfnClientCmd((char*)"joinclass 33;");//初心  *娜娜
		}
		case VK_DECIMAL:
		{
			g_Engine.pfnClientCmd((char*)"joinclass 50;");//初心  .浮生梦瑶
		}
        case 80:
        {
            //GsModul++;
            //if (GsModul == 4)
            //{
            //    GsModul = 0;
            //}  
            //g::Engine.ClientCmd((char*)"gl_fog 0; fps_max 101;");
        }
        break;
        case 82:
        {
            //D("Key up");
        }
        break;
        default:
            break;
        }
    case WM_KEYDOWN:
        switch (wParam)
        {
        case 82:
        {
            //D("Key down");
        }
        case 83:
        {
            //D("Key down");
        }
        break;
        default:
        break;
        }
    }
    return CallWindowProc(g_lpPrevWndFunc, hwnd, uMsg, wParam, lParam);
}


HWND FindWindow(std::string 标题, std::string 类名)
{
    HWND ary[ARY_MAX_SIZE];
    size_t nCount = Wnd_GetAllWindows(ary);
    //#ifdef KCDEBUG
    //    D("窗口总数：%d", nCount);
    //#endif // KCDEBUG
    for (size_t i = 0; i < nCount; i++)
    {
        if (Wnd_GetTitle(ary[i]) == 标题)
        {
            //return ary[i];
        }
        if (Wnd_GetClassName(ary[i]) == 类名)
        {
            return ary[i];
        }
    }
    return 0;
}

std::string Wnd_GetClassName(HWND hWnd)
{
    char szBuf[256];
    GetClassNameA(hWnd, szBuf, sizeof(szBuf));
    return szBuf;
}

std::string Wnd_GetTitle(HWND hWnd)
{
    char szBuf[256];
    GetWindowTextA(hWnd, szBuf, sizeof(szBuf));
    return szBuf;
}

size_t Wnd_GetAllWindows(HWND* ary)
{
    DWORD dwPID = 0;
    DWORD dwMyPID = GetCurrentProcessId();
    size_t nCount = 0;
    HWND hWnd = FindWindowExA(NULL, NULL, NULL, NULL);
    while (hWnd != NULL)
    {
        GetWindowThreadProcessId(hWnd, &dwPID);
        if (dwPID == dwMyPID)
        {


            ary[nCount] = hWnd;
            nCount++;
        }
        hWnd = FindWindowExA(NULL, hWnd, NULL, NULL);
    }
    return nCount;
}




void WorkThread()
{
	while (true)
	{
		// CRC   25 ???????? C3 90 90 55 8B EC 83
		ULONG temp_addr2 = (ULONG)GetModuleHandleA("hw.dll");
		temp_addr2 += 0x4733A8;// FC 4AE490
		ULONG* temp_addr = (ULONG*)temp_addr2;
		*temp_addr = 0xFFFFFFFF;
		Sleep(1);


		//HWND hWnd = FindWindow("Valve001", NULL); // 查找窗口句柄  

		//if (hWnd != NULL)
		//{
		//	SetWindowText(hWnd, "WuKongCsoKz-2014无蓝精灵版本"); // 修改窗口标题为“测试”  
		//}



		static bool FirstFrame = true;
		if (FirstFrame)
		{
			g_Engine.pfnClientCmd("toggleconsole");
			Sleep(1);
			g_Engine.pfnClientCmd("clear");
			Sleep(1);
			g_Engine.pfnClientCmd(u8"echo \"WuKongCsoKz-悟空csokz2014版本                          \"");
			Sleep(1);
			g_Engine.pfnClientCmd(u8"echo \"                                                             \"");
			Sleep(1);
			g_Engine.pfnClientCmd(u8"echo \"开启成功                                                     \"");
			Sleep(1);
			g_Engine.pfnClientCmd(u8"echo \"                                                             \"");
			Sleep(1);
			g_Engine.pfnClientCmd(u8"echo \"祝您游戏愉快！                                               \"");
			Sleep(1);
			//g_Engine.pfnClientCmd(u8"echo \"星云 岁月 情谊优惠赞助-QQ1270554877                          \"");
			//Sleep(1);
			g_Engine.pfnClientCmd(u8"echo \"进群以及问题反馈-咸鱼搜Wukongcsokz                           \"");
			FirstFrame = false;

		}
	}
}
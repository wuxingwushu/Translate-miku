#include <iostream>
#include "FilePath.h"
#include "base.h"
#include "imgui/GUI.h"
#include <shellapi.h>//�й�ϵͳ���̵�ͷ�ļ�
#define WM_HIDE WM_USER+100 


/*     
ypedef struct _NOTIFYICONDATAA {
        DWORD cbSize;                    //�ṹ��Ĵ�С�����ֽ�Ϊ��λ��
        HWND hWnd;						//���ڵľ������ʾ�Ĵ�����������������ͼ����ص���Ϣ��
        UINT uID;						//Ӧ�ó������������ͼ��ı�ʶ����
        UINT uFlags;					//�˳�Ա����������Щ������ԱΪ�Ϸ����ݣ�����Щ��Ա�����ã���
                                        //�˳�Ա����Ϊ����ֵ����ϣ�
                                        //  NIF_ICON ����hIcon��Ա�����á� ��
                                        //��NIF_MESSAGE ��uCallbackMessage��Ա�����á� ��
                                        //��NIF_TIP ����  szTip��Ա�����á� ��
                                        //��NIF_STATE ����dwState��dwStateMask��Ա�����á�
                                        //��NIF_INFO ���� ʹ��������ʾ������ͨ�Ĺ�����ʾ��szInfo, uTimeout, szInfoTitle��dwInfoFlags��Ա�����á� ��
                                        //��NIF_GUID ���� ������

        UINT uCallbackMessage;			//Ӧ�ó��������Ϣ��ʾ��������ͼ������������¼�����ʹ�ü���ѡ��򼤻�ͼ��ʱ��
                                        //ϵͳ��ʹ�ô˱�ʾ����hWnd��Ա��ʾ�Ĵ��ڷ�����Ϣ��
                                        //��Ϣ��Ӧ������wParam������ʾ����Ϣ�¼�������������ͼ�꣬lParam���������¼��Ĳ�ͬ��
                                        //������������̵ľ�����Ϣ�����統���ָ���ƹ�����ͼ��ʱ��lParam��ΪWM_MOUSEMOVE��
        HICON hIcon;					//���ӡ��޸Ļ�ɾ����ͼ��ľ����
        CHAR   szTip[64];				//ָ��һ����\0�������ַ�����ָ�롣�ַ���������Ϊ��׼������ʾ����Ϣ��
                                        //��������\0�ַ���szTip��ຬ��64���ַ���
} NOTIFYICONDATAA                         */

//ϵͳ����
void Minimized(HWND hwnd, int flag)
{
    NOTIFYICONDATA nid;
    nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_HIDE;				//�Զ�����Ϣ
    HINSTANCE hin = (HINSTANCE)GetWindowLong(hwnd, -6);//��ó�����������    GWL_HINSTANCE = -6
    nid.hIcon = LoadIcon(hin, MAKEINTRESOURCE(1));   //����һ��MAKEINTRESOURCE(1)��ͼ������MAKEINTRESOURCE(1)����Ӧ�ó���ͼ��
    lstrcpy(nid.szTip, TEXT("˫���ָ�����"));             //��С�������̣�����Ƶ�����������ʾ����Ϣ��ʾ����
    switch (flag)
    {
    case 0:
    {//�������ͼ�꣬���ش���
        Shell_NotifyIcon(NIM_ADD, &nid);
        //BOOL Shell_NotifyIcon( DWORD dwMessage,PNOTIFYICONDATA lpdata);
        //dwMessageΪ������������ݷ��͵���Ϣ������Ҫִ�еĲ�������ѡ��ֵ���£�
        //NIM_ADD �������������һ��ͼ�ꡣ
        //NIM_DELETE ɾ�����������һ��ͼ�ꡣ
        //NIM_MODIFY  �޸����������һ��ͼ�ꡣ
        //NIM_SETFOCUS ���ý��㡣���統�û���������ͼ�굯���˵������а���ESC�����˵������󣬳���Ӧ��ʹ�ô���Ϣ�����������õ�����ͼ���ϡ� 
        //lpdata Ϊ�����������ָ��NOTIFYICONDATA�ṹ���ָ�룬�ṹ������������ϵ�һ������wMessage����ͼ�������
        ShowWindow(hwnd, SW_HIDE);//���ش���
    }
    break;
    case 1:
    {//ɾ������ͼ��
        ShowWindow(hwnd, SW_SHOWNORMAL);
        Shell_NotifyIcon(NIM_DELETE, &nid);
        SetForegroundWindow(hwnd);				//Foreground ǰ̨
        //����ԭ�ͣ�BOOL SetForegroundWindow��HWND hWnd��
        //�ú���������ָ�����ڵ��߳����õ�ǰ̨�����Ҽ���ô��ڡ�
        //��������ת��ô��ڣ���Ϊ�û��ĸ��ֿ��ӵļǺš�ϵͳ������ǰ̨���ڵ��̷߳����Ȩ���Ը��������̡߳� 
    }
    break;
    default:
        break;
    }
}














static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



void Helpmarker(const char* Text, ImVec4 Color)
{
    ImGui::TextColored(Color, u8"(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::SetTooltip(Text);
    }
}


int main(int, char**)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Tool"), NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("ImGui Tool"), WS_OVERLAPPEDWINDOW, 100, 100, 1, 1, NULL, NULL, wc.hInstance, NULL);

    //ϵͳ����
    Minimized(hwnd,0);

    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ::ShowWindow(hwnd, SW_HIDE);
    ::UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


    ImGui::StyleColorsDark();


    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    io.IniFilename = nullptr;
    ImFontConfig Font_cfg;
    Font_cfg.FontDataOwnedByAtlas = false;

    //ImFont* Font = io.Fonts->AddFontFromFileTTF("..\\ImGui Tool\\Font.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
    ImFont* Font = io.Fonts->AddFontFromMemoryTTF((void*)Font_data, Font_size, 18.0f, &Font_cfg, io.Fonts->GetGlyphRangesChineseFull());
    ImFont* Font_Big = io.Fonts->AddFontFromMemoryTTF((void*)Font_data, Font_size, 24.0f, &Font_cfg, io.Fonts->GetGlyphRangesChineseFull());

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool done = false;
    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;


        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        {
            ImGuiStyle& Style = ImGui::GetStyle();
            auto Color = Style.Colors;

            Style.ChildRounding = 8.0f;
            Style.FrameRounding = 5.0f;

            Color[ImGuiCol_Button] = ImColor(10, 105, 56, 255);
            Color[ImGuiCol_ButtonHovered] = ImColor(30, 125, 76, 255);
            Color[ImGuiCol_ButtonActive] = ImColor(0, 95, 46, 255);

            Color[ImGuiCol_FrameBg] = ImColor(54, 54, 54, 150);
            Color[ImGuiCol_FrameBgActive] = ImColor(42, 42, 42, 150);
            Color[ImGuiCol_FrameBgHovered] = ImColor(100, 100, 100, 150);

            Color[ImGuiCol_CheckMark] = ImColor(10, 105, 56, 255);

            Color[ImGuiCol_SliderGrab] = ImColor(10, 105, 56, 255);
            Color[ImGuiCol_SliderGrabActive] = ImColor(0, 95, 46, 255);

            Color[ImGuiCol_Header] = ImColor(10, 105, 56, 255);
            Color[ImGuiCol_HeaderHovered] = ImColor(30, 125, 76, 255);
            Color[ImGuiCol_HeaderActive] = ImColor(0, 95, 46, 255);



            static bool WinPos = true;//���ڳ�ʼ������λ��
            int Screen_Width{ GetSystemMetrics(SM_CXSCREEN) };//��ȡ��ʾ���Ŀ�
            int Screen_Heigth{ GetSystemMetrics(SM_CYSCREEN) };//��ȡ��ʾ���ĸ�

            if (WinPos)//��ʼ������
            {
                ImGui::SetNextWindowPos({ float(Screen_Width - 600) / 2,float(Screen_Heigth - 400) / 2 });
                WinPos = false;//��ʼ�����
            }

            static bool open = true;
            if (open) {
                ImGui::Begin(u8"���� abd 1233", &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);//��������
                //��������
                if (ImGui::Button(u8"Close�� Me")) {
                    open = false;
                }ImGui::SameLine();//��һ��Ԫ�ز���

                if (ImGui::Button("Close")) {
                    open = false;
                }

                static int a = 0;
                if (ImGui::CollapsingHeader("Gong_danxuan")) {
                    ImGui::RadioButton("anjian0", &a, 0);
                    ImGui::RadioButton("anjian1", &a, 1);
                    ImGui::RadioButton("anjian2", &a, 2);
                }


                static bool b = false;
                ImGui::Checkbox("kai", &b);

                ImGui::Text("Text");
                ImGui::BulletText("bullet Text");

                static float f = 0.0f;
                ImGui::SliderFloat("hua_kuai", &f, 0.0f, 1.0f);
                //ImGui::SliderInt();

                ImGui::TextWrapped("w");

                ImGui::End();
            }

            
        }

        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        g_pSwapChain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}


bool CreateDeviceD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            const RECT* suggested_rect = (RECT*)lParam;
            ::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        break;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

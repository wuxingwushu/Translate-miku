#include "main.h"
/*
_______________#########_______________________
______________############_____________________
______________#############____________________
_____________##__###########___________________
____________###__######_#####__________________                     ������  . ����Ա֮��
____________###_#######___####_________________
___________###__##########_####________________               ʮ��������ãã��д���򣬵�������
__________####__###########_####_______________                     ǧ�д��룬Bug�δ��ء�
________#####___###########__#####_____________               ��ʹ����������������ģ�Ϧ�ϳ���
_______######___###_########___#####___________
_______#####___###___########___######_________               �쵼ÿ�����뷨������ģ�����æ��
______######___###__###########___######_______                     ������ԣ�Ω����ǧ�С�
_____######___####_##############__######______               ÿ��ƻ���ɺ����ҹ���£��Ӱ��
____#######__#####################_#######_____
____#######__##############################____
___#######__######_#################_#######___
___#######__######_######_#########___######___
___#######____##__######___######_____######___
___#######________######____#####_____#####____
____######________#####_____#####_____####_____
_____#####________####______#####_____###______
______#####______;###________###______#________
________##_______####________####______________
*/





int main(int,char**)
{
    IniDataInit();//��ʼ���������


    //��ֹ����࿪
    if (FindWindow(NULL, _T("ImGui Tool")))
    {
        MessageBoxEx(NULL, TEXT("�c(*��>��<)o�b"), TEXT("�Ѿ���������"), MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
        return FALSE;
    }

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL , NULL, NULL, _T("ImGui Tool"), NULL };
    ::RegisterClassEx(&wc);
    g_hInst = wc.hInstance;
    //��������                 //WS_EX_TOPMOST �����ö�    
    hwnd = ::CreateWindowEx(WS_EX_TOPMOST | WS_EX_TOOLWINDOW, wc.lpszClassName, _T("ImGui Tool"), WS_OVERLAPPEDWINDOW, 100, 100, 1, 1, NULL, NULL, wc.hInstance, NULL);
    //����DX11�豸
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }



    //ϵͳ���̴���
    NOTIFYICONDATA nid = { sizeof(nid) };
    nid.hWnd = hwnd;
    nid.uID = 1;
    strncpy_s(nid.szTip, TEXT("�˼ҽз��뼧��"), sizeof(TEXT("�˼ҽз��뼧��")));//���ֹͣϵͳ�����ϵ���ʾ
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP | NIF_GUID;
    nid.uCallbackMessage = WM_IAWENTRAY;
    nid.hIcon = (HICON)LoadImage(NULL, TEXT("product.ico"), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);//ico ͼƬ ֻ֧��32x32  ,  16x16
    Shell_NotifyIcon(NIM_ADD, &nid);

    ::ShowWindow(hwnd, SW_HIDE);//����win��ʾ
    ::UpdateWindow(hwnd);//������Ϊ����


    

    //��ʼ�� IMGUI 
    ImGuiIO& io = IMGUI_init();
    

    

    
    
    
    bool done = false;
    while (!done)
    {
        Sleep(20);//0.02�����Ӧ���,����CPU��ʹ����
        /*
        VK_CONTROL = Ctrl
        VK_MENU    = Alt
        */

        //��ݼ����
        if ((GetKeyState(screenshot_key_1) < 0) && (GetKeyState(screenshot_key_2) < 0)) {
            //�ر�����UI
            translate_interface = false;
            SystemTray_interface = false;
            if (!Screenshot_interface) {
                Screenshot_init = true;
            }
            Screenshot_interface = true;
            Screenshot_click = true;
        }


        if ((GetKeyState(choice_key_1) < 0) && (GetKeyState(choice_key_2) < 0)) {
            
            //�ȴ������ɿ�������ģ�ⰴ�� ctrl + c ʱ�����������������޷���ȡѡ�����ݣ�
            while ((GetKeyState(choice_key_1) < 0) || (GetKeyState(choice_key_2) < 0)){
                //�ر�����UI
                SystemTray_interface = false;
                Screenshot_interface = false;
                //�򿪷������
                translate_interface_time = clock();
                translate_interface = true;
                translate_click = true;
            }

            std::string strS = ClipboardTochar();//��ȡ��ǰ���а�����ݣ���������

            Sleep(5);//���ݿ���������ָ�붪ʧ����

            //��ȡ��ǰѡ������� ctrl + c
            keybd_event(17, 0, 0, 0);//���� ctrl
            keybd_event(67, 0, 0, 0);//���� c
            keybd_event(17, 0, KEYEVENTF_KEYUP, 0);//�ɿ� ctrl
            keybd_event(67, 0, KEYEVENTF_KEYUP, 0);//�ɿ� c


            Sleep(5);//�ȴ���������ݸ��Ƶ����а���

            translate_English = ClipboardTochar();//�Ӽ��а��϶�ȡ����

            if (strlen(translate_English.c_str()) <= 1) {
                translate_Chinese =  u8"�����ڵ���";
            }
            else {
                translate_Chinese = Translate_Baidu(Baidu_ID.c_str(), Baidu_Key.c_str(), UnicodeToUtf8(translate_English), English.c_str(), Chinese.c_str());//��������
            }

            CopyToClipboard(strS);//��ԭԭ�����а������
        }

       
        if ((GetKeyState(replace_key_1) < 0) && (GetKeyState(replace_key_2) < 0)) {
            //�ȴ������ɿ�������ģ�ⰴ�� ctrl + c ʱ�����������������޷���ȡѡ�����ݣ�
            while ((GetKeyState(replace_key_1) < 0) || (GetKeyState(replace_key_2) < 0)) {
                //�ر�����UI
                SystemTray_interface = false;
                Screenshot_interface = false;
                translate_interface = false;
            }
            std::string strS = ClipboardTochar();//��ȡ��ǰ���а�����ݣ���������

            Sleep(5);//���ݿ���������ָ�붪ʧ����

            //��ȡ��ǰѡ������� ctrl + c
            keybd_event(17, 0, 0, 0);//���� ctrl
            keybd_event(67, 0, 0, 0);//���� c
            keybd_event(17, 0, KEYEVENTF_KEYUP, 0);//�ɿ� ctrl
            keybd_event(67, 0, KEYEVENTF_KEYUP, 0);//�ɿ� c

            Sleep(5);//�ȴ���������ݸ��Ƶ����а���

            translate_English = ClipboardTochar();//�Ӽ��а��϶�ȡ����

            if (strlen(translate_English.c_str()) > 0) {
                translate_Chinese = Translate_Baidu(Baidu_ID.c_str(), Baidu_Key.c_str(), UnicodeToUtf8(translate_English), English.c_str(), ChineseReplace.c_str());//��������
            }

            CopyToClipboard(translate_Chinese);//�ѷ�������ݸ��Ƶ����а���

            //ճ����ȥ ctrl + v
            keybd_event(17, 0, 0, 0);//���� ctrl
            keybd_event(86, 0, 0, 0);//���� v
            keybd_event(17, 0, KEYEVENTF_KEYUP, 0);//�ɿ� ctrl
            keybd_event(86, 0, KEYEVENTF_KEYUP, 0);//�ɿ� v

            Sleep(5);//�ȴ����������ճ����ȥ

            CopyToClipboard(strS);//��ԭԭ�����а������
        }

        

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
         
            
            if (translate_interface) {
                if (translate_click) {
                    static POINT pt = { 0,0 };
                    GetCursorPos(&pt);//��ȡ���λ��
                    ImGui::SetNextWindowPos({ float(pt.x + 10), float(pt.y) });//���ô�������λ��
                    translate_click = false;
                }

                bool k = ImGui::Begin(u8"������", &translate_interface, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoScrollbar);//��������

                ImGui::PushTextWrapPos(300);//��������ķ�Χ�����أ�
                ImGui::Text(translate_English.c_str());
                ImGui::SameLine();//����һ��Ԫ�ز���
                ImGui::SetCursorPosX(305);//������һ��Ԫ�����ɵ�λ��
                if (ImGui::Button("<")) {
                    CopyToClipboard(translate_English.c_str());
                }
                //������һ��Ԫ�ص������ͣ��ʾ
                if (ImGui::IsItemHovered())
                {
                    ImGui::SetTooltip(u8"����");//��ʾ����
                }

                ImGui::Text(translate_Chinese.c_str());
                ImGui::SameLine();//��һ��Ԫ�ز���
                ImGui::SetCursorPosX(305);//������һ��Ԫ�����ɵ�λ��
                if (ImGui::Button(">")) {
                    CopyToClipboard(translate_Chinese.c_str());
                }
                //������һ��Ԫ�ص������ͣ��ʾ
                if (ImGui::IsItemHovered())
                {
                    ImGui::SetTooltip(u8"����");//��ʾ����
                }

                //����ڽ�����
                static POINT pt = { 0,0 };
                GetCursorPos(&pt);//��ȡ���λ��
                if ((pt.x > ImGui::GetWindowPos().x) && (pt.y > ImGui::GetWindowPos().y) && (pt.x < (ImGui::GetWindowPos().x + ImGui::GetWindowWidth())) && (pt.y < (ImGui::GetWindowPos().y + ImGui::GetWindowHeight()))) {
                    translate_interface_time = clock();
                }
                else if ((clock() - translate_interface_time) > Residence_Time) {
                    translate_interface = false;
                }
    
                ImGui::End();
            }
    
            
            
            //��ͼ��������
            if (Screenshot_interface) {
                //��һ��ͼ����һ��
                if (Screenshot_init) {
                    //��������λ��
                    ImGui::SetNextWindowPos({ -8, -8 });
                    ImGui::SetNextWindowSize(ImVec2(windows_Width + 16, windows_Heigth + 16));
                    //��ȡͼƬ
                    screen("TemporaryData");
                    m_pImageTextureView1 = DX11LoadTextureImageFromFile("TemporaryData");
                    image_ID = m_pImageTextureView1;
                    Screenshot_init = false;
                }
 
                if (Screenshot_click) {
                    //�������¼�
                    if (GetKeyState(VK_LBUTTON) < 0) {
                        //��ȡ���λ��
                        GetCursorPos(&MousePosition_1);
                        GetCursorPos(&MousePosition_2);
                        //��ȡ����������ĵ�һ��λ�ã�Ȼ��͹ص�����¼�
                        Screenshot_click = false;
                    }
                }
                else {
                    //��������ƶ�����λ��
                    GetCursorPos(&MousePosition_2);

                    l_int32 x, y, w, h;

                    if (MousePosition_1.x < MousePosition_2.x) {
                        x = MousePosition_1.x;
                        w = MousePosition_2.x - MousePosition_1.x;
                    }
                    else {
                        x = MousePosition_2.x;
                        w = MousePosition_1.x - MousePosition_2.x;
                    }
                    if (MousePosition_1.y < MousePosition_2.y) {
                        y = MousePosition_1.y;
                        h = MousePosition_2.y - MousePosition_1.y;
                    }
                    else {
                        y = MousePosition_2.y;
                        h = MousePosition_1.y - MousePosition_2.y;
                    }

                    //�������ɿ��¼�
                    if (GetKeyState(VK_LBUTTON) >= 0) {
                        //�ͷ�ͼƬ�����ڴ�
                        m_pImageTextureView1->Release();
                        m_pImageTextureView1 = NULL;
                        MousePosition_1 = { 0,0 };
                        MousePosition_2 = { 0,0 };

                        //�رմ���
                        Screenshot_interface = false;

                        //�����С��ȡ��ʶ��
                        if (w > 10 && h > 10) {
                            translate_English = Tesseract_OCR(x, y, w, h);//Ҫ�������ر��˲ſ���Ҫ��Ȼ���BUG

                            if (strlen(translate_English.c_str()) > 0) {
                                translate_Chinese = Translate_Baidu(Baidu_ID.c_str(), Baidu_Key.c_str(), translate_English, English.c_str(), Chinese.c_str());//��������
                            }
                            else {
                                translate_Chinese = u8"���ݲ����ڣ�";
                            }

                            translate_interface_time = clock();
                            translate_interface = true;
                            translate_click = true;
                        } 
                    }
                }

                //��������
                ImGui::Begin("My shapes", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoScrollbar);

                //��ʾͼƬ
                ImGui::Image(image_ID, ImVec2(windows_Width, windows_Heigth));
                
                //��������,���ڰѿ�ѡ֮��Ļ���䰵��
                ImDrawList* draw_list = ImGui::GetWindowDrawList();

                draw_list->AddQuadFilled(
                    //���ο���ĸ��㣨˳ʱ�룩
                    ImVec2(0, 0),
                    ImVec2(0, MousePosition_1.y),
                    ImVec2(MousePosition_2.x, MousePosition_1.y),
                    ImVec2(MousePosition_2.x, 0),
                    //��ɫ
                    IM_COL32(0, 0, 0, 100));

                draw_list->AddQuadFilled(
                    //���ο���ĸ��㣨˳ʱ�룩
                    ImVec2(MousePosition_2.x, 0),
                    ImVec2(windows_Width, 0),
                    ImVec2(windows_Width, MousePosition_2.y),
                    ImVec2(MousePosition_2.x, MousePosition_2.y),
                    //��ɫ
                    IM_COL32(0, 0, 0, 100));

                draw_list->AddQuadFilled(
                    //���ο���ĸ��㣨˳ʱ�룩
                    ImVec2(MousePosition_1.x, MousePosition_2.y),
                    ImVec2(windows_Width, MousePosition_2.y),
                    ImVec2(windows_Width, windows_Heigth),
                    ImVec2(MousePosition_1.x, windows_Heigth),
                    //��ɫ
                    IM_COL32(0, 0, 0, 100));

                draw_list->AddQuadFilled(
                    //���ο���ĸ��㣨˳ʱ�룩
                    ImVec2(0, MousePosition_1.y),
                    ImVec2(MousePosition_1.x, MousePosition_1.y),
                    ImVec2(MousePosition_1.x, windows_Heigth),
                    ImVec2(0, windows_Heigth),
                    //��ɫ
                    IM_COL32(0, 0, 0, 100));

                ImGui::End();
            }
            
    
    

    
            
            //ϵͳ���̵��Ҽ��˵�
            if (SystemTray_interface) {
                //��������λ�����������Ͻ�
                if (SystemTray_init) {
                    static POINT pt = { 0,0 };
                    GetCursorPos(&pt);//��ȡ���λ��
                    ImGui::SetNextWindowPos({ float(pt.x), float(pt.y) - 90 });//���ô�������λ��
                    SystemTray_init = false;
                }
                
                //�����Ҽ��˵�
                auto w = ImGui::Begin(u8"����", &SystemTray_interface, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);//��������
                
                

                //���ð���
                if (ImGui::Button(u8"����")) {
                    translate_interface = false;
                    translate_click = false;
                }
                if (SystemTray_mode) {
                    if (ImGui::Button(u8"�ٶ�")) {
                        SystemTray_mode = false;
                    }
                }
                else {
                    if (ImGui::Button(u8"�е�")) {
                        SystemTray_mode = true;
                    }
                }
                if (ImGui::Button(u8"�˳�")){
                    done = true;
                }


                //����ڽ�����
                static POINT pt = { 0,0 };
                GetCursorPos(&pt);//��ȡ���λ��
                if ((pt.x > ImGui::GetWindowPos().x) && (pt.y > ImGui::GetWindowPos().y) && (pt.x < (ImGui::GetWindowPos().x + ImGui::GetWindowWidth())) && (pt.y < (ImGui::GetWindowPos().y + ImGui::GetWindowHeight()))) {
                    SystemTray_interface_time = clock();
                }
                else if ((clock() - SystemTray_interface_time) > Residence_Time) {
                    SystemTray_interface = false;
                }

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
    case WM_IAWENTRAY:
        /*
        MK_LBUTTON�������������¡�
        MK_MBUTTON������м������¡�
        MK_RBUTTON������Ҽ������¡�
        */
        switch (lParam)
        {
        case WM_RBUTTONDOWN://�Ҽ�ͼ��
        {
            SystemTray_interface_time = clock();
            if (SystemTray_interface) {
                SystemTray_interface = false;
                SystemTray_init = false;
            }
            else {
                SystemTray_interface = true;
                SystemTray_init = true;
            }
        }
        break;
        case WM_LBUTTONUP://���ͼ��
            break;
        }
        break;









    case WM_KEYDOWN://�Դ�Сд������
        if (wParam == 'F') {//���F�Ƿ񱻰���
            //SetWindowText(hWnd, "off FFFF");//����⵽F�������Ǹı����
        }
        break;


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










//��ü����������
std::string ClipboardTochar() {
    OpenClipboard(NULL);//�򿪼�����
    hmem = GetClipboardData(CF_TEXT);//��ȡ���а����ݿ�
    std::string CharS = (char*)GlobalLock(hmem);//��ȡ���ݿ�ĵ�ַ
    CloseClipboard();//�رռ�����
    return CharS;
}



//�����ݸ��Ƶ�������
void CopyToClipboard(std::string str) {
    str = Utf8ToUnicode(str.c_str());// utf8 ת�� Unicode Ҫ��Ȼճ������������
    OpenClipboard(NULL);
    if (!EmptyClipboard())       // ��ռ��а壬д��֮ǰ����������ռ��а�
    {
        puts("��ռ��а�ʧ��\n");
        CloseClipboard();
    }

    HGLOBAL hMemory;
    if ((hMemory = GlobalAlloc(GMEM_MOVEABLE, strlen(str.c_str()) + 1)) == NULL)    // �Լ��а�����ڴ�
    {
        puts("�ڴ渳ֵ����!!!\n");
        CloseClipboard();
    }

    LPTSTR lpMemory;
    if ((lpMemory = (LPTSTR)GlobalLock(hMemory)) == NULL)             // ���ڴ���������
    {
        puts("�����ڴ����!!!\n");
        CloseClipboard();
    }

    memcpy_s(lpMemory, strlen(str.c_str()) + 1, str.c_str(), strlen(str.c_str()) + 1);   // �����ݸ��ƽ����ڴ�����

    GlobalUnlock(hMemory);                   // ����ڴ�����

    if (SetClipboardData(CF_TEXT, hMemory) == NULL)
    {
        puts("���ü��а�����ʧ��!!!\n");
        CloseClipboard();
    }


    CloseClipboard();//�رռ�����
}


//IMGUI ��ʼ��
ImGuiIO& IMGUI_init() {
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

    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);



    //ImGui �������
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

    return io;
}

//����ͼƬ
ID3D11ShaderResourceView* DX11LoadTextureImageFromFile(LPCSTR lpszFilePath)
{
    ID3D11Texture2D* pTexture2D = NULL;
    D3D11_TEXTURE2D_DESC dec;

    HRESULT result;
    D3DX11_IMAGE_LOAD_INFO loadInfo;
    ZeroMemory(&loadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
    loadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    loadInfo.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    loadInfo.MipLevels = D3DX11_DEFAULT; //��ʱ���������mipmaps�㡣 
    loadInfo.MipFilter = D3DX11_FILTER_LINEAR;
    D3DX11CreateTextureFromFile(g_pd3dDevice, lpszFilePath, &loadInfo, NULL, (ID3D11Resource**)(&pTexture2D), &result);
    pTexture2D->GetDesc(&dec);

    if (result != S_OK)
    {
        return NULL;
    }

    ID3D11ShaderResourceView* pFontTextureView = NULL;

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = dec.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    g_pd3dDevice->CreateShaderResourceView(pTexture2D, &srvDesc, &pFontTextureView);

    pTexture2D->Release();
    pTexture2D = NULL;

    return pFontTextureView;
}




//��ͼ&���棨ȫ����
void screen(LPCSTR fileName)
{
    HWND window = GetDesktopWindow();
    HDC _dc = GetWindowDC(window);//��ĻDC
    HDC dc = CreateCompatibleDC(0);//�ڴ�DC

    RECT re;
    GetWindowRect(window, &re);
    int w = re.right,
        h = re.bottom;
    void* buf = new char[w * h * 4];
    void* buff = buf;//���ݱ��������ڴ�ĵ�ַ����Ϊ���� buf ����ڴ��ַ�ᶪʧ�����ڴ�й¶��

    HBITMAP bm = CreateCompatibleBitmap(_dc, w, h);//��������Ļ���ݵ�bitmap
    SelectObject(dc, bm);//��memBitmapѡ���ڴ�DC    
    StretchBlt(dc, 0, 0, w, h, _dc, 0, 0, w, h, SRCCOPY);//������Ļͼ���ڴ�DC

    void* f = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);

    GetObject(bm, 84, buf);

    tagBITMAPINFO bi;
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = h;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = 0;
    bi.bmiHeader.biSizeImage = 0;

    void* dcf = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &buf, NULL, NULL);
    GetDIBits(dc, bm, 0, h, buf, &bi, DIB_RGB_COLORS);

    BITMAPFILEHEADER bif;
    bif.bfType = MAKEWORD('B', 'M');
    bif.bfSize = w * h * 4 + 54;
    bif.bfOffBits = 54;

    BITMAPINFOHEADER bii;
    bii.biSize = 40;
    bii.biWidth = w;
    bii.biHeight = h;
    bii.biPlanes = 1;
    bii.biBitCount = 32;
    bii.biCompression = 0;
    bii.biSizeImage = w * h * 4;

    DWORD r;
    WriteFile(f, &bif, sizeof(bif), &r, NULL);
    WriteFile(f, &bii, sizeof(bii), &r, NULL);
    WriteFile(f, buf, w * h * 4, &r, NULL);



    DeleteObject(dcf);
    DeleteObject(bm);
    delete[] buff;
    CloseHandle(f);
    DeleteDC(_dc);
    DeleteDC(dc);
}

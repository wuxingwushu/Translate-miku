#include "base.h"
#include <windows.h>//WIN API
#include "imgui/GUI.h"//��ʾ����
#include "Function/tesseract.h"//ͼƬʶ������
#include "Function/Translate.h"//��������
#include "ini.h"//�������
using namespace inih;//���� ini ��ȡ
//#define	PI					3.14






/*
 ����������   ���������Щ������Щ������Щ������� ���������Щ������Щ������Щ������� ���������Щ������Щ������Щ������� ���������Щ������Щ�������
 ��Esc   ��   ��  F1  ��  F2  ��  F3  ��  F4  �� ��  F5  ��  F6  ��  F7  ��  F8  �� ��  F9  ��  F10 ��  F11 ��  F12 �� ��  P/S ��  S L ��  P/B ��           ����    ����    ����
 ����������   ���������ة������ة������ة������� ���������ة������ة������ة������� ���������ة������ة������ة������� ���������ة������ة�������           ����    ����    ����
 ���������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ��������������� ���������Щ������Щ������� ���������Щ������Щ������Щ�������
 ��  ~ ` �� ! 1  �� @ 2  ��  # 3 �� $ 4  �� % 5  �� ^ 6  �� & 7  �� * 8  �� ( 9  ��  ) 0 �� _ -  �� + =  ��     BacSp    �� �� Ins  �� Hom  ��  PUp �� �� N L  ��   /  ��   *  ��   -  ��
 ���������ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ����������� ���������੤�����੤������ ���������੤�����੤�����੤������
 ��   Tab    ��   Q  ��   W  ��   E  ��   R  ��   T  ��   Y  ��   U  ��   I  ��   O  ��   P  ��  { [ ��  } ] ��   | \    �� ��  Del ��  End ��  PDn �� ��   7  ��   8  ��   9  ��      ��
 �������������ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ة����������� ���������ة������ة������� ���������੤�����੤������   +  ��
 ��    Caps    ��   A  ��   S  ��   D  ��   F  ��   G  ��   H  ��   J  ��   K  ��   L  ��  : ; ��  " ' ��      Enter     ��                            ��   4  ��   5  ��   6  ��      ��
 ���������������ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة�����������������         ����������         ���������੤�����੤�����੤������
 ��     Shift      ��   Z  ��   X  ��   C  ��   V  ��   B  ��   N  ��   M  ��  < , ��  > . ��  ? / ��        Shift       ��         ��  ��  ��         ��   1  ��   2  ��   3  ��      ��
 �������������Щ����ة��Щ��ة����Щة������ة������ة������ة������ة������ة����Щة������੤�����ةЩ��������Щ��������� ���������੤�����੤������ ���������ة������੤������   E����
 ��   Ctrl   ��        ��   Alt  ��                    Space                     ��  Alt   ��        ��        ��   Ctrl �� ��  ��  ��  ��  ��  ��  �� ��   0          ��  .   ����������
 �������������ة��������ة��������ة����������������������������������������������ة��������ة��������ة��������ة��������� ���������ة������ة������� �����������������ة������ة�������
*/



//����API �� ID �� Key
std::string Baidu_ID;
std::string Baidu_Key;




//����
static int  screenshot_key_1;//��ͼ���� screenshot_key_1 && screenshot_key_2
static char screenshot_key_2;

static int  choice_key_1;//ѡ�񰴼� choice_key_1 && choice_key_2
static char choice_key_2;

static int  replace_key_1;//�滻���� replace_key_1 && replace_key_2
static char replace_key_2;

//�������
static int Residence_Time;//����뿪����ʱ����ʾʱ��

char* English = "auto";
char* Chinese = "zh";
char* ChineseReplace = "en";

void IniDataInit() {
/*
INIReader r{ "./Data.ini" };
r.Get<int>("data", "int1");//��ȡ��������
r.GetVector<int>("data", "intixx")//��ȡ��������
std::cout <<   << std::endl;
*/

	INIReader iniData{ "./Data.ini" };

	Baidu_ID = iniData.Get<std::string>("API", "Baidu_ID");
	Baidu_Key = iniData.Get<std::string>("API", "Baidu_Key");

	screenshot_key_1 = iniData.Get<int>("Key", "screenshot_key_1");
	screenshot_key_2 = iniData.Get<char>("Key", "screenshot_key_2");
	choice_key_1 = iniData.Get<int>("Key", "choice_key_1");
	choice_key_2 = iniData.Get<char>("Key", "choice_key_2");
	replace_key_1 = iniData.Get<int>("Key", "replace_key_1");
	replace_key_2 = iniData.Get<char>("Key", "replace_key_2");

	Residence_Time = int(iniData.Get<float>("Set", "Residence_Time") * 1000);
}
static HGLOBAL hmem;














//�������
static bool translate_interface = false;//���濪��
static bool translate_click = false;//�ж�����һ�ε��
static clock_t translate_interface_time;//����뿪�����ʱ���
std::string translate_English;
std::string translate_Chinese;



//��ͼ����
static bool Screenshot_interface = false;//���濪��
static bool Screenshot_click = false;//�ж�����һ�ε��
static bool Screenshot_init = false;//�Ƿ��ǵ�һ�δ򿪽���
static POINT MousePosition_1 = { 0,0 };//��һ��������λ��
static POINT MousePosition_2 = { 0,0 };//����ɿ�λ��
static ImTextureID image_ID;//IMGUIͼƬID
static ID3D11ShaderResourceView* m_pImageTextureView1;//DX11��ͼƬID

//ϵͳ���̲˵�
static bool SystemTray_interface = false;//���濪��
static bool SystemTray_init = false;//�Ƿ��ǵ�һ�δ򿪽���
static bool SystemTray_mode = false;//���뷽ʽ 0���е�   1���ٶ�
static clock_t SystemTray_interface_time;//����뿪�����ʱ���


//IMGUI
static ImVec4 clear_color;
//IMGUI ��ʼ��
ImGuiIO& IMGUI_init();


static int windows_Width{ GetSystemMetrics(SM_CXSCREEN) };//��ȡ��ʾ���Ŀ�
static int windows_Heigth{ GetSystemMetrics(SM_CYSCREEN) };//��ȡ��ʾ���ĸ�



//����ͼƬ
ID3D11ShaderResourceView* DX11LoadTextureImageFromFile(LPCSTR lpszFilePath);
//��ͼ&���棨ȫ����
void screen(LPCSTR fileName);



static HWND hwnd = NULL;

HINSTANCE g_hInst = NULL;

#define WM_IAWENTRAY    WM_USER+2  //ϵͳ���̵��Զ�����Ϣ 

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);















//string ת wstring
std::string ws2s(const std::wstring& ws)
{
    size_t i;
    std::string curLocale = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "chs");
    const wchar_t* _source = ws.c_str();
    size_t _dsize = 2 * ws.size() + 1;
    char* _dest = new char[_dsize];
    memset(_dest, 0x0, _dsize);
    wcstombs_s(&i, _dest, _dsize, _source, _dsize);
    std::string result = _dest;
    delete[] _dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

//wstring ת string
std::wstring s2ws(const std::string& s)
{
    size_t i;
    std::string curLocale = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "chs");
    const char* _source = s.c_str();
    size_t _dsize = s.size() + 1;
    wchar_t* _dest = new wchar_t[_dsize];
    wmemset(_dest, 0x0, _dsize);
    mbstowcs_s(&i, _dest, _dsize, _source, _dsize);
    std::wstring result = _dest;
    delete[] _dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

//Unicode ת�� utf8
std::string  UnicodeToUtf8(const std::string& Unicode)
{
    std::wstring wstr = s2ws(Unicode);

    int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    char* pAssii = (char*)malloc(sizeof(char) * ansiiLen);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
    std::string ret_str = pAssii;
    free(pAssii);
    return ret_str;
}



//utf8 ת�� Unicode
char* Utf8ToUnicode(const char* szU8)
{
    int wcsLen = MultiByteToWideChar(CP_UTF8, NULL, szU8, (int)strlen(szU8), NULL, 0);
    wchar_t* wszString = new wchar_t[wcsLen + 1];
    MultiByteToWideChar(CP_UTF8, NULL, szU8, (int)strlen(szU8), wszString, wcsLen);
    wszString[wcsLen] = '\0';
    int len = WideCharToMultiByte(CP_ACP, 0, wszString, (int)wcslen(wszString), NULL, 0, NULL, NULL);
    char* c = new char[len + 1];
    WideCharToMultiByte(CP_ACP, 0, wszString, (int)wcslen(wszString), c, len, NULL, NULL);
    c[len] = '\0';
    delete[] wszString;
    return c;
}
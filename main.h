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

static int  replace_key_1;//��ͼ���� replace_key_1 && replace_key_2
static char replace_key_2;

//�������
static int Residence_Time;//����뿪����ʱ����ʾʱ��

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
	replace_key_2 = iniData.Get<char>("Key", "screenshot_key_2");

	Residence_Time = int(iniData.Get<float>("Set", "Residence_Time") * 1000);
}















//�������
static bool translate_interface = false;//���濪��
static bool translate_click = false;//�ж�����һ�ε��
static clock_t translate_interface_time;//����뿪�����ʱ���
char* translate_English = "adwafiawbfiuawbfiuawbfiubawifbiauwbifabwifbaiwfbawifbia";
std::string translate_Chinese = u8"���ʴ󰲷־��Ǹ������շ���󼪰·���Ŷ��Ŷ��Ů���i�����i������";



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


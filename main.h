#include "base.h"
#include "Tool.h"//���ݸ�ʽת��
#include "imgui/GUI.h"//��ʾ����
#include "Function/tesseract.h"//ͼƬʶ������
#include "Function/Translate.h"//��������
#include "ini.h"//�������
using namespace inih;//���� ini ��ȡ
//#define	PI					3.14


//ģ�� ת �ַ���
template<typename T>std::string toString(const T& t);
std::string ColorArraytoString(int* color);
void GetColor(std::vector<int> colordata, int* color, float* set_color);
void PreservationSetColor(float* setcolor, int* color);
void IniDataPreservation();



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



static LPTSTR lpPath = new char[MAX_PATH];

//****************************************************************************************************
static char* set_English = new char[5];
static char* set_Chinese = new char[5];
static char* set_ChineseReplace = new char[5];

static char* set_Baidu_ID = new char[30];
static char* set_Baidu_Key = new char[30];
static char* set_TesseractModel = new char[10];
static int set_Residence_Time;

static float set_ButtonColor[4];
static float set_ButtonHoveredColor[4];
static float set_ButtonActiveColor[4];

const char* items[] = { "Shift", "Ctrl", "Alt" };
//****************************************************************************************************

//����Ŀ����������
std::string English;//���Ŀ������
std::string Chinese;//����Ŀ������
std::string ChineseReplace;//�滻��Ŀ������

//����API �� ID �� Key
std::string Baidu_ID;
std::string Baidu_Key;

//����
static int  screenshot_key_1;//��ͼ���� screenshot_key_1 && screenshot_key_2
static char* screenshot_key_2 = new char[1];

//static int  choice_key_1;//ѡ�񰴼� choice_key_1 && choice_key_2
static char* choice_key_2 = new char[1];

//static int  replace_key_1;//�滻���� replace_key_1 && replace_key_2
static char* replace_key_2 = new char[1];

//�������
static int Residence_Time;//����뿪����ʱ����ʾʱ��
static int WindowWidth;//������� ��� ��ʼ��С
static float FontSize;//�����С
static float ButtonRounding;//����Բ���
std::string TesseractModel;//Tesseract-ORC ģ��
static int ButtonColor[4];//������ɫ
static int ButtonHoveredColor[4];//�����ͣ��ɫ
static int ButtonActiveColor[4];//�������ɫ


void IniDataInit() {
/*
INIReader r{ "./Data.ini" };
r.Get<int>("data", "int1");//��ȡ��������
r.GetVector<int>("data", "intixx")//��ȡ��������
std::cout <<   << std::endl;
*/
	strcpy(lpPath, "./Data.ini");
	INIReader iniData{ lpPath };

	English = iniData.Get<std::string>("language", "English");
	strcpy(set_English, English.c_str());
	Chinese = iniData.Get<std::string>("language", "Chinese");
	strcpy(set_Chinese, Chinese.c_str());
	ChineseReplace = iniData.Get<std::string>("language", "ChineseReplace");
	strcpy(set_ChineseReplace, ChineseReplace.c_str());

	Baidu_ID = iniData.Get<std::string>("API", "Baidu_ID");
	strcpy(set_Baidu_ID, Baidu_ID.c_str());
	Baidu_Key = iniData.Get<std::string>("API", "Baidu_Key");
	strcpy(set_Baidu_Key, Baidu_Key.c_str());

	screenshot_key_1 = iniData.Get<int>("Key", "screenshot_key_1");
	screenshot_key_2[0] = iniData.Get<char>("Key", "screenshot_key_2");
	//choice_key_1 = iniData.Get<int>("Key", "choice_key_1");
	choice_key_2[0] = iniData.Get<char>("Key", "choice_key_2");
	//replace_key_1 = iniData.Get<int>("Key", "replace_key_1");
	replace_key_2[0] = iniData.Get<char>("Key", "replace_key_2");

	Residence_Time = int(iniData.Get<float>("Set", "Residence_Time") * 1000);
	WindowWidth = iniData.Get<int>("Set", "WindowWidth");
	FontSize = iniData.Get<float>("Set", "FontSize");
	ButtonRounding = iniData.Get<float>("Set", "ButtonRounding");
	TesseractModel = iniData.Get<std::string>("Set", "TesseractModel");
	strcpy(set_TesseractModel, TesseractModel.c_str());
	GetColor(iniData.GetVector<int>("Set", "ButtonColor"), ButtonColor, set_ButtonColor);
	GetColor(iniData.GetVector<int>("Set", "ButtonHoveredColor"), ButtonHoveredColor, set_ButtonHoveredColor);
	GetColor(iniData.GetVector<int>("Set", "ButtonActiveColor"), ButtonActiveColor, set_ButtonActiveColor);


	//�޸���ֵ
	//WritePrivateProfileString("Set", "Residence_Time", ColorArraytoString(pxd).c_str(), lpPath);
}

void IniDataPreservation() {
	WritePrivateProfileString("language", "English", set_English, lpPath);
	WritePrivateProfileString("language", "Chinese", set_Chinese, lpPath);
	WritePrivateProfileString("language", "ChineseReplace", set_ChineseReplace, lpPath);
	WritePrivateProfileString("API", "Baidu_ID", set_Baidu_ID, lpPath);
	WritePrivateProfileString("API", "Baidu_Key", set_Baidu_Key, lpPath);

	WritePrivateProfileString("Key", "screenshot_key_1", toString(screenshot_key_1).c_str(), lpPath);
	WritePrivateProfileString("Key", "screenshot_key_2", toString(screenshot_key_2[0]).c_str(), lpPath);
	WritePrivateProfileString("Key", "choice_key_2", toString(choice_key_2[0]).c_str(), lpPath);
	WritePrivateProfileString("Key", "replace_key_2", toString(replace_key_2[0]).c_str(), lpPath);

	WritePrivateProfileString("Set", "Residence_Time", toString(set_Residence_Time).c_str(), lpPath);
	WritePrivateProfileString("Set", "WindowWidth", toString(WindowWidth).c_str(), lpPath);
	WritePrivateProfileString("Set", "FontSize", toString(FontSize).c_str(), lpPath);
	WritePrivateProfileString("Set", "ButtonRounding", toString(ButtonRounding).c_str(), lpPath);
	WritePrivateProfileString("Set", "TesseractModel", set_TesseractModel, lpPath);
	WritePrivateProfileString("Set", "ButtonColor", ColorArraytoString(ButtonColor).c_str(), lpPath);
	WritePrivateProfileString("Set", "ButtonHoveredColor", ColorArraytoString(ButtonHoveredColor).c_str(), lpPath);
	WritePrivateProfileString("Set", "ButtonActiveColor", ColorArraytoString(ButtonActiveColor).c_str(), lpPath);
}


static HGLOBAL hmem;











//����
static bool Set_interface = false;
static bool Set_init = false;//�Ƿ��ǵ�һ�δ򿪽���

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
static bool Screenshot_translate = false;//�Ƿ��������ݣ���ֹ��ͼBUG
static int Screenshot_translate_shu = 2;
static POINT MousePosition_1 = { 0,0 };//��һ��������λ��
static POINT MousePosition_2 = { 0,0 };//����ɿ�λ��
static ImTextureID image_ID;//IMGUIͼƬID
static ID3D11ShaderResourceView* m_pImageTextureView1;//DX11��ͼƬID
static l_int32 x, y, w, h;


//ϵͳ���̲˵�
static bool SystemTray_interface = false;//���濪��
static bool SystemTray_init = false;//�Ƿ��ǵ�һ�δ򿪽���
static bool SystemTray_mode = false;//���뷽ʽ 0���е�   1���ٶ�
static clock_t SystemTray_interface_time;//����뿪�����ʱ���


//IMGUI
static ImVec4 clear_color;



static int windows_Width{ GetSystemMetrics(SM_CXSCREEN) };//��ȡ��ʾ���Ŀ�
static int windows_Heigth{ GetSystemMetrics(SM_CYSCREEN) };//��ȡ��ʾ���ĸ�







static HWND hwnd = NULL;

HINSTANCE g_hInst = NULL;

#define WM_IAWENTRAY    WM_USER+2  //ϵͳ���̵��Զ�����Ϣ 

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;



//IMGUI ��ʼ��
ImGuiIO& IMGUI_init();
//��ü����������
std::string ClipboardTochar();
//�����ݸ��Ƶ�������
void CopyToClipboard(std::string str);
//����ͼƬ
ID3D11ShaderResourceView* DX11LoadTextureImageFromFile(LPCSTR lpszFilePath);
//��ͼ&���棨ȫ����
void screen(LPCSTR fileName);

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


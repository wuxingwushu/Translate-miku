#pragma once//��ֹ���α���
#include <time.h>
#include <string.h>
#include <iostream>
#include <tchar.h>
#include <sstream>
#include <windows.h>//WIN API
//#include "vld.h"//�ڴ�й¶���� ��Debug ʱ�Ż�������


static clock_t shijian;//���Ժ�ʱ
/*shijian = clock();
printf("%d\n", shijian - clock());
*/

/*
std::cout <<   << std::endl;
 

GetKeyState������
https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
*/


/*
#include <iostream>
#include <string>
#include <curl/curl.h>

// �����е����� API �ĵ�ַ
const std::string API_URL = "http://fanyi.youdao.com/translate?&doctype=json&type=ZH_CN2EN";

// �����е����� API ��˽�� key����Ҫ���е������������
const std::string PRIVATE_KEY = "your_private_key";

// �����е����� API ��˽�� key����Ҫ���е������������
const std::string APP_KEY = "your_app_key";

// �����е����� API ���������ԣ������� "ZH_CN" �� "EN"
const std::string INPUT_LANG = "ZH_CN";

// �����е����� API ��������ԣ������� "ZH_CN" �� "EN"
const std::string OUTPUT_LANG = "EN";

// ����һ�����������ڽ��ַ���ת��Ϊ URL ����
std::string url_encode(const std::string& str) {
  // ��ʼ�� curl ��
  CURL *curl = curl_easy_init();
  if (!curl) {
    std::cerr << "Error: failed to initialize curl" << std::endl;
    return "";
  }

  // ���� curl ���ѡ��
  curl_easy_setopt(curl, CURLOPT_URL, API_URL.c_str());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, ("q=" + str).c_str());
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, -1L);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);

  // ���� HTTP ͷ��
  struct curl_s

*/
#pragma once//��ֹ���α���
#include "base.h"



//string ת wstring
std::string ws2s(const std::wstring& ws);

//wstring ת string
std::wstring s2ws(const std::string& s);

//Unicode ת�� utf8
std::string  UnicodeToUtf8(const std::string& Unicode);

//utf8 ת�� Unicode
std::string Utf8ToUnicode(const char* szU8);

#pragma once//��ֹ���α���
#include "../base.h"
#include <json.h>
#include <curl/curl.h>


bool getUrl(char* filename);
bool postUrl(char* filename);

//http POST����  
CURLcode curl_post_req(const std::string& url, const std::string& postParams, std::string& response);
size_t req_reply(void* ptr, size_t size, size_t nmemb, void* stream);
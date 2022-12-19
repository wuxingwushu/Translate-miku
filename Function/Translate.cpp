#include "Translate.h"



size_t req_reply(void* ptr, size_t size, size_t nmemb, void* stream)
{
    //��ע�͵�������Դ�ӡ��������cookie����Ϣ
    //cout << "----->reply" << endl;
    std::string* str = (std::string*)stream;
    //cout << *str << endl;
    (*str).append((char*)ptr, size * nmemb);
    return size * nmemb;
}
//http POST����  
CURLcode curl_post_req(const std::string& url, const std::string& postParams, std::string& response)
{
    // curl��ʼ��  
    CURL* curl = curl_easy_init();
    // curl����ֵ 
    CURLcode res;
    if (curl)
    {
        // set params
        //����curl������ͷ
        struct curl_slist* header_list = NULL;
        header_list = curl_slist_append(header_list, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko");
        header_list = curl_slist_append(header_list, "Content-Type:application/x-www-form-urlencoded; charset=UTF-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

        //��������Ӧͷ����0�������� 1�������
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);

        //��������Ϊpost����
        curl_easy_setopt(curl, CURLOPT_POST, 1);

        //���������URL��ַ
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        //����post����Ĳ���
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postParams.c_str());

        //����ssl��֤
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

        //CURLOPT_VERBOSE��ֵΪ1ʱ������ʾ��ϸ�ĵ�����Ϣ
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);

        //�������ݽ��պ�д�뺯��
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&response);

        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

        //���ó�ʱʱ��
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 6);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);

        // ����post����
        res = curl_easy_perform(curl);
    }
    //�ͷ�curl 
    curl_easy_cleanup(curl);
    return res;
}

bool getUrl(char* filename)
{
    CURL* curl;
    CURLcode res;
    FILE* fp;
    if ((fp = fopen(filename, "w")) == NULL)  // ���ؽ�����ļ��洢
        return false;
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Accept: Agent-007");
    curl = curl_easy_init();    // ��ʼ��
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);   // ��Э��ͷ
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);         //�����ص�httpͷ�����fpָ����ļ�
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, fp);        //�����ص�html�������������fpָ����ļ�
        res = curl_easy_perform(curl);   // ִ��
        if (res != 0) {

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
        fclose(fp);
        return true;
    }
}

bool postUrl(char* filename)
{
    CURL* curl;
    CURLcode res;
    FILE* fp;
    if ((fp = fopen(filename, "w")) == NULL)
        return false;
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt");     // ָ��cookie�ļ�
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "&logintype=uid&u=xieyan&psw=xxx86");    // ָ��post����        
        curl_easy_setopt(curl, CURLOPT_URL, "http://mail.sina.com.cn/cgi-bin/login.cgi");   // ָ��url
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    return true;
}
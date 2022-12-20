#include "Translate.h"





unsigned char ToHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}

unsigned char FromHex(unsigned char x)
{
    unsigned char y;
    if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
    else if (x >= '0' && x <= '9') y = x - '0';
    else assert(0);
    return y;
}



std::string UrlEncode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)str[i]) ||
            (str[i] == '-') ||
            (str[i] == '_') ||
            (str[i] == '.') ||
            (str[i] == '~'))
            strTemp += str[i];
        else if (str[i] == ' ')
            strTemp += "+";
        else
        {
            strTemp += '%';
            strTemp += ToHex((unsigned char)str[i] >> 4);
            strTemp += ToHex((unsigned char)str[i] % 16);
        }
    }
    return strTemp;
}


std::string UrlDecode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] == '+') strTemp += ' ';
        else if (str[i] == '%')
        {
            assert(i + 2 < length);
            unsigned char high = FromHex((unsigned char)str[++i]);
            unsigned char low = FromHex((unsigned char)str[++i]);
            strTemp += high * 16 + low;
        }
        else strTemp += str[i];
    }
    return strTemp;
}



//�� ��ϸ��ϸ�鿴�ٶȷ���API�ĵ���https ://fanyi-api.baidu.com/product/113 ��
std::string Translate_Baidu(const char* appid, const char* secret_key, std::string English, char* from, char* to) {
    //appid             //replace myAppid with your own appid
    //secret_key        //replace mySecretKey with your own mySecretKey
    //English           //replace apple with your own text to be translate, ensure that the input text is encoded with UTF-8!
    //from;             //replace en with your own language type of input text
    //to;               //replace zh with your own language type of output text

    //�����ڵ���ȡ������
    if (strlen(English.c_str()) <= 1) {
        return std::string(u8"�����ڵ���");
    }



    CURL* curl;
    CURLcode res;
    FILE* fp;
    fp = fopen("TemporaryData", "w+");

    curl = curl_easy_init();
    if (curl) {
        char myurl[1000] = "http://api.fanyi.baidu.com/api/trans/vip/translate?";
        
        char salt[60];
        int a = rand();
        sprintf(salt, "%d", a);
        char sign[120] = "";
        strcat(sign, appid);
        strcat(sign, English.c_str());//��ȡ����MD5ʱ English ��Ҫ���� Url_Encode ����  �� ��ϸ��ϸ�鿴�ٶȷ���API�ĵ���https://fanyi-api.baidu.com/product/113 ��
        strcat(sign, salt);
        strcat(sign, secret_key);
        unsigned char md[16];
        int i;
        char tmp[3] = { '\0' }, buf[33] = { '\0' };
        MD5((unsigned char*)sign, strlen(sign), md);
        for (i = 0; i < 16; i++) {
            sprintf(tmp, "%2.2x", md[i]);
            strcat(buf, tmp);
        }
        //printf("%s\n", buf);
        strcat(myurl, "appid=");
        strcat(myurl, appid);
        strcat(myurl, "&q=");
        strcat(myurl, UrlEncode(English).c_str());//������ҳ����ʱ English ��Ҫ���� Url_Encode ����   �� ��ϸ��ϸ�鿴�ٶȷ���API�ĵ���https://fanyi-api.baidu.com/product/113 ��
        strcat(myurl, "&from=");
        strcat(myurl, from);
        strcat(myurl, "&to=");
        strcat(myurl, to);
        strcat(myurl, "&salt=");
        strcat(myurl, salt);
        strcat(myurl, "&sign=");
        strcat(myurl, buf);
        //printf("%s\n", myurl);
        //���÷��ʵĵ�ַ
        curl_easy_setopt(curl, CURLOPT_URL, &myurl);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
        fseek(fp, 0, SEEK_END);//���ļ��ڲ���ָ��ָ���ļ�ĩβ
        long lsize = ftell(fp);//��ȡ�ļ����ȣ����õ��ļ�λ��ָ�뵱ǰλ��������ļ��׵�ƫ���ֽ�����
        fseek(fp, NULL, SEEK_SET);//���ļ��ڲ���ָ������ָ��һ�����Ŀ�ͷ
        char* kaox = new char[lsize];//�����ڴ�ռ䣬lsize*sizeof(char)��Ϊ�˸��Ͻ���16λ��charռһ���ַ������������Ͽ��ܱ仯
        fread(kaox, 1, lsize, fp);//��pfile�����ݶ���preadָ���ڴ���
        fclose(fp);


        Json::Value value;
        Json::Reader reader;
        if (!reader.parse(kaox, value)) {
            printf("parse json error!");
            delete[] kaox;
            return 0;
        }
        std::string Chinese = value["trans_result"][0]["dst"].asString();
        delete[] kaox;

        return Chinese;
    }
    return 0;
}
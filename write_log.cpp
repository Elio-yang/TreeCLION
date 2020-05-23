
#include <cstring>
#include <cstdarg>
#include <ctime>
#include <direct.h>
#include <cstdlib>
#include <cstdio>


const unsigned long long log_file_max_size = 5 * 1024 * 1024;
const char * log_file_name = "\\log.txt";

void WriteLog(const char *szFile, const int nLine, const char *szFunc, const char *szFmt, ...) {
    FILE *fp = nullptr;
    size_t stSize = 0;
    int nStrLen = 0;
    char szPath[260] = {0};
    va_list va;
    va_start(va, szFmt);
    struct tm *tm_time = nullptr;
    time_t t_time = 0;
    t_time = time(nullptr);
    char *pszWrite = (char *) malloc(sizeof(char) * 10240);
    if (pszWrite == nullptr) {
        return;
    }

    // clean
    memset(pszWrite, 0, sizeof(char) * 10240);

    // get time
    tm_time = localtime(&t_time);
    nStrLen += strftime(pszWrite, 32, "[%Y.%m.%d-%H:%M:%S]", tm_time);

    // file
    szFile = strrchr(szFile, '\\') + 1;
    nStrLen += sprintf(pszWrite + nStrLen, "[File:%s]", szFile);

    // line
    nStrLen += sprintf(pszWrite + nStrLen, "[Line:%d]", nLine);

    // function
    nStrLen += sprintf(pszWrite + nStrLen, "[Function:%s] ", szFunc);

    // fmt
    nStrLen += vsprintf(pszWrite + nStrLen, szFmt, va);

    // enter
    nStrLen += sprintf(pszWrite + nStrLen, "\n");

    // path
    _getcwd(szPath, 260);
    strcat(szPath, log_file_name);

    // size check
    fp = fopen(szPath, "r");
    if (fp != nullptr) {// file exists
        fseek(fp, 0L, SEEK_END);
        stSize = ftell(fp);
        fclose(fp);

        if (stSize > log_file_max_size) {
            remove(szPath);
        }
    }

    // write
    fp = fopen(szPath, "ab+");
    if (fp == nullptr) {
        return;
    }
    fwrite(pszWrite, nStrLen, 1, fp);
    fclose(fp);

    // free
    if (pszWrite != nullptr)
    {
        free(pszWrite);
        pszWrite = nullptr;
    }
}

//int main(int argc, char const *argv[]) {
//    // example
//    WriteLog(__FILE__, __LINE__, __FUNCTION__, "err : %s", "hello, world");
//    return 0;
//}
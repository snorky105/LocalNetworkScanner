#include <iostream>
#include <windows.h>
#include <lm.h>
#include <lm.h>

#pragma comment(lib, "Netapi32.lib")

int main() {
    DWORD dwLevel = 101;
    LPUSER_INFO_101 pBuf = NULL;
    DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
    DWORD dwEntriesRead = 0;
    DWORD dwTotalEntries = 0;
    DWORD dwResumeHandle = 0;

   
    NET_API_STATUS nStatus = NetUserEnum(
        NULL,       
        dwLevel,
        FILTER_NORMAL_ACCOUNT,  
        (LPBYTE*)&pBuf,
        dwPrefMaxLen,
        &dwEntriesRead,
        &dwTotalEntries,
        &dwResumeHandle
    );

    if (nStatus == NERR_Success) {
        for (DWORD i = 0; i < dwEntriesRead; i++) {
            std::wcout << pBuf[i].usri101_name << std::endl;
        }
    } else {
        std::cerr << "Error: " << nStatus << std::endl;
    }

    
    if (pBuf != NULL) {
        NetApiBufferFree(pBuf);
    }

    return 0;
}

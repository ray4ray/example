#include <iostream>  
#include <windows.h>  
  
using namespace std;  
HANDLE hMutex;  
  
DWORD WINAPI Fun(LPVOID lpParamter)  
{  
    while(1)  
    {  
        WaitForSingleObject(hMutex, INFINITE);  
        cout<<"A"<<endl;   
        Sleep(1000);  
        ReleaseMutex(hMutex);  
    }  
    return 0;  
}  
  
DWORD WINAPI Fun1(LPVOID lpParamter)  
{  
    while(1)   
    {   
         WaitForSingleObject(hMutex, INFINITE);  
         cout<<"B"<<endl;   
         Sleep(1000);  
         ReleaseMutex(hMutex);  
    }  
    return 0;  
}  
  
int main()  
{  
    HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);  
    hMutex = CreateMutex(NULL, FALSE, (LPWSTR)"screen");  
    CloseHandle(hThread);  
  
    HANDLE hThread1 = CreateThread(NULL, 0, Fun1, NULL, 0, NULL);  
    CloseHandle(hThread1);  
      
    while(1);  
    return 0;  
}  
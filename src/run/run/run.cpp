#include <windows.h>  
#include <stdio.h>  
#include <string>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    // 初始化STARTUPINFO结构体  
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOW; // 可以指定新窗口的显示方式  

    std::string name = "SecondDownloader.exe autorun";
    // 创建新进程  
    
    if (!CreateProcessA(NULL,   // 使用命令行参数本身来定位可执行文件  
        (LPSTR)name.c_str(), // 可执行文件路径  
        NULL,           // 进程安全属性  
        NULL,           // 线程安全属性  
        FALSE,          // 句柄继承选项  
        0,              // 创建标志  
        NULL,           // 使用父进程的环境块  
        NULL,           // 使用父进程的起始目录   
        &si,            // 指向STARTUPINFO结构  
        &pi)           // 指向PROCESS_INFORMATION结构  
        ) {
        
        return -1;
    }
    return 0;

}



#if defined( Q_OS_WIN )
#include <windows.h>
#endif

/* example of creating independent (detached) process on Windows */

int main()
{
#if defined( Q_OS_WIN )
    LPCSTR lpApplicationName = R"(Application.exe)";                  // Name of application (or full path)
    LPSTR lpCommandLine = NULL;                                       // Entity of commandline
    DWORD dwCreationFlags = DETACHED_PROCESS | CREATE_NO_WINDOW;      // Flags
    STARTUPINFO si;                                                   // Descriptor for initialization process
    PROCESS_INFORMATION pi;                                           // Descriptor of process

    ZeroMemory( &si, sizeof(si) );                                    // Explicit zeroing memory
    si.cb = sizeof(si);

    BOOL bSuccess = CreateProcess(lpApplicationName,
                                  lpCommandLine,
                                  NULL,
                                  NULL,
                                  false,
                                  dwCreationFlags,
                                  NULL,
                                  NULL,
                                  &si,                                 // Must be a pointer (or link)
                                  &pi);                                // Must be a pointer (or link)

                                  /*
                                   * \We can use a link to local object (si, pi), because function only needs
                                   * \a fields of structure to initialize process. Objects can be deleted automaticly,
                                   * \after process start, they no more needed.
                                   */
    if (bSuccess) {
        CloseHandle(pi.hThread);                                       // Descriptors must be closed
        CloseHandle(pi.hProcess);                                      // Descriptors must be closed
    }
#endif

    return 0;
}
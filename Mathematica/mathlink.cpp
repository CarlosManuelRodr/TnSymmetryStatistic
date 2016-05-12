#include <vector>
#include "mathlink.h"
#include "../common/TnStatistic.h"

double mathlink_tn(double* v, int nx, double c)
{
    std::vector<double> input(v, v + nx);
    return tn(input, c);
}

#if defined(WIN32)

int __stdcall WinMain(HINSTANCE hinstCurrent, HINSTANCE hinstPrevious, LPSTR lpszCmdLine, int nCmdShow)
{
    char  buff[512];
    char FAR * buff_start = buff;
    char FAR * argv[32];
    char FAR * FAR * argv_end = argv + 32;

    if (!MLInitializeIcon(hinstCurrent, nCmdShow)) return 1;
    MLScanString(argv, &argv_end, &lpszCmdLine, &buff_start);
    return MLMain(argv_end - argv, argv);
}

#else

int main(int argc, char* argv[])
{
    return MLMain(argc, argv);
}

#endif
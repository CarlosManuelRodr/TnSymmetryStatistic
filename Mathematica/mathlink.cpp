#include <vector>
#include <functional>
#include "mathlink.h"
#include "../common/TnStatistic.h"
#include "ThreadPool.h"

double mathlink_tn(double* v, int nx, double c)
{
    std::vector<double> input(v, v + nx);
    return tn(input, c);
}

void parallel_mathlink_tn(double* v, int nx, int* sizes, int ny, double c)
{
    std::vector<int> sublist_sizes(sizes, sizes + ny);

    ThreadPool pool(std::thread::hardware_concurrency());
    std::vector< std::future<double> > results;
    std::vector<double> result_values;

    std::function<double(std::vector<double>, const double)> lambda_tn = tn;
    int current_index = 0;
    for (int i = 0; i < ny; i++)
    {
        results.push_back(pool.enqueue(lambda_tn, std::vector<double>(v + current_index, v + current_index + sizes[i]), c));
        current_index += sizes[i];
    }

    for (unsigned i = 0; i < results.size(); ++i)
        result_values.push_back(results[i].get());

    MLPutReal64List(stdlink, result_values.data(), result_values.size());
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
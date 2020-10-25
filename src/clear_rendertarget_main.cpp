#include "clear_rendertarget.h"

#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char* argv[])
{
    auto start = chrono::high_resolution_clock::now();
    try
    {
        cg::ClearRenderTarget* render = new cg::ClearRenderTarget(1920, 1080);

        render->Clear();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "Clear: " << diff.count() << " s\n";

        render->Save("results/clear_rendertarget.png");

        // Just show the resulted image
        system("start results/clear_rendertarget.png");
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
}
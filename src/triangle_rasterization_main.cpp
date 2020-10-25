#include "triangle_rasterization.h"

#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char* argv[])
{
    auto start = chrono::high_resolution_clock::now();
    try
    {
        cg::TriangleRasterization* render = new cg::TriangleRasterization(1920, 1080, "models/CornellBox-Original.obj");

        render->Clear();
        render->DrawScene();

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "Scene: " << diff.count() << " s\n";

        render->Save("results/triangle_rasterization.png");

        // Just show the resulted image
        system("start results/triangle_rasterization.png");
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
}
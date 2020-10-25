#include "depth_buffer.h"

#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char* argv[])
{  
    try
    {
        cg::ZCulling* render = new cg::ZCulling(1920, 1080, "models/CornellBox-Original.obj");

        render->Clear();

        auto start = chrono::high_resolution_clock::now();
        render->DrawScene();
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "Scene: " << diff.count() << " s\n";

        render->Save("results/depth_buffer.png");

        // Just show the resulted image
        system("start results/depth_buffer.png");
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
}
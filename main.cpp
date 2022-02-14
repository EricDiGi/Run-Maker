#include <string>
#include <iostream>

#include "road.hpp"
#include "route.hpp"
#include "road-graph.hpp"
#include "file-reader.hpp"

using namespace std;
/*
int main(){
    FileReader reader;
    reader.SetFile("simple.tsv");
    reader.IgnoreHeader();
    //cout << "File Set" << endl;
    int vC = 4;
    RoadGraph rg(vC);
    //cout << "adjacency Matrix built" << endl;
    reader.LoadData(rg); 
    int startingVertex = 3;
    double desiredDistance = 3;
    cout << rg.FindLoop(startingVertex, desiredDistance);
    reader.close();
}
*/
int main ()
{
    FileReader reader;

    std::string file;
    do
    {
        std::cout << "Enter the name of the file containing the road network: ";
        std::cin >> file;
        std::cout << file <<std::endl;
    } while (!reader.SetFile(file));

    reader.IgnoreHeader();

    int vertexCount;
    std::cout << "Enter the number of vertices in the input data: ";
    std::cin >> vertexCount;
    std::cout << vertexCount <<std::endl;

    RoadGraph rg(vertexCount);
    reader.LoadData(rg);

    int startingVertex;
    double desiredDistance;
    //Route routeToRun;

    do
    {
        std::cout << "Which vertex is the start (negative to end program)? ";
        std::cin >> startingVertex;
        std::cout << startingVertex <<std::endl;

        if (startingVertex < 0)
        {
            std::cout << "Enjoy your run!!\n";
            break;
        }

        std::cout << "How far do you want to go? ";
        std::cin >> desiredDistance;
        std::cout << desiredDistance <<std::endl;
        std::cout << "===== RUN =====\n" << rg.FindLoop(startingVertex, desiredDistance);
    } while (true);

}
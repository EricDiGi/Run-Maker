#include <string>
#include <fstream>
#include <sstream>
#include "road-graph.hpp"
#include "road.hpp"
#include "file-reader.hpp"

using namespace std;

FileReader::~FileReader(){
    if(this->inFile.is_open())
        this->inFile.close();
}

bool FileReader::SetFile(string filename){
    this->inFile.open(filename.c_str(), ios::in);
    return this->inFile.good();
}

void FileReader::IgnoreHeader(){
    string header;
    if(this->inFile.good())
    getline(this->inFile,header, '\n');
}

void FileReader::LoadData(RoadGraph &g){
    int E1 = -1; int E2 = -1; double D;
    string n, e1, e2, d;
    Road r = Road();

    const char delim = '\t';

    while(!this->inFile.eof()){
        stringstream ss;
        getline(this->inFile, e1, delim);
        getline(this->inFile, e2, delim);
        getline(this->inFile, d, delim);
        getline(this->inFile, n, '\n');
        ss << e1 << " " << e2 << " " << d;
        ss >> E1 >> E2 >> D;
        if(E1 > -1 && E2 > -1){
            r = Road(n,D);
            g.AddAdjacency(E1,E2,r);
        }
        E1 = -1; E2 = -1;
        D = 0.0; n = "";
    }
    inFile.close();
}

void FileReader::close(){
    if(this->inFile.is_open())
        this->inFile.close();
}
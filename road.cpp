#include <iostream>
#include "road.hpp"
#include <string>

using namespace std;

Road::Road(){
    this->streetName = "";
    this->distance = -1.0;
}

Road::Road(string streetName, double distance){
    this->streetName = streetName;
    this->distance = distance;
}

string Road::GetName() const{
    return this->streetName;
}

double Road::GetDistance() const{
    return this->distance;
}

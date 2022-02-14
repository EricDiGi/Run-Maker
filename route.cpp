#include <vector>
#include <iostream>
#include <algorithm>
#include "road.hpp"
#include "route.hpp"

using namespace std;

void Route::AddLeg(Road r){
    this->distance += r.GetDistance();
    this->legs.push_back(r);
}

double Route::GetDistance() const{
    return this->distance;
}

bool Route::Includes(Road roadToSearchFor) const{
    auto I = find(this->legs.begin(), this->legs.end(), roadToSearchFor);
    return ( I != this->legs.end());
}

int Route::SIZE(){
    return this->legs.size();
}

Road Route::FIRST(){
    if(!this->legs.empty())
        return this->legs[0];
    return Road();
}

Road Route::LAST(){
    if(!this->legs.empty())
        return this->legs[SIZE()-1];
    return Road();
}
#include "route.hpp"
#include "road.hpp"
#include "road-graph.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

RoadGraph::RoadGraph(int vertexCount){
    this->vertexCount = vertexCount;
    this->adjacencyMatrix = new Road*[vertexCount];
    for(int i = 0; i < vertexCount; i++){
        this->adjacencyMatrix[i] = new Road[vertexCount];
    }
}

RoadGraph::~RoadGraph(){
    for(int i = 0; i < this->vertexCount;i++){
        delete[] this->adjacencyMatrix[i];
    }
    delete[] this->adjacencyMatrix;
}

bool RoadGraph::AddAdjacency(int endpoint1, int endpoint2, Road r){
    if((endpoint1 < 0) || (endpoint2 < 0) || (endpoint1 > this->vertexCount-1)|| (endpoint2 > this->vertexCount-1)){
        return false;
    }
    this->adjacencyMatrix[endpoint1][endpoint2] = r;
    this->adjacencyMatrix[endpoint2][endpoint1] = r;
    return true;
}


//PRIVATE

/*
Treat the map as a tree. Each road is a branch on the tree.
To work we must be able to compare all followed routes to the criteria.
Similar to standing at the root of the tree and measuring the branches from the leaf to the root.
*/
Route RoadGraph::FindRoute(Route &routeSoFar, int startingVertex, int endingVertex, double distance){
        vector<Route> r;
        r.push_back(routeSoFar); //Solves space complexity

        Route curr;
        for(int i = 0; i < this->vertexCount; i++){
            if(ValidVertices(startingVertex,i) && !routeSoFar.Includes(this->adjacencyMatrix[startingVertex][i])){
                curr = routeSoFar;
                curr.AddLeg(this->adjacencyMatrix[startingVertex][i]);
                
                //routeSoFar.GetDistance() > distance solves time complexity
                if((isLoop(endingVertex, curr) && curr.SIZE() > 2) || routeSoFar.GetDistance() > distance){
                    return curr;
                }

                r.push_back(FindRoute(curr,i,endingVertex,distance));
            }
        }

        vector<double> n;
        for(Route it: r){
            if(isLoop(endingVertex, it))
                n.push_back(fabs(it.GetDistance() - distance));
            else
                n.push_back(fabs(distance) + 1000); //trims non loops from tree without taking more space in stack
        }

        double min = *min_element(n.begin(),n.end());
        int loc = find(n.begin(),n.end(),min) - n.begin();
        return r[loc];
}

bool RoadGraph::isLoop(int end, Route path){
    Road r1 = path.FIRST();
    Road rL = path.LAST();

    int find = 0;

    //t_worst = n
    for(int i = 0; i < this->vertexCount; i++){
        if(ValidVertices(i,end)){
            Road curr = this->adjacencyMatrix[i][end];
            if((curr == r1)||(curr == rL))
                find++;
        }
        if(find >= 2)
            return true;
    }
    if(find >= 2)
        return true;
    return false;
}

bool RoadGraph::ValidVertices(int i, int j){
    if(!((i < 0) || (j < 0) || (i > this->vertexCount-1)||(j > this->vertexCount-1)))
        return (this->adjacencyMatrix[i][j].GetDistance() > -1.0);
    return false;
}

Route RoadGraph::FindLoop(int startingVertex, double distance){
    Route r;
    if((startingVertex > this->vertexCount-1) || startingVertex < 0){ //out of bounds
        return r;
    }
    r = FindRoute(r,startingVertex,startingVertex,distance); //walk graph
    return r;
}

int RoadGraph::vC(){
    return this->vertexCount;
}
#ifndef ROAD_GRAPH_HPP
#define ROAD_GRAPH_HPP

#include <cmath>
#include "road.hpp"
#include "route.hpp"

class RoadGraph
{
	private:
		int vertexCount;
		Road** adjacencyMatrix;
		bool ValidVertices (int i, int j);
		Route FindRoute (Route &routeSoFar, int startingVertex, int endingVertex, double distance);
		static constexpr double EPSILON = 0.001;
	public:
		bool isLoop(int end, Route path); //best time complexity
		RoadGraph (int vertexCount = 0);
		bool AddAdjacency (int endpoint1, int endpoint2, Road r);
		Route FindLoop(int startingVertex, double distance);
		~RoadGraph ();
		int vC();
};

#endif /*ROAD_GRAPH_HPP*/

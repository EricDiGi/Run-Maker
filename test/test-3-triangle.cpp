#include "catch/catch.hpp"
#include "../road-graph.hpp"
#include "../route.hpp"
#include "../road.hpp"

TEST_CASE("Testing simplest path")
{
	RoadGraph rg(3); // 3 vertex graph

	Road a("A", 1.0);
	Road b("B", 1.5);
	Road c("C", 1.5);

	REQUIRE(false == rg.AddAdjacency(-1, 1, a)); // negative vertex id
	REQUIRE(false == rg.AddAdjacency(1, 3, a)); // 3 - beyond available vertex list

	REQUIRE(true == rg.AddAdjacency(0, 1, a));
	REQUIRE(true == rg.AddAdjacency(1, 2, b));
	REQUIRE(true == rg.AddAdjacency(0, 2, c));

	Route path; // empty path

	REQUIRE(path == rg.FindLoop(3, 4.1)); // start (3) outside vertex list
	path.AddLeg(a);
	path.AddLeg(b);
	path.AddLeg(c); // path now goes A->B->C
	REQUIRE(path == rg.FindLoop(0, 4.1));
}

// Compile & run:
// make clean test-2-triangle

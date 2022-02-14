#include "catch/catch.hpp"
#include "../road.hpp"
#include "../file-reader.hpp"
#include "../road-graph.hpp"

TEST_CASE("Test path selection")
{
	FileReader reader;
	reader.SetFile("simple.tsv");

	reader.IgnoreHeader();

	RoadGraph rg(4); // 4 (0-3) vertices in simple.tsv
	reader.LoadData(rg);

	/* Create 3km path */
	Route shortPath;
	Road a("A", 1.0);
	Road b("B", 1.0);
	Road c("C", 1.0);
	shortPath.AddLeg(a);
	shortPath.AddLeg(b);
	shortPath.AddLeg(c);

	// look for 4.4km route, which is closer to 3 than 6
	REQUIRE(shortPath == rg.FindLoop(0, 4.4));


	/* Create 6km path */
	Route longPath;
	longPath.AddLeg(a);
	longPath.AddLeg(Road("Foo", 2.0));
	longPath.AddLeg(Road("Bar", 2.0));
	longPath.AddLeg(c);

	// look for 5km route, which is closer to 6 than 3
	REQUIRE(longPath == rg.FindLoop(0, 5.0));
}

// Compile & run:
// make clean test-4-reader

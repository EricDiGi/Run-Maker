#include "catch/catch.hpp"
#include "../road.hpp"
#include "../file-reader.hpp"
#include "../road-graph.hpp"

TEST_CASE("Test file init")
{
	FileReader reader;
	REQUIRE(false == reader.SetFile("foo.bar")); // file not present
	REQUIRE(true == reader.SetFile("simple.tsv"));
}

TEST_CASE("Test file reader")
{
	FileReader reader;
	reader.SetFile("simple.tsv");

	reader.IgnoreHeader();

	RoadGraph rg(4); // 4 (0-3) vertices in simple.tsv
	reader.LoadData(rg);

	Route path; // Create simple 3km path
	Road a("A", 1.0);
	Road b("B", 1.0);
	Road c("C", 1.0);
	path.AddLeg(a); // path now passes along A
	path.AddLeg(b); // path now goes A->B
	path.AddLeg(c); // path now goes A->B->C

	REQUIRE(path == rg.FindLoop(0, 3.0));

}

// Compile & run:
// make clean test-4-reader

#include "catch/catch.hpp"
#include "../road.hpp"
#include <sstream>

TEST_CASE("Test constructor")
{
	Road gravel; // default needed for array allocation
	REQUIRE("" == gravel.GetName());
	REQUIRE(Approx(-1.0) == gravel.GetDistance());

	Road main("Main", 1.3); // main street, length 1.3km
	REQUIRE("Main" == main.GetName());
	REQUIRE(Approx(1.3) == main.GetDistance());

	std::ostringstream os;
	os << main;
	REQUIRE("Main: 1.3km" == os.str());
}
TEST_CASE("Check equality")
{
	Road main("Main", 1.3);
	Road main2("Main", 1.3); // same attributes as main1

	REQUIRE(main == main2);

	Road notMain("Main", 1.2);
	REQUIRE(!(main == notMain));

	Road alsoNotMain("This-in-not-main", 1.3);
	REQUIRE(!(main == alsoNotMain));

	// now test copy
	alsoNotMain = main;
	REQUIRE(main == alsoNotMain);
}

// Compile & run:
// make clean test-1-road

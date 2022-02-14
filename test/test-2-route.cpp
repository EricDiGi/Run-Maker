#include "catch/catch.hpp"
#include "../route.hpp"
#include <sstream>

TEST_CASE("Test basic Route object")
{
	Route myRun;
	REQUIRE(Approx(0.0) == myRun.GetDistance());

	Road a("A", 1.0);
	Road b("B", 2.0);
	Road c("C", 2.5);
	myRun.AddLeg(a);
	myRun.AddLeg(b);
	myRun.AddLeg(c);

	REQUIRE(Approx(5.5) == myRun.GetDistance());

	std::ostringstream os;
	os << myRun;
	REQUIRE("5.5km route\nA: 1km\nB: 2km\nC: 2.5km\n" == os.str());
}

TEST_CASE("Test for existing edges")
{
	Route myRun;

	Road a("A", 1.0);

	REQUIRE(false == myRun.Includes(a));

	myRun.AddLeg(a);
	REQUIRE(true == myRun.Includes(a));
}

TEST_CASE("Equality")
{
	Route myRun;
	Route myRun2;

	Road a("A", 1.0);
	Road b("B", 2.0);
	Road c("C", 2.5);

	myRun.AddLeg(a);
	myRun.AddLeg(b);
	REQUIRE(!(myRun == myRun2)); // myRun2 is still empty

	myRun2.AddLeg(a);
	myRun2.AddLeg(b);
	REQUIRE(myRun == myRun2);
}

// Compile & run:
// make clean test-2-route

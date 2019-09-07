#include <string>
#include <vector>

#include "container\DataSet.h"
#include "container\Bimap.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "testing\catch.hpp"

using namespace std;

TEST_CASE( "Bimap can be instanciated", "[Bimap]" ) {

    Bimap<long double, string> bm;

    REQUIRE( bm.size() == 0);

    SECTION ("SAME KEY AND VALUE TYPE") {
        Bimap<long double, long double> bm_ld_ld;
        REQUIRE(bm_ld_ld.size() == 0);
    }
}

TEST_CASE( "Bimap can assign a key-value pair" ) {
    Bimap<long double, string> bm;

    bm.set(1, "one");
    bm.set(2, "two");

    REQUIRE(bm.get_key("one") == 1);
    REQUIRE(bm.get_key("two") == 2);

    REQUIRE( bm.get_value(1) == "one");
    REQUIRE( bm.get_value(2) == "two");
}

TEST_CASE( "Bimap can report if a key or value already exists" ) {
    Bimap<long double, string> bm;

    bm.set(1, "one");
    bm.set(2, "two");

    REQUIRE(bm.has_key(1) == true);
    REQUIRE(bm.has_value("one") == true);

    REQUIRE(bm.has_key(2) == true);
    REQUIRE(bm.has_value("two") == true);

    SECTION("REMOVE VIA KEY") {
        bm.remove_key(1);

        REQUIRE(bm.size() == 1);
        
        bm.remove_key(2);

        REQUIRE(bm.size() == 0);
    }

    SECTION("REMOVE VIA VALUE") {
        bm.remove_value("one");

        REQUIRE(bm.size() == 1);

        bm.remove_value("two");

        REQUIRE(bm.size() == 0);
    }
}
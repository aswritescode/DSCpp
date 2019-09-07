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
        Bimap<long double, long double> mb_ld_ld;
        REQUIRE(bm_ld_ld.size() == 0);
    }
}

TEST_CASE( "Bimap can assign a key-value pair" ) {
    Bimap<long double, string>


}
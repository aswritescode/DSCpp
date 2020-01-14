#include <string>
#include <vector>

#include "Container/DataSet.h"
#include "Container/Bimap.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "testing/catch.hpp"

using namespace std;

TEST_CASE( "Bimap can be instantiated", "[Bimap]" ) {

    Bimap<long double, string> bm;

    REQUIRE( bm.size() == 0);

    SECTION ("SAME KEY AND VALUE TYPE") {
        Bimap<long double, long double> bm_ld_ld;
        REQUIRE(bm_ld_ld.size() == 0);
    }
}

TEST_CASE( "Bimap can assign a key-value pair", "[Bimap]" ) {
    Bimap<long double, string> bm;

    bm.set(1, "one");
    bm.set(2, "two");

    REQUIRE(bm.get_key("one") == 1);
    REQUIRE(bm.get_key("two") == 2);

    REQUIRE( bm.get_value(1) == "one");
    REQUIRE( bm.get_value(2) == "two");
}

TEST_CASE( "Bimap can report if a key or value already exists", "[Bimap]" ) {
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

TEST_CASE( "Columns can be instantiated", "[Column]" ) {
    
    Column c;
    std::vector<long double> v = {0,1,2,3,4,5};
    std::string label = "CoLuMn";

    SECTION("DEFAULT CONSTRUCTOR") {
        c = Column();
    
        REQUIRE(c.get_label() == DEFAULT_LABEL);
        REQUIRE(c.get_data().size() == 0);
        REQUIRE(!c.is_masked());
    }

    SECTION("DATA CONSTRUCTOR") {
        c = Column(v);

        REQUIRE(c.get_data().size() == v.size());
        REQUIRE(c.get_label() == "col");
        REQUIRE(!c.is_masked());
    }

    SECTION("DATA AND LABEL CONSTRUCTOR") {
        c = Column(v, label);

        REQUIRE(c.get_data().size() == v.size());
        REQUIRE(c.get_label() == label);
        REQUIRE(!c.is_masked());
    }

    SECTION("COPY CONSTRUCTOR WITH NO MAP") {
        Column c2(v, label);

        c = c2;

        REQUIRE(c.get_label() == label);
        REQUIRE(c.get_data() == v);
        REQUIRE(!c.is_masked());
    }

    SECTION("COPY CONSTRUCTOR WITH MAP") {
        Column c2(v, label);
        Bimap<long double, std::string> bm;
        bm.set(1, "one");
        c2.set_map(bm);

        c = c2;

        c2.set_map(*(new Bimap<long double, std::string>()));

        REQUIRE(c.get_label() == label);
        REQUIRE(c.get_data() == v);
        REQUIRE(c.get_map().size() == 1);
        REQUIRE(c.get_map().get_value(1) == "one");
    }
}

TEST_CASE("Column can have a translation map", "[Column]") {
    Column c;
    std::shared_ptr<Bimap<long double, std::string>> bm_ptr = std::make_shared<Bimap<long double, std::string>>();
    bm_ptr.get()->set(1, "one");
    bm_ptr.get()->set(2, "two");
    bm_ptr.get()->set(3, "three");

    SECTION("SET_MAP") {
        c.set_map(bm_ptr);

        REQUIRE(c.get_map_ptr().get() != nullptr);
        REQUIRE(c.get_map().get_key("one") == 1);
        REQUIRE(c.get_map_ptr().get()->get_value(2) == "two");
    }
}
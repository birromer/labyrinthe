#define CATCH_CONFIG_MAIN

#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <list>
#include <limits>

#include "../include/vibes.h" // might need to change those includes
#include "../include/Cell.h"
#include "../include/Path.h"

//#include "catch2/catch_amalgamated.hpp"
#include <catch2/catch.hpp>

#define protected public

TEST_CASE("Cell")
{

    SECTION("Test 1: Initialize Cells")
    {
        Cell *c11 = new Cell(1,1);
        REQUIRE (c11->m_x == 1);
        REQUIRE (c11->m_y == 1);

        Cell *c12 = new Cell(1,2);
        REQUIRE (c12->m_x == 1);
        REQUIRE (c12->m_y == 2);
    }

//    SECTION("Test 2: Connect Cells")
//    {
//        REQUIRE (c11->m_nb_neighb == 0);
//        Cell::add_neighb(c11,c12);
//        REQUIRE (c11->m_nb_neighb == 1);
//    }
//
//    SECTION("Test 3: Connects Cells")
//    {
//        display_graph(c21);  // testing only if function doesn't result in errors
//                             // visual testing done separately
//    }
//
//    SECTION("Test 4: Display Graph")
//    {
//        display_graph(c21);  // testing only if function doesn't result in errors
//                             // visual testing done separately
//    }

}

//TEST_CASE("Path")
//{
//
//}
//
//TEST_CASE("Maze")
//{
//
//}

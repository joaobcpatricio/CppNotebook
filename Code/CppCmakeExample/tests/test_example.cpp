//*********************************************************************************************************************
//*
//*   Programmer    : patj
//*   Date          : 2024-01-04 08:29:34 +0200 (Do., 04 01 2024)
//*
//*********************************************************************************************************************

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "../src/example_class.hpp"

TEST_CASE("Factorials are computed", "[factorial]")
{
        ExampleClass exampleClass;
        exampleClass.PrintConfigured();
        REQUIRE(exampleClass.GetCounter() == 0);

        exampleClass.CounterAddOne();
        uint8_t value = exampleClass.GetCounter();
        REQUIRE(value == 1);
}

TEST_CASE("How Pointers Work", "[pointers]")
{
        int var = 8; // Created on the stack
        int *ptr = &var;
        *ptr = 10; // Dereferencing a pointer and writing on it
        std::cout << var << std::endl;

        char *buffer = new char[8]; // Created at the heap
        memset(buffer, 0, 8);       // Fills this memory with 0
        char **dptr = &buffer;       // Double pointer (pointer to a pointer)
        delete[] buffer;

        SUCCEED();
}

TEST_CASE("Enums examples", "[enums]"){
        DayOfWeek today = DayOfWeek::Friday;
        REQUIRE( today == DayOfWeek::Friday ); // Direct comparison within the enum
        REQUIRE( static_cast<int>(today) == 5); // Explicit cast to int
}

TEST_CASE("Dog Constructor", "[construct]") {
  Dog myDog("Buddy", 3);
  REQUIRE(myDog.getName() == "Buddy");
  REQUIRE(myDog.getAge() == 3);

  Dog defaultDog;
  REQUIRE(defaultDog.getName() == "Unknown");
  REQUIRE(defaultDog.getAge() == 0);

}


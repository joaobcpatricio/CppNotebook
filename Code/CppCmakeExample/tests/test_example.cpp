//*********************************************************************************************************************
//*
//*   Programmer    : patj
//*   Date          : 2024-01-04 08:29:34 +0200 (Do., 04 01 2024)
//*
//*********************************************************************************************************************

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "../src/example_class.h"

TEST_CASE("Factorials are computed", "[factorial]")
{
        ExampleClass exampleClass;
        exampleClass.PrintConfigured();
        REQUIRE(exampleClass.GetCounter() == 0);

        exampleClass.CounterAddOne();
        uint8_t value = exampleClass.GetCounter();
        REQUIRE(value == 1);
}
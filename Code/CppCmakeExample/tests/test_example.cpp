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

        REQUIRE(1 == 1);
}
//
// Created by Stefanie on 02.10.2018.
//

#include <Cell.h>
#include <Model.h>
#include "gtest/gtest.h"
#include <cmath>
#include <cstdint>
#include <cstring>

class ModelTestFixture : public ::testing::Test {
public:
    ModelTestFixture() {
        // initialization code here
    }

    void SetUp() {
        // code here will execute just before the test runs
    }

    void TearDown() {
        // code here will be called just after the test completes
        // ok to throw exceptions from here if needed
    }

    ~ModelTestFixture() {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put here in any custom data members that you need (for several/all tests)

};

TEST_F (ModelTestFixture, errorTestingforNan) {

    //Arrange
    double x = 5.0;
    double y = std::nan("1");
    double z = 0;


    //double f1 = std::nan("1");
    //std::uint64_t f1n; std::memcpy(&f1n, &f1, sizeof f1);
    //std::cout << "nan(\"1\") = " << f1 << " (" << std::hex << f1n << ")\n";

    //Act
    double NanIsPresent = Model::NanIsPresent(x, y, z);

    //Assert
    ASSERT_EQ(NanIsPresent, true);
}

#include <Cell.h>
#include <Geometrics.h>
#include "gtest/gtest.h"


class GeometricsTestFixture : public ::testing::Test {
public:
    GeometricsTestFixture() {
        // initialization code here
    }

    void SetUp() {
        // code here will execute just before the test runs
    }

    void TearDown() {
        // code here will be called just after the test completes
        // ok to throw exceptions from here if need be
    }

    ~GeometricsTestFixture() {
        // cleanup any pending stuff, but no exceptions allowed
    }

    Cell cell = Cell(0, 0, 0, 0);
    // put in any custom data members that you need
};

TEST_F (GeometricsTestFixture, ShouldReturnCorrectDistanceForZero) {
    //Arrange
    Cell cell1(0, 0, 0, 0);
    Cell cell2(0, 0, 0, 0);
    //Act

    double distance = Geometrics::centerDistance2D(cell1, cell2);

    //Assert
    ASSERT_EQ(distance, 0) << "Distance is wrong";
}

TEST_F (GeometricsTestFixture, centerDistance2D_PositiveIntegers) {
    //Arrange
    Cell cell1(1, 2, 3, 4);
    Cell cell2(5, 6, 7, 8);

    //Act
    double distance = Geometrics::centerDistance2D(cell1, cell2);

    //Assert
    ASSERT_NEAR(distance, 5.65685424949, 0.0000001) << "Distance is wrong";
}
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
        // ok to throw exceptions from here if needed
    }

    ~GeometricsTestFixture() {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put here in any custom data members that you need (for several/all tests)
};

TEST_F (GeometricsTestFixture, centerDistance2D_Zero) {
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

TEST_F (GeometricsTestFixture, centerDistance2D_NegativeIntegers) {
    //Arrange
    Cell cell1(-1, 2, -3, 4);
    Cell cell2(5, -6, 7, 8);

    //Act
    double distance = Geometrics::centerDistance2D(cell1, cell2);

    //Assert
    ASSERT_EQ(distance, 10) << "Distance is wrong";
}

TEST_F (GeometricsTestFixture, centerDistance3D_Zero) {
    //Arrange
    Cell cell1(0, 0, 0, 4);
    Cell cell2(0, 0, 0, 8);

    //Act
    double distance = Geometrics::centerDistance3D(cell1, cell2);

    //Assert
    ASSERT_EQ(distance, 0) << "Distance is wrong";
}

TEST_F (GeometricsTestFixture, centerDistance3D_PositiveIntegers) {
    //Arrange
    Cell cell1(1, 2, 3, 4);
    Cell cell2(5, 6, 7, 8);

    //Act
    double distance = Geometrics::centerDistance3D(cell1, cell2);

    //Assert
    ASSERT_NEAR(distance, 6.92820323028, 0.000000001) << "Distance is wrong";
}

TEST_F (GeometricsTestFixture, centerDistance3D_NegativeIntegers) {
    //Arrange
    Cell cell1(-1, 2, -3, 4);
    Cell cell2(5, -6, 7, 8);

    //Act
    double distance = Geometrics::centerDistance3D(cell1, cell2);

    //Assert
    ASSERT_NEAR(distance, 14.1421356237, 0.000000001) << "Distance is wrong";
}

TEST_F (GeometricsTestFixture, distance2D_Zero) {
    //Arrange
    std::vector<double> v1 = {0, 0, 0};
    std::vector<double> v2 = {0, 0, 0};

    //Act
    double distance = Geometrics::distance2D(v1, v2);

    //Assert
    ASSERT_EQ(distance, 0) << "Distance is wrong";
}

TEST_F (GeometricsTestFixture, distance2D_PositiveDoubles) {
    //Arrange
    std::vector<double> v1 = {1, 2, 3};
    std::vector<double> v2 = {4, 6, 7};

    //Act
    double distance = Geometrics::distance2D(v1, v2);

    //Assert
    ASSERT_EQ(distance, 5) << "Distance is wrong";
}

TEST_F (GeometricsTestFixture, distance2D_NegativeDoubles) {
    //Arrange
    std::vector<double> v1 = {-1, 2, -3};
    std::vector<double> v2 = {4, -6, 7};

    //Act
    double distance = Geometrics::distance2D(v1, v2);

    //Assert
    ASSERT_NEAR(distance, 9.43398113206, 0.000000001) << "Distance is wrong";
}

TEST_F (GeometricsTestFixture, distance3D_Zero) {
    //Arrange
    std::vector<double> v1 = {0, 0, 0};
    std::vector<double> v2 = {0, 0, 0};

    //Act
    double distance = Geometrics::distance3D(v1, v2);

    //Assert
    ASSERT_EQ(distance, 0) << "Distance is wrong";
}

TEST_F (GeometricsTestFixture, distance3D_PostivieDoubles) {
    //Arrange
    std::vector<double> v1 = {1, 2, 3};
    std::vector<double> v2 = {4, 6, 7};

    //Act
    double distance = Geometrics::distance3D(v1, v2);

    //Assert
    ASSERT_NEAR(distance, 6.40312423743, 0.000000001) << "Distance is wrong";
}

TEST_F (GeometricsTestFixture, distance3D_NegativeDoubles) {
    //Arrange
    std::vector<double> v1 = {-1, 2, -3};
    std::vector<double> v2 = {4, -6, 7};

    //Act
    double distance = Geometrics::distance3D(v1, v2);

    //Assert
    ASSERT_NEAR(distance, 13.7477270849, 0.000000001) << "Distance is wrong";
}

TEST_F (GeometricsTestFixture, vectorNorm3D_Zero) {
    //Arrange
    std::vector<double> v = {0, 0, 0};

    //Act
    double norm = Geometrics::vectorNorm3D(v);

    //Assert
    ASSERT_EQ(norm, 0);
}

TEST_F (GeometricsTestFixture, vectorNorm3D_PositiveDoubles) {
    //Arrange
    std::vector<double> v = {1, 2, 3};

    //Act
    double norm = Geometrics::vectorNorm3D(v);

    //Assert
    ASSERT_NEAR(norm, 3.74165738677, 0.000000001);
}

TEST_F (GeometricsTestFixture, vectorNorm3D_NegativeDoubles) {
    //Arrange
    std::vector<double> v = {1, -2, 3};

    //Act
    double norm = Geometrics::vectorNorm3D(v);

    //Assert
    ASSERT_NEAR(norm, 3.74165738677, 0.000000001);
}

TEST_F (GeometricsTestFixture, crossProduct_Zero) {
    //Arrange
    std::vector<double> v1 = {0, 0, 0};
    std::vector<double> v2 = {0, 0, 0};

    std::vector<double> expected = {0, 0, 0};

    //Act
    std::vector<double> crossProduct = Geometrics::crossProduct(v1, v2);

    //Assert
    ASSERT_EQ(crossProduct, expected);
}

TEST_F (GeometricsTestFixture, crossProduct_PositiveDoubles) {
    //Arrange
    std::vector<double> v1 = {1, 2, 3};
    std::vector<double> v2 = {4, 6, 7};

    std::vector<double> expected = {-4, 5, -2};

    //Act
    std::vector<double> crossProduct = Geometrics::crossProduct(v1, v2);

    //Assert
    ASSERT_EQ(crossProduct, expected);
}

TEST_F (GeometricsTestFixture, crossProduct_NegativeDoubles) {
    //Arrange
    std::vector<double> v1 = {-1.33, 2.2, -3.5};
    std::vector<double> v2 = {4.0, -6.2, 7.1};

    std::vector<double> expected = {-6.08, -4.557, -0.554};

    //Act
    std::vector<double> crossProduct = Geometrics::crossProduct(v1, v2);

    //Assert
    ASSERT_EQ(crossProduct, expected);
}

TEST_F (GeometricsTestFixture, vectorSum_Zero) {
    //Arrange
    std::vector<double> v = {0, 0, 0};
    double expected = 0;

    //Act
    double sum = Geometrics::vectorSum(v);

    //Assert
    ASSERT_EQ(sum, expected);
}

TEST_F (GeometricsTestFixture, vectorSum_PositiveDoubles) {
    //Arrange
    std::vector<double> v = {1, 2, 3};
    double expected = 6;

    //Act
    double sum = Geometrics::vectorSum(v);

    //Assert
    ASSERT_EQ(sum, expected);
}

TEST_F (GeometricsTestFixture, vectorSum_NegativeDoubles) {
    //Arrange
    std::vector<double> v = {-1, 2, -3};
    double expected = -2;

    //Act
    double sum = Geometrics::vectorSum(v);

    //Assert
    ASSERT_EQ(sum, expected);
}

TEST_F (GeometricsTestFixture, calculatePerimeterAndArea_Zero) {
    //Arrange
    std::vector<double> v = {-1, 2, -3};
    double expected = -2;

    //Act
    double sum = Geometrics::vectorSum(v);

    //Assert
    ASSERT_EQ(sum, expected);
}

/*TEST_F (GeometricsTestFixture, calculatePerimeter_Zero) {
    //Arrange
    Cell cell1(0, 0, 0, 0);
    Cell cell2(0, 0, 0, 0);
    std::vector<Cell> cells = {cell1, cell2};
    int cell = 0;

    double expected = -2;

    //Act
    double sum = Geometrics::vectorSum(v);

    //Assert
    ASSERT_EQ(sum, expected);
}*/
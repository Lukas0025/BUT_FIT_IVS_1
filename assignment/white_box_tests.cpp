//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Lukáš Plevač <xpleva07@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Lukáš Plevač
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

/**
 * Transfer static array to object of Matrix Class
 * @param value static array to convertion
 * @return Matrix object with data from value param
 */
template <size_t rows, size_t cols>
Matrix static_array_to_matrix(double (&value)[rows][cols]) {
    Matrix mat = Matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat.set(i, j, value[i][j]);
        }
    }

    return mat;
}

/**
 * Transfer static array to object of 1D Matrix vector [double]
 * @param value static array to convertion
 * @return Double Vector object with data from value param
 */
template <size_t cols>
std::vector< double > static_array_to_1DVector(double (&value)[cols]) {
    std::vector< double > line;

    for (int j = 0; j < cols; j++) {
        line.push_back(value[j]);
    }

    return line;
}

/**
 * Transfer static array to object of 2D Matrix vector [double]
 * @param value static array to convertion
 * @return Double Vector object with data from value param
 */
template <size_t rows, size_t cols>
std::vector<std::vector< double > > static_array_to_2DVector(double (&value)[rows][cols]) {
    std::vector<std::vector< double > > vec;

    for (int j = 0; j < rows; j++) {
        vec.push_back(static_array_to_1DVector(value[j]));
    }

    return vec;
}

class Matrix2x2 : public ::testing::Test
{
protected:
    virtual void SetUp() {
        double array[2][2] = { 
            { 10, -2 },
            { 12, 99 }
        };

        mat = static_array_to_matrix(array);
    }

    Matrix mat;
};

class Matrix5x3 : public ::testing::Test
{
protected:
    virtual void SetUp() {
        double array[5][3] = {
            {10.87,   -10.10,    2.70},
            {100,      -81.63,    10},
            {5,          -1.333,     99.89},
            {-42,      -10,           24},
            {65,       -10,           2}
        };

        mat = static_array_to_matrix(array);
    }

    Matrix mat;
};

class Matrix3x6 : public ::testing::Test
{
protected:
    virtual void SetUp() {
        double array[3][6] = {
            {10.1,    -10.8,     2.7,      -100.3,   64.0,    42.7},
            {100.6,  -81.66,  10.18,   -42.1,    54.54,  30.1},
            {5.544,  -1.568,  99.99,    10.5,    73.1,    57.3}
        };

        mat = static_array_to_matrix(array);
    }

    Matrix mat;
};

class MatrixTest : public ::testing::Test {

};

TEST_F(MatrixTest, Setup)
{
    EXPECT_THROW(Matrix(0,1), std::runtime_error);
    EXPECT_THROW(Matrix(1,0), std::runtime_error);
    EXPECT_THROW(Matrix(-1,0), std::runtime_error);
    //try setup empy matrix (1x1)
    auto matrix1 = Matrix();

    //try set
    EXPECT_EQ(matrix1.set(0, 0, 10), true);
}

/***
 * operation set value on all sizes
 */

TEST_F(Matrix2x2, SetValue)
{
    EXPECT_EQ(mat.set(0, 0, 10), true);

    //check is set
    EXPECT_DOUBLE_EQ(mat.get(0, 0), 10);

    EXPECT_EQ(mat.set(3, 0, 10), false);
    EXPECT_EQ(mat.set(0, 3, 10), false);
    EXPECT_EQ(mat.set(3, 3, 10), false);
}

TEST_F(Matrix5x3, SetValue)
{
    EXPECT_EQ(mat.set(4, 2, 10.15), true);

    //check is set
    EXPECT_DOUBLE_EQ(mat.get(4, 2), 10.15);

    EXPECT_EQ(mat.set(5, 0, 10), false);
    EXPECT_EQ(mat.set(0, 3, 10), false);
    EXPECT_EQ(mat.set(-1, 0, 10), false);
}

TEST_F(Matrix3x6, SetValue)
{
    EXPECT_EQ(mat.set(2, 5, 10.15), true);

    //check is set
    EXPECT_DOUBLE_EQ(mat.get(2, 5), 10.15);

    EXPECT_EQ(mat.set(3, 0, 10), false);
    EXPECT_EQ(mat.set(0, 6, 10), false);
    EXPECT_EQ(mat.set(-1, 0, 10), false);
}

/***
 * operation set vector on all sizes
 */


TEST_F(Matrix2x2, SetVector)
{
    double vec1x2[1][2] = {
        {1, 2.2}
    };

    EXPECT_EQ(mat.set(static_array_to_2DVector(vec1x2)), false);

    double vec1x4[1][4] = {
        {1, 2, 5, 6.1}
    };

    EXPECT_EQ(mat.set(static_array_to_2DVector(vec1x4)), false);

    double vec2x2[2][2] = {
        {1.65, 2},
        {3,      4.58}
    };

    EXPECT_EQ(mat.set(static_array_to_2DVector(vec2x2)), true);

    //check values
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            EXPECT_DOUBLE_EQ(mat.get(i, j), vec2x2[i][j]);
        }
    }
}

TEST_F(Matrix5x3, SetVector)
{
    double vec1x2[1][2] = {
        {1, 2.5}
    };

    EXPECT_EQ(mat.set(static_array_to_2DVector(vec1x2)), false);

    double vec1x4[1][4] = {
        {1, 2.1, 5, 6}
    };

    EXPECT_EQ(mat.set(static_array_to_2DVector(vec1x4)), false);

    double vec5x3[5][3] = {
        {1.01, 2,      2.22},
        {3,      4,      5.658},
        {1,      2,      10},
        {3,      4,      199},
        {1,      2.19, 158.1}
    };

    EXPECT_EQ(mat.set(static_array_to_2DVector(vec5x3)), true);

    //check values
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_DOUBLE_EQ(mat.get(i, j), vec5x3[i][j]);
        }
    }
}

TEST_F(Matrix3x6, SetVector)
{
    double vec1x2[1][2] = {
        {1, 2.5}
    };

    EXPECT_EQ(mat.set(static_array_to_2DVector(vec1x2)), false);

    double vec1x4[1][4] = {
        {1, 2.1, 5, 6}
    };

    EXPECT_EQ(mat.set(static_array_to_2DVector(vec1x4)), false);

    double vec3x6[3][6] = {
        {310.1,    -110.8,     52.7,      -1100.3,   264.0,    342.7},
        {4100.6,  -581.66,  410.18,   -642.1,    254.54,  530.1},
        {55.544,  -61.568,  399.99,    110.5,    173.1,    457.3}
    };

    EXPECT_EQ(mat.set(static_array_to_2DVector(vec3x6)), true);

    //check values
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            EXPECT_DOUBLE_EQ(mat.get(i, j), vec3x6[i][j]);
        }
    }
}

/***
 * operation getValue on all sizes
 */


TEST_F(Matrix2x2, getValue)
{
    EXPECT_DOUBLE_EQ(mat.get(1, 1), 99);
    EXPECT_THROW(mat.get(-1, 1), std::runtime_error);
    EXPECT_THROW(mat.get(-1, -1), std::runtime_error);
    EXPECT_THROW(mat.get(1, -1), std::runtime_error);
}

TEST_F(Matrix3x6, getValue)
{
    EXPECT_DOUBLE_EQ(mat.get(2, 5),  57.3);
    EXPECT_THROW(mat.get(3, 1), std::runtime_error);
    EXPECT_THROW(mat.get(-1, -1), std::runtime_error);
    EXPECT_THROW(mat.get(1, 6), std::runtime_error);
}

TEST_F(Matrix5x3, getValue)
{
    EXPECT_DOUBLE_EQ(mat.get(4, 2), 2);
    EXPECT_THROW(mat.get(5, 1), std::runtime_error);
    EXPECT_THROW(mat.get(-1, -1), std::runtime_error);
    EXPECT_THROW(mat.get(1, 4), std::runtime_error);
}

/***
 * operation EQ on all sizes
 */


TEST_F(Matrix2x2, operatorEQ)
{
    Matrix mat3x3 = Matrix(3,3);
    EXPECT_THROW(mat == mat3x3, std::runtime_error);
    
    //same test
    EXPECT_EQ(mat == mat, true);

    double notsame[2][2] = {
        {1, 2},
        {3, 3}
    };

    auto mat2 = static_array_to_matrix(notsame);
    //not same test
    EXPECT_EQ(mat == mat2, false);
}

TEST_F(Matrix5x3, operatorEQ)
{
    Matrix mat3x3 = Matrix(3,3);
    EXPECT_THROW(mat == mat3x3, std::runtime_error);
    
    //same test
    EXPECT_EQ(mat == mat, true);

    double notsame[5][3] = {
        {1.01, 2,      2.22},
        {3,      4,      5.658},
        {1,      2,      10},
        {3,      4,      199},
        {1,      2.19, 158.1}
    };

    auto mat2 = static_array_to_matrix(notsame);
    //not same test
    EXPECT_EQ(mat == mat2, false);
}

TEST_F(Matrix3x6, operatorEQ)
{
    Matrix mat3x3 = Matrix(3,3);
    EXPECT_THROW(mat == mat3x3, std::runtime_error);
    
    //same test
    EXPECT_EQ(mat == mat, true);

    double notsame[3][6] = {
        {310.1,    -110.8,     52.7,      -1100.3,   264.0,    342.7},
        {4100.6,  -581.66,  410.18,   -642.1,    254.54,  530.1},
        {55.544,  -61.568,  399.99,    110.5,    173.1,    457.3}
    };

    auto mat2 = static_array_to_matrix(notsame);
    //not same test
    EXPECT_EQ(mat == mat2, false);
}

/***
 * operation add on all sizes
 */

TEST_F(Matrix2x2, operatorADD)
{
    Matrix mat3x3 = Matrix(3,3);
    EXPECT_THROW(mat + mat3x3, std::runtime_error);
    
    //same size test
    double add_mat[2][2] = {
        {4, 3},
        {2, 1}
    };

    double res_mat[2][2] = {
        {14, 1},
        {14, 100}
    };

    auto res = static_array_to_matrix(res_mat);
    auto add = static_array_to_matrix(add_mat);

    EXPECT_EQ((mat + add), res);
}

TEST_F(Matrix5x3, operatorADD)
{
    Matrix mat3x4 = Matrix(3,4);
    EXPECT_THROW(mat + mat3x4, std::runtime_error);
    
    //same size test
    double add_mat[5][3] = {
        {1.01, 2,      2.22},
        {3,      4,      5.658},
        {1,      2,      10},
        {3,      4,      199},
        {1,      2.19, 158.1}
    };

    double res_mat[5][3];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            res_mat[i][j] = mat.get(i, j) + add_mat[i][j];
        }
    }

    auto res = static_array_to_matrix(res_mat);
    auto add = static_array_to_matrix(add_mat);

    EXPECT_EQ((mat + add), res);
}

TEST_F(Matrix3x6, operatorADD)
{
    Matrix mat3x5 = Matrix(3,5);
    EXPECT_THROW(mat + mat3x5, std::runtime_error);
    
    //same size test
    double add_mat[3][6] = {
        {310.1,    -110.8,     52.7,      -1100.3,   264.0,    342.7},
        {4100.6,  -581.66,  410.18,   -642.1,    254.54,  530.1},
        {55.544,  -61.568,  399.99,    110.5,    173.1,    457.3}
    };

    double res_mat[3][6];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            res_mat[i][j] = mat.get(i, j) + add_mat[i][j];
        }
    }

    auto res = static_array_to_matrix(res_mat);
    auto add = static_array_to_matrix(add_mat);

    EXPECT_EQ((mat + add), res);
}

/***
 * operation mul on all sizes
 */

TEST_F(Matrix2x2, operatorMUL)
{
    //bad size
    Matrix mat3x3 = Matrix(3,3);
    EXPECT_THROW(mat * mat3x3, std::runtime_error);

    //correct size
    double mul_mat[2][3] = {
        {1,    2, 1},
        {-10, 4, 0}
    };

    double res_mat[2][3] = {
        {30, 12, 10},
        {-978, 420, 12}
    };

    auto res = static_array_to_matrix(res_mat);
    auto mul = static_array_to_matrix(mul_mat);

    EXPECT_EQ((mat * mul), res);
}


TEST_F(Matrix5x3, operatorMUL)
{
    //bad size
    Matrix mat2x3 = Matrix(2,3);
    EXPECT_THROW(mat * mat2x3, std::runtime_error);

    //correct size
    double mul_mat[3][1] = {
        {3},
        {2},
        {1}
    };

    double res_mat[5][1] = {
        {15.11},
        {146.74},
        {112.224},
        {-122},
        {177}
    };

    auto mul = static_array_to_matrix(mul_mat);

    for (int i = 0; i < 5; i++) {
        EXPECT_NEAR((mat * mul).get(i, 0), res_mat[i][0], 0.0001);
    }
}


TEST_F(Matrix3x6, operatorMUL)
{
    //bad size
    Matrix mat3x3 = Matrix(3,3);
    EXPECT_THROW(mat * mat3x3, std::runtime_error);

    //correct size
    double mul_mat[6][1] = {
        {3},
        {2},
        {1},
        {3},
        {2},
        {1}
    };

    double res_mat[3][1] = {
        {-118.8},
        {161.54},
        {348.486}
    };

    auto mul = static_array_to_matrix(mul_mat);

    for (int i = 0; i < 3; i++) {
        EXPECT_NEAR((mat * mul).get(i, 0), res_mat[i][0], 0.0001);
    }
}

/***
 * operation mul by costant on all sizes
 */

TEST_F(Matrix2x2, operatorMULConst)
{
    
    double res_mat[2][2] = {
        {40, -8},
        {48, 396}
    };

    auto res = static_array_to_matrix(res_mat);

    EXPECT_EQ((mat * 4), res);
}

TEST_F(Matrix5x3, operatorMULConst)
{
    
    double res_mat[5][3];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            res_mat[i][j] = (mat.get(i,j) * 4);
        }
    }

    auto res = static_array_to_matrix(res_mat);

    EXPECT_EQ((mat * 4), res);
}

TEST_F(Matrix3x6, operatorMULConst)
{
    
    double res_mat[3][6];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            res_mat[i][j] = (mat.get(i,j) * 4);
        }
    }
    auto res = static_array_to_matrix(res_mat);

    EXPECT_EQ((mat * 4), res);
}

/***
 * operation solveEquation on all sizes
 */

TEST_F(Matrix2x2, solveEquation)
{
    std::vector< double > b;

    b.push_back(10);

    //bad sizes
    Matrix mat4x1 = Matrix(4,1);
    EXPECT_THROW(mat.solveEquation(b), std::runtime_error);
    EXPECT_THROW(mat4x1.solveEquation(b), std::runtime_error);

    //singular
    b.push_back(20);
    double singular_mat[2][2] = {
        {1, -2},
        {-2, 4}
    };
    auto singular = static_array_to_matrix(singular_mat);

    EXPECT_THROW(singular.solveEquation(b), std::runtime_error);

    //correct
    std::vector< double > res;
    res.push_back(1.0157790927);
    res.push_back(0.07889546351);


    EXPECT_NEAR(mat.solveEquation(b) [0] , res[0], 0.0001);
    EXPECT_NEAR(mat.solveEquation(b) [1] , res[1], 0.0001);
}

TEST_F(MatrixTest, detTest)
{
    std::vector< double > b;

    //1x1 size
    double mat1[1][1] = {
        {10}
    };
    auto mat1x1 = static_array_to_matrix(mat1);
    b.push_back(1);

    EXPECT_NEAR(mat1x1.solveEquation(b)[0], 0.1, 0.00001);

    //2x2 size
    double mat2[2][2] = {
        {1, 2},
        {2, 1}
    };
    auto mat2x2 = static_array_to_matrix(mat2);
    b.push_back(1);

    EXPECT_NEAR(mat2x2.solveEquation(b)[0], (double)1/3, 0.00001);

    //3x3 size
    double mat3[3][3] = {
        {1, 2, 3},
        {3, 2, 1},
        {2, 3, 1}
    };
    auto mat3x3 = static_array_to_matrix(mat3);
    b.push_back(1);

    EXPECT_NEAR(mat3x3.solveEquation(b)[0], (double)1/6, 0.00001);

    //4x4 size
    double mat4[4][4] = {
        {1, 2, 3, 4},
        {3, 2, 1, 4},
        {2, 3, 1, 4},
        {4, 3, 1, 2}
    };
    auto mat4x4 = static_array_to_matrix(mat4);
    b.push_back(1);

    EXPECT_NEAR(mat4x4.solveEquation(b)[0], (double)1/10, 0.00001);
}

/***
 * operation transpose on all sizes
 */

TEST_F(Matrix2x2, transpose)
{
    double res_mat[2][2] = {
        {10, 12},
        {-2, 99}
    };
    auto res = static_array_to_matrix(res_mat);

    EXPECT_EQ(mat.transpose(), res);
}

TEST_F(Matrix5x3, transpose)
{
    double res_mat[3][5];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            res_mat[i][j] = mat.get(j,i);
        }
    }

    auto res = static_array_to_matrix(res_mat);

    EXPECT_EQ(mat.transpose(), res);
}

TEST_F(Matrix3x6, transpose)
{
    double res_mat[6][3];

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            res_mat[i][j] = mat.get(j, i);
        }
    }

    auto res = static_array_to_matrix(res_mat);

    EXPECT_EQ(mat.transpose(), res);
}

/***
 * operation inverse on all sizes
 */

TEST_F(MatrixTest, inverse)
{
    //small test
    auto mat1x1 = Matrix(1,1);
    EXPECT_THROW(mat1x1.inverse(), std::runtime_error);

    //big test
    auto mat5x5 = Matrix(5,5);
    EXPECT_THROW(mat5x5.inverse(), std::runtime_error);

    //sinular test
    double singular_mat[2][2] = {
        {1, -2},
        {-2, 4}
    };
    auto singular = static_array_to_matrix(singular_mat);
    EXPECT_THROW(singular.inverse(), std::runtime_error);

    //clac on 2x2
    double mat1[2][2] = {
        {1, 2},
        {-2, 4}
    };
    
    double res1[2][2] = {
        {0.5, -0.25},
        {0.25,0.125}
    };
    auto mat2x2 = static_array_to_matrix(mat1);
    auto res2x2 = static_array_to_matrix(res1);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            EXPECT_NEAR(mat2x2.inverse().get(i,j) , res2x2.get(i,j), 0.00001);
        }
    }


    //clac on 3x3
    double mat2[3][3] = {
        {1, 2, 3},
        {-2, 4, 3},
        {1, 1, 1}
    };
    
    double res2[3][3] = {
        {-1/7.0,    -1/7.0,   6/7.0},
        {-5/7.0,     2/7.0,    9/7.0},
        {6/7.0,     -1/7.0,   -8/7.0}
    };
    auto mat3x3 = static_array_to_matrix(mat2);
    auto res3x3 = static_array_to_matrix(res2);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_NEAR(mat3x3.inverse().get(i,j) , res3x3.get(i,j), 0.00001);
        }
    }

}


/*** Konec souboru white_box_tests.cpp ***/

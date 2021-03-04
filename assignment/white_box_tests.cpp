//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author JMENO PRIJMENI
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

class Matrix2x2 : public ::testing::Test
{
protected:
    virtual void SetUp() {
        double value[2][2] = { 
            { 10, -2 },
            { 12, 99 }
        };

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                mat.set(i, j, value[i][j]);
            }
        }
    }

    Matrix mat = Matrix(2,2);
};

class EmptyMatrix  : public ::testing::Test
{
protected:
    Matrix mat;
};

TEST_F(EmptyMatrix, BadSetup)
{
    EXPECT_THROW(Matrix(0,1), std::runtime_error);
    EXPECT_THROW(Matrix(1,0), std::runtime_error);
    EXPECT_THROW(Matrix(-1,0), std::runtime_error);
}

TEST_F(Matrix2x2, SetValue)
{
    EXPECT_EQ(mat.set(0, 0, 10), true);

    //check is set
    EXPECT_DOUBLE_EQ(mat.get(0, 0), 10);

    EXPECT_EQ(mat.set(3, 0, 10), false);
    EXPECT_EQ(mat.set(0, 3, 10), false);
    EXPECT_EQ(mat.set(3, 3, 10), false);
}

TEST_F(Matrix2x2, SetVector)
{
    std::vector<std::vector< double > > toset;
    std::vector< double > line;

    line.push_back(1);
    line.push_back(2);

    toset.push_back(line);

    EXPECT_EQ(mat.set(toset), false);

    //for same size line 53 but fail on 58
    toset[0].push_back(3);
    toset[0].push_back(4);

    EXPECT_EQ(mat.set(toset), false);

    //now pass
    toset[0].pop_back();
    toset[0].pop_back();

    line.pop_back();
    line.pop_back();

    line.push_back(3);
    line.push_back(4);

    toset.push_back(line);

    EXPECT_EQ(mat.set(toset), true);

    //check values
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            EXPECT_DOUBLE_EQ(mat.get(i, j), toset[i][j]);
        }
    }
}

TEST_F(Matrix2x2, getValue)
{
    EXPECT_DOUBLE_EQ(mat.get(1, 1), 99);
    EXPECT_THROW(mat.get(-1, 1), std::runtime_error);
    EXPECT_THROW(mat.get(-1, -1), std::runtime_error);
    EXPECT_THROW(mat.get(1, -1), std::runtime_error);
}

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

    EXPECT_EQ((mat + add) == res, true);
}

TEST_F(Matrix2x2, operatorMULConst)
{
    
    double res_mat[2][2] = {
        {40, -8},
        {48, 396}
    };

    auto res = static_array_to_matrix(res_mat);

    EXPECT_EQ((mat * 4) == res, true);
}

/*** Konec souboru white_box_tests.cpp ***/

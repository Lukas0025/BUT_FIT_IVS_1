//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

/*** Konec souboru black_box_tests.cpp ***/
class NonEmptyRedBlack : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int keys[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 0, -10000, 10000, 55, -82, 62, 95, 100 };

        for(int i = 0; i < 17; ++i)
            EXPECT_EQ(tree.InsertNode(keys[i]).first, true);
    }

    BinaryTree tree;
};

class EmptyRedBlack : public ::testing::Test
{
protected:
    BinaryTree tree;
};

TEST_F(NonEmptyRedBlack, Insert)
{
    auto out = tree.InsertNode(-82);
    EXPECT_EQ(out.first, false);

    //exist?
    EXPECT_EQ(tree.FindNode(-82) == NULL, false);
    //value?
    EXPECT_EQ(tree.FindNode(-82)->key, -82);
    //return ptr
    EXPECT_EQ(out.second == NULL, false);
    EXPECT_EQ(out.second->key, -82);

    out = tree.InsertNode(96);
    EXPECT_EQ(out.first, true);

    //exist?
    EXPECT_EQ(tree.FindNode(96) == NULL, false);
    //value?
    EXPECT_EQ(tree.FindNode(96)->key, 96);
    //return ptr
    EXPECT_EQ(out.second == NULL, false);
    EXPECT_EQ(out.second->key, 96);
}

TEST_F(NonEmptyRedBlack, ExistInsert)
{
    auto out = tree.InsertNode(100);
    EXPECT_EQ(out.first, false);
    EXPECT_EQ(out.second == NULL, false);
    EXPECT_EQ(out.second->key, 100);

    out = tree.InsertNode(-82);
    EXPECT_EQ(out.first, false);
    EXPECT_EQ(out.second == NULL, false);
    EXPECT_EQ(out.second->key, -82);
}

TEST_F(NonEmptyRedBlack, Find)
{
    auto out = tree.FindNode(-82);
    EXPECT_EQ(out == NULL, false);
    EXPECT_EQ(out->key, -82);

    out = tree.FindNode(82);
    EXPECT_EQ(out == NULL, true);

    out = tree.FindNode(62);
    EXPECT_EQ(out == NULL, false);
    EXPECT_EQ(out->key, 62);

    out = tree.FindNode(-1234);
    EXPECT_EQ(out == NULL, true);
}

TEST_F(NonEmptyRedBlack, DeleteNode)
{
    auto out = tree.DeleteNode(-82);
    EXPECT_EQ(out, true);
    EXPECT_EQ(tree.FindNode(-82) == NULL, true);

    out = tree.DeleteNode(82);
    EXPECT_EQ(out, false);
    EXPECT_EQ(tree.FindNode(82) == NULL, true);

    out = tree.DeleteNode(62);
    EXPECT_EQ(out, true);
    EXPECT_EQ(tree.FindNode(62) == NULL, true);

    out = tree.DeleteNode(-1234);
    EXPECT_EQ(out, false);
    EXPECT_EQ(tree.FindNode(-1234) == NULL, true);

    /* axioms test */

}
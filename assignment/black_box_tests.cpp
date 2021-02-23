//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Lukáš Plevač <xpleva07@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Lukáš Plevač
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include <limits.h>

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

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int keys[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, -10000, 10000, 55, -82, 62, 95, 100 };

        for(int i = 0; i < 17; ++i)
            EXPECT_EQ(tree.InsertNode(keys[i]).first, true);
    }

    BinaryTree tree;
};

class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18, 10, 11, 12, 13, 14, 15, 16, 17, 18, -10000, 10000, 55, -82, 62, 95, 100 };

        for(int i = 0; i < 25; ++i)
            EXPECT_EQ(tree.InsertNode(keys[i]).first, true);
    }

    BinaryTree tree;
};

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

/**
 * Get number of black nodes from node to root
 * @param BinaryTree::Node_t * node
 * @return unsigned
 */
unsigned blackToRoot(BinaryTree::Node_t * node) {
    unsigned count = 0;
    
    while (node != NULL) {
        if (node->color == BinaryTree::Color_t::BLACK) {
            count++;
        }

        node = node->pParent;
    }

    return count;
}

TEST_F(NonEmptyTree, InsertNode)
{
    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        auto out = tree.InsertNode(keys[i]);
        EXPECT_EQ(out.first, true);

        //exist?
        EXPECT_EQ(tree.FindNode(keys[i]) == NULL, false);
        //value?
        EXPECT_EQ(tree.FindNode(keys[i])->key, keys[i]);
        //return ptr
        EXPECT_EQ(out.second == NULL, false);
        EXPECT_EQ(out.second->key, keys[i]);
    }

    //exist test
    auto out = tree.InsertNode(100);
    EXPECT_EQ(out.first, false);
    EXPECT_EQ(out.second == NULL, false);
    EXPECT_EQ(out.second->key, 100);

    out = tree.InsertNode(-82);
    EXPECT_EQ(out.first, false);
    EXPECT_EQ(out.second == NULL, false);
    EXPECT_EQ(out.second->key, -82);

}

TEST_F(NonEmptyTree, FindNode)
{

    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        tree.InsertNode(keys[i]);
        auto out = tree.FindNode(keys[i]);
        
        EXPECT_EQ(out == NULL, false);
        EXPECT_EQ(out->key, keys[i]);

        //we need empty tree for test
        tree.DeleteNode(keys[i]);
    }

    //not exist
    //původně vlatní test    
    for(int i = 0; i < 8; ++i) {
        auto out = tree.FindNode(keys[i]);
        EXPECT_EQ(out == NULL, true);
    }
}


TEST_F(NonEmptyTree, DeleteNode)
{
    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        tree.InsertNode(keys[i]);
        auto out = tree.DeleteNode(keys[i]);
        
        EXPECT_EQ(out, true);
        EXPECT_EQ(tree.FindNode(keys[i]) == NULL, true);
    }

    //not exist
    //původně vlatní test
    for(int i = 0; i < 8; ++i) {
        auto out = tree.DeleteNode(keys[i]);
        
        EXPECT_EQ(out, false);
        EXPECT_EQ(tree.FindNode(keys[i]) == NULL, true);
    }
}

/** 
 * empty tree tests
 */

TEST_F(EmptyTree, InsertNode)
{
    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        auto out = tree.InsertNode(keys[i]);
        EXPECT_EQ(out.first, true);

        //exist?
        EXPECT_EQ(tree.FindNode(keys[i]) == NULL, false);
        //value?
        EXPECT_EQ(tree.FindNode(keys[i])->key, keys[i]);
        //return ptr
        EXPECT_EQ(out.second == NULL, false);
        EXPECT_EQ(out.second->key, keys[i]);
    }
}

TEST_F(EmptyTree, FindNode)
{

    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        tree.InsertNode(keys[i]);
        auto out = tree.FindNode(keys[i]);
        
        EXPECT_EQ(out == NULL, false);
        EXPECT_EQ(out->key, keys[i]);

        //we need empty tree for test
        tree.DeleteNode(keys[i]);
    }

    //not exist
    //původně vlatní test    
    for(int i = 0; i < 8; ++i) {
        auto out = tree.FindNode(keys[i]);
        EXPECT_EQ(out == NULL, true);
    }
}


TEST_F(EmptyTree, DeleteNode)
{
    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        tree.InsertNode(keys[i]);
        auto out = tree.DeleteNode(keys[i]);
        
        EXPECT_EQ(out, true);
        EXPECT_EQ(tree.FindNode(keys[i]) == NULL, true);
    }

    //not exist
    //původně vlatní test
    for(int i = 0; i < 8; ++i) {
        auto out = tree.DeleteNode(keys[i]);
        
        EXPECT_EQ(out, false);
        EXPECT_EQ(tree.FindNode(keys[i]) == NULL, true);
    }
}

/**
 * Axioms tests
 */
TEST_F(TreeAxioms, Axiom1)
{
    std::vector<BinaryTree::Node_t *> leafs;
    tree.GetLeafNodes(leafs);

    for(unsigned i = 0; i < leafs.size(); i++) {
        EXPECT_EQ(leafs[i]->color, BinaryTree::Color_t::BLACK);
    }
}

TEST_F(TreeAxioms, Axiom2)
{
    std::vector<BinaryTree::Node_t *> all;
    tree.GetAllNodes(all); 

    for(unsigned i = 0; i < all.size(); i++) {
        if (all[i]->color == BinaryTree::Color_t::RED) {
            if (all[i]->pRight != NULL) {
                EXPECT_EQ(all[i]->pRight->color, BinaryTree::Color_t::BLACK);
            }

            if (all[i]->pLeft != NULL) {
                EXPECT_EQ(all[i]->pLeft->color, BinaryTree::Color_t::BLACK);
            }
        }
    }
}


TEST_F(TreeAxioms, Axiom3)
{
    std::vector<BinaryTree::Node_t *> leafs;
    tree.GetLeafNodes(leafs);

    if ( leafs.size() > 0) {
        unsigned firstCount = blackToRoot(leafs[0]);
        for(unsigned i = 1; i < leafs.size(); i++) {
            EXPECT_EQ(blackToRoot(leafs[i]), firstCount);
        }
    }
}

/*** Konec souboru black_box_tests.cpp ***/
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

/*** Konec souboru black_box_tests.cpp ***/
class NonEmptyRedBlack : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int keys[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, -10000, 10000, 55, -82, 62, 95, 100 };

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

void axiomsTest(BinaryTree *tree) {
    //1. všechny listy černé
    std::vector<BinaryTree::Node_t *> leafs;
    tree->GetLeafNodes(leafs);

    for(unsigned i = 0; i < leafs.size(); i++) {
        EXPECT_EQ(leafs[i]->color, BinaryTree::Color_t::BLACK);
    }

    //2. červený uzel pouze černé potomky
    std::vector<BinaryTree::Node_t *> all;
    tree->GetAllNodes(all); 

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

    //3. cesty od listu ke kořeni musím mít vždy stejný počet černých uzlů
    if ( leafs.size() > 0) {
        unsigned firstCount = blackToRoot(leafs[0]);
        for(unsigned i = 1; i < leafs.size(); i++) {
            EXPECT_EQ(blackToRoot(leafs[i]), firstCount);
        }
    }

}

TEST_F(NonEmptyRedBlack, Insert)
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

        axiomsTest(&tree);
    }

}

TEST_F(NonEmptyRedBlack, ExistInsert)
{
    auto out = tree.InsertNode(100);
    EXPECT_EQ(out.first, false);
    EXPECT_EQ(out.second == NULL, false);
    EXPECT_EQ(out.second->key, 100);
    axiomsTest(&tree);

    out = tree.InsertNode(-82);
    EXPECT_EQ(out.first, false);
    EXPECT_EQ(out.second == NULL, false);
    EXPECT_EQ(out.second->key, -82);
    axiomsTest(&tree);
}

TEST_F(NonEmptyRedBlack, FindExist)
{

    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        tree.InsertNode(keys[i]);
        auto out = tree.FindNode(keys[i]);
        
        EXPECT_EQ(out == NULL, false);
        EXPECT_EQ(out->key, keys[i]);

        axiomsTest(&tree);
    }
}

TEST_F(NonEmptyRedBlack, FindNotExist)
{

    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        auto out = tree.FindNode(keys[i]);
        EXPECT_EQ(out == NULL, true);

        axiomsTest(&tree);
    }
}


TEST_F(NonEmptyRedBlack, DeleteExistNode)
{
    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        tree.InsertNode(keys[i]);
        auto out = tree.DeleteNode(keys[i]);
        
        EXPECT_EQ(out, true);
        EXPECT_EQ(tree.FindNode(keys[i]) == NULL, true);

        axiomsTest(&tree);
    }
}

TEST_F(NonEmptyRedBlack, DeleteNotExistNode)
{
    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        auto out = tree.DeleteNode(keys[i]);
        
        EXPECT_EQ(out, false);
        EXPECT_EQ(tree.FindNode(keys[i]) == NULL, true);

        axiomsTest(&tree);
    }
}

/** 
 * empty tree tests
 */

TEST_F(EmptyRedBlack, Insert)
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

        axiomsTest(&tree);

        //we need empty tree for test
        tree.DeleteNode(keys[i]);
    }

}

TEST_F(EmptyRedBlack, FindExist)
{

    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        tree.InsertNode(keys[i]);
        auto out = tree.FindNode(keys[i]);
        
        EXPECT_EQ(out == NULL, false);
        EXPECT_EQ(out->key, keys[i]);

        axiomsTest(&tree);

        //we need empty tree for test
        tree.DeleteNode(keys[i]);
    }
}

TEST_F(EmptyRedBlack, FindNotExist)
{

    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        auto out = tree.FindNode(keys[i]);
        EXPECT_EQ(out == NULL, true);

        axiomsTest(&tree);
    }
}


TEST_F(EmptyRedBlack, DeleteExistNode)
{
    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        tree.InsertNode(keys[i]);
        auto out = tree.DeleteNode(keys[i]);
        
        EXPECT_EQ(out, true);
        EXPECT_EQ(tree.FindNode(keys[i]) == NULL, true);

        axiomsTest(&tree);
    }
}

TEST_F(EmptyRedBlack, DeleteNotExistNode)
{
    int keys[] = { INT_MAX, INT_MIN, 0, -76, 76, 54545, 456, -451, -18};
    
    for(int i = 0; i < 8; ++i) {
        auto out = tree.DeleteNode(keys[i]);
        
        EXPECT_EQ(out, false);
        EXPECT_EQ(tree.FindNode(keys[i]) == NULL, true);

        axiomsTest(&tree);
    }
}
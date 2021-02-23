//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    this->m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()
{
    //todo remove all elements
    auto el = this->GetHead();

    while (el != NULL) {
        auto tmp_next = el->pNext;
        delete el;
        el = tmp_next;
    }
}

void PriorityQueue::Insert(int value)
{
    auto next = this->GetHead();
    auto el    = new Element_t;

    el->value = value;

    //find correct postion
    PriorityQueue::Element_t *previous = NULL;
    while (next  != NULL) {
        if (next->value <= value) {
            break;
        }

        previous = next;
        next        = next->pNext;
    }

    //relink
    if (previous == NULL) {
        //first element

        el->pNext = NULL;
        if (next != NULL) {
            //not empty list
            el->pNext = next;
        }

        this->m_pHead = el;
    } else {
        el->pNext             = next;
        previous->pNext = el;
    }
}

bool PriorityQueue::Remove(int value)
{
    auto to_remove = this->Find(value);

    if (to_remove == NULL) {
        return false;
    }

    //re-link
    if (this->GetHead() == to_remove) {
        //on top
        this->m_pHead = to_remove->pNext;
    } else {
        //not on top have previous element
        auto previous = this->GetHead();

        while (previous->pNext != to_remove) {
            previous = previous->pNext;
        }

        previous->pNext = to_remove->pNext;
    }

    //remove element by pointer
    delete to_remove;

    return true;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    auto el = this->GetHead();
    while (el != NULL) {
        if (el->value == value) {
            return el;
        }

        el = el->pNext;
    }

    return NULL;
}

size_t PriorityQueue::Length()
{
    unsigned len = 0;
    auto el = this->GetHead();
    
    while (el != NULL) {
        len++;
        el = el->pNext;
    }

    return len;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return this->m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/

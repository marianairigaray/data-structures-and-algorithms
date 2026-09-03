#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "product.h"

// Node struct
typedef struct Node
{
    struct Node *prev;
    struct Node *next;
    Product data;
} Node;

// Doubly Linked List struct
typedef struct
{
    Node *head;
    Node *tail;
} DoublyLinkedList;

// Prototypes
void    initialize(DoublyLinkedList *l);
void    print(const DoublyLinkedList *l);
void    printReverse(const DoublyLinkedList *l);
Product search(const DoublyLinkedList *l, int id);
int     insertBeginning(DoublyLinkedList *l, Product prod);
int     insertEnd(DoublyLinkedList *l, Product prod);
int     removeById(DoublyLinkedList *l, int id);
void    destroy(DoublyLinkedList *l);
int     size(const DoublyLinkedList *l);
int     insertBefore(DoublyLinkedList *list, int id, Product prod);

#endif
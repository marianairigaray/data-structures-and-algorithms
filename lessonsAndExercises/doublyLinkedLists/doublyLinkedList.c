#include <stdio.h>
#include <stdlib.h>
#include "doublyLinkedList.h"
#include "product.h"

void initialize(DoublyLinkedList *l)
{
    l->head = NULL;
    l->tail = NULL;
}

void print(const DoublyLinkedList *l)
{
    Node *current = l->head;

    while (current != NULL)
    {
        printf("%d - %s - R$%.2f\n", current->data.id, current->data.name, current->data.price);
        current = current->next;
    }
}

void printReverse(const DoublyLinkedList *l)
{
    Node *current = l->tail;

    while (current != NULL)
    {
        printf("%d - %s - R$%.2f\n", current->data.id, current->data.name, current->data.price);
        current = current->prev;
    }
}

Product search(const DoublyLinkedList *l, int id)
{

}

int insertBeginning(DoublyLinkedList *l, Product prod)
{
    // Create new node
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) return 0;

    // Set new node values
    newNode->data = prod;
    newNode->prev = NULL;
    newNode->next = l->head;

    // If list is empty
    if (l->head == NULL)
        // New node is first and last node 
        l->tail = newNode;

    // If list is not empty
    else
        // Previous head points back to the new node
        l->head->prev = newNode;
    
    // New node becomes first node (list head)
    l->head = newNode;    
}

int insertEnd(DoublyLinkedList *l, Product prod)
{
    // Create new node
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) return 0;

    // Set new node values
    newNode->data = prod;
    newNode->prev = l->tail;
    newNode->next = NULL;

    // If list is empty
    if (l->head == NULL)
        // New node is first and last node 
        l->head = newNode;

    // If list is not empty
    else
        // Previous head points back to the new node
        l->tail->next = newNode;
    
    // New node becomes first node (list head)
    l->tail = newNode;    
}

int insertBefore(DoublyLinkedList *list, int id, Product prod) 
{
    // Create auxiliary node to help to iterate throuh the list
    Node *current = list->head;

    // Search for node id
    while(current != NULL && current->data.id != id)
    {
        // go to next node - iteration
        current = current->next;
    }

    // case didnt found the id
    if (current == NULL) return 0;

    // Create new node
    Node *new = (Node*) malloc(sizeof(Node));
    if (new == NULL) return 0;

    // Put node data
    new->data = prod;
    new->prev = current->prev; // new node prev field points to prev node
    new->next = current;       // new node next field points to "new" next node

    // first node
    if (current->prev == NULL)
    {
        list->head = new;
    }
    // node in the middle
    else 
    {
        // previus node points to new node
        current->prev->next = new;    
    }

    // current ant node points to new node
    current->prev = new;

    return 1;
}
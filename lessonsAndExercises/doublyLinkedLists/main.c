#include <stdio.h>
#include "doublyLinkedList.h"
#include "product.h"

// Prototypes
void logOperation(const int result, const char *fname);

int main ()
{
    printf("==============================\n");
    printf("Class 6a - Doubly Linked Lists\n\n");

    // Creates a doubly linked list called list
    DoublyLinkedList list;

    initialize(&list);

    // Creates 5 products
    Product products[5] = {
        {1, "Product A", 10.0f},
        {2, "Product B", 20.0f},
        {3, "Product C", 30.0f},
        {4, "Product D", 40.0f},
        {5, "Product E", 50.0f}   
    };

    // Insert products in the list
    for (int i = 0; i < 5; i++)
        insertEnd(&list, products[i]);

    // Prints the list of products
    printf("Products list: \n");
    print(&list);

    // EXERCISE 6

    Product p100 = { 8, "Product Z", 1000.0f };

    // Test 1: Insert before an existing ID - expected to return success
    int result = insertBefore(&list, 3, p100);
    logOperation(result, "insertBefore");

    // Test 2: Try to insert before a non-existing ID - expected to return error
    result = insertBefore(&list, 10, p100);
    logOperation(result, "insertBefore");

    // Prints the list of products
    printf("\nProducts list: \n");
    print(&list);
    
    return 0;
}

void logOperation(const int result, const char *fname)
{
    if (result) 
        printf("\nFunction %s returned successfully\n", fname);
    else 
        printf("\nFunction %s failed\n", fname);
}
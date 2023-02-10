#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *next;
    struct Node *prev;
};

typedef struct Node node;

int isEmpty ( node *head )
{
    return head == NULL;
}

node *printList ( node *head )
{
    if (isEmpty( head )) printf("List is empty\n");
    else 
    {
        printf("The list is");
        node *tmp = head;

        while (tmp != NULL)
        {
            printf("%d --> NULL\n", tmp->value);
            tmp = tmp->next;
        }
    }
}

node *printReverseList ( node *head )
{
    if (isEmpty( head )) printf("List is empty\n");
    else 
    {
        printf("The list is");
        node *tmp = head;

        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }

        while (tmp->prev != NULL)
        {
            printf("%d --> NULL\n", tmp->value);
            tmp = tmp->prev;
        }
    }
}

void instructions()
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
}

node *createNode ( int value )
{
    node *result = malloc(sizeof(node));
    result->value = value;
    result->next = NULL; 
    result->prev = NULL;
    return result; 
}

node *insert (node *node_to_insert_after, node* new_node)
{
    new_node->next = node_to_insert_after->next;
    node_to_insert_after->next->prev = new_node;
    new_node->prev = node_to_insert_after;
    node_to_insert_after->next = new_node;
}

node *removeNode ( node **head, node *node_to_remove)
{
    if(*head == node_to_remove)
    {
        node *tmp = *head;
        *head = node_to_remove->next;
        free(tmp);
    }
    else
    {
        node *tmp = *head;
        
        while (tmp != NULL && tmp->next != node_to_remove)
        {
            tmp->next;
        }
        // if (tmp == NULL) return;
        tmp->next = node_to_remove->next;
        tmp->next->prev = node_to_remove->prev;
        node_to_remove->next = NULL;
        free(node_to_remove);
    }
}

node *insert_node_at_head ( node **head, node *node_to_insert)
{
    node_to_insert->next = *head;
    (*head)->prev = node_to_insert;
    *head = node_to_insert;
    return node_to_insert; 
}

node *findNode ( node *head, int value)
{
    node *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->value == value) return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

int main (void)
{
    node *head = NULL;

    unsigned int choice;
    int item;

    instructions();
    printf( "%s", "? " );
    scanf( "%u", &choice );
    int counter = 0;
    while ( choice != 3 ) { 
        counter++;
        switch ( choice ) { 
            case 1:
            printf( "%s", "Enter a number: " );
            scanf( "%d", &item );
            if (counter == 1) insert_node_at_head( &head, createNode(item));
            else insert( head, createNode(item) ); // insert item in list
            printList( head );
            printReverseList( head );
            break;
            case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( head ) ) { 
                printf( "%s", "Enter number to be deleted: " );
                scanf( "%d", &item );
                // if character is found, remove it
                if ( removeNode( &head, createNode(item))) { // remove item
                    printf( "%d deleted.\n", item );
                    printList( head );
                } // end if
                else {
                    printf( "%d not found.\n\n", item );
                } // end else
            } // end if
            else {
                puts( "List is empty.\n" );
            } // end else

            break;
            default:
            puts( "Invalid choice.\n" );
            instructions();
            break;
        } // end switch

    printf( "%s", "? " );
    scanf( "%u", &choice );
   } // end while

    return 1;
}
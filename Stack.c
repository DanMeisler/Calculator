#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

void init( Stack *stackPtr )
{
    stackPtr->elements = NULL;
    stackPtr->size = 0;
    stackPtr->topIndex = -1;
}

void destroy( Stack *stackPtr )
{
    stackPtr->size = 0;
    stackPtr->topIndex = -1;
    free( stackPtr->elements );
}

void push( Stack *stackPtr, const Element element )
{
    Element *newElements = (Element *)realloc( stackPtr->elements, ( stackPtr->size + 1 ) * sizeof( Element ) );

    if( newElements == NULL )
        return;

    stackPtr->elements = newElements;
    stackPtr->elements[stackPtr->size] = element;
    stackPtr->size += 1;
    stackPtr->topIndex += 1;
}

Element pop( Stack *stackPtr )
{
    if( stackPtr->size <= 0 )
        return (Element){ .kind = END_OF_STACK_ELEMENT };

    Element poppedElement = stackPtr->elements[stackPtr->topIndex]; 
    stackPtr->size -= 1;
    stackPtr->topIndex -= 1;
    
    return poppedElement;
}

Element top( Stack *stackPtr )
{
    if( stackPtr->size <= 0 )
        return (Element){ .kind = END_OF_STACK_ELEMENT };

    return stackPtr->elements[stackPtr->topIndex];
}

uint8_t endOfStackElement( const Element element )
{
    if( element.kind == END_OF_STACK_ELEMENT )
        return 1;

    return 0;
}

void printStack( const Stack *stackPtr )
{
    printf( "Stack size = %u, topIndex = %d\n", stackPtr->size, stackPtr->topIndex );

    for( int32_t i = stackPtr->size - 1; i >= 0; --i )
    {
        if( stackPtr->elements[i].kind == NUMERIC_ELEMENT )
            printf( "%lf", stackPtr->elements[i].number );

        else if( stackPtr->elements[i].kind == CHARACTER_ELEMENT )
            printf( "%c", stackPtr->elements[i].character );

        printf( "\n---\n" );
    }
}



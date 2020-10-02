#pragma once
#include <stdint.h>

#define NUMERIC_ELEMENT 0
#define CHARACTER_ELEMENT 1
#define END_OF_STACK_ELEMENT 2
#define LAST_ELEMENT 3

typedef struct {
    uint8_t kind;
    double number;
    char character;
} Element;


typedef struct {
    Element *elements;
    uint32_t size;
    int32_t topIndex;
} Stack;


void init( Stack *stackPtr );

void destroy( Stack *stackPtr );

void push( Stack *stackPtr, const Element element );

Element pop( Stack *stackPtr );

Element top( Stack *stackPtr );

uint8_t endOfStackElement( const Element element );

void printStack( const Stack *stackPtr );

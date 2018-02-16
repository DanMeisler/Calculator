#include <stdio.h>
#include <ctype.h>
#include "Stack.h"

static Element parseNextElement()
{
	Element element;
	unsigned char currentChar;
	while( ( currentChar = getchar() ) == ' ' );
	int isNumber = isdigit( currentChar );
	ungetc( currentChar, stdin );

	if( isNumber )
	{
		element.kind = NUMERIC_ELEMENT;
		scanf( "%lf", &element.number );
	}
	else
	{ 
		currentChar = getchar();
		if( currentChar == '\n' )
		{
			element.kind = END_OF_STACK_ELEMENT;
		}
		else
		{
			element.kind = CHARACTER_ELEMENT;
			element.character = currentChar;
		}
	}

	return element;
}


int main( void )
{
	Stack stack;
	Element topElement;
	Element currentElement;
	Element newElement;
	int needParseNextElement = 1;
	char currentChar = 0;
	double currentNumber;
	init( &stack );

	printf( "Insert an equation:\n" );
	while( 1 )
	{
		if( needParseNextElement )
			currentElement = parseNextElement();
		else
			needParseNextElement = 1;

		if( currentElement.kind == END_OF_STACK_ELEMENT )
		{
			newElement.kind = NUMERIC_ELEMENT;
			newElement.number = 0;
			while( 1 )
			{
				topElement = pop( &stack );
				if( topElement.kind == END_OF_STACK_ELEMENT )
				{
					push( &stack, newElement );
					break;
				}
                else
				{
					if( topElement.kind != NUMERIC_ELEMENT )
						return 1;
					newElement.number += topElement.number;
				}
			}
			break;
				
		}
		else if( currentElement.kind == NUMERIC_ELEMENT )
		{
			topElement = top( &stack );
			if( topElement.kind == END_OF_STACK_ELEMENT )
			{
				push( &stack, currentElement );
			}
			else if( topElement.kind == CHARACTER_ELEMENT && topElement.character == '(' )
			{
				push( &stack, currentElement );
			}
			else if( topElement.kind == CHARACTER_ELEMENT && topElement.character == '+' )
			{
				pop( &stack );
				push( &stack, currentElement );
			}
	        else if( topElement.kind == CHARACTER_ELEMENT && topElement.character == '-' )
			{
				pop( &stack );
				currentElement.number *= -1;
				push( &stack, currentElement );
			}
			else if( topElement.kind == CHARACTER_ELEMENT && topElement.character == '*' )
			{
				pop( &stack );
				topElement = pop( &stack );
				newElement.kind = NUMERIC_ELEMENT;
				newElement.number = topElement.number * currentElement.number;
				push( &stack, newElement );
			}
            else if( topElement.kind == CHARACTER_ELEMENT && topElement.character == '/' )
			{
				pop( &stack );
				topElement = pop( &stack );
				newElement.kind = NUMERIC_ELEMENT;
				newElement.number = topElement.number / currentElement.number;
				push( &stack, newElement );
			}

		}
		else if( currentElement.kind == CHARACTER_ELEMENT )
		{
			switch( currentElement.character )
			{
				case ')':
					newElement.kind = NUMERIC_ELEMENT;
					newElement.number = 0;
					while( 1 )
					{
						 topElement = pop( &stack );
						 if( topElement.kind == END_OF_STACK_ELEMENT )
							 return 1;
						 else if( topElement.kind == CHARACTER_ELEMENT && topElement.character == '(' )
						 {
                             currentElement = newElement;
			 	             needParseNextElement = 0;
							 break;
						 }
						 else
						 {
							 newElement.number += topElement.number;
						 }
					}
					break;
				default:
					push( &stack, currentElement );
					break;
			}
		}
		printStack( &stack );
	}
    printStack( &stack );
	destroy( &stack );
	return 0;
}

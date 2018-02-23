#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Stack.h"

#define MAX_STRING_EQUATION_SIZE 1000


static Element *getElementsFromString( char *string )
{
	Element *elements = NULL, *newElements = NULL;
	uint32_t elementsCount = 0;
	uint32_t stringIndex = 0;
	uint32_t currentBytesRead = 0;

	while( string[stringIndex] != EOF )
	{
		newElements = (Element *)calloc( sizeof( Element ), elementsCount + 1 );

		if( !newElements )
			return NULL;

		memcpy( newElements, elements, sizeof( Element ) * elementsCount );

		if( elements )
		    free( elements );

		elements = newElements;

		while( string[stringIndex] == ' ' )
			++stringIndex;

		if( string[stringIndex] == '\n' )
		{
			elements[elementsCount].kind = LAST_ELEMENT;
			break;
		}
		else if( isdigit( string[stringIndex] ) )
		{
			elements[elementsCount].kind = NUMERIC_ELEMENT;
			sscanf( string + stringIndex, "%lf%n", &( elements[elementsCount].number ), &currentBytesRead );
		}
		else
		{ 
			elements[elementsCount].kind = CHARACTER_ELEMENT;
			elements[elementsCount].character = string[stringIndex];
			currentBytesRead = 1;
		}

		++elementsCount;
		stringIndex += currentBytesRead;
	}

	return elements;
}

static char matchingParenthesis( char closing )
{
	switch( closing )
	{
		case ')':
			return '(';
		case ']':
			return '[';
		case '}':
			return '{';
	}
	return '\0';
}

static int sumUp( Stack *stack, char closingParenthesis, double *result )
{
	Element topElement;
	double sum = 0;

	while( 1 )
	{
		topElement = pop( stack );

		if ( topElement.kind == NUMERIC_ELEMENT )
		{	
			sum += topElement.number;
			continue;
		}

		switch( closingParenthesis )
		{
			case '\0':
				if( topElement.kind == END_OF_STACK_ELEMENT )
				{
					*result = sum;
					return 1;
				}
				break;

			case ')':
			case ']':
			case '}':
				if( topElement.kind == CHARACTER_ELEMENT && topElement.character == matchingParenthesis( closingParenthesis ) ) 
				{
					*result = sum;
					return 1;
				}
				break;
		}

		return 0;
	}

	return 0; 
}

static int evaluate( char *stringEquation, double *result )
{
	Stack stack;
	Element *elements;
	Element topElement,currentElement, newElement;
	uint32_t currentElementIndex = 0;

	init( &stack );

	elements = getElementsFromString( stringEquation );

	currentElement = elements[0];

	while( currentElement.kind != LAST_ELEMENT )
	{
		if( currentElement.kind == NUMERIC_ELEMENT )
		{
			topElement = top( &stack );
            
			switch( topElement.kind )
			{
				case END_OF_STACK_ELEMENT:
					push( &stack, currentElement );
					break;
				
				case NUMERIC_ELEMENT:
					return 0;

				case CHARACTER_ELEMENT:
					switch( topElement.character )
					{
						case '(':
						case '[':
						case '{':
				            push( &stack, currentElement );
							break;
						
						case '+':
                        	pop( &stack );
							push( &stack, currentElement );
							break;

						case '-':
                        	pop( &stack );
							currentElement.number *= -1;
							push( &stack, currentElement );
							break;

						case '*':
							pop( &stack );
				 			topElement = pop( &stack );
							newElement.kind = NUMERIC_ELEMENT;
							newElement.number = topElement.number * currentElement.number;
							push( &stack, newElement );
							break;

						case '/':
							pop( &stack );
							topElement = pop( &stack );
							newElement.kind = NUMERIC_ELEMENT;
							newElement.number = topElement.number / currentElement.number;
							push( &stack, newElement );
							break;

					}
			}
		}
		else if( currentElement.kind == CHARACTER_ELEMENT )
		{
			switch( currentElement.character )
			{
				case ')':
				case ']':
				case '}':
					newElement.kind = NUMERIC_ELEMENT;
					if( !sumUp( &stack, currentElement.character, &( newElement.number ) ) )
						return 0;
					currentElement = newElement;
					continue;
				default:
					push( &stack, currentElement );
					break;
			}
		}

		// printStack( &stack );
	    currentElement = elements[++currentElementIndex];
	}

	free( elements );

	if( !sumUp( &stack, '\0', result ) )
	{
		destroy( &stack );
		return 0;
	}

	destroy( &stack );
	return 1;
}

int main( void )
{
	char stringEquation[MAX_STRING_EQUATION_SIZE] = { 0 };
	double result;

	printf( "Insert an equation:\n" );

	fgets( stringEquation, MAX_STRING_EQUATION_SIZE, stdin );

	if( !evaluate( stringEquation, &result ) )
	{
		printf( "Some error occurred\n" );
		return 1;
	}

	printf( "result = %lf\n", result );

	return 0;
}

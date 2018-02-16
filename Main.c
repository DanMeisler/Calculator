#include <stdio.h>
#include "Stack.h"

int main( void )
{
	Stack stack;
	Element a = { 0, 3, 0 };
	init( &stack );
	printStack( &stack );
	push( &stack, a ); 
	printStack( &stack );
	a = pop( &stack );
	printStack( &stack );
	push( &stack, a ); 
	printStack( &stack );
	destroy( &stack );
	printStack( &stack );
	return 0;
}

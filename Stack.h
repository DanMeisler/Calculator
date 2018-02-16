typedef struct {
    int kind;
    double num;
    char ch;
} Element;


typedef struct {
    Element *content;
    int size;
    int topIndex;
} Stack;


void init(Stack* stackPtr);

void destroy(Stack* stackPtr);

void push(Stack* stackPtr, Element element);

Element pop(Stack *stackPtr);

Element top(Stack *stackPtr);

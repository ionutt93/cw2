/* Below is a string (char array) Stack in C with push, pop and peek functions.
The main function shows how this stack can be implemmented*/

#include <stdio.h>
#define ARRAY_SIZE 6

typedef struct stak{
    char *content[ARRAY_SIZE];
    int top;
} myStack;


int size(myStack s)
{
    return s.top;
}

// boolean function to check whether stack is empty or not
int isEmpty(myStack *s)
{
    if (s->top == -1)
    {
        return 1;
    }
    else if (s->top > -1)
    {
        return 0;
    }
    return -1;
}

// boolean function to check whether stack is full or not
int isFull(myStack *s) {
    if (s->top == (ARRAY_SIZE-1))
    {
        return 1;
    }
    else {
        return 0;
    }
}

// function to return the top element of the stack
char* peek(myStack *s)
{
    if (isEmpty(s) == 1)
    {
        printf("Can't peek: Stack is empty!\n");
        return "";
    }
    else {
        return s->content[s->top];
    }
}

// function to add an element to the stack
void push(myStack *s, char *element)
{
    if (isFull(s) == 1)
    {
        printf("Cant push: Stack is full!\n");
    }
    else {
        s->top++;
        s->content[s->top] = element;
    }
}

// function to remove the top element of the stack 
void pop(myStack *s)
{
    if (isEmpty(s) == 1) {
        printf("Cant pop: Stack is empty!\n");
    }
    else {
        s->content[s->top] = "\0";
        s->top--;
    }
}

// function to print the entire stack
void printStack(myStack *s)
{
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
    }
    else {
        for (int i=s->top; i>-1; i--)
        {
            printf("%s\n", s->content[i]);
        }
        
        printf("\n");
    }
}

int main()
{
    myStack aStack;
    aStack.top = -1;
    
    // adds 'cat', 'dog' and 'chicken' to the stack
    printf("Push Stack!\n");
    push(&aStack, "cat");
    push(&aStack, "dog");
    push(&aStack, "chicken");
    printStack(&aStack); // prints the entire stack

    
    printf("Pop Stack!\n");
    pop(&aStack); // pops top element off stack which should be 'chicken'
    printStack(&aStack); // should print only 'dog' and 'cat'
    
    printf("Peek Stack: %s\n", peek(&aStack)); // returns top element of stack aka 'dog'

    
    return 0;
}


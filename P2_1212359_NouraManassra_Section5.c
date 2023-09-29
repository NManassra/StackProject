#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 100
/// Name : Noura Awni Jaber Manassra
/// ID   : 1212359
/// Instructor : Dr. Anas Arram
///Section : 5


int top = -1;
char stack[MAX]; // this is the one that will be used to check the validity
int stackNumbers[MAX]; // this is the stack used for evaluation
int topN = -1;

void pushN(int data) { // this to push numbers
    topN++;
    stackNumbers[topN] = data;
}

int popN() { // this to delete number and return the deleted one
    int value = stackNumbers[topN];
    topN--;
    return value;
}

void pushLetter(char data) { // to insert an elemnt to the stack
    top++;
    stack[top] = data;
}

char popLetter() {// to delete an elemnt to the stack
    char value = stack[top];
    top--;
    return value;
}

void printStackLetter() { //print the stack
    int i;
    if (top == -1)
        return;
    for (i = 0; i <= top; i++)
        printf("%c ", stack[i]);
    printf("\n");
}

void makeStackEmpty() { // makes the stack empty
    top = -1; // Reset the top index to -1
}

int isEmptyLetter() { // checks if the stack empty or not
    if (top == -1)
        return 1;
    else
        return 0;
}

int matchLetter(char a, char b) { // checks if the brackets match each other or not
    if (a == '[' && b == ']')
        return 1;
    if (a == '(' && b == ')')
        return 1;
    if (a == '{' && b == '}')
        return 1;
    return 0;
}

int checkBalance(char *s) { // checks if the equation is balanced or not
    char temp;
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] == '[' || s[i] == '{' || s[i] == '(')
            pushLetter(s[i]);
        else if (s[i] == ']' || s[i] == '}' || s[i] == ')') {
            if (isEmptyLetter()) {
                printf("Right brackets are more than the left ones\n");
                return 0;
            }
            temp = popLetter();
            if (!matchLetter(temp, s[i])) {
                printf("MisMatched brackets!\n");
                return 0;
            }
        } else if (s[i] >= '0' && s[i] <= '9' && i > 2) {
            if ((s[i - 1] == '[' || s[i - 1] == ']' || s[i - 1] == '{' || s[i - 1] == '}' || s[i - 1] == '(' ||
                 s[i - 1] == ')') && (s[i - 2] >= '0' && s[i - 2] <= '9')) {
                printf("Invalid equation: No operator between two numbers\n");
                return 0;
            }
        } else if (i == 0 && (s[i] == '/' || s[i] == '*')) {
            printf("The first operation should be true!\n");
            return 0;
        } else if (i > 0 &&
                   ((s[i] == '*' && s[i + 1] == '+') || (s[i] == '*' && s[i + 1] == '-') || (s[i] == '/' && s[i + 1] == '+') ||
                    (s[i] == '/' && s[i + 1] == '-'))) {
            printf("The operations shouldn't be next to each other like this!!\n");
            return 0;
        }
        i++;
    }
    if (isEmptyLetter() == 1) {
        printf("Brackets are well balanced\n");
        return 1;
    } else {
        printf("Left Brackets are more than the right ones\n");
        return 0;
    }
}

int priority(char op) { // checks the priority of the operations
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '^')
        return 3;
    else if (op == '_')
        return 3;
    return 0;
}

int OpLetter(char op) { // the function returns an integer value: 1 if the character is an operand, and 0 if it is not.
    if ((op >= '0' && op <= '9') || (op >= 'A' && op <= 'Z') || (op >= 'a' && op <= 'z'))
        return 1;
    else
        return 0;
}

void reverseLetters(char *str1) { //reverse the string to get the prefix
    int i, len, temp;
    len = strlen(str1); // use strlen() to get the length of str string


    for (i = 0; i < len / 2; i++) {
         //temp variable use to temporarily hold the string
        temp = str1[i];
        str1[i] = str1[len - i - 1];
        str1[len - i - 1] = temp;
    }
}

int isdigitt(char c) { // checks if this char is a digit or not
    return (c >= '0' && c <= '9');
}

int isOperation(char c) { // checks if this char is an operation or not
    if (c =='*' || c=='+' || c=='^' || c=='-' || c=='/' ||c=='_' ) return 1;
    else return 0;
}


void preConverter(char *VALID, char *PRE) { //convert the infix to prefix
    makeStackEmpty();
    int i, j;
    char temp; // this is the char which will be sorting the data inside the new pre
// ------------> The idea is to use two pointers, so if there is an operation needs higher priority should be added first
    reverseLetters(VALID);
    for (i = 0, j = 0; VALID[i] != '\0'; i++) {
        temp = VALID[i];
        if (OpLetter(temp)) { // the idea here is to check if it's a letter or number, so if it's a number or letter, it will be added to the new pre
            PRE[j++] = temp;
        }

//        -----------> Here is the most important one, which will work when it's not empty, and priority of the operator at the top of the stack (stack[top]) is greater than the priority of the current operator
        else if (temp == '+' || temp == '-' || temp == '*' || temp == '/' || temp == '^' ||temp == '_') {
            while (top >= 0 && priority(stack[top]) > priority(temp)) {
                 PRE[j++] = popLetter(); // pops the operator at the top of the stack and adds it to the prefix expression. This ensures that operators with higher priority are placed in the prefix expression before operators with lower priority

            }
                if (!(isOperation(PRE[j-1])&& isOperation(PRE[j])))
                PRE[j++] = ' ';
            pushLetter(temp);
        }

//        -----------> The idea here is, since I reversed the string, I have to reverse its symbols again to have a true logical equation
        else if (temp == ')') {
            pushLetter(temp);
        }
          else if (temp == '(') {
            while (top >= 0 && stack[top] != ')') {
                PRE[j++] = popLetter();
            }

            if (top >= 0 && stack[top] == ')') {
                popLetter();
            }
        }
        else if (temp == ']') {
            pushLetter(temp);
        }
        else if (temp == '[') {
            while (top >= 0 && stack[top] != ']') {
                PRE[j++] = popLetter();
            }

            if (top >= 0 && stack[top] == ']') {
                popLetter();
            }
        }
    }

    while (top >= 0) {
        PRE[j++] = popLetter();
    }
    PRE[j] = '\0';
    reverseLetters(PRE);


}

int preEvaluation(char *pre) { // this is the one which will convert the prefix into it's final result
    char s[100][MAX]; // i made a opy so the original one won't change
    strcpy(s[0], pre);
    topN = -1; // to clear the current one and make sure that there is no random data
    reverseLetters(s[0]);
    int len = strlen(pre);
    int result = 0;
    for (int i = 0; i < len; i++) {
        int temp = 0; // this one at it the data will be stored at
        //these if statments in case it's multi digits
        if (isdigit(s[0][i])) {
            temp = s[0][i] - '0';
            if (isdigit(s[0][i + 1])) {
                int temp2 = s[0][i + 1] - '0';
                temp = temp2 * 10 + temp;
                i++;
            }
            pushN(temp);
        }
        if (isOperation(s[0][i])) {
            char c = s[0][i];
            int op1=0, op2=0;
            if (c=='+' || c=='-' || c=='^'  || c=='*'  || c=='/'  )
           {
            op1 = popN();
            op2 = popN();
           }

            if (c=='_') {op1 = popN();result = op1 *-1;}
            if (c == '+') {
                result = op1 + op2;
            }
            if (c == '-') {
                result = op1 - op2;
            }
            if (c == '/') {
                result = op1 / op2;
            }
            if (c == '*') {
                result = op1 * op2;
            }
            if (c == '^') {
                result = pow(op2, op1);
            }
            pushN(result);
        }
    }
    return result;
}

void handleNegativeNumbers(char *equation) {
    char temp[100];
    int counter = 0;

    for (int i = 0; equation[i] != '\0'; i++) {
        if (equation[i] == '-' && (i == 0 || equation[i - 1] == '(' || equation[i - 1] == '[' || equation[i - 1] == '{')) {
           temp[counter] = '(';            ++counter;
            temp[counter] = '_';
            ++counter;
            temp[counter] = '_';

            while (isdigitt(equation[i])) {
                counter++;
                temp[counter] = equation[i];
                i++;
            }

            temp[counter] = ')';
        }
        else {
            temp[counter] = equation[i];
        }

        counter++;
    }

    temp[counter] = '\0';
    strcpy(equation, temp);
}

int main() {
     FILE* file2 = fopen("output.txt", "w");
    char NAME[100] = "";
    int balance = 0;
    char FullArray[100][MAX];
    char expr[MAX];
    char INVALID[100][MAX];
    char VALID[100][MAX];
    char VALID2[100][MAX];
    char pre2[100][MAX];
    char PRE[100][MAX];
    int FinalResults [MAX];
    while (1) {
        printf("Welcome, please choose what you need to do ?\n1.Read the equations from a file.\n2.Check the validity\n3.Convert valid equations from infix to prefix and print the prefix.\n4.Evaluate the prefix.\n5.Print invalid equations.\n6.Print all equations to a file.\n7.Exit\n");
        int x = 0;
        scanf("%d", &x);
        switch (x) {
            case 1:
//                print the equations

                printf("Please enter the name of the file you need to scan from:\n");
                scanf("%s", NAME);
                FILE *file = fopen(NAME, "r");
                if (file == NULL) {
                    printf("Failed to open the file.\n");
                    exit(0);
                }

                int counter = 0;
                while (fgets(expr, MAX, file) != NULL) {
                    strcpy(FullArray[counter], expr);
                    counter++;
                }
                printf("Here are the equations from the file:\n");
                for (int i = 0; i < counter; i++) {
                handleNegativeNumbers(FullArray[i]);
                printf("Equation %d: %s", i + 1, FullArray[i]);
                }
//                 check the validity
                printf("\n\n");
                break;
            case 2:

                for (int i = 0; i < counter; i++) {
                    makeStackEmpty();
                    printf("For Equation No.%d : ", i + 1);
                    balance = checkBalance(FullArray[i]);
                    if (balance == 1) {
                        strcpy(VALID[i], FullArray[i]);
                        strcpy(VALID2[i], FullArray[i]);
                        printf("The equation is valid.\n\n");
                    } else {
                        strcpy(INVALID[i], FullArray[i]);
                        printf("The equation is invalid.\n\n");
                    }

                }
                break;
            case 3:

                printf("Here are the valid equations after converting them into prefix.\n");
                for (int i = 0; i < counter; i++) {

                    preConverter(VALID[i], PRE[i]);
                }
                for (int i = 0; i < counter; i++) {
                    printf("%s", PRE[i]);
                    printf("\n");
                    strcpy(pre2[i], PRE[i]);
                }
                break;
            case 4:
                printf("Here are the result of the equations after evaluation them as prefix equations \n");
                for (int i = 0; i < counter; i++) {
                    FinalResults[i] = preEvaluation(PRE[i]) ;
                    printf("%d", preEvaluation(PRE[i]) );
                    printf("\n");
                }
                break;
            case 5:
                printf("Here are the invalid Equations : \n");
                for (int i = 0; i < counter; i++) {
                    printf("%s", INVALID[i]);
                    printf("\n");
                }
                break;
            case 6 :
                fprintf(file2,"The valid EQUATIONS ARE : \n\n");
                for (int i = 0; i < counter; i++) {
                    fprintf(file2,"%s",VALID2[i]);
                    fprintf(file2,"\n");
                    }
                fprintf(file2,"The invalid EQUATIONS ARE : \n\n");
                for (int i=0;i<counter;i++)
                {
                    fprintf(file2,"%s",INVALID[i]);
                    fprintf(file2,"\n");
                }
                fprintf(file2,"Here are the valid equations after converting them into prefix.\n");
                for (int i = 0; i < counter; i++) {
                    fprintf(file2,"%s",pre2[i] );
                    fprintf(file2,"\n");
                }
                fprintf(file2,"Here are the results of the valid equation after converting them into prefix.\n");
                for (int i = 0; i < counter; i++) {
                    fprintf(file2,"%d", FinalResults[i] );
                    fprintf(file2,"\n");
                }
               fclose(file2);
               printf ("Print succeed ! :) \n");
               break;
            case 7:
                exit(0);
        }
    }
    return 0;
}

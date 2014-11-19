#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sy_parser.h"

#define YES 1
#define NO 0

#define STREQU(a, b) ( strcmp( (a) , (b) ) == 0 )

typedef enum sy_node_type {GARBAGE, OPERATOR, FUNCTION, NUMBER, VARIABLE, L_PAREN, R_PAREN, L_BRACKET, R_BRACKET} sy_node_type_t;
typedef enum sy_operator_type {ADD, SUBTRACT, DIVIDE, MULTIPLY, POWER} sy_operator_type_t;
typedef enum sy_function_type {SIN, COS, RAND, ABS, TAN, ACOS, ASIN, ATAN, COSH, SINH, TANH, EXP, LOG, SQRT, CEIL, FLOOR} sy_function_type_t;

typedef int BOOL;

typedef struct sy_node {
    struct sy_node *next;
    struct sy_node *prev;
    struct sy_node *left;
    struct sy_node *right;
    sy_node_type_t type;
    union {
        sy_operator_type_t operator;
        sy_function_type_t function;
        double num_value;
    } token;
} sy_node_t;

BOOL is_alpha_numeric(char c)
{
    if(c >= '0' && c <= '9')
        return YES;
    if(c >= 'a' && c <= 'z')
        return YES;
    if(c >= 'A' && c <= 'Z')
        return YES;
    
    return c == '.' || c == '[';
}

BOOL is_numeric(char c)
{
    return c >= '0' && c <= '9';
}
//                                    node        , opstack
BOOL operator_is_of_higher_precedance(sy_node_t *a, sy_node_t *b)
{
    // Handle the parens
    if(a->type == L_PAREN)
        return NO;
    if(a->type == R_PAREN)
        return b->type != L_PAREN;

    // Handle functions and brackets
    if(a->type == FUNCTION)
        return NO;
    if(a->type == R_BRACKET)
        return b->type != FUNCTION;

    if(a->type != OPERATOR || b->type != OPERATOR)
        return NO;

    sy_operator_type_t ao = a->token.operator;
    sy_operator_type_t bo = b->token.operator;

    if(bo == POWER && ao != POWER)
        return YES;
    if((bo == MULTIPLY || bo == DIVIDE) && (ao == ADD || ao == SUBTRACT))
        return YES;
    return NO;
}

sy_node_t *make_node_from_string(char *str)
{
    if(!strlen(str))
        return NULL;

    sy_node_t *node = malloc(sizeof(sy_node_t));
    node->next = NULL;
    node->prev = NULL;
    node->left = NULL;
    node->right = NULL;

    char *top = str;
    while(*top == '-')
        top++;

    if(is_numeric(top[0]))
    {
        node->type = NUMBER;
        node->token.num_value = atof(str);
    }
    else
    {
        node->type = FUNCTION;

        if(STREQU(str, "Abs["))
            node->token.function = ABS;
        else if(STREQU(str, "Sin["))
            node->token.function = SIN;
        else if(STREQU(str, "Cos["))
            node->token.function = COS;
        else if(STREQU(str, "Tan["))
            node->token.function = TAN;
        else if(STREQU(str, "Rand["))
            node->token.function = RAND;
        else if(STREQU(str, "ArcCos["))
            node->token.function = ACOS;
        else if(STREQU(str, "ArcSin["))
            node->token.function = ASIN;
        else if(STREQU(str, "ArcTan["))
            node->token.function = ATAN;
        else if(STREQU(str, "Cosh["))
            node->token.function = COSH;
        else if(STREQU(str, "Sinh["))
            node->token.function = SINH;
        else if(STREQU(str, "Tanh["))
            node->token.function = TANH;
        else if(STREQU(str, "Exp["))
            node->token.function = EXP;
        else if(STREQU(str, "Log["))
            node->token.function = LOG;
        else if(STREQU(str, "Sqrt["))
            node->token.function = SQRT;
        else if(STREQU(str, "Ceil["))
            node->token.function = CEIL;
        else if(STREQU(str, "Floor["))
            node->token.function = FLOOR;
        else
            node->type = GARBAGE;
    }

    return node;
}

sy_node_t *make_node_from_char(char c)
{
    sy_node_t *node = malloc(sizeof(sy_node_t));
    node->next = NULL;
    node->prev = NULL;
    node->left = NULL;
    node->right = NULL;

    switch(c)
    {
    case '+':
        node->type = OPERATOR;
        node->token.operator = ADD;
        break;
    case '-':
        node->type = OPERATOR;
        node->token.operator = SUBTRACT;
        break;
    case '/':
        node->type = OPERATOR;
        node->token.operator = DIVIDE;
        break;
    case '*':
        node->type = OPERATOR;
        node->token.operator = MULTIPLY;
        break;
    case '^':
        node->type = OPERATOR;
        node->token.operator = POWER;
        break;
    case '(':
        node->type = L_PAREN;
        break;
    case ')':
        node->type = R_PAREN;
        break;
    case '[':
        node->type = L_BRACKET;
        break;
    case ']':
        node->type = R_BRACKET;
        break;
    case '$':
        node->type = VARIABLE;
        break;
    default:
        node->type = GARBAGE;
        break;
    }

    return node;
}

sy_node_t *pop(sy_node_t **stack)
{
    sy_node_t *head = *stack;
    if(head)
    {
        *stack = (*stack)->next;
        head->next = NULL;
    }
    return head;
}

void push(sy_node_t **stack, sy_node_t *page)
{
    page->next = *stack;
    *stack = page;
}

void sy_convert_to_tree(sy_node_t **node)
{
    sy_node_t *start = *node;
    sy_node_t *last = start;
    while(start)
    {
        sy_node_t *next = start->next;
        if(start->type == OPERATOR)
        {
            sy_node_t *a = start->prev->prev;
            sy_node_t *b = start->prev;

            start->left = a;
            start->right = b;
            start->prev = a->prev;
        }
        if(start->type == FUNCTION)
        {
            sy_node_t *a = start->prev;
            start->left = a;
            start->prev = a->prev;
        }
        start = next;

        if(next)
            last = next;
    }

    *node = last;
}

void sy_list_free(sy_node_t *node)
{
    while(node)
    {
        sy_node_t *next = node->next;
        free(node);
        node = next;
    }
}

void handle_error(sy_error_t *err, char *message, int index)
{
    if(!err)
    {
        printf("Error at %d: %s\n", index, message);
        exit(0);
    }
    else
    {
        err->message = message;
        err->location = index;
    }
}

sy_node_t *sy_parse_string(char *str, sy_error_t *err)
{
    sy_node_t *head = NULL;
    sy_node_t *cur = NULL;

    BOOL treatMinusAsNegative = YES;

    sy_node_t *opstack = NULL;

    int index = -1;

    char strtmp[strlen(str) + 1];
    strcpy(strtmp, "");
    char c;
    while((c = *str++))
    {
        index++;
        if(is_alpha_numeric(c) || (c == '-' && treatMinusAsNegative))
        {
            treatMinusAsNegative = NO;
            sprintf(strtmp, "%s%c", strtmp, c);

            if(c != '[')
                continue;
        }

        sy_node_t *node = NULL;

        if(strlen(strtmp) > 0)
        {
            node = make_node_from_string(strtmp);
            strcpy(strtmp, "");

            if(node->type == NUMBER || node->type == VARIABLE)
            {
                if(!head)
                {
                    head = node;
                    cur = node;
                }
                else
                {
                    cur->next = node;
                    node->prev = cur;
                    cur = node;
                }
            }
        }

        if(c == ' ' && (!node || node->type == NUMBER || node->type == VARIABLE))
            continue;

        if(!node || node->type == NUMBER || node->type == VARIABLE)
            node = make_node_from_char(c);

        if(node->type == GARBAGE)
        {
            sy_list_free(opstack);
            sy_list_free(head);
            free(node);

            handle_error(err, "Invalid token.", index);
            return NULL;
        }

        treatMinusAsNegative = node->type == OPERATOR || node->type == FUNCTION;

        if(node->type == VARIABLE)
        {
            if(!head)
            {
                head = node;
                cur = node;
            }
            else
            {
                cur->next = node;
                node->prev = cur;
                cur = node;
            }
            continue;
        }

        // if(!opstack)
        // {
        //     opstack = node;

        //     continue;
        // }

        while(opstack && operator_is_of_higher_precedance(node, opstack))
        {
            sy_node_t *next = pop(&opstack);

            cur->next = next;
            cur = cur->next;
        }

        if(node->type == R_PAREN)
        {
            if(!opstack)
            {
                sy_list_free(head);
                free(node);
                handle_error(err, "Extra parenthesis.", index);
                return NULL;
            }
            free(pop(&opstack));
        }

        if(node->type != R_PAREN && node->type != R_BRACKET)
            push(&opstack, node);
        else
            free(node);
    }

    if(strlen(strtmp) > 0)
    {
        sy_node_t *node = make_node_from_string(strtmp);
        strcpy(strtmp, "");

        if(node->type == GARBAGE)
        {
            sy_list_free(opstack);
            sy_list_free(head);
            free(node);

            handle_error(err, "Invalid token.", index);
            return NULL;
        }

        if(!head)
        {
            head = node;
            cur = node;
        }
        else
        {
            cur->next = node;
            node->prev = cur;
            cur = node;
        }
    }

    while(opstack)
    {
        sy_node_t *next = pop(&opstack);

        if(next->type == L_PAREN)
        {
            free(next);
            sy_list_free(opstack);
            sy_list_free(head);
            handle_error(err, "Missing closing parenthesis.", index + 1);
            return NULL;
        }

        cur->next = next;
        cur = cur->next;
    }

    sy_node_t *n = head;
    while(n)
    {
        if(n->next)
            n->next->prev = n;
        n = n->next;
    }

    sy_convert_to_tree(&head);

    return head;
}

float malloctime = 0;

sy_node_t *sy_copy(sy_node_t *node)
{
    
    sy_node_t *head = NULL;
    sy_node_t *cur = NULL;

    for(; node; node = node->next)
    {
        sy_node_t *next = malloc(sizeof(sy_node_t));
        ///emcpy(next, node, sizeof(sy_node_t));
        next->type = node->type;
        next->token = node->token;
        next->next = NULL;
        if(!head)
        {
            head = next;
            cur = head;
        }
        else
        {
            cur->next = next;
            next->prev = cur;
            cur = next;
        }
    }

    return head;
}

void sy_free(sy_node_t *node)
{
    if(node->left)
        sy_free(node->left);
    if(node->right)
        sy_free(node->right);

    free(node);
}

double sy_evaluate(sy_node_t *start, double var)
{
    if(start->type == NUMBER)
        return start->token.num_value;
    else if(start->type == VARIABLE)
        return var;

    if(start->type == OPERATOR)
    {
        double a = sy_evaluate(start->left, var);
        double b = sy_evaluate(start->right, var);
        switch(start->token.operator)
        {
        case ADD:
            return a + b;
        case SUBTRACT:
            return a - b;
        case MULTIPLY:
            return a * b;
        case DIVIDE:
            return a / b;
        case POWER:
            return pow(a, b);
        }
    }

    if(start->type == FUNCTION)
    {
        double a = sy_evaluate(start->left, var);
        switch(start->token.function)
        {
        case ABS:
            return fabs(a);
        case SIN:
            return sin(a);
        case COS:
            return cos(a);
        case TAN:
            return tan(a);
        case RAND:
            return rand() % (abs((long)a) + 1);
        case ACOS:
            return acos(a);
        case ASIN:
            return asin(a);
        case ATAN:
            return atan(a);
        case COSH:
            return cosh(a);
        case SINH:
            return sinh(a);
        case TANH:
            return tanh(a);
        case EXP:
            return exp(a);
        case LOG:
            return log(a);
        case SQRT:
            return sqrt(a);
        case CEIL:
            return ceil(a);
        case FLOOR:
            return floor(a);
        }
    }

    return 0;
}

double sy_evaluate_string(char *str, double var)
{
    return sy_evaluate_string_with_error(str, var, NULL);
    //return sy_evaluate(sy_parse_string(str, NULL), 0);
}

double sy_evaluate_string_with_error(char *str, double var, sy_error_t *err)
{
    sy_node_t *parsed = sy_parse_string(str, err);
    if(!parsed)
        return 0.0;

    double retval = sy_evaluate(parsed, var);
    sy_free(parsed);
    return retval;
}

void sy_run_timer(sy_node_t *br, int reps)
{
    clock_t startTime = clock();

    int i;
    for(i = 0; i < reps; i++)
        sy_evaluate(br, 1);

    float secs = (float)(clock() - startTime) / CLOCKS_PER_SEC;

    printf("Evaluated %d times. Result is: %lf\nTook: %f. Malloc Time: %f\n", reps, sy_evaluate(br, 1), secs, malloctime);
}
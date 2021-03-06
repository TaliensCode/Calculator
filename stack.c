
#include <stdio.h>
#include <stdlib.h>
#include "head.h"

LinkStack *Create_empty_Stack()
{
    LinkStack *s = (LinkStack *)malloc(sizeof(LinkStack));
    if (NULL == s)
    {
        printf("No free memory!\n");
        return NULL;
    }

    s->n = 0;
    s->top = NULL; 

    return s;
}

int Is_empty_Stack(LinkStack *s)
{
    return s->top == NULL ? 1 : 0;
}

DATATYPE Get_top_Data(LinkStack *s)
{
    if (Is_empty_Stack(s))
    {
        printf("LinkStack is empty!\n");
        return -1;
    }

    return s->top->data;
}

int Push_LinkStack(LinkStack *s,DATATYPE data)
{
    LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
    if (NULL == p)
    {
        printf("No free memory!\n");
        return -1;
    }

    p->next = s->top;
    s->top = p;
    s->n++;

    p->data = data;

    return 0;
}

DATATYPE Pop_LinkStack(LinkStack *s)
{
    LinkNode *t;
    DATATYPE r;

    if (Is_empty_Stack(s))
    {
        printf("LinkStack is empty!\n");
        return -1;
    }
    t = s->top;
    r = t->data;
    s->top = t->next;
    free(t);
    s->n--;

    return r;
}
int Get_Level(char operator)
{
    switch (operator)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        printf("Invalid operator : %c.\n",operator);
        return -1;
    }

    return 0;
}

int Compute(LinkStack *opd_s,LinkStack *opt_s)
{
    int data,data1,data2;

    switch (Pop_LinkStack(opt_s))
    {
    case '+':
        data2 = Pop_LinkStack(opd_s);
        data1 = Pop_LinkStack(opd_s);
        data = (data1 + data2);
        Push_LinkStack(opd_s,data);
        break;
    case '-':
        data2 = Pop_LinkStack(opd_s);
        data1 = Pop_LinkStack(opd_s);
        data = (data1 - data2);
        Push_LinkStack(opd_s,data);
        break;
    case '*':
        data2 = Pop_LinkStack(opd_s);
        data1 = Pop_LinkStack(opd_s);
        data = (data1 * data2);
        Push_LinkStack(opd_s,data);
        break;
    case '/':
        data2 = Pop_LinkStack(opd_s);
        data1 = Pop_LinkStack(opd_s);
        data = (data1 / data2);
        Push_LinkStack(opd_s,data);
        break;
    default:
        printf("Errot\n");
        return -1;
    }
    return 0;
}

int Scan_char_Cal(char *p)
{

    int tmp;
    int opt1,opt2;
    LinkStack *operand_stack = Create_empty_Stack(); 
    LinkStack *operator_stack = Create_empty_Stack();
    while (*p != '\0')
    {
        tmp = 0;
        while (*p >= '0' && *p <= '9')
        {
            tmp = tmp*10 + (*p-'0');
            p++;
        }
        Push_LinkStack(operand_stack,tmp);
        /*printf("%d\n",Get_top_Data(operand_stack));*/
        while (*p == ' ')
        {
            p++;
        }
        switch (*p)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            if (!Is_empty_Stack(operator_stack))
            {
                opt1 = Get_Level(*p);
                opt2 = Get_Level(Get_top_Data(operator_stack)); 
                if (opt1 > opt2)
                {
                    Push_LinkStack(operator_stack,*p);
                }
                else
                {
                    Compute(operand_stack,operator_stack);
                    Push_LinkStack(operator_stack,*p);
                }
            }
            else
            {
                Push_LinkStack(operator_stack,*p);
            }
            p++;

            break;
        default:
            printf("Error char %c\n",*p);
        }
        /*printf("%c\n",Get_top_Data(operator_stack));*/
        while (*p == ' ')
        {
            p++;
        }
    }
    while (operator_stack->n != 0)
    {
        Compute(operand_stack,operator_stack);
    }

    return Pop_LinkStack(operand_stack);
}


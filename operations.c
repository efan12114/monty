#include "monty.h"

int is_digit(char *str)
{
        int i = 0;
        if (!str)
                return (0);
        if (str[0] == '-')
                i = 1;
        for (; str[i]; i++)
        {
                if (str[i] < '0' || str[i] > '9')
                        return (0);
        }
        return (1);
}

void f_push(stack_t **stack, unsigned int line_number)
{
        stack_t *new, *temp;
        int n;

        if (!global.arg || !is_digit(global.arg))
        {
                fprintf(stderr, "L%u: usage: push integer\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        n = atoi(global.arg);
        new = malloc(sizeof(stack_t));
        if (!new)
        {
                fprintf(stderr, "Error: malloc failed\n");
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        new->n = n;
        new->prev = NULL;
        new->next = NULL;

        if (global.lifi == 0) /* Stack (LIFO) - Default */
        {
                new->next = *stack;
                if (*stack)
                        (*stack)->prev = new;
                *stack = new;
        }
        else /* Queue (FIFO) */
        {
                temp = *stack;
                if (!temp)
                {
                        *stack = new;
                }
                else
                {
                        while (temp->next)
                                temp = temp->next;
                        temp->next = new;
                        new->prev = temp;
                }
        }
}

void f_stack(stack_t **stack, unsigned int line_number)
{
        (void)stack;
        (void)line_number;
        global.lifi = 0;
}

void f_queue(stack_t **stack, unsigned int line_number)
{
        (void)stack;
        (void)line_number;
        global.lifi = 1;
}


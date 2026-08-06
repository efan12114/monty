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

        if (global.lifi == 0)
        {
                new->next = *stack;
                if (*stack)
                        (*stack)->prev = new;
                *stack = new;
        }
        else
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

void f_pall(stack_t **stack, unsigned int line_number)
{
        stack_t *h = *stack;
        (void)line_number;

        while (h)
        {
                printf("%d\n", h->n);
                h = h->next;
        }
}

void f_pint(stack_t **stack, unsigned int line_number)
{
        if (!*stack)
        {
                fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        printf("%d\n", (*stack)->n);
}

void f_pop(stack_t **stack, unsigned int line_number)
{
        stack_t *h;

        if (!*stack)
        {
                fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        h = *stack;
        *stack = h->next;
        if (*stack)
                (*stack)->prev = NULL;
        free(h);
}

void f_swap(stack_t **stack, unsigned int line_number)
{
        stack_t *h = *stack;
        int temp;

        if (!h || !h->next)
        {
                fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        temp = h->n;
        h->n = h->next->n;
        h->next->n = temp;
}

void f_add(stack_t **stack, unsigned int line_number)
{
        stack_t *h = *stack;

        if (!h || !h->next)
        {
                fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        h->next->n += h->n;
        *stack = h->next;
        (*stack)->prev = NULL;
        free(h);
}

void f_nop(stack_t **stack, unsigned int line_number)
{
        (void)stack;
        (void)line_number;
}

void f_sub(stack_t **stack, unsigned int line_number)
{
        stack_t *h = *stack;

        if (!h || !h->next)
        {
                fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        h->next->n -= h->n;
        *stack = h->next;
        (*stack)->prev = NULL;
        free(h);
}

void f_div(stack_t **stack, unsigned int line_number)
{
        stack_t *h = *stack;

        if (!h || !h->next)
        {
                fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        if (h->n == 0)
        {
                fprintf(stderr, "L%u: division by zero\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        h->next->n /= h->n;
        *stack = h->next;
        (*stack)->prev = NULL;
        free(h);
}

void f_mul(stack_t **stack, unsigned int line_number)
{
        stack_t *h = *stack;

        if (!h || !h->next)
        {
                fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        h->next->n *= h->n;
        *stack = h->next;
        (*stack)->prev = NULL;
        free(h);
}

void f_mod(stack_t **stack, unsigned int line_number)
{
        stack_t *h = *stack;

        if (!h || !h->next)
        {
                fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        if (h->n == 0)
        {
                fprintf(stderr, "L%u: division by zero\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        h->next->n %= h->n;
        *stack = h->next;
        (*stack)->prev = NULL;
        free(h);
}

void f_pchar(stack_t **stack, unsigned int line_number)
{
        stack_t *h = *stack;

        if (!h)
        {
                fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        if (h->n < 0 || h->n > 127)
        {
                fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        printf("%c\n", h->n);
}

void f_pstr(stack_t **stack, unsigned int line_number)
{
        stack_t *h = *stack;
        (void)line_number;

        while (h && h->n > 0 && h->n <= 127)
        {
                printf("%c", h->n);
                h = h->next;
        }
        printf("\n");
}

void f_rotl(stack_t **stack, unsigned int line_number)
{
        stack_t *tmp = *stack, *head;
        (void)line_number;

        if (!*stack || !(*stack)->next)
                return;
        head = (*stack)->next;
        head->prev = NULL;
        while (tmp->next)
                tmp = tmp->next;
        tmp->next = *stack;
        (*stack)->next = NULL;
        (*stack)->prev = tmp;
        *stack = head;
}

void f_rotr(stack_t **stack, unsigned int line_number)
{
        stack_t *copy = *stack;
        (void)line_number;

        if (!*stack || !(*stack)->next)
                return;
        while (copy->next)
                copy = copy->next;
        copy->prev->next = NULL;
        copy->next = *stack;
        copy->prev = NULL;
        (*stack)->prev = copy;
        *stack = copy;
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

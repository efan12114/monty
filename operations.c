#include "monty.h"

void f_pop(stack_t **stack, unsigned int line_number)
{
        stack_t *temp;
        if (stack == NULL || *stack == NULL)
        {
                fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        temp = *stack;
        *stack = temp->next;
        if (*stack != NULL)
                (*stack)->prev = NULL;
        free(temp);
}

void f_swap(stack_t **stack, unsigned int line_number)
{
        int temp;
        if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        {
                fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        temp = (*stack)->n;
        (*stack)->n = (*stack)->next->n;
        (*stack)->next->n = temp;
}

void f_add(stack_t **stack, unsigned int line_number)
{
        if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        {
                fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        (*stack)->next->n += (*stack)->n;
        f_pop(stack, line_number);
}

void f_nop(stack_t **stack, unsigned int line_number)
{
        (void)stack;
        (void)line_number;
}

void f_sub(stack_t **stack, unsigned int line_number)
{
        if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        {
                fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        (*stack)->next->n -= (*stack)->n;
        f_pop(stack, line_number);
}

void f_div(stack_t **stack, unsigned int line_number)
{
        if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        {
                fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        if ((*stack)->n == 0)
        {
                fprintf(stderr, "L%u: division by zero\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        (*stack)->next->n /= (*stack)->n;
        f_pop(stack, line_number);
}

void f_mul(stack_t **stack, unsigned int line_number)
{
        if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        {
                fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        (*stack)->next->n *= (*stack)->n;
        f_pop(stack, line_number);
}

void f_mod(stack_t **stack, unsigned int line_number)
{
        if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
        {
                fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        if ((*stack)->n == 0)
        {
                fprintf(stderr, "L%u: division by zero\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        (*stack)->next->n %= (*stack)->n;
        f_pop(stack, line_number);
}

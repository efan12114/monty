#include "monty.h"

/**
 * f_pint - prints the value at the top of the stack
 * @stack: stack head
 * @line_number: line_number
 */
void f_pint(stack_t **stack, unsigned int line_number)
{
        if (*stack == NULL)
        {
                fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
                fclose(global.file);
                free(global.line);
                free_stack(*stack);
                exit(EXIT_FAILURE);
        }
        printf("%d\n", (*stack)->n);
}

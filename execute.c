#include "monty.h"

void execute_instruction(char *opcode, stack_t **stack, unsigned int line)
{
        instruction_t opst[] = {
                {"push", f_push},
                {"pall", f_pall},
                {"pint", f_pint},
                {"pop", f_pop},
                {"swap", f_swap},
                {"add", f_add},
                {"nop", f_nop},
                {"sub", f_sub},
                {"div", f_div},
                {"mul", f_mul},
                {"mod", f_mod},
                {NULL, NULL}
        };
        unsigned int i = 0;

        while (opst[i].opcode && opcode)
        {
                if (strcmp(opcode, opst[i].opcode) == 0)
                {
                        opst[i].f(stack, line);
                        return;
                }
                i++;
        }
        fprintf(stderr, "L%u: unknown instruction %s\n", line, opcode);
        fclose(global.file);
        free(global.line);
        free_stack(*stack);
        exit(EXIT_FAILURE);
}

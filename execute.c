#include "monty.h"

/**
 * execute_instruction - executes the opcode
 * @opcode: opcode to execute
 * @stack: head of stack
 * @line: line number
 */
void execute_instruction(char *opcode, stack_t **stack, unsigned int line)
{
	instruction_t opst[] = {
		{"push", f_push},
		{"pall", f_pall},
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

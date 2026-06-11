#include "monty.h"

global_t global = {NULL, NULL, NULL};

/**
 * main - monty code interpreter
 * @argc: number of arguments
 * @argv: monty file location
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	char *opcode;
	size_t size = 0;
	ssize_t read_line = 1;
	stack_t *stack = NULL;
	unsigned int line_number = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	global.file = fopen(argv[1], "r");
	if (!global.file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (read_line > 0)
	{
		global.line = NULL;
		read_line = getline(&global.line, &size, global.file);
		line_number++;
		if (read_line > 0)
		{
			opcode = strtok(global.line, " \n\t");
			if (opcode && opcode[0] != '#')
			{
				global.arg = strtok(NULL, " \n\t");
				execute_instruction(opcode, &stack, line_number);
			}
		}
		free(global.line);
	}
	free_stack(stack);
	fclose(global.file);
	return (0);
}

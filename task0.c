#include "monty.h"

/**
 * is_number - iterates through a string to check if it's a number
 * @str: string to check
 * Return: 1 if number, 0 if not
 */
int is_number(char *str)
{
	int i = 0;

	if (!str || *str == '\0')
		return (0);
	if (str[0] == '-')
	{
		if (str[1] == '\0')
			return (0);
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * f_push - add node to the stack
 * @stack: stack head
 * @line_number: line_number
 */
void f_push(stack_t **stack, unsigned int line_number)
{
	int n;
	stack_t *new_node;

	if (global.arg == NULL || is_number(global.arg) == 0)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		fclose(global.file);
		free(global.line);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	n = atoi(global.arg);
	new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		fclose(global.file);
		free(global.line);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	new_node->n = n;
	new_node->prev = NULL;
	new_node->next = *stack;
	if (*stack)
		(*stack)->prev = new_node;
	*stack = new_node;
}

/**
 * f_pall - prints the stack
 * @stack: stack head
 * @line_number: no used
 */
void f_pall(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;
	(void)line_number;

	while (tmp)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}

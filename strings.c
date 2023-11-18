#include "monty.h"

/**
 * print_char - Prints the ASCII character represented by the top node value.
 * @stack: Pointer to the top node of the stack.
 * @line_number: Line number of the opcode.
 */
void print_char(stack_t **stack, unsigned int line_number)
{
	int ascii;

	/* Check if the stack is empty */
	if (stack == NULL || *stack == NULL)
		string_err(11, line_number);

	/* Retrieve the ASCII value from the top node */
	ascii = (*stack)->n;

	/* Check if the ASCII value is within the valid range */
	if (ascii < 0 || ascii > 127)
		string_err(10, line_number);

	/* Print the corresponding character */
	printf("%c\n", ascii);
}

/**
 * print_str - Prints a string represented by ASCII values in the stack.
 * @stack: Pointer to the top node of the stack.
 * @ln: Line number of the opcode.
 */
void print_str(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	int ascii;
	stack_t *tmp;

	/* Check if the stack is empty */
	if (stack == NULL || *stack == NULL)
	{
		printf("\n");
		return;
	}

	tmp = *stack;

	/* Iterate through the stack and print characters */
	while (tmp != NULL)
	{
		ascii = tmp->n;

		/* Break if the ASCII value is not a printable character */
		if (ascii <= 0 || ascii > 127)
			break;

		/* Print the character */
		printf("%c", ascii);
		tmp = tmp->next;
	}
	/* Print a newline character after printing the string */
	printf("\n");
}

/*
 * rotl - Rotates the first node of the stack to the bottom.
 * @stack: Pointer to the top node of the stack.
 * @ln: Line number of the opcode.
 */
void rotl(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	/* Check if the stack is empty or has only one node */
	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	tmp = *stack;

	/* Find the last node in the stack */
	while (tmp->next != NULL)
		tmp = tmp->next;

	/* Rotate the first node to the bottom */
	tmp->next = *stack;
	(*stack)->prev = tmp;
	*stack = (*stack)->next;
	(*stack)->prev->next = NULL;
	(*stack)->prev = NULL;
}

/**
 * rotr - Rotates the last node of the stack to the top.
 * @stack: Pointer to the top node of the stack.
 * @ln: Line number of the opcode.
 */
void rotr(stack_t **stack, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	/* Check if the stack is empty or has only one node */
	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	tmp = *stack;

	/* Find the last node in the stack */
	while (tmp->next != NULL)
		tmp = tmp->next;

	/* Rotate the last node to the top */
	tmp->next = *stack;
	tmp->prev->next = NULL;
	tmp->prev = NULL;
	(*stack)->prev = tmp;
	(*stack) = tmp;
}


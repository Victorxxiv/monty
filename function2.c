#include "monty.h"

/**
 * nop - Implemets nothing.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Line number of the opcode.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
	/* Nothing to do here */
}

/**
 * swap_nodes - Exchanges the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Line number of the opcode.
 */
void swap_nodes(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "swap");

	tmp = (*stack)->next;
	(*stack)->next = tmp->next;

	if (tmp->next != NULL)
		tmp->next->prev = *stack;

	tmp->next = *stack;
	(*stack)->prev = tmp;
	tmp->prev = NULL;
	*stack = tmp;
	/* Swapping complete */
}

/**
 * add_nodes - Brings the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Line number of the opcode.
 */
void add_nodes(stack_t **stack, unsigned int line_number)
{
	int sum;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "add");

	(*stack) = (*stack)->next;
	sum = (*stack)->n + (*stack)->prev->n;

	if (sum > INT_MAX || sum < INT_MIN)
	{
		more_err(10, line_number); /* Handle integer overflow */
	}

	(*stack)->n = sum;
	free((*stack)->prev);
	(*stack)->prev = NULL;
	/* Addition complete */
}

/**
 * div_nodes - Divides the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Line number of the opcode.
 */
void div_nodes(stack_t **stack, unsigned int line_number)
{
	int quotient;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "div");

	if ((*stack)->n == 0)
		more_err(9, line_number);

	(*stack) = (*stack)->next;
	quotient = (*stack)->n / (*stack)->prev->n;

	if (quotient > INT_MAX || quotient < INT_MIN)
	{
		more_err(10, line_number); /* Handle integer overflow */
	}

	(*stack)->n = quotient;
	free((*stack)->prev);
	(*stack)->prev = NULL;
	/* Division complete */
}

/**
 * sub_nodes - Subtracts the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Line number of the opcode.
 */
void sub_nodes(stack_t **stack, unsigned int line_number)
{
	int difference;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "sub");

	(*stack) = (*stack)->next;
	difference = (*stack)->n - (*stack)->prev->n;

	if (difference > INT_MAX || difference < INT_MIN)
	{
		more_err(10, line_number); /* Handle integer overflow */
	}

	(*stack)->n = difference;
	free((*stack)->prev);
	(*stack)->prev = NULL;
	/* Subtraction complete */
}


#include "monty.h"

/**
 * err - Handles errors and prints appropriate error messages based on
 * error codes.
 * @error_code: The error codes are as follows:
 * (1) => No file provided or more than one file to the program.
 * (2) => Cannot open or read the provided file.
 * (3) => Invalid instruction in the file.
 * (4) => Unable to allocate more memory (malloc failed).
 * (5) => Parameter passed to "push" instruction is not an int.
 * (6) => Stack is empty for "pint".
 * (7) => Stack is empty for "pop".
 * (8) => Stack is too short for the operation.
 */
void err(int error_code, ...)
{
va_list args;
char *op;
int line_num;

va_start(args, error_code);
switch (error_code)
{
case 1:
fprintf(stderr, "USAGE: monty file\n");
break;
case 2:
fprintf(stderr, "Error: Can't open file %s\n",
va_arg(args, char *));
break;
case 3:
line_num = va_arg(args, int);
op = va_arg(args, char *);
fprintf(stderr, "L%d: unknown instruction %s\n", line_num, op);
break;
case 4:
fprintf(stderr, "Error: malloc failed\n");
break;
case 5:
fprintf(stderr, "L%d: usage: push integer\n", va_arg(args, int));
break;
default:
break;
}
freenodes();
exit(EXIT_FAILURE);
}

/**
 * more_err - Handles additional errors.
 * @error_code: The error codes are as follows:
 * (6) => Stack is empty for "pint".
 * (7) => Stack is empty for "pop".
 * (8) => Stack is too short for the operation.
 * (9) => Division by zero.
 */
void more_err(int error_code, ...)
{
va_list args;
char *op;
int line_num;

va_start(args, error_code);
switch (error_code)
{
case 6:
fprintf(stderr, "L%d: can't pint, stack empty\n",
va_arg(args, int));
break;
case 7:
fprintf(stderr, "L%d: can't pop an empty stack\n",
va_arg(args, int));
break;
case 8:
line_num = va_arg(args, unsigned int);
op = va_arg(args, char *);
fprintf(stderr, "L%d: can't %s, stack too short\n", line_num, op);
break;
case 9:
fprintf(stderr, "L%d: division by zero\n",
va_arg(args, unsigned int));
break;
default:
break;
}
freenodes();
exit(EXIT_FAILURE);
}

/**
 * string_err - Handles string-related errors.
 * @error_code: The error codes are as follows:
 * (10) => The number inside a node is outside ASCII bounds.
 * (11) => The stack is empty.
 */
void string_err(int error_code, ...)
{
va_list args;
int line_num;

va_start(args, error_code);
line_num = va_arg(args, int);
switch (error_code)
{
case 10:
fprintf(stderr, "L%d: can't pchar, value out of range\n", line_num);
break;
case 11:
fprintf(stderr, "L%d: can't pchar, stack empty\n", line_num);
break;
default:
break;
}
freenodes();
exit(EXIT_FAILURE);
}

/**
 * mul_nodes - Multiplies the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Integer representing the line number of the opcode.
 */
void mul_nodes(stack_t **stack, unsigned int line_number)
{
int product;

if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
more_err(8, line_number, "mul");

(*stack) = (*stack)->next;
product = (*stack)->n * (*stack)->prev->n;
(*stack)->n = product;
free((*stack)->prev);
(*stack)->prev = NULL;
}

/**
 * mod_nodes - Computes the modulo of the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @line_number: Integer representing the line number of the opcode.
 */
void mod_nodes(stack_t **stack, unsigned int line_number)
{
int result;

if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
more_err(8, line_number, "mod");

if ((*stack)->n == 0)
more_err(9, line_number);
(*stack) = (*stack)->next;
result = (*stack)->n % (*stack)->prev->n;
(*stack)->n = result;
free((*stack)->prev);
(*stack)->prev = NULL;
}


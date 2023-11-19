#define _POSIX_C_SOURCE 200809L
#include "monty.h"
#include <stdio.h>

/**
 * open_file - Opens a file for reading Monty bytecode instructions.
 * @file_name: The path to the Monty bytecode file.
 * Return: Void.
 */
void open_file(char *file_name)
{
FILE *fd = fopen(file_name, "r");

/* Check if the file and file name are valid */
if (file_name == NULL || fd == NULL)
err(2, file_name);

/* Read instructions from the file */
read_file(fd);

/* Close the file */
fclose(fd);
}

/**
 * read_file - Reads Monty bytecode instructions from a file.
 * @fd: Pointer to the file descriptor.
 * Return: Void.
 */
void read_file(FILE *fd)
{
int line_number, format = 0;
char *buffer = NULL;
size_t len = 0;

/* Read each line from the file and parse the instructions */
for (line_number = 1; getline(&buffer, &len, fd) != -1; line_number++)
{
format = parse_line(buffer, line_number, format);
}

/* Free allocated memory for the buffer */
free(buffer);
}

/**
 * parse_line - Separates each line into tokens to determine which function to
 * call based on the opcode.
 * @buffer: Line from the file containing Monty bytecode.
 * @line_number: Line number in the file.
 * @format: Storage format. If 0, nodes will be entered as a stack.
 * If 1, nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */
int parse_line(char *buffer, int line_number, int format)
{
char *opcode, *value;
const char *delim = "\n ";

/* Check if the buffer is valid */
if (buffer == NULL)
err(4);

/* Tokenize the line to extract opcode and value */
opcode = strtok(buffer, delim);
if (opcode == NULL)
return (format);
value = strtok(NULL, delim);

/* Check if the opcode specifies stack or queue format */
if (strcmp(opcode, "stack") == 0)
return (0);
if (strcmp(opcode, "queue") == 0)
return (1);

/* Find and execute the appropriate function for the opcode */
find_func(opcode, value, line_number, format);

/* Return the storage format */
return (format);
}

/**
 * find_func - Finds the appropriate function for the given opcode.
 * @opcode: Opcode string.
 * @value: Argument of the opcode.
 * @format: Storage format. If 0, nodes will be entered as a stack.
 * If 1, nodes will be entered as a queue.
 * @ln: Line number in the file.
 * Return: Void.
 */
void find_func(char *opcode, char *value, int ln, int format)
{
int i;
int flag;

/* List of available opcode functions with their associated functions */
instruction_t func_list[] = {
{"push", add_to_stack},
{"pall", print_stack},
{"pint", print_top},
{"pop", pop_top},
{"nop", nop},
{"swap", swap_nodes},
{"add", add_nodes},
{"sub", sub_nodes},
{"div", div_nodes},
{"mul", mul_nodes},
{"mod", mod_nodes},
{"pchar", print_char},
{"pstr", print_str},
{"rotl", rotl},
{"rotr", rotr},
{NULL, NULL}
};

/* Ignore lines starting with '#' */
if (opcode[0] == '#')
return;

/* Iterate through the list of functions to find the matching opcode */
for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
{
if (strcmp(opcode, func_list[i].opcode) == 0)
{
/* Call the matched function */
call_fun(func_list[i].f, opcode, value, ln, format);
flag = 0;
}
}
/* If no matching opcode is found, print an error */
if (flag == 1)
err(3, ln, opcode);
}

/**
 * call_fun - Calls the required function based on the opcode.
 * @func: Pointer to the function that is about to be called.
 * @op: String representing the opcode.
 * @val: String representing a numeric value.
 * @ln: Line number for the instruction.
 * @format: Format specifier. If 0, nodes will be entered as a stack.
 * If 1, nodes will be entered as a queue.
 * Return: Void.
 */
void call_fun(op_func func, char *op, char *val, int ln, int format)
{
stack_t *node;
int flag;
int i;

flag = 1;

/* Check if the opcode is 'push' */
if (strcmp(op, "push") == 0)
{
/* Handle negative values for 'push' opcode */
if (val != NULL && val[0] == '-')
{
val = val + 1;
flag = -1;
}

/* Check if the value is not NULL */
if (val == NULL)
err(5, ln);

/* Validate that the value contains only digits */
for (i = 0; val[i] != '\0'; i++)
{
if (isdigit(val[i]) == 0)
err(5, ln);
}
/* Create a new node with the parsed value and call the function */
node = create_node(atoi(val) * flag);

/* Call the appropriate function based on the storage format */
if (format == 0)
func(&node, ln);
if (format == 1)
add_to_queue(&node, ln);
}
else
{
/* Call the function with the global head and line number */
func(&head, ln);
}
}


#include "monty.h"
stack_t *head = NULL;

/**
 * main - Entry point of the Monty interpreter.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 * Return: Always returns 0.
 */
int main(int argc, char *argv[])
{
if (argc != 2)
{
fprintf(stderr, "USAGE: monty file\n");
exit(EXIT_FAILURE);
}

open_file(argv[1]);
freenodes();
return (EXIT_SUCCESS);
}

/**
 * create_node - Creates a new stack node with the given value
 * @n: Value to be stored in the new node.
 * Return: A pointer to the newly created node. Returns NULL on failure.
 */
stack_t *create_node(int n)
{
stack_t *node;

node = malloc(sizeof(stack_t));
if (node == NULL)
err(4, "Failed to allocate memory for a new node");
node->next = NULL;
node->prev = NULL;
node->n = n;
return (node);
}

/**
 * freenodes - The function will be used to release all nodes in the stack.
 */
void freenodes(void)
{
stack_t *tmp;

if (head == NULL)
return;

while (head != NULL)
{
tmp = head;
head = head->next;
free(tmp);
}
/* Additional cleanup if needed */
}

/**
 * add_to_queue - Brings a node to the queue.
 * @new_node: Pointer to the new node to be added.
 * @ln: Line number of the opcode.
 */
void add_to_queue(stack_t **new_node, __attribute__((unused)) unsigned int ln)
{
stack_t *tmp;

if (new_node == NULL || *new_node == NULL)
err(EXIT_FAILURE, "Invalid new node provided to add_to_queue");
if (head == NULL)
{
head = *new_node;
return;
}
tmp = head;
while (tmp->next != NULL)
tmp = tmp->next;

tmp->next = *new_node;
(*new_node)->prev = tmp;
}


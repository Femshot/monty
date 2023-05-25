#include "monty.h"

/**
 * exec_opp - Function that checks for a command "opcode" and execute match.
 * @token: Tokane containing the opcode to execute.
 * @stack: Doubly linked list representation of a stack.
 * @line_num: Line number where the opcode was found.
 *
 * Return: EXIT_SUCCESS in success, or EXIT_FAILURE on failure.
 */
int exec_opp(char **token, stack_t **stack, unsigned int line_num)
{
	unsigned int i = 0;
	instruction_t op[] = {{"pall", pall_opp}, {"pint", pint_opp},
		{"pop", pop_opp}, {"swap", swap_opp}, {"add", add_opp},
		{"sub", sub_opp}, {"mul", mul_opp}, {"div", div_opp},
		{"mod", mod_opp}, {"null", NULL}};

	for (i = 0; i < 14; i++)
	{
		if (strcmp(op[i].opcode, token[0]) == 0)
		{
			op[i].f(stack, line_num);
			return (EXIT_SUCCESS);
		}
	}
	free_stack(stack);
	fprintf(stderr, "L%i: unknown instruction %s\n", line_num, token[0]);
	return (EXIT_FAILURE);
}

/**
  * push_opp - A function that pushes an element to stack.
  * @stack: The pointer to the stck struct.
  * @token: The pointer to command.
  * @line_num: The number of the line.
  *
  * Return: EXIT_SUCCESS on success, or EXIT_FAILURE on failure.
  */
int push_opp(stack_t **stack, char **token, unsigned int line_num)
{
	stack_t *new;
	int i = 0;

	if (token[1] == NULL)
		return (opp_err(0, line_num));
	while (token[1][i])
	{
		if (token[1][i] == '-' && i == 0)
		{
			i++;
			continue;
		}
		if (token[1][i] < '0' || token[1][i] > '9')
		{
			free_stack(stack);
			return (opp_err(0, line_num));
		}
		i++;
	}

	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		fprintf(stderr, "%s\n", "Error: malloc failed");
		return (EXIT_FAILURE);
	}
	new->n = atoi(token[1]);
	if ((*stack) != NULL)
		(*stack)->prev = new;
	new->next = *stack;
	new->prev = NULL;
	*stack = new;
	return (EXIT_SUCCESS);
}

/**
 * pushq_opp - Pushes an element to queue.
 * @stack: The pointer to the stck struct.
 * @token: The pointer to command.
 * @line_num: The number of the line.
 *
 * Return: EXIT_SUCCESS on success, or EXIT_FAILURE on failure.
 */
int pushq_opp(stack_t **stack, char **token, unsigned int line_num)
{
	stack_t *new, *temp = NULL;
	int i = 0;

	if (token[1] == NULL)
		return (opp_err(0, line_num));
	while (token[1][i])
	{
		if (token[1][i] == '-' && i == 0)
		{
			i++;
			continue;
		}
		if (token[1][i] < '0' || token[1][i] > '9')
		{
			free_stack(stack);
			return (opp_err(0, line_num));
		}
		i++;
	}
	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		fprintf(stderr, "%s\n", "Error: malloc failed");
		return (EXIT_FAILURE);
	}
	new->next = NULL;
	new->prev = NULL;
	new->n = atoi(token[1]);
	if (!stack || !(*stack))
	{
		(*stack) = new;
		return (EXIT_SUCCESS);
	}
	else
	{
		temp = *stack;
		while (temp->next)
			temp = temp->next;
		new->prev = temp;
		temp->next = new;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/**
 * pall_opp - Prints the values of the stack_t.
 * @stack: The pointer to the top of a stack_t.
 * @line_num: The number of the line.
 */
void pall_opp(stack_t **stack, unsigned int line_num)
{
	stack_t *tmp = *stack;
	(void)line_num;

	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}

/**
 * opp_err - A function that print the errors.
 * @flag: The index to type of error.
 * @line_num: The number of line in file with error.
 *
 * Return: EXIT_FAILURE.
 */
int opp_err(int flag, unsigned int line_num)
{
	char *errors[] = {"usage: push integer", "can\'t pint, stack empty",
	     "can\'t pop an empty stack", "can\'t swap, stack too short",
	     "can\'t add, stack too short", "can\'t sub, stack too short",
	     "can\'t div, stack too short", "division by zero",
	     "can\'t mul, stack too short", "can\'t mod, stack too short",
	     "can\'t pchar, value out of range", "can\'t pchar, stack empty"};

	fprintf(stderr, "L%d: %s\n", line_num, errors[flag]);
	return (EXIT_FAILURE);
}

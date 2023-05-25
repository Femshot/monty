#include "monty.h"

/**
 * free_stack - A function that frees the memory allocated for stack.
 * @stack: Pointer to the doubly linked list representation of a stack.
 */
void free_stack(stack_t **stack)
{
	stack_t *tmp = *stack;

	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

/**
 * pint_opp - Prints the top value of the stack.
 * @stack: The pointer to the stack list.
 * @line_number: The current working line number of a Monty bytecodes file.
 */
void pint_opp(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	if (!tmp)
	{
		opp_err(1, line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", tmp->n);
}

/**
 * pop_opp - Removes the top value in the stack.
 * @stack: The pointer to the stack_t list.
 * @line_number: The line number of a Monty bytecodes file.
 */
void pop_opp(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	if (!tmp)
	{
		opp_err(2, line_number);
		exit(EXIT_FAILURE);
	}

	if (tmp->next)
		tmp->next->prev = tmp->prev;
	*stack = tmp->next;
	free(tmp);
}

/**
 * swap_opp - Swaps the two values at the top of stack.
 * @stack: The pointer to the top of a stack list.
 * @line_number: The line number of a Monty bytecodes file.
 */
void swap_opp(stack_t **stack, unsigned int line_number)
{
	int tmp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		opp_err(3, line_number);
		exit(EXIT_FAILURE);
	}
	tmp = (*stack)->next->n;
	(*stack)->next->n = (*stack)->n;
	(*stack)->n = tmp;
}

/**
 * add_opp - Adds the two top values of a stack, stores result in 2nd to last
 * @stack: The pointer to the stack list.
 * @line_number: The line number of a Monty bytecodes file.
 */
void add_opp(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		opp_err(4, line_number);
		exit(EXIT_FAILURE);
	}
	temp = (*stack)->n + (*stack)->next->n;
	(*stack)->next->n = temp;
	pop_opp(stack, line_number);
}

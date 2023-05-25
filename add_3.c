#include "monty.h"

/**
 * sub_opp - Subtracts the second value from the top of stack by the top value
 * @stack: The pointer to the stack list.
 * @line_number: The line number of a Monty bytecodes file.
 */
void sub_opp(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		opp_err(5, line_number);
		exit(EXIT_FAILURE);
	}
	temp = (*stack)->next->n - (*stack)->n;
	(*stack)->next->n = temp;
	pop_opp(stack, line_number);
}

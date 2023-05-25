#ifndef MN_TY
#define MN_TY

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>


/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

int read_file(FILE *fd);
char **tokenise(char *line, char *delim);
int empty_line(char *line, char *delims);
int exec_opp(char **token, stack_t **stack, unsigned int line_num);
int push_opp(stack_t **stack, char **token, unsigned int line_num);
int pushq_opp(stack_t **stack, char **token, unsigned int line_num);
void pall_opp(stack_t **stack, unsigned int line_num);
int opp_err(int flag, unsigned int line_num);
void free_stack(stack_t **stack);
void pop_opp(stack_t **stack, unsigned int line_number);
void pint_opp(stack_t **stack, unsigned int line_number);
void swap_opp(stack_t **stack, unsigned int line_number);
void add_opp(stack_t **stack, unsigned int line_number);
void sub_opp(stack_t **stack, unsigned int line_number);
void div_opp(stack_t **stack, unsigned int line_number);
void mul_opp(stack_t **stack, unsigned int line_number);
void mod_opp(stack_t **stack, unsigned int line_number);

#endif

#include "monty.h"

/**
 * main - Entry point of program.
 * @ac: The number of arguments.
 * @av: The pointer to an array of inputed arguments.
 *
 * Return: 0 on Success.
 */
int main(int ac, char **av)
{
	FILE *fd = NULL;
	int exit_status = EXIT_SUCCESS;

	if (ac != 2)
	{
		fprintf(stderr, "%s\n", "USAGE: monty file");
		exit(EXIT_FAILURE);
	}
	fd = fopen(av[1], "r");
	if (fd == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	exit_status = read_file(fd);
	fclose(fd);
	return (exit_status);
}

/**
 * tokenise - A function that splits the line.
 * @line: The pointer to bytecode line.
 * @delim: Delimiters to use being " \n\t\a\b".
 *
 * Return: The pointer to tokens.
 */
char **tokenise(char *line, char *delim)
{
	char *operations = NULL, **token = NULL;
	size_t buf = 0;
	int i = 0;

	if (line == NULL || !*line)
		return (NULL);

	buf = strlen(line);
	if (buf == 0)
		return (NULL);
	token = (char **)malloc(buf * sizeof(char *));
	if (token == NULL)
	{
		free(line);
		free(token);
		fprintf(stderr, "%s\n", "Error: malloc failed");
		exit(EXIT_FAILURE);
	}
	operations = strtok(line, delim);
	if (operations == NULL)
	{
		free(token);
		free(line);
		return (NULL);
	}
	while (operations != NULL)
	{
		token[i] = operations;
		i++;
		operations = strtok(NULL, delim);
	}
	token[i] = '\0';
	return (token);
}

/**
 * read_file - Reads text from open file.
 * @fd: File descriptor for an open Monty bytecodes script.
 *
 * Return: EXIT_SUCCESS on success, or EXIT_FAILURE on error.
 */
int read_file(FILE *fd)
{
	stack_t *stk_que = NULL;
	char *line = NULL, **token = NULL, delim[] = " \n\t\a\b";
	size_t len = 0, mode = 1;
	ssize_t base;
	unsigned int exit_status = EXIT_SUCCESS, line_num = 0;

	while ((base = getline(&line, &len, fd)) != -1)
	{
		line_num++;
		if (empty_line(line, delim))
			continue;
		token = tokenise(line, delim);
		if (token[0][0] == '#' || strcmp(token[0], "nop") == 0)
		{
			free(token);
			continue;
		}
		else if (strcmp(token[0], "stack") == 0)
			mode = 1;
		else if (strcmp(token[0], "queue") == 0)
			mode = 0;
		else if (strcmp(token[0], "push") == 0 && mode == 0)
			exit_status = pushq_opp(&stk_que, token, line_num);
		else if (strcmp(token[0], "push") == 0 && mode == 1)
			exit_status = push_opp(&stk_que, token, line_num);
		else
			exit_status = exec_opp(token, &stk_que, line_num);
		free(token);
		if (exit_status == EXIT_FAILURE)
			break;
	}
	free_stack(&stk_que);
	free(line);
	return (exit_status);
}

/**
 * empty_line - Checks if line only contains delimiters or not.
 * @line: The pointer to the line.
 * @delims: The string with delimiter characters.
 *
 * Return: 1 if the line only contains delimiters, otherwise 0.
 */
int empty_line(char *line, char *delims)
{
	int i, j;

	for (i = 0; line[i]; i++)
	{
		for (j = 0; delims[j]; j++)
		{
			if (line[i] == delims[j])
				break;
		}
		if (delims[j] == '\0')
			return (0);
	}
	return (1);
}

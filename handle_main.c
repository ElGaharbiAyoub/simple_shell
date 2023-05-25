#include "main.h"

/**
 * handle_exit - handle the exit commande
 * @first_arg: the first command
 * @buffer: the main buffer
 * @argv: the array of args
 */

void handle_exit(char *first_arg, char *buffer, char **argv)
{
	int num_exit = 0;

	if (argv[1])
		num_exit = _atoi(argv[1]);

	free(first_arg), free(buffer), free(argv);
	exit(num_exit);
}


/**
 * _getdir_forcamd - get a directory based on the command provided
 * @comd: command provided by the user
 * Return: a pointer to dir or NULL
 */

char *_getdir_forcamd(char *comd)
{
	char *path;
	char *tok;
	char *full_comd;
	struct stat st;

	path = _getenv("PATH");
	tok = strtok(path, ":");

	if (stat(comd, &st) == 0)
	{
		return (comd);
	}
	else
	{
		while (tok)
		{
			full_comd = malloc(strlen(tok) + strlen(comd) + 2);

			strcpy(full_comd, tok);
			strcat(full_comd, "/");
			strcat(full_comd, comd);
			if (stat(full_comd, &st) == 0)
				return (full_comd);

			free(full_comd);
			tok = strtok(NULL, ":");
		}
	}
	return (NULL);
}

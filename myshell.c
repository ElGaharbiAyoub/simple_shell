#include "main.h"

extern char **environ;

/**
 * _getenv - searches the environment variables at runtime
 * @name: fan entry with the specified name
 * Return: a pointer to the variable’s value on success or NULL
 */

char *_getenv(const char *name)
{
	int i = 0;
	char *split;
	char *value;

	while (environ[i])
	{
		split = strtok(environ[i], "=");
		if (strcmp(split, name) == 0)
		{
			value = strtok(NULL, "\n");
			return (value);
		}
		i++;
	}
	return (NULL);
}

/**
 * execute_command - handle the execute command
 * @argv: the array of args
 */

void execute_command(char **argv)
{
	char *first_arg = _getdir_forcamd(argv[0]);

	if (first_arg)
		execve(first_arg, argv, environ);
	else
		perror("error");

	free(argv);
	exit(0);
}


/**
 * handle_file - check the file
 * @msg: string
 * @len: lenght of msg
 */
void handle_file(char *msg, int len)
{
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, msg, len);
}

/**
 * main - the main logic of the program
 * Return: 0 on success or 1 otherwise
 */


int main(void)
{
	char *buffer = NULL, *first_arg = NULL;
	char **argv = NULL;
	/**int num_exit = 0;*/
	size_t buffer_s = 0;
	pid_t child_pid;
	int status, nbr_chars;

	while (1)
	{
		handle_file("$ ", 2);
		nbr_chars = getline(&buffer, &buffer_s, stdin);
		if (nbr_chars == -1)
		{
			free(first_arg), free(buffer), free(argv);
			exit(0);
		}
		if (nbr_chars == 0)/* exit if ctrl- d */
			handle_file("\n", 1), exit(1);
		argv = spt_args(buffer, " \t\n");

		if (argv[0] && strcmp(argv[0], "exit") == 0)
			handle_exit(first_arg, buffer, argv);
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("error");
			return (1);
		}
		if (child_pid == 0)
			execute_command(argv);
		else
			wait(&status);
		free(first_arg), free(argv);
		first_arg = NULL, argv = NULL;
	}
	return (0);
}

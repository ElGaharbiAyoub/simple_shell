#include "main.h"

extern char **environ;

/**
 * _atoi - convert a string of characters to an integer value
 * @s: a string to convert
 * Return: value on success or NULL on failure
 */

int _atoi(char *s)
{
	unsigned int count = 0, size = 0, toi = 0;
	unsigned int i, sign = 1, mult = 10;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			sign *= -1;

		if (*(s + count) >= '0' && *(s + count) <= '9')
		{
			if (size > 0)
				mult *= 10;

			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		mult /= 10;
		toi = toi + ((*(s + i) - '0') * mult);
	}
	return (toi * sign);
}

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

    while(environ[i])
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
 * _getdir_forcamd - get a directory based on the command provided 
 * @comd: command provided by the user
 * Return: a pointer to dir or NULL
 */

char *_getdir_forcamd( char *comd)
{
    char *path;
    char *tok;
    char *full_comd;
    struct stat st;

    path = _getenv("PATH");
    tok = strtok(path, ":");

    if (stat(comd, &st) == 0)
        return (comd);
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

/**
 * spt_args - split tha args 
 * @buffer: the main buffer to split
 * @spt_args: the delimeter to split with
 * Return: a pointer to splited buffer or NULL
 */

char **spt_args(char *buffer, char *del)
{
     char **toks;
     char *tok;
     int i = 0;

     toks = malloc(sizeof(char *) * 1024);
     tok = strtok(buffer , del);
     while (tok)
     {
        toks[i] = tok;
        tok = strtok(NULL, del);
        i++;
     }
     toks[i] = NULL;
     return (toks);
}

/**
 * handle_exit - handle the exit commande 
 * @first_arg: the first command
 * @buffer: the main buffer
 * @argv: the array of args
 */

void handle_exit(char *first_arg, char *buffer, char **argv) {
    int num_exit = 0;
    
    if (argv[1]) {
        num_exit = _atoi(argv[1]);
    }

    free(first_arg);
    free(buffer);
    free(argv);
    exit(num_exit);
}

 int main()
 {
    char *buffer = NULL, *first_arg = NULL;
    char **argv = NULL;
    /**int num_exit = 0;*/
    size_t buffer_s = 0;
    pid_t child_pid;
    int status, nbr_chars;

    while (1){
        if (isatty(STDIN_FILENO))
            write(STDERR_FILENO, "$ ", 2);
        nbr_chars = getline(&buffer, &buffer_s, stdin);
        if (nbr_chars == -1)
        {
            free(first_arg), free(buffer), free(argv);
            exit(0);
        }
        if (nbr_chars == 0)/* exit if ctrl- d */
			{
				if (isatty(STDIN_FILENO))
					write(STDERR_FILENO, "\n", 1);
				exit(1);
			}
        argv = spt_args(buffer, " \t\n");
    
            if (argv[0] && strcmp(argv[0], "exit") == 0)
               handle_exit(first_arg, buffer, argv);
        child_pid =fork();
        if (child_pid == -1)
        {
            perror("error");  
            return (1);
        }
        if (child_pid == 0)
        { 
            first_arg = _getdir_forcamd(argv[0]);
            if (first_arg)
                execve(first_arg, argv, environ);
            else
                perror("error");
            free(buffer),free(argv);
            exit(0);
        }
        else
            wait(&status);
        free(first_arg), free(argv);
        first_arg = NULL, argv= NULL;
    }
    return (0);
 }

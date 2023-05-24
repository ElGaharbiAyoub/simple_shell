#include "main.h"

extern char **environ;

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
            printf("\n");
            free(first_arg), free(buffer), free(argv);
            exit(1);
        }
        if (nbr_chars == 0)/* exit if ctrl- d */
			{
				if (isatty(STDIN_FILENO))
					write(STDERR_FILENO, "\n", 1);
				exit(0);
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
    }
    return (0);
 }

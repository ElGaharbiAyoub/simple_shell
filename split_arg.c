#include "main.h"

/**
 * spt_args - split tha args
 * @buffer: the main buffer to split
 * @del: the delimeter to split with
 * Return: a pointer to splited buffer or NULL
 */

char **spt_args(char *buffer, char *del)
{
	char **toks;
	char *tok;
	int i = 0;

	toks = malloc(sizeof(char *) * 1024);
	tok = strtok(buffer, del);
	while (tok)
	{
		toks[i] = tok;
		tok = strtok(NULL, del);
		i++;
	}
	toks[i] = NULL;
	return (toks);
}

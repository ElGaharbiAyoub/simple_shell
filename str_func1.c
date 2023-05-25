#include "main.h"
/**
 * _strlen -  the length of a string.
 * @s: character
 *
 * Return: number of length.
 */
int _strlen(char *s)
{
	int c = 0;

	while (*s != '\0')
	{
		c++;
		s++;
	}
	return (c);
}

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

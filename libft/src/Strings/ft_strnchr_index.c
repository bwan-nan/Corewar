#include "string.h"

int		ft_strnchr_index(const char *str, int n, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		if (count == n)
			return (i);
		i++;
	}
	return (-1);
}

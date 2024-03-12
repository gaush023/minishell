#include "../../includes/minishell.h"

size_t get_num_len(int n)
{
	size_t len;
	long long num;

	num = (long long)n;
	len = 0;
	if (num < 0)
	{
		len++;
		num *= -1;
	}
	while (num >= 10)
	{
		num /= 10;
		len++;
	}
	return (len + 1);
}

char *ft_itoa(int n)
{
	char *res;
	size_t len;
	size_t is_negative;
	long long num;

	len = get_num_len(n);
	num = (long long)n;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	is_negative = 0;
	if(n < 0)
	{
		res[0] = '-';
		num = -num;
		is_negative = 1;
	}
	while (len-- > is_negative)
	{
		res[len] = (num % 10) + '0';
		num /= 10;
	}
	return (res);
}


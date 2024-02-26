#include "../../includes/minishell.h"

int ft_atoi(const char *s)
{
	long long int res;
	int sign;
	size_t i;

	res = 0;
	sign = 1;
	i = 0;
	while(s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if(s[i] == '-' || s[i] == '+')
	{
		if(s[i] == '-')
			sign = -1;
		i++;
	}
	while(s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		if(res > INT_MAX && sign == 1)
			return (INT_MAX);
		if(res > INT_MIN && sign == -1)
			return (INT_MIN);
		i++;
	}
	return (res * sign);
}



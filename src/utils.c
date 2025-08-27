#include "philo.h"

//atoi
int	ft_atoi(char *nptr)
{
	int	output;
	int	sign;

	output = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if ((*nptr == '-') || (*nptr == '+'))
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (('0' <= *nptr) && (*nptr <= '9'))
	{
		output = output * 10 + (*nptr - '0');
		nptr++;
	}
	return (output * sign);
}

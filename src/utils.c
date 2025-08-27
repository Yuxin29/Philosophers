#include "philo.h"

static int ft_is_digit(char c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

static int ft_is_pos_int(char *nptr)
{
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-') // minus
		return (0);
	if (*nptr == '+')
		nptr++;
	if (!*nptr) //empty as first digit
		return (0);
	while (*nptr)
	{
		if (!ft_is_digit(*nptr))
			return (0);
		nptr++;
	}
	return (1);
}

// is_numeric checked, over_flow is not checked yes
int	safe_atoi(char *nptr)
{
	int	output;

	output = 0;
    if (!ft_is_pos_int(nptr))
		return (0); //error code
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '+')
		nptr++;
	while (('0' <= *nptr) && (*nptr <= '9'))
	{
		if (output * 10 + (*nptr - '0') > 2147483647)
            return (0); //error code for over flow
        output = output * 10 + (*nptr - '0');
		nptr++;
	}
	return (output);
}

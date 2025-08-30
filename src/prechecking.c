#include "philo.h"

static int ft_is_pos_int(char *nptr)
{
	char c;

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
		c = *nptr;
		if (c < '0' || c > '9')
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

int err_return_int(char *str, int i)
{
    if (str)
        printf("%s\n", str); //should I print stderr??
    return (i);
}

// input check
int    pre_check_argv(int argc, char **argv)
{
    if (argc != 5 && argc != 6) 
        return (err_return_int("wrong ac nbr", 0));
    if (!safe_atoi(argv[1]) || !safe_atoi(argv[2])
        || !safe_atoi(argv[3]) || !safe_atoi(argv[4]))
        return (err_return_int("invalid ac", 0)); //error: invalude input or over flow
    if ( argv[5] && !safe_atoi(argv[5]))
        return (err_return_int("invalid ac", 0));
    return (1);
}

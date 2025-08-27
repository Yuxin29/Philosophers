/* ************************************************************************** */
#include "philo.h"

int err_return_int(char *str, int i)
{
    if (str)
        printf("%s\n", str); //should I print stderr??
    return (i);
}
/* ************************************************************************** */
#include "philo.h"

// for testing, delete later
static void ft_print_table(t_table  *table)
{
    printf("%d\n", table->nbr);
    printf("%d\n", table->to_die_time);
    printf("%d\n", table->eat_time);
    printf("%d\n", table->sleep_time);
    printf("%d\n", table->total_eating_time);
}

int main(int argc, char **argv)
{
    t_table *philo_table;
    pthread_t *tids;

    // input check
    if (argc != 5 && argc != 6) 
        return (err_return_int("wrong ac nbr", -1));
    if (!safe_atoi(argv[1]) || !safe_atoi(argv[2])
        || !safe_atoi(argv[3]) || !safe_atoi(argv[4]))
        return (err_return_int("invalid ac", -1)); //error: invalude input or over flow
    if ( argv[5] && !safe_atoi(argv[5]))
        return (err_return_int("invalid ac", -1));

    //testing print threads
    philo_table = malloc(sizeof(t_table) * 1);
    if (!philo_table)
       return (err_return_int("table malloc failed", -1));
    get_table(philo_table, argv);
    ft_print_table(philo_table);
    
    //create and join
    tids = create_threads(philo_table);
    if (!tids) //malloc inside
    {
        free(philo_table);
        return (err_return_int("tids failed", -1));
    }
    joint_all_threads(tids, philo_table);

    //finishing
    free(philo_table);
    free(tids);
    return (0);
}
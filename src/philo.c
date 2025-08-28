/* ************************************************************************** */
#include "philo.h"

//------------------------------------------------->
// for testing, delete later
static void ft_print_philos(t_table  *table)
{
    int i;

    i = 0;
    while (i < table->nbr)
    {
        printf("id of the philo is %d\n", table->philos[i].id);
        printf("id of the fork on left is %d\n", table->philos[i].fork_l);
        printf("id of the fork on right is %d\n", table->philos[i].fork_r);
        printf("this philo has eatedn %d meals so far\n", table->philos[i].meals_eaten);
        i++;
    }
}

// for testing, delete later
static void ft_print_table(t_table  *table)
{
    printf("number of philos on the table is %d\n", table->nbr);
    printf("if the philo does not eat in %d seconds, he will die\n", table->to_die_time);
    printf("each meal takes %d seconds to eat\n", table->eat_time);
    printf("each sleep takes %d seconds\n", table->sleep_time);
    printf("if all philos has eaten %d meals, table ends\n", table->total_eating_time);
    printf("%s\n", "-----here is info for each philo----");
    ft_print_philos(table);
}
//------------------------------------------------->

// input check
static int    pre_check_argv(int argc, char **argv)
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

int main(int argc, char **argv)
{
    t_table *philo_table;
    pthread_t *tids;

    if (!pre_check_argv(argc, argv))
        return(-1);

    philo_table = init_table(argv);
    if (!philo_table)
       return (-1);
    ft_print_table(philo_table);  //testing, delete later
    
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
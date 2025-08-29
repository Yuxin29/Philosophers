/* ************************************************************************** */
#include "philo.h"

// for testing, delete later
//-------------------------------------------------------------------->
static void ft_print_philos_thread(t_table  *table)
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
    i = 0;
    while (i < table->nbr)
    {
        printf("ptr address of the forks is %p\n", (void *)&table->forks[i]);
        i++;
    }
    printf("ptr address of the printf_lock is %p\n", (void *)&table->printf_lock);
}

static void ft_print_table(t_table  *table)
{
    printf("number of philos on the table is %d\n", table->nbr);
    printf("if the philo does not eat in %d seconds, he will die\n", table->to_die_time);
    printf("each meal takes %d seconds to eat\n", table->eat_time);
    printf("each sleep takes %d seconds\n", table->sleep_time);
    printf("if all philos has eaten %d meals, table ends\n", table->total_eating_time);
    printf("%s\n", "-----here is info for each philo----");
    printf("The starting time of the table is %lu\n", table->starting_time_ms);
    ft_print_philos_thread(table);

}
//-------------------------------------------------------------------->

int main(int argc, char **argv)
{
    t_table *philo_table;

    if (!pre_check_argv(argc, argv))
        return(-1);

    philo_table = init_table(argv);
    if (!philo_table)
       return (-1);
    //testing, delete later
    ft_print_table(philo_table);

    //finishing
    ft_free_table(philo_table);
    return (0);
}
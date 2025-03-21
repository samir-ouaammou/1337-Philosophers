#include "Philo.h"

void    ft_philo_one(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    ft_print_status(philo, "has taken a fork");
    pthread_mutex_unlock(philo->left_fork);
    ft_usleep(philo->time_to_die);
    ft_print_status(philo, "died");
}

void ft_philo_create(t_data *data)
{
    short   i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_create(&data->philos[i].thread, NULL, ft_philosopher_routine, &data->philos[i]);
        i++;
    }
    pthread_create(&data->monitor_threads, NULL, ft_monitor_threads, data);
}

void ft_philo_wait(t_data *data)
{
    short   i;

    i = 0;
    pthread_join(data->monitor_threads, NULL);
    while (i < data->num_philos)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
}

void ft_philo_destroy(t_data *data)
{
    short   i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(data->philos[i].print_mutex);
        i++;
    }
    ft_exit(0);
}

int main(int ac, char **av)
{
    t_data  data;

    if (ac != 5 && ac != 6)
        ft_print_usage_and_exit(NULL);
    ft_philo_pars(&data, ac, av);
    ft_philo_init(&data);
    if (data.num_philos == 1)
        ft_philo_one(&data.philos[0]);
    else
    {
        ft_philo_create(&data);
        ft_philo_wait(&data);
    }
    ft_philo_destroy(&data);
    return (0);
}

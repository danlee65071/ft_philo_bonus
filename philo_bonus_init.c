#include "philo_bonus.h"

static void	philo_init_sems(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("sem_write");
	sem_unlink("sem_eat");
	data->forks = sem_open("forks", O_CREAT, S_IRWXU, data->num_philos);
	data->sem_eat = sem_open("sem_eat", O_CREAT, S_IRWXU, 1);
	data->sem_write = sem_open("sem_write", O_CREAT, S_IRWXU, 1);
	if (data->forks <= 0 || data->sem_eat <= 0 || data->sem_write <= 0)
		error_message("Semaphore initialization failed!\n");
}

void	philo_init(t_data *data, t_philo *philo)
{
	int	i;

	philo_init_sems(data);
	if (gettimeofday(&data->start_time, NULL) != 0)
		error_message("Time initialization failed!\n");
	i = -1;
	while (++i < data->num_philos)
	{
		philo[i].right_fork = i;
		philo[i].left_fork = (i + 1) % data->num_philos;
		philo[i].philo_ind = i;
		philo[i].num_of_eat = 0;
		philo[i].data = data;
		philo[i].time_last_eat = data->start_time;
	}
}

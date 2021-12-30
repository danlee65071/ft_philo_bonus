#include "philo_bonus.h"

static void	*waiter_bonus(void *void_philo)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)void_philo;
	data = philo->data;
	usleep(250);
	while (1)
	{
		sem_wait(data->sem_eat);
		gettimeofday(&data->current_time, NULL);
		if (timeval_to_ms(data->current_time)
			- timeval_to_ms(philo->time_last_eat) >
			(unsigned long)data->time_to_die)
		{
			sem_wait(data->sem_write);
			printf("%ld %d %s\n", get_current_time(data),
				   philo->philo_ind + 1, "died");
			exit(1);
		}
		sem_post(data->sem_eat);
	}
	return (NULL);
}

static void	philo_eat(t_data *data, t_philo *philo)
{
	sem_wait(data->forks);
	print_message(data, philo->philo_ind, "has taken a fork");
	sem_wait(data->forks);
	print_message(data, philo->philo_ind, "has taken a fork");
	sem_wait(data->sem_eat);
	print_message(data, philo->philo_ind, "is eating");
	philo->num_of_eat++;
	gettimeofday(&(philo->time_last_eat), NULL);
	sem_post(data->sem_eat);
	philo_usleep(data->time_to_eat);
	sem_post(data->forks);
	sem_post(data->forks);
	if (data->num_must_eat != -1 && philo->num_of_eat >= data->num_must_eat)
	{
		sem_post(data->sem_eat);
		exit(0);
	}
}

static void	philo_routine(t_data *data, t_philo *philo)
{
	if (pthread_create(&(philo->waiter_thread), NULL, waiter_bonus,
								   (void *)(philo)) != 0)
		error_message("Thread creation failed!\n");
	if (pthread_detach(philo->waiter_thread) != 0)
		error_message("Thread detach failed!\n");
	if (philo->philo_ind % 2 == 0)
		usleep(200);
	while (1)
	{
		philo_eat(data, philo);
		print_message(data, philo->philo_ind, "is sleeping");
		philo_usleep(data->time_to_sleep);
		print_message(data, philo->philo_ind, "is thinking");
	}
}

void	philo_start(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		philo[i].philo_pid = fork();
		if (philo[i].philo_pid == -1)
			error_message("Process creation failed!\n");
		if (philo[i].philo_pid == 0)
			philo_routine(data, &(philo[i]));
	}
}
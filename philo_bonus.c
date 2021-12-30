#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	philo[200];
	int		i;
	int		wait_status;

	philo_parser(argc, argv, &data);
	philo_init(&data, philo);
	philo_start(&data, philo);
	i = -1;
	while (++i < data.num_philos)
	{
		waitpid(-1, &wait_status, 0);
		if (wait_status != 0)
		{
			i = -1;
			while (++i < data.num_philos)
				kill(philo->philo_pid, SIGTERM);
			break ;
		}
	}
	sem_close(data.forks);
	sem_close(data.sem_write);
	sem_close(data.sem_eat);
	sem_unlink("forks");
	sem_unlink("sem_write");
	sem_unlink("sem_eat");
	return (0);
}
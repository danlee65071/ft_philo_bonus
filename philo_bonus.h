#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct timeval t_timeval;

typedef struct s_data
{
	int			num_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_must_eat;
	sem_t		*forks;
	sem_t		*sem_write;
	sem_t		*sem_eat;
	t_timeval	start_time;
	t_timeval	current_time;
} t_data;

typedef struct s_philo
{
	int			right_fork;
	int			left_fork;
	int			philo_ind;
	pid_t		philo_pid;
	int			num_of_eat;
	t_timeval	time_last_eat;
	pthread_t	waiter_thread;
	t_data		*data;
} t_philo;

void			error_message(const char *message);
int				ft_atoi(const char *str);
void			philo_parser(int argc, char **argv, t_data *data);
void			philo_init(t_data *data, t_philo *philo);
unsigned long	timeval_to_ms(const t_timeval time);
void			print_message(t_data *data, int philo_ind, const char* message);
void			philo_usleep(int time);
void			philo_start(t_data *data, t_philo *philo);
void			philo_waiter(t_data *data, t_philo *philo);
unsigned long	get_current_time(t_data *data);

#endif
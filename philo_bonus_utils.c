#include "philo_bonus.h"

void	error_message(const char *message)
{
	printf("%s\n", message);
	exit(1);
}

static long	to_int(const char *str, size_t i, int sign)
{
	int	rank;
	int	res;

	res = 0;
	rank = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (rank > 11 && sign == 1)
			return (-1);
		else if (rank > 11 && sign == -1)
			return (0);
		res = res * 10 + str[i] - '0';
		rank++;
		i++;
	}
	res *= sign;
	return (res);
}

int	ft_atoi(const char *str)
{
	long	res;
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		   || str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	res = to_int(str, i, sign);
	return ((int)res);
}

unsigned long	get_current_time(t_data *data)
{
	t_timeval	current_time;
	t_timeval	start_time;

	start_time = data->start_time;
	gettimeofday(&current_time, NULL);
	return (timeval_to_ms(current_time) - timeval_to_ms(start_time));
}

void	print_message(t_data *data, int philo_ind, const char* message)
{
	sem_wait(data->sem_write);
	printf("%lu %d %s\n", get_current_time(data), philo_ind + 1, message);
	sem_post(data->sem_write);
}

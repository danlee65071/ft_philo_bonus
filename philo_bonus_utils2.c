#include "philo_bonus.h"

unsigned long	timeval_to_ms(const t_timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	philo_usleep(int time)
{
	t_timeval		current_time;
	unsigned long	till_time;

	gettimeofday(&current_time, NULL);
	till_time = timeval_to_ms(current_time) + time;
	while (timeval_to_ms(current_time) < till_time)
	{
		gettimeofday(&current_time, NULL);
		usleep(200);
	}
}
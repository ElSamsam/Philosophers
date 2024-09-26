/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:40:18 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/18 16:40:18 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	ft_strlen(char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	super_atoi(char const *input)
{
	int			index;
	int			sign;
	long		result;

	index = 0;
	sign = 1;
	result = 0;
	while (*input == ' ')
		input++;
	if (input[index] == '+' || input[index] == '-')
	{
		if (input[index] == '-')
			sign *= -1;
		index++;
	}
	while (input[index] >= '0' && input[index] <= '9')
	{
		result = result * 10 + (input[index] - 48);
		if ((result > 2147483647 && sign == 1) || result > (long)2147483647 + 1)
			return (-4000000000);
		index++;
	}
	if (input[index] == '-' || input[index] == '+')
		return (-4000000000);
	return (result * (long)sign);
}

void	ft_sleep(long time)
{
	long	entry_time;

	entry_time = get_time();
	usleep(time * 0.8 * 1000);
	while (get_time() < time + entry_time)
		usleep(100);
	return ;
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_philo_state(int id, char *action, t_scene *scene, int state)
{
	if (dead_philos(&(scene->philo[id - 1])) == 0 && state == 0)
	{
		pthread_mutex_lock(&(scene->stdout_mtx));
		printf("%ld %d %s\n", get_time() - scene->start_time, id, action);
		pthread_mutex_unlock(&(scene->stdout_mtx));
	}
	else if (state == 1)
	{
		usleep(1500);
		pthread_mutex_lock(&(scene->stdout_mtx));
		printf("%ld %d %s\n", get_time() - scene->start_time, id, action);
		pthread_mutex_unlock(&(scene->stdout_mtx));
	}
}

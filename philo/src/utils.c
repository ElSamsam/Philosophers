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

int	ft_atoi(char const *nptr)
{
	int			index;
	int			sign;
	int long	result;

	index = 0;
	sign = 1;
	result = 0;
	while (nptr[index] == ' '
		|| (nptr[index] >= '\t' && nptr[index] <= '\r'))
		index++;
	if (nptr[index] == '+' || nptr[index] == '-')
	{
		if (nptr[index] == '-')
			sign *= -1;
		index++;
	}
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		if (result != ((result * 10) + nptr[index] - '0') / 10)
			return ((sign + 1) / 2 / -1);
		result = result * 10 + (nptr[index] - '0');
		index++;
	}
	return (result * sign);
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
		pthread_mutex_lock(&(scene->stdout_mtx));
		printf("%ld %d %s\n", get_time() - scene->start_time, id, action);
		pthread_mutex_unlock(&(scene->stdout_mtx));
	}
}

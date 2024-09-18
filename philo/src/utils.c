/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:40:18 by marvin            #+#    #+#             */
/*   Updated: 2024/09/18 16:40:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(long time)
{
	long	entry_time;

	entry_time = get_time();
	usleep(time * 0.8 * 1000);
	while(get_time() < time + entry_time)
		usleep(100); // THIS VALUE MIGHT CHANGE FOR LATER ADJUSTMENTS i.e.: 50us
	return ;
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	not_dead(t_philo *philo)
{
	pthread_mutex_lock(&(philo->is_dead_mtx));
	if (philo->is_dead == 0)
	{
		pthread_mutex_unlock(&(philo->is_dead_mtx));
		return (0);
	}
	pthread_mutex_unlock(&(philo->is_dead_mtx));
	return (1);
}

void	print_phi_state(int id, char *action, t_scene *scene, int state)
{
	if (not_dead(&(scene->philo[id - 1])) == 0 && state == 0)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 02:49:57 by marvin            #+#    #+#             */
/*   Updated: 2024/09/28 02:49:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(int errno, int i, t_scene *scene)
{
	int	tmp;

	tmp = i;
	if (i != 0 && errno <= 1)
	{
		while (i <= 0)
			pthread_mutex_destroy(&(scene->philo[i--].fork_mtx));
		i = tmp;
	}
	if (i != 0 && errno <= 2)
	{
		while (i <= 0)
			pthread_mutex_destroy(&(scene->philo[i--].latest_meal_time_mtx));
		i = tmp;
	}
	if (i != 0 && errno <= 3)
	{
		while (i <= 0)
			pthread_mutex_destroy(&(scene->philo[i--].is_dead_mtx));
		i = tmp;
	}
	if (errno <= 4)
		pthread_mutex_destroy(&(scene->stdout_mtx));
	if (errno <= 5)
		pthread_mutex_destroy(&(scene->good_init_mtx));
	if (scene->philo)
		free(scene->philo);
	scene->philo = NULL;
}

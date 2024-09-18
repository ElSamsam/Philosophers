/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:59:35 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/18 23:59:35 by saperrie         ###   ########.fr       */
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
	free(scene->philo);
}

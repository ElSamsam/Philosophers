/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:57:03 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/18 23:57:03 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	local_philo_init(t_scene *scene, int i)
{
	scene->philo[i].scene = scene;
	scene->philo[i].id = i + 1;
	scene->philo[i].fork = 1;
	scene->philo[i].latest_meal_time = 0;
	scene->philo[i].is_dead = 0;
	scene->philo[i].nbr_meals_eaten = 0;
}

int	init_philo(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nbr_philo)
	{
		if (0 != pthread_mutex_init(&(scene->philo[i].fork_mtx), NULL))
			return (free_all(1, i - 1, scene), 1);
		if (0 != pthread_mutex_init(&(scene->philo[i].latest_meal_time_mtx), \
			NULL))
			return (free_all(2, i - 1, scene), 1);
		if (0 != pthread_mutex_init(&(scene->philo[i].is_dead_mtx), NULL))
			return (free_all(3, i - 1, scene), 1);
		if (i == scene->nbr_philo - 1)
		{
			scene->philo[i].next_fork = &(scene->philo[0].fork);
			scene->philo[i].next_fork_mtx = &(scene->philo[0].fork_mtx);
		}
		else
		{
			scene->philo[i].next_fork = &(scene->philo[i + 1].fork);
			scene->philo[i].next_fork_mtx = &(scene->philo[i + 1].fork_mtx);
		}
		local_philo_init(scene, i++);
	}
	return (0);
}

int	init_scene(t_scene *scene)
{
	scene->philo = malloc(sizeof(t_philo) * scene->nbr_philo);
	if (!scene->philo)
		return (1);
	if (init_philo(scene) == 1)
		return (1);
	if (0 != pthread_mutex_init(&(scene->stdout_mtx), NULL))
		return (free_all(4, scene->nbr_philo - 1, scene), 1);
	if (0 != pthread_mutex_init(&(scene->good_init_mtx), NULL))
		return (free_all(5, scene->nbr_philo - 1, scene), 1);
	scene->good_init = 0;
	return (0);
}

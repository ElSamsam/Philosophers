/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:03:36 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/19 00:03:36 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_death_status(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nbr_philo)
	{
		pthread_mutex_lock(&scene->philo[i].is_dead_mtx);
		scene->philo[i].is_dead = 1;
		pthread_mutex_unlock(&scene->philo[i++].is_dead_mtx);
	}
}

int	is_dead(int i, t_scene *scene, long current_time, int *nbr_philos_out)
{
	long	death_time;
	long	nbr_of_meals;

	pthread_mutex_lock(&scene->philo[i].latest_meal_time_mtx);
	death_time = scene->philo[i].latest_meal_time + scene->time_to_die;
	nbr_of_meals = scene->philo[i].nbr_meals_eaten;
	pthread_mutex_unlock(&scene->philo[i].latest_meal_time_mtx);
	if (death_time <= current_time)
	{
		update_death_status(scene);
		print_philo_state(i + 1, DIE, scene, 1);
		return (1);
	}
	if (scene->nbr_of_meals != -1 && nbr_of_meals >= scene->nbr_of_meals)
	{
		pthread_mutex_lock(&scene->philo[i].is_dead_mtx);
		scene->philo[i].is_dead = 1;
		pthread_mutex_unlock(&scene->philo[i].is_dead_mtx);
		*nbr_philos_out += 1;
	}
	return (0);
}

int	still_alive(t_philo *philo)
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

void	status_check(t_scene *scene)
{
	int		i;
	long	current_time;
	int		nbr_philos_out;

	nbr_philos_out = 0;
	while (1)
	{
		i = 0;
		while (i < scene->nbr_philo)
		{
			if (still_alive(&(scene->philo[i])) == 1)
			{
				i += 1;
				continue ;
			}
			current_time = get_time() - scene->start_time;
			if (is_dead(i, scene, current_time, &nbr_philos_out))
				return ;
			if (nbr_philos_out >= scene->nbr_philo)
				return ;
			i += 1;
		}
		usleep(1000);
	}
}

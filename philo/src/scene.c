/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:46:19 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/18 23:46:19 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	int	fork_in_my_hand[2];

	fork_in_my_hand[0] = 0;
	fork_in_my_hand[1] = 0;
	while (!fork_in_my_hand[0] || !fork_in_my_hand[1])
	{
		pthread_mutex_lock(&philo->fork_mtx);
		if (philo->fork == 1)
		{
			philo->fork = 0;
			fork_in_my_hand[0] = 1;
		}
		pthread_mutex_unlock(&philo->fork_mtx);
		pthread_mutex_lock(philo->next_fork_mtx);
		if (*(philo->next_fork) == 1)
		{
			*(philo->next_fork) = 0;
			fork_in_my_hand[1] = 1;
		}
		pthread_mutex_unlock(philo->next_fork_mtx);
		usleep(200);
	}
	print_philo_state(philo->id, EAT, philo->scene, 0);
	pthread_mutex_lock(&(philo->latest_meal_time_mtx));
	philo->latest_meal_time = get_time() - philo->scene->start_time;
	philo->nbr_meals_eaten += 1;
	pthread_mutex_unlock(&(philo->latest_meal_time_mtx));
	ft_sleep(philo->scene->time_to_eat);
	pthread_mutex_lock(&philo->fork_mtx);
	philo->fork = 1;
	pthread_mutex_unlock(&philo->fork_mtx);
	pthread_mutex_lock(philo->next_fork_mtx);
	*(philo->next_fork) = 1;
	pthread_mutex_unlock(philo->next_fork_mtx);
	fork_in_my_hand[1] = 0;
	fork_in_my_hand[0] = 0;
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = philosopher;
	print_philo_state(philo->id, THINK, philo->scene, 0);
	if (philo->id % 2 != 0)
		ft_sleep(0.8 * philo->scene->time_to_eat);
	while (still_alive(philo) == 0)
	{
		eat(philo);
		print_philo_state(philo->id, SLEEP, philo->scene, 0);
		ft_sleep(philo->scene->time_to_sleep);
		print_philo_state(philo->id, THINK, philo->scene, 0);
	}
	return (NULL);
}

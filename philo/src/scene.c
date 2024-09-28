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

char	fork_play(t_philo *philo, int *fork_in_my_hand)
{
	while (!fork_in_my_hand[0] || !fork_in_my_hand[1])
	{
		pthread_mutex_lock(&philo->is_dead_mtx);
		if (philo->is_dead == 1)
			return (pthread_mutex_unlock(&philo->is_dead_mtx), 0);
		pthread_mutex_unlock(&philo->is_dead_mtx);
		pthread_mutex_lock(&philo->fork_mtx);
		if (philo->fork == 1)
		{
			philo->fork = 0;
			fork_in_my_hand[0] = 1;
			print_philo_state(philo->id, FORK, philo->scene, 0);
		}
		pthread_mutex_unlock(&philo->fork_mtx);
		pthread_mutex_lock(philo->next_fork_mtx);
		if (*(philo->next_fork) == 1)
		{
			*(philo->next_fork) = 0;
			fork_in_my_hand[1] = 1;
			print_philo_state(philo->id, FORK, philo->scene, 0);
		}
		pthread_mutex_unlock(philo->next_fork_mtx);
		usleep(200);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	int	fork_in_my_hand[2];

	fork_in_my_hand[0] = 0;
	fork_in_my_hand[1] = 0;
	fork_play(philo, fork_in_my_hand);
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
	while (1)
	{
		pthread_mutex_lock(&(philo->scene->good_init_mtx));
		if (philo->scene->good_init == -1)
			return (pthread_mutex_unlock(&(philo->scene->good_init_mtx)), NULL);
		else if (philo->scene->good_init == 1)
			break ;
		pthread_mutex_unlock(&(philo->scene->good_init_mtx));
	}
	pthread_mutex_unlock(&(philo->scene->good_init_mtx));
	print_philo_state(philo->id, THINK, philo->scene, 0);
	if (philo->id % 2 != 0)
		ft_sleep(0.8 * philo->scene->time_to_eat);
	while (dead_philos(philo) == 0)
	{
		eat(philo);
		print_philo_state(philo->id, SLEEP, philo->scene, 0);
		ft_sleep(philo->scene->time_to_sleep);
		print_philo_state(philo->id, THINK, philo->scene, 0);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:00:12 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/17 17:23:33 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>


# define TOO_FEW_ARGS "too few args\nor too many..\n"
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define FORK "has taken a fork"
# define DIE "died"

typedef struct s_scene
{
	t_philo			*philo;
	unsigned int	nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_of_meals;
	pthread_mutex_t	stdout_mtx;
}	t_scene;

typedef struct s_philo
{
	t_scene			*scene;
	unsigned int	philo_id;
	// unsigned int	next_philo_id;
	int				fork;
	pthread_mutex_t	fork_mtx;
	int				*next_fork;
	pthread_mutex_t	*next_fork_mtx;
	long			latest_meal_time;
	bool			is_dead;
}	t_philo;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:00:12 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/18 17:37:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

# define TOO_FEW_ARGS "too few args\nor too many..\n"
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define FORK "has taken a fork"
# define DIE "died"

typedef struct s_scene
{
	struct s_philo			*philo;
	unsigned int	nbr_philo;
	long			start_time;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nbr_of_meals;
	pthread_mutex_t	stdout_mtx;
}	t_scene;

typedef struct s_philo
{
	t_scene			*scene;
	unsigned int	id;
	// unsigned int	next_philo_id;
	pthread_t		thread;
	int				fork;
	pthread_mutex_t	fork_mtx;
	int				*next_fork;
	pthread_mutex_t	*next_fork_mtx;
	long			latest_meal_time;
	int				is_dead;
}	t_philo;

void	ft_sleep(long time);
long	get_time(void);
void	print_phi_state(int id, char *action, t_scene *scene);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:00:12 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/24 14:31:08 by saperrie         ###   ########.fr       */
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
	struct s_philo	*philo;
	long			nbr_philo;
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
	pthread_t		thread;
	int				fork;
	pthread_mutex_t	fork_mtx;
	int				*next_fork;
	pthread_mutex_t	*next_fork_mtx;
	long			latest_meal_time;
	pthread_mutex_t	latest_meal_time_mtx;
	int				is_dead;
	pthread_mutex_t	is_dead_mtx;
	long			nbr_meals_eaten;
}	t_philo;

// SCENE
void			*routine(void *philosopher);
void			eat(t_philo *philo);

// STATUS
void			status_check(t_scene *scene);
int				dead_philos(t_philo *philo);

// FREE
void			free_all(int errno, int i, t_scene *scene);

// INIT
int				init_scene(t_scene *scene);
int				init_philo(t_scene *scene);

// UTILS
unsigned int	ft_strlen(char *s);
long			super_atoi(char const *input);
void			ft_sleep(long time);
long			get_time(void);
void			print_philo_state(int id, char *action, t_scene *scene, \
	int state);
int				parse_user_input(int argc, char *argv[], t_scene *scene);

#endif

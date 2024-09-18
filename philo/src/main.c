/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:06:51 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/18 17:03:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	ft_strlen(char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(char const *nptr)
{
	int			index;
	int			sign;
	int long	result;

	index = 0;
	sign = 1;
	result = 0;
	while (nptr[index] == ' '
		|| (nptr[index] >= '\t' && nptr[index] <= '\r'))
		index++;
	if (nptr[index] == '+' || nptr[index] == '-')
	{
		if (nptr[index] == '-')
			sign *= -1;
		index++;
	}
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		if (result != ((result * 10) + nptr[index] - '0') / 10)
			return ((sign + 1) / 2 / -1);
		result = result * 10 + (nptr[index] - '0');
		index++;
	}
	return (result * sign);
}

void	free_all(int errno, int i, t_scene *scene)
{
	if (i != 0 && errno <= 1)
	{
		while (i <= 0)
			pthread_mutex_destroy(&(scene->philo[i--].fork_mtx));
	}
	// if (errno <= 2)
		// ;
	if (errno <= 3)
		pthread_mutex_destroy(&(scene->stdout_mtx));
	free(scene->philo);
}

int	init_philo(t_scene *scene)
{
	unsigned int i;

	i = 0;
	while (i < scene->nbr_philo)
	{
		scene->philo[i].scene = scene;
		scene->philo[i].id = i + 1;
		scene->philo[i].fork = 1;
		if (0 != pthread_mutex_init(&(scene->philo[i].fork_mtx), NULL))
			return (free_all(0, i - 1, scene), 1);
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
		scene->philo[i].latest_meal_time = 0;
		scene->philo[i].is_dead = 0;
		i += 1;
	}
	return (0);
}

int	init_scene(t_scene *scene)
{
	scene->philo = malloc(sizeof(t_philo) * scene->nbr_philo);
	if (!scene->philo)
		return (write(2, "BAD\n", 4), 1);
	if (init_philo(scene) == 1)
		return (1);
	if (0 != pthread_mutex_init(&(scene->stdout_mtx), NULL))
		return (free_all(2, scene->nbr_philo - 1, scene), 1);
	return (0);
}


void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = philosopher;
	printf("timestamp: %ld\n", get_time() - philo->scene->start_time);
	ft_sleep(1000);
	printf("timestamp: %ld\n", get_time() - philo->scene->start_time);
	printf("ID %d\n", philo->id);
	return (NULL);
}

int	start_simulation(t_scene *scene)
{
	unsigned int	i;

	i = 0;
	scene->start_time = get_time();
	while (i < scene->nbr_philo)
	{
		if (0 != pthread_create(&(scene->philo[i].thread), NULL, routine, &(scene->philo[i])))
		{
			while (i > 0)
				pthread_join(scene->philo[--i].thread, NULL);
			return (free_all(3, scene->nbr_philo - 1, scene), 1);
		}
		i += 1;
	}
	while (i > 0)
		pthread_join(scene->philo[--i].thread, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (argc < 5 || argc > 6)
		return (write(2, TOO_FEW_ARGS, ft_strlen(TOO_FEW_ARGS)), 0);
	scene.nbr_philo = ft_atoi(argv[1]);
	// check ret_val
	scene.time_to_die = ft_atoi(argv[2]);
	scene.time_to_eat = ft_atoi(argv[3]);
	scene.time_to_sleep = ft_atoi(argv[4]);
	scene.nbr_of_meals = -1;
	if (argc == 6)
		scene.nbr_of_meals = ft_atoi(argv[5]);
	if (init_scene(&scene) == 1)
		return (1);
	start_simulation(&scene);
	// check philo alloc
}

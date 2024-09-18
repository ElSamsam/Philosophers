/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:06:51 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/18 20:57:10 by marvin           ###   ########.fr       */
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
		if (0 != pthread_mutex_init(&(scene->philo[i].latest_meal_time_mtx), NULL))
			return (free_all(1, i - 1, scene), 1);
		if (0 != pthread_mutex_init(&(scene->philo[i].is_dead_mtx), NULL))
			return (free_all(2, i - 1, scene), 1);
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
		scene->philo[i].meals_eaten = 0;
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
		return (free_all(3, scene->nbr_philo - 1, scene), 1);
	return (0);
}

void	eat(t_philo *philo)
{
	int	forks_in_my_hands[2];

	forks_in_my_hands[0] = 0;
	forks_in_my_hands[1] = 0;
	while (!forks_in_my_hands[0] || !forks_in_my_hands[1])
	{
		pthread_mutex_lock(&philo->fork_mtx);
		if (philo->fork == 1)
		{
			philo->fork = 0;
			forks_in_my_hands[0] = 1;
		}
		pthread_mutex_unlock(&philo->fork_mtx);
		pthread_mutex_lock(philo->next_fork_mtx);
		if (*(philo->next_fork) == 1)
		{
			*(philo->next_fork) = 0;
			forks_in_my_hands[1] = 1;
		}
		pthread_mutex_unlock(philo->next_fork_mtx);
		usleep(200);
	}
	print_phi_state(philo->id, EAT, philo->scene, 0);
	pthread_mutex_lock(&(philo->latest_meal_time_mtx));
	philo->latest_meal_time = get_time() - philo->scene->start_time;
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&(philo->latest_meal_time_mtx));
	ft_sleep(philo->scene->time_to_eat);
	pthread_mutex_lock(&philo->fork_mtx);
	philo->fork = 1;
	pthread_mutex_unlock(&philo->fork_mtx);
	pthread_mutex_lock(philo->next_fork_mtx);
	*(philo->next_fork) = 1;
	pthread_mutex_unlock(philo->next_fork_mtx);
	forks_in_my_hands[1] = 0;
	forks_in_my_hands[0] = 0;
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = philosopher;
	print_phi_state(philo->id, THINK, philo->scene, 0);
	if (philo->id % 2 != 0)
		ft_sleep(0.8 * philo->scene->time_to_eat);
	while (not_dead(philo) == 0)
	{
		eat(philo);
		print_phi_state(philo->id, SLEEP, philo->scene, 0);
		ft_sleep(philo->scene->time_to_sleep);
		print_phi_state(philo->id, THINK, philo->scene, 0);
	}
	return (NULL);
}

void	update_death_status(t_scene *scene)
{
	unsigned int	i;

	i = 0;
	while (i < scene->nbr_philo)
	{
		pthread_mutex_lock(&scene->philo[i].is_dead_mtx);
		scene->philo[i].is_dead = 1;
		pthread_mutex_unlock(&scene->philo[i++].is_dead_mtx);
	}
}

int	is_dead(int i, t_scene *scene, long current_time, unsigned int *nbr_philos_out)
{
	long	death_time;
	long	nbr_of_meals;

	pthread_mutex_lock(&scene->philo[i].latest_meal_time_mtx);
	death_time = scene->philo[i].latest_meal_time + scene->time_to_die;
	nbr_of_meals = scene->philo[i].meals_eaten;
	pthread_mutex_unlock(&scene->philo[i].latest_meal_time_mtx);
	if (death_time < current_time)
	{
		update_death_status(scene);
		print_phi_state(i + 1, DIE, scene, 1);
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

void	status_check(t_scene *scene)
{
	unsigned int	i;
	unsigned int	nbr_philos_out;

	nbr_philos_out = 0;
	while (1)
	{
		i = 0;
		while (i < scene->nbr_philo)
		{
			if (not_dead(&(scene->philo[i])) == 1)
			{
				i += 1;
				continue ;
			}
			if (is_dead(i, scene, get_time() - scene->start_time, &nbr_philos_out))
				return ;
			if (nbr_philos_out >= scene->nbr_philo)
				return ;
			i += 1;
		}
		usleep(1000);
	}
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
			return (free_all(4, scene->nbr_philo - 1, scene), 1);
		}
		i += 1;
	}
	status_check(scene);
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
	// print is thinking and is dead at appropriate death time if philo is alone
	// Handle parsing too
	if (init_scene(&scene) == 1)
		return (1);
	start_simulation(&scene);
	free_all(5, scene.nbr_philo - 1, &scene);
}

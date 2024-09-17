/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:06:51 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/17 17:24:34 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_scene *scene)
{
	int		i;

	i = 0;
	while (i < scene->nbr_philo)
	{
		scene->philo[i].scene = scene;
		scene->philo[i].philo_id = i + 1;
		scene->philo[i].fork = 1;
		if (i == scene->nbr_philo - 1)
		{
			scene->philo[i].next_fork = &scene->philo[0].fork;
			scene->philo[i].next_for_mtx;
		}
		else
			scene->philo[i].next_fork = &scene->philo[i + 1].fork;
		scene->philo[i].latest_meal_time = 0;
		scene->philo[i].is_dead = 0;
		i += 1;
	}
}

void	init_scene(t_scene *scene)
{
	scene->philo = malloc(sizeof(t_philo) * nbr_philo);
	if (!scene->philo)
	{
		write(2, "BAD\n", 4);
		return ;
	}
	init_philo(scene);
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
	if (argc == 6)
		scene.nbr_of_meals = ft_atoi(argv[5]);
	init_scene(&scene);
	// check philo alloc
}

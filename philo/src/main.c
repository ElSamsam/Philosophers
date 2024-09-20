/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:06:51 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/20 01:53:02 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_scene(t_scene *scene)
{
	int	i;

	i = 0;
	scene->start_time = get_time();
	while (i < scene->nbr_philo)
	{
		if (0 != pthread_create(&(scene->philo[i].thread), \
				NULL, routine, &(scene->philo[i])))
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
	// Handle parsing too
	if (init_scene(&scene) == 1)
		return (1);
	start_scene(&scene);
	free_all(5, scene.nbr_philo - 1, &scene);
}

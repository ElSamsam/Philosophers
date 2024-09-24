/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:06:51 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/24 14:27:47 by saperrie         ###   ########.fr       */
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

	if (parse_user_input(argc, argv, &scene) == 1)
		return (1);
	if (init_scene(&scene) == 1)
		return (1);
	start_scene(&scene);
	free_all(5, scene.nbr_philo - 1, &scene);
}

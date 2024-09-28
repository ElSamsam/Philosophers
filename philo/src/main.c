/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:06:51 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/28 14:09:37 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	bad_init(t_scene *scene)
{
	pthread_mutex_lock(&(scene->good_init_mtx));
	scene->good_init = -1;
	pthread_mutex_unlock(&(scene->good_init_mtx));
}

int	start_scene(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->nbr_philo)
	{
		if (0 != pthread_create(&(scene->philo[i].thread), \
				NULL, routine, &(scene->philo[i])))
		{
			bad_init(scene);
			while (i > 0)
				pthread_join(scene->philo[--i].thread, NULL);
			return (free_all(5, scene->nbr_philo - 1, scene), 1);
		}
		i += 1;
	}
	scene->start_time = get_time();
	pthread_mutex_lock(&(scene->good_init_mtx));
	scene->good_init = 1;
	pthread_mutex_unlock(&(scene->good_init_mtx));
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
	free_all(6, scene.nbr_philo - 1, &scene);
}

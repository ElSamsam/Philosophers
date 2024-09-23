/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:06:51 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/23 02:38:17 by saperrie         ###   ########.fr       */
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

int	parse_user_input(int argc, char *argv[], t_scene *scene)
{
	char	*s;

	s = "./philo nbr_philo time_to_die time_to_eat time_to_sleep [nbr_meals]\n";
	if (argc < 5 || argc > 6)
		return (write(2, s, ft_strlen(s)), 1);
	scene->nbr_philo = super_atoi(argv[1]);
	scene->time_to_die = super_atoi(argv[2]);
	scene->time_to_eat = super_atoi(argv[3]);
	scene->time_to_sleep = super_atoi(argv[4]);
	scene->nbr_of_meals = -2;
	if (argc == 6)
		scene->nbr_of_meals = super_atoi(argv[5]);
	if (scene->nbr_philo == -4000000000 || scene->nbr_philo <= 0 \
		|| scene->time_to_die == -4000000000 || scene->time_to_die < 0 \
		|| scene->time_to_eat == -4000000000 || scene->time_to_eat <= 0 \
		|| scene->time_to_sleep == -4000000000 || scene->time_to_sleep <= 0 \
		|| scene->nbr_of_meals == -4000000000 || scene->nbr_of_meals == -1 \
		|| scene->nbr_of_meals == 0)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (parse_user_input(argc, argv, &scene) == 1)
		return (write(2, "bad_input\n", 10), 1);
	if (init_scene(&scene) == 1)
		return (1);
	start_scene(&scene);
	free_all(5, scene.nbr_philo - 1, &scene);
}

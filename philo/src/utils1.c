/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saperrie <saperrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:59:35 by saperrie          #+#    #+#             */
/*   Updated: 2024/09/18 23:59:35 by saperrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		|| scene->nbr_of_meals == 0 || scene->nbr_philo > 200)
		return (write(2, "wrong input\n", 12), 1);
	return (0);
}

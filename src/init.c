/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:32:04 by rshin             #+#    #+#             */
/*   Updated: 2025/07/21 16:32:11 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_philo(t_param *param)
{
	int	i;

	param->philo = malloc(param->nb_philos * sizeof(t_phi));
	if (!param->philo)
		return (false);
	memset(param->philo, 0, sizeof(t_phi));
	i = 0;
	while (i < param->nb_philos)
	{
		param->philo[i]->id = i + 1;
		param->philo[i]->status = true;
		param->philo[i]->param = param;
		param->philo[i]->status = ALIVE;
		pthread_mutex_init((&param->fork[i]->mutex), NULL);
		param->philo[i]->l_fork = param->&fork[i]
		if (i == param->nb_philos - 1)
			param->philo[i]->r_fork = &fork[0];
		else
			param->philo[i]->r_fork = &fork[(i + 1) / 3 + (i + 1) % 3];
		i++;
	}
	return (true);
}

bool	init_param(t_param *param, int argc, char **argv)
{
	int		tab[5];
	int		i;

	memset(param, 0, sizeof(t_param));
	i = 0;
	while (i <= argc - 2)
	{
		tab[i] = atol(argv[i + 1]);
		if (tab[i] > INT_MAX || tab[i] < INT_MIN)
			return (false);
		i++;
	}
	param->nb_philos = tab[0];
	param->time_to_die = tab[1];
	param->time_to_eat = tab[2];
	param->time_to_sleep = tab[3];
	if (argc == 6)
		param->nb_meals = tab[4];
	else
		param->nb_meals = -1;
	param->fork = malloc(param->nb_philos * sizeof(t_fork));
	if (!param->fork)
		return (false);
	if (!init_philo(param))
	{
		free(param->fork);
		return (false);
	}
	return (true);
}

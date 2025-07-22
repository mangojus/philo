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

bool	init_philo(t_data *data)
{
	int	i;

	data->philo = malloc(data->nb_philos * sizeof(t_phi));
	if (!data->philo)
		return (false);
	memset(data->philo, 0, sizeof(t_phi));
	i = 0;
	while (i < data->nb_philos)
	{
		data->philo[i]->id = i + 1;
		data->philo[i]->status = true;
		i++;
	}
	return (true);
}

static bool	init_mutex(t_data *data)
{
	int	i;

	data->death = malloc(sizeof(pthread_mutex_t));
	if (!data->death)
		return (false);
	data->fork = malloc(data->nb_philos * sizeof(pthread_mutex_t));
	if (!data->fork)
	{
		free(data->death);
		return (false);
	}
	if (pthread_mutex_init(data->death, NULL) == -1)
	{
		free(data->death);
		free(data->fork);
		return (false);
	}
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) == -1)
			return (false);
		i++;
	}
	return (true);
}

bool	init_data(t_data *data, int argc, char **argv)
{
	int		tab[5];
	int		i;

	memset(data, 0, sizeof(t_data));
	i = 0;
	while (i <= argc - 2)
	{
		tab[i] = atol(argv[i + 1]);
		if (tab[i] > INT_MAX || tab[i] < INT_MIN)
			return (false);
		i++;
	}
	data->nb_philos = tab[0];
	data->time_to_die = tab[1];
	data->time_to_eat = tab[2];
	data->time_to_sleep = tab[3];
	if (argc == 6)
		data->nb_meals = tab[4];
	else
		data->nb_meals = -1;
	if (!init_philo(data))
		return (false);
	if (!init_mutex(data))
	{
		free(data->philo);
		return (false);
	}
	return (true);
}

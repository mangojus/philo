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

bool	init_table(t_data *data)
{
	int	i;

	data->philos = malloc(data->tab[0] * sizeof(pthread_t));
	if (!data->philos)
		return (false);
	i = 0;
//	while (i < data->tab[0])
//		pthread_create(data->philos[i], NULL, &routine, NULL);
	return (true);
	data->forks = malloc(data->tab[0] * sizeof(pthread_t));
	if (!data->forks)
	{
		free(data->philos);
		return (false);
	}
	i = 0;
	while (i < data->tab[0])
	{
		data->forks->id = i;
		data->philos->id = i + 1;
		i++;
	}
}

bool	init_data(t_data *data, int argc, char **argv)
{
	int		i;

	pthread_mutex_init(&mutex, NULL);
	memset(data, 0, sizeof(t_data));
	i = 0;
	while (i <= argc - 2)
	{
		data->tab[i] = atol(argv[i + 1]);
		if (data->tab[i] > INT_MAX || data->tab[i] < INT_MIN)
		{
			free(data->tab);
			return (false);
		}
		i++;
	}
	if (!init_table(data))
	{
		free(data->tab);
		return (false);
	}
}

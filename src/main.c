/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:39:46 by rshin             #+#    #+#             */
/*   Updated: 2025/07/21 16:31:31 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

void	*routine(void)
{
	while (i < 10)
	
}

void	run_prog(t_data *data)
{
	pthread_mutex_lock(data->fork);
	
	pthread_mutex_unlock(data->fork);
}

bool	args_checker(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (false);
	i = 1;
	while (argv[i])
	{
		j = 0;
		if ((argv[i][0] == '-' || argv[i][0] == '+') && argv[i][1])
			j++;
		while (argv[i][j])
		{
			if (!is_digit(argv[i][j++]))
				return (false);
		}
		i++;
	}
	return (true);
}

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

int	main(int argc, char **argv)
{
	t_data	data;

	if (!args_checker(argc, argv))
		return (EXIT_FAILURE);
	if (!init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	run_prog(&data);
	pthread_mutex_destroy(&mutex);
	return (EXIT_SUCCESS);
}

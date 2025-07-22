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

void	*loop(void *arg)
{
	t_phi	*philo;

	philo = (t_phi *)arg;
	while (true)
	{
		if (philo
	}
}

void	assign_forks(void)
{
	
}

bool	run_thread(t_data *data, t_phi *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&(philo[i]->tid), NULL, &loop, philo[i]))
			return (false)
		philo[i]->status = true;
		i++;
	}
	return (true);
}

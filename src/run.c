/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:39:46 by rshin             #+#    #+#             */
/*   Updated: 2025/07/22 15:07:43 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

void	*loop(void *arg)
{
	t_phi	*philo;

	philo = (t_phi *)arg;
	while (true)
	{
		if (!philo->start)
			continue;
		eat;
		sleep;
		think;
	}
}

void	assign_forks(void)
{
	
}

bool	run_thread(t_data *data, t_phi *philo)
{
	int		i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&(philo[i]->tid), NULL, &loop, philo[i]))
			return (false)
		philo[i]->status = true;
		i++;
	}
	if (i == data->nb_philos)
		data->i(*philo)->start = true;
	monitor;
	return (true);
}

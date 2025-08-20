/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:46:50 by rshin             #+#    #+#             */
/*   Updated: 2025/08/20 19:04:40 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	take_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mtx);
	if (fork->is_taken == false)
	{
		fork->is_taken = true;
		pthread_mutex_unlock(&fork->mtx);
		return (true);
	}
	pthread_mutex_unlock(&fork->mtx);
	return (false);
}

void	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mtx);
	fork->is_taken = false;
	pthread_mutex_unlock(&fork->mtx);
}

bool	assign_forks(t_phi *p)
{
	while (true)
	{
		if (!take_fork(p->f[0]))
			continue;
		if (!print_output(p, "has taken a fork"))
			return (false);
		if (!take_fork(p->f[1]))
		{
			drop_fork(p->f[0]);
			usleep(500);
			continue;
		}
		if (!print_output(p, "has taken a fork"))
			return (false);
		else
			break ;
	}
	return (true);
}

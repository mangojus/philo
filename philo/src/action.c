/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <rshin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:46:50 by rshin             #+#    #+#             */
/*   Updated: 2025/08/27 16:09:15 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	take_fork(t_fork *fork)
{
	pthread_mutex_lock(fork->mtx);
	if (fork->is_taken == false)
	{
		fork->is_taken = true;
		pthread_mutex_unlock(fork->mtx);
		return (true);
	}
	pthread_mutex_unlock(fork->mtx);
	return (false);
}

void	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(fork->mtx);
	fork->is_taken = false;
	pthread_mutex_unlock(fork->mtx);
}

bool	assign_forks(t_phi *p)
{
	while (!check_death(p->cfg))
	{
		if (!take_fork(p->f[0]))
			continue ;
		if (!take_fork(p->f[1]))
		{
			drop_fork(p->f[0]);
			usleep(200);
			continue ;
		}
		print_output(p, "has taken a fork");
		print_output(p, "has taken a fork");
		print_output(p, "is eating");
		return (true);
	}
	return (false);
}

bool	eat(t_phi *p)
{
	print_output(p, "stopped here");
	if (!assign_forks(p))
		return (false);
	if (check_full(p))
	{
		drop_fork(p->f[0]);
		drop_fork(p->f[1]);
		return (false);
	}
	smart_sleep(p->cfg->time_to_eat);
	drop_fork(p->f[0]);
	drop_fork(p->f[1]);
	return (true);
}

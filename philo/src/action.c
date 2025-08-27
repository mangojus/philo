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
		if (check_death(p->cfg))
		{
			drop_fork(p->f[0]);
			drop_fork(p->f[1]);
			break ;
		}
		print_output(p, "has taken a fork");
		print_output(p, "has taken a fork");
		return (true);
	}
	return (false);
}

bool	eat(t_phi *p)
{
	if (!assign_forks(p))
		return (false);
	print_output(p, "is eating");
	if (check_full(p))
	{
		drop_fork(p->f[0]);
		drop_fork(p->f[1]);
		return (false);
	}
	smart_sleep(p->cfg->time_to_eat, p->cfg);
	drop_fork(p->f[0]);
	drop_fork(p->f[1]);
	return (true);
}

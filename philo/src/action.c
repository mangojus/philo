/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <rshin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:46:50 by rshin             #+#    #+#             */
/*   Updated: 2025/09/04 08:57:52 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	take_fork(t_fork *fork)
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

static void	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(fork->mtx);
	fork->is_taken = false;
	pthread_mutex_unlock(fork->mtx);
}

static void	drop_forks(t_phi *p)
{
	drop_fork(p->f[0]);
	drop_fork(p->f[1]);
}

static bool	assign_forks(t_phi *p)
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
		return (true);
	}
	return (false);
}

bool	eat(t_phi *p)
{
	if (!assign_forks(p))
		return (false);
	pthread_mutex_lock(p->meal.mtx);
	p->meal.last = get_time();
	p->meal.count++;
	pthread_mutex_unlock(p->meal.mtx);
	if (!print_output(p, "is eating"))
	{
		drop_forks(p);
		return (false);
	}
	smart_sleep(p->cfg->eat_t);
	drop_forks(p);
	if (check_full(p))
		return (false);
	return (true);
}

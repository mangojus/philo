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
	while (!check_death(p->cfg))
	{
		usleep(2000);
		if (!take_fork(p->f[1]))
			continue;
		if (check_death(p->cfg))
			return (false);
		print_output(p, "has taken a fork");
		while (!take_fork(p->f[0]))
		{
//			drop_fork(p->f[0]);
			continue;
		}
		if (check_death(p->cfg))
			return (false);
		print_output(p, "has taken a fork");
		return (true);
	}
	return (false);
}

bool	action(t_phi *p, t_act action)
{
	if (check_death(p->cfg))
		return (false);
	if (action == THINK)
		print_output(p, "is thinking");
	if (action == EAT)
	{
		if (!assign_forks(p))
			return (false);
		print_output(p, "is eating");
		smart_sleep(p->cfg->time_to_eat);
		drop_fork(p->f[1]);
		drop_fork(p->f[0]);
		if (check_death(p->cfg))
			return (false);
		if (check_full(p))
			return (false);
	}
	if (action == SLEEP)
	{
		print_output(p, "is sleeping");
		smart_sleep(p->cfg->time_to_sleep);
	}
	return (true);
}

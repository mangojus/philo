/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:39:46 by rshin             #+#    #+#             */
/*   Updated: 2025/08/27 18:41:21 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	smart_sleep(long duration, t_cfg *cfg)
{
	long	end_time;

	end_time = get_time() + duration;
	while (end_time > get_time())
	{
		if (check_death(cfg))
			break ;
		usleep(100);
	}
}

void	sync_time(long target_t)
{
	long	rem_t;

	rem_t = target_t - get_time();
	if (rem_t > 0)
		usleep(rem_t * 1000);
}

bool	check_full(t_phi *p)
{
	pthread_mutex_lock(p->meal.mtx);
	p->meal.last = get_time();
	p->meal.count++;
	if (p->meal.count == p->cfg->max_meals && p->cfg->max_meals != 0)
	{
		pthread_mutex_lock(p->cfg->death_mtx);
		p->cfg->full++;
		pthread_mutex_unlock(p->cfg->death_mtx);
		pthread_mutex_unlock(p->meal.mtx);
		return (true);
	}
	pthread_mutex_unlock(p->meal.mtx);
	return (false);
}

bool	check_death(t_cfg *cfg)
{
	pthread_mutex_lock(cfg->death_mtx);
	if (cfg->death_flag == true)
	{
		pthread_mutex_unlock(cfg->death_mtx);
		return (true);
	}
	pthread_mutex_unlock(cfg->death_mtx);
	return (false);
}

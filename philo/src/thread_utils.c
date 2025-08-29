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

bool	philos_full(t_cfg *cfg)
{
	pthread_mutex_lock(cfg->full_mtx);
	if (cfg->full == cfg->nb_philos)
	{
		pthread_mutex_unlock(cfg->full_mtx);
		return (true);
	}
	pthread_mutex_unlock(cfg->full_mtx);
	return (false);
}

bool	philo_died(t_phi *p)
{
	long	elapsed_t;

	pthread_mutex_lock(p->meal.mtx);
	elapsed_t = get_time() - p->meal.last;
	pthread_mutex_unlock(p->meal.mtx);
	if (elapsed_t > p->cfg->time_to_die)
	{
		pthread_mutex_lock(p->cfg->death_mtx);
		p->cfg->death_flag = true;
		pthread_mutex_unlock(p->cfg->death_mtx);
		print_output(p, "died");
		return (true);
	}
	return (false);
}

bool	check_full(t_phi *p)
{
	pthread_mutex_lock(p->meal.mtx);
	p->meal.last = get_time();
	p->meal.count++;
	if (p->cfg->max_meals != 0 && p->meal.count == p->cfg->max_meals)
	{
		pthread_mutex_lock(p->cfg->full_mtx);
		p->cfg->full++;
		pthread_mutex_unlock(p->cfg->full_mtx);
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

bool	thread_barrier(t_cfg *cfg)
{
	pthread_mutex_lock(cfg->cfg_mtx);
	cfg->nb_threads++;
	if (cfg->status != ERR_OK)
	{
		pthread_mutex_unlock(cfg->cfg_mtx);
		return (false);
	}
	pthread_mutex_unlock(cfg->cfg_mtx);
	return (true);
}

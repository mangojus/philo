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
	if (cfg->full >= cfg->nb_philos)
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
	long	cur_t;

	pthread_mutex_lock(p->meal.mtx);
	elapsed_t = get_time() - p->meal.last;
	pthread_mutex_unlock(p->meal.mtx);
	if (elapsed_t > p->cfg->die_t && p->meal.last != -1)
	{
		pthread_mutex_lock(p->cfg->death_mtx);
		p->cfg->death_flag = true;
		pthread_mutex_unlock(p->cfg->death_mtx);
		pthread_mutex_lock(p->cfg->print_mtx);
		cur_t = get_time() - p->cfg->start_t;
		printf("%ld %d died\n", cur_t, p->id);
		pthread_mutex_unlock(p->cfg->print_mtx);
		return (true);
	}
	return (false);
}

bool	check_full(t_phi *p)
{
	pthread_mutex_lock(p->meal.mtx);
	p->meal.count++;
	if (p->cfg->max_meals != -1 && p->meal.count >= p->cfg->max_meals)
	{
		pthread_mutex_unlock(p->meal.mtx);
		pthread_mutex_lock(p->cfg->full_mtx);
		p->cfg->full++;
		pthread_mutex_unlock(p->cfg->full_mtx);
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

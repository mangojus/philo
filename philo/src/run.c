/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:39:46 by rshin             #+#    #+#             */
/*   Updated: 2025/08/27 18:40:49 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

void	*philo_loop(void *arg)
{
	t_phi	*p;
	long 	think_t;

	p = (t_phi *)arg;
//	if (!thread_barrier(p->cfg))
//		return (NULL);
	pthread_mutex_lock(p->meal.mtx);
	p->meal.last = p->cfg->start_t;
	pthread_mutex_unlock(p->meal.mtx);
	sync_time(p->cfg->start_t);
	if (check_full(p))
		return (NULL);
	if (check_death(p->cfg))
		return (NULL);
	print_output(p, "is thinking");
	if (p->id % 2 != 0)
		smart_sleep(p->cfg->eat_t / 2);
	while (!check_death(p->cfg))
	{
		if (!eat(p))
			break ;
		if (!print_output(p, "is sleeping"))
			break;
		smart_sleep(p->cfg->sleep_t);
		if (!print_output(p, "is thinking"))
			break ;
		if (p->cfg->nb_philos % 2 == 1)
		{
			think_t = (p->cfg->eat_t * 2) - p->cfg->sleep_t;
			if (think_t > 0)
				smart_sleep(think_t / 2);
			else
				usleep(1000);
		}
	}
	return (NULL);
}

static void	*monitor_loop(void *arg)
{
	t_env	*env;
	int		i;

	env = (t_env *)arg;
//	if (!thread_barrier(&env->cfg))
//		return (NULL);
	sync_time(env->cfg.start_t);
	while (true)
	{
		if (philos_full(&env->cfg))
			return (NULL);
		i = 0;
		while (i < env->cfg.nb_philos)
		{
			if (philo_died(&env->philos[i]))
				return (NULL);
			++i;
		}
		usleep(500);
	}
	return (NULL);
}

bool	run_simulation(t_env *env, t_phi *philos)
{
	int		i;

	env->cfg.start_t = get_time() + env->cfg.nb_philos + 1000;
	if (pthread_create(&env->monitor, NULL, &monitor_loop, env))
	{
		env->cfg.status = ERR_THREAD;
		return (false);
	}
	i = 0;
	while (i < env->cfg.nb_philos)
	{
		if (pthread_create((&philos[i].tid), NULL, &philo_loop, &philos[i]))
		{
			env->cfg.status = ERR_THREAD;
			break ;
		}
		++i;
	}
	while (--i >= 0)
		pthread_join(philos[i].tid, NULL);
	pthread_join(env->monitor, NULL);
	return (true);
}

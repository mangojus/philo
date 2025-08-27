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

	p = (t_phi *)arg;
	pthread_mutex_lock(p->meal.mtx);
	p->meal.last = p->cfg->start;
	pthread_mutex_unlock(p->meal.mtx);
	sync_time(p->cfg->start);
	if (p->cfg->status != ERR_OK)
		return (NULL);
	print_output(p, "is thinking");
	if (p->id % 2 != 0)
		smart_sleep(p->cfg->time_to_eat / 2, p->cfg);
	while (true)
	{
		if (!eat(p))
			break ;
		print_output(p, "is sleeping");
		smart_sleep(p->cfg->time_to_sleep, p->cfg);
		if (check_death(p->cfg))
			break ;
		print_output(p, "is thinking");
		if (p->cfg->nb_philos % 2 == 1)
		{
			usleep(200);
			if (p->cfg->time_to_sleep < p->cfg->time_to_eat)
				smart_sleep(p->cfg->time_to_sleep, p->cfg);
		}
		if (check_death(p->cfg))
			break ;
	}
	return (NULL);
}

static void	*monitor_loop(void *arg)
{
	t_env	*env;
	long	elapsed_time;
	int		i;

	env = (t_env *)arg;
	sync_time(env->cfg.start);
	if (env->cfg.status != ERR_OK)
		return (NULL);
	while (!check_death(&env->cfg))
	{
		i = 0;
		while (i < env->cfg.nb_philos && env->cfg.start != -1)
		{
			pthread_mutex_lock(env->philos[i].meal.mtx);
			elapsed_time = get_time() - env->philos[i].meal.last;
			pthread_mutex_unlock(env->philos[i].meal.mtx);
			if (elapsed_time > env->cfg.time_to_die)
			{
				print_output(&env->philos[i], "died");
				pthread_mutex_lock(env->cfg.death_mtx);
				env->cfg.death_flag = true;
				pthread_mutex_unlock(env->cfg.death_mtx);
				break ;
			}
			pthread_mutex_lock(env->cfg.death_mtx);
			if (env->cfg.full == env->cfg.nb_philos)
			{
				pthread_mutex_unlock(env->cfg.death_mtx);
				return (NULL);
			}
			pthread_mutex_unlock(env->cfg.death_mtx);
			++i;
		}
		usleep(100);
	}
	return (NULL);
}

bool	run_simulation(t_env *env, t_phi *philos)
{
	int		i;

	env->cfg.start = get_time() + env->cfg.nb_philos + 1000;
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
	env->cfg.nb_threads = i;
	while (--i >= 0)
		pthread_join(philos[i].tid, NULL);
	pthread_join(env->monitor, NULL);
	return (true);
}

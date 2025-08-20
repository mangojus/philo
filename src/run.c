/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:39:46 by rshin             #+#    #+#             */
/*   Updated: 2025/08/20 19:00:14 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

void	*philo_loop(void *arg)
{
	t_phi	*p;

	p = (t_phi *)arg;
	if (!thread_barrier(p->cfg))
		return (NULL);
	while (true)
	{
		if (!print_output(p, "is thinking"))
			break ;
		if (!assign_forks(p))
			break ;
		if (!print_output(p, "is eating"))
			break ;
		smart_sleep(p->cfg->time_to_eat);
		if (!check_full(p))
			break ;
		drop_fork(p->f[0]);
		drop_fork(p->f[1]);
		if (!print_output(p, "is sleeping"))
			break;
		smart_sleep(p->cfg->time_to_sleep);
	}
	return (NULL);
}

static void	*monitor_loop(void *arg)
{
	t_env	*env;
	long	elapsed_time;
	int		i;

	env = (t_env *)arg;
	if (!thread_barrier(&env->cfg))
		return (NULL);
	while (!check_death(&env->cfg))
	{
		i = 0;
		while (i < env->cfg.nb_philos)
		{
			pthread_mutex_lock(&env->philos[i].meal.mtx);
			elapsed_time = get_time() - env->philos[i].meal.last;
			pthread_mutex_unlock(&env->philos[i].meal.mtx);
			if (elapsed_time > env->cfg.time_to_die)
			{
				print_output(&env->philos[i], "is dead");
				pthread_mutex_lock(&env->cfg.death_mtx);
				env->cfg.death_flag = true;
				pthread_mutex_unlock(&env->cfg.death_mtx);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}

bool	run_simulation(t_env *env, t_phi *philos)
{
	int		i;

	if (pthread_create(&env->monitor, NULL, &monitor_loop, env))
		return (false);
	i = 0;
	while (i < env->cfg.nb_philos)
	{
		if (pthread_create((&philos[i].tid), NULL, &philo_loop, &philos[i]))
		{
			env->cfg.status = ERR_THREAD;
			break;
		}
		i++;
	}
	env->cfg.nb_threads = i + 1;
	if (i == env->cfg.nb_philos)
	{
		usleep(1000);
		env->cfg.start = get_time();
	}
	while (--i > 0)
		pthread_join(philos[i].tid, NULL);
	pthread_join(env->monitor, NULL);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:39:46 by rshin             #+#    #+#             */
/*   Updated: 2025/07/22 15:07:43 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

void	print_event(t_phi *p, t_stat status, long time)
{
	char	*msg;

	if (status == THINK)
		msg = "is thinking";
	if (status == EAT)
		msg = "is eating";
	if (status == SLEEP)
		msg = "is sleeping";
	printf("%ld %d %s\n", time, p->id, msg); 
}

static bool	event(t_phi *p, t_stat status, long	duration)
{
	long	time;

	pthread_mutex_lock(&p->rts->death_mtx);
	if (p->rts->death_flag == true)
	{
		pthread_mutex_unlock(&p->rts->death_mtx);
		return (false);
	}
	pthread_mutex_unlock(&p->rts->death_mtx);
	time = get_time();
	pthread_mutex_lock(&p->meal.mtx);
	if (status == EAT)
	{
		p->meal.last = time;
		p->meal.count++;
	}
	pthread_mutex_unlock(&p->meal.mtx);
	smart_sleep(duration);
	pthread_mutex_lock(&p->rts->print_mtx);
	print_event(p, status, time);
	pthread_mutex_unlock(&p->rts->print_mtx);
	return (true);
} 

void	*philo_loop(void *arg)
{
	t_phi	*p;

	p = (t_phi *)arg;
	while (!p->cfg->start)
		usleep(1000);
	while (true)
	{
		if (!event(p, THINK, 0))
			break;
		if (p->id % 2 == 0)
		{
			pthread_mutex_lock(&p->lfork->mtx);
			pthread_mutex_lock(&p->rfork->mtx);
		}
		else
		{
			pthread_mutex_lock(&p->rfork->mtx);
			pthread_mutex_lock(&p->lfork->mtx);
		}
		if (!event(p, EAT, p->cfg->time_to_eat))
			break ;
		pthread_mutex_unlock(&p->lfork->mtx);
		pthread_mutex_unlock(&p->rfork->mtx);
		if (!event(p, SLEEP, p->cfg->time_to_sleep))
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
	while (true)
	{
		i = 0;
		while (i < env->cfg.nb_philos)
		{
			pthread_mutex_lock(&env->philos[i].meal.mtx);
			elapsed_time = get_time() - env->philos[i].meal.last;
			if (elapsed_time > env->cfg.time_to_die)
			{
				pthread_mutex_unlock(&env->philos[i].meal.mtx);
				env->rts.death_flag = true;
				break ;
			}
			pthread_mutex_unlock(&env->philos[i].meal.mtx);
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
		if (pthread_create((&philos[i]), NULL, &philo_loop, &philos[i]))
			return (false)
		i++;
	}
	env->cfg.start = get_time() + (env->cfg.nb_philos *  );
	return (true);
}

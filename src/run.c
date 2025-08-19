/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:39:46 by rshin             #+#    #+#             */
/*   Updated: 2025/08/19 19:10:21 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

bool	check_death(t_rts *rts)
{
	pthread_mutex_lock(&p->rts->death_mtx);
	if (p->rts->death_flag == true)
	{
		pthread_mutex_unlock(&p->rts->death_mtx);
		return (false);
	}
	pthread_mutex_unlock(&p->rts->death_mtx);
	return (true);
}

void	print_output(long time, int id, char *msg)
{
	pthread_mutex_lock(&p->rts->print_mtx);
	printf("%ld %d %s\n", time, p->id, msg); 
	pthread_mutex_unlock(&p->rts->print_mtx);
}

static bool	action(t_phi *p, char *msg)
{
	long	time;

	if (!check_death(p->rts))
		return (false);
	time = get_time() - p->cfg->start;
	print_output(time, p->id, msg);
	return (true);
}

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

bool	drop_fork(t_fork *fork)
{
	
}

bool	take_forks(t_phi *p)
{
	int	first;
	int	second;

	while (true)
	{
		if (!check_death(p->rts))
			return (false);
		first = p->id % 2;
		second = 1 - first;
		pthread_mutex_lock(p->forks[first]->mtx);
		if (p->forks[first]->is_taken == false)
		{
			p->forks[first]->is_taken = true;
			pthread_mutex_unlock(p->forks[first]->mtx);
			if (!action(p, "has taken a fork"))
				return (false);
			pthread_mutex_lock(p->forks[second]->mtx);
			if (p->forks[second]->is_taken == false)
			{
				p->forks[second]->is_taken = true;
				pthread_mutex_unlock(p->forks[second]->mtx);
				if (!action(p, "has taken a fork"))
					return (false);
				break;
			}
			pthread_mutex_unlock(p->forks[second]->mtx);
			p->forks[first]->is_taken = false;
		}
		pthread_mutex_unlock(p->forks[first]->mtx);
	}
	return (true);
}

bool	drop_forks(t_phi *p)
{
	int	first;
	int	second;
	
	first = p->id % 2;
	second = 1 - first;
	pthread_mutex_lock(p->forks[first]->mtx);
	p->forks[first]->is_taken = false;
	pthread_mutex_unlock(p->forks[first]->mtx);
	pthread_mutex_lock(p->forks[second]->mtx);
	p->forks[second]->is_taken = false;
	pthread_mutex_unlock(p->forks[second]->mtx);
}

void	*philo_loop(void *arg)
{
	t_phi	*p;

	p = (t_phi *)arg;
	while (p->cfg->start == -1)
		continue;
//		usleep(1000);
	while (true)
	{
		if (!action(p, "is thinking", 0))
			break;
		if (!take_forks(p))
			break;
		if (!action(p, "is eating", p->cfg->time_to_eat))
		{
			drop_forks(p);
			break ;
		}
		smart_sleep(p->cfg->time_to_eat);
		pthread_mutex_lock(&p->meal.mtx);
		p->meal.last = time;
		p->meal.count++;
		if (p->meal.count == p->cfg->max_meals)
		{
			pthread_mutex_unlock(&p->meal.mtx);
			break;
		}
		pthread_mutex_unlock(&p->meal.mtx);
		drop_forks(p);
		if (!action(p, "is sleeping")
			break ;
		smart_sleep(p->cfg->time_to_sleep);
	}
	return (NULL);
}

static void	*monitor_loop(void *arg)
{
	t_env	*env;
	long	time;
	long	elapsed_time;
	int		i;
	int		c;

	env = (t_env *)arg;
	while (env->cfg.start == -1)
		continue;
//		usleep(1000);
	c = 0;
	while (true)
	{
		i = 0;
		while (i < env->cfg.nb_philos)
		{
			time = get_time() - env->cfg.start;
			pthread_mutex_lock(&env->philos[i].meal.mtx);
			elapsed_time = time - env->philos[i].meal.last;
			pthread_mutex_unlock(&env->philos[i].meal.mtx);
			if (elapsed_time > env->cfg.time_to_die)
			{
				print_output(time, env->philos[i], "is dead");
				pthread_mutex_lock(&env->rts->death_mtx);
				env->rts.death_flag = true;
				pthread_mutex_unlock(&env->rts->death_mtx);
				break ;
			}
			i++;
		}
		c++;
	}
	return (NULL);
}

bool	init_threads(t_env *env)
{
	
}

bool	run_simulation(t_env *env, t_phi *philos)
{
	int		i;

	env->cfg.start = -1;
	if (pthread_create(&env->monitor, NULL, &monitor_loop, env))
		return (false);
	i = 0;
	while (i < env->cfg.nb_philos)
	{
		if (pthread_create((&philos[i].tid), NULL, &philo_loop, &philos[i]))
			return (false);
		i++;
	}
	usleep(1000);
	env->cfg.start = get_time();
	i = 0;
	while (i < env->cfg.nb_philos)
	{
		pthread_join(philos[i].tid, NULL);
		pthread_mutex_destroy(&env->forks[i].mtx);
		i++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:32:04 by rshin             #+#    #+#             */
/*   Updated: 2025/08/18 14:37:47 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_config(t_env *env, int argc, char **argv)
{
	int	param[5];
	int	i;

	i = 0;
	while (i <= argc - 2)
	{
		param[i] = atol(argv[i + 1]);
		if (param[i] > INT_MAX || param[i] < INT_MIN)
			return (false);
		i++;
	}
	env->cfg.nb_philos = param[0];
	env->cfg.time_to_die = param[1];
	env->cfg.time_to_eat = param[2];
	env->cfg.time_to_sleep = param[3];
	env->cfg.max_meals = param[4];
	env->forks = malloc(env->cfg.nb_philos * sizeof(t_fork));
	if (!env->forks)
		return (false);
	i = 0;
	while (i < env->cfg.nb_philos)
	{
		env->forks[i].id = i;
		i++;
	}
	return (true);
}

static bool	init_philos(t_env *env)
{
	int	i;

	env->philos = malloc(env->cfg.nb_philos * sizeof(t_phi));
	if (!env->philos)
		return (false);
	memset(env->philos, 0, sizeof(t_phi));
	i = 0;
	while (i < env->cfg.nb_philos)
	{
		env->philos[i].id = i + 1;
		env->philos[i].cfg = &env->cfg;
		env->philos[i].rts = &env->rts;
		env->philos[i].lfork = &env->forks[i];
		if (i == env->cfg.nb_philos - 1)
			env->philos[i].rfork = &env->forks[0];
		else
			env->philos[i].rfork = &env->forks[(i + 1) / 3 + (i + 1) % 3];
		i++;
	}
	return (true);
}

static bool	init_mutexes(t_env *env)
{
	int	i;

	if (pthread_mutex_init(&env->rts.death_mtx, NULL))
		return (false);
	if (pthread_mutex_init(&env->rts.print_mtx, NULL))
		return (false);
	i = 0;
	while (i < env->cfg.nb_philos)
	{
		if (pthread_mutex_init(&env->philos[i].meal.mtx, NULL))
			return (false);
		if (pthread_mutex_init(&env->forks[i].mtx, NULL))
			return (false);
		i++;
	}
	return (true);
}

t_err	init_env(t_env *env, int argc, char **argv)
{
	memset(env, 0, sizeof(t_env));
	if (!init_config(env, argc, argv))
		return (ERR_MALLOC);
	pthread_mutex_init(&env->rts.death_mtx, NULL);
	pthread_mutex_init(&env->rts.print_mtx, NULL);
	if (!init_philos(env))
	{
		free(env->forks);
		return (ERR_MALLOC);
	}
	if (!init_mutexes(env))
	{
		free(env->philos);
		free(env->forks);
		return (ERR_MUTEX);
	}
	return (ERR_OK);
}

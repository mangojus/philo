/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:42:21 by rshin             #+#    #+#             */
/*   Updated: 2025/07/24 16:08:40 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef pthread_mutex_t t_mtx;

typedef struct	s_fork
{
	bool	is_taken;
	t_mtx	mutex;
}	t_fork;

typedef struct	s_philo
{
	pthread_t		tid;
	int				id;
	struct s_fork	*l_fork;
	struct s_fork	*r_fork;
	bool			is_dead;
	struct s_param	*param;
}	t_phi;

typedef struct	s_param
{
	struct s_philo	*philo;
	pthread_t		monitor;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	bool			start;
	bool			end;
}	t_param;

void	*routine(void *arg)
{
	int				ms;
	int				last_time;
	struct timeval	tv;
	t_phi	*p;
//	int		count;

//	count = 0;
	p =	(t_phi *)arg;
	while (true)
	{
//		count++;
		if (p->param->start == true)
			break;
		else
			continue;
	}
//	printf("%d\n", count);
	while (true)
	{
		gettimeofday(&tv, NULL);
		last_time = tv.tv_usec;
		if (p->id % 2 == 0)
		{
			pthread_mutex_lock(&p->l_fork->mutex);
			pthread_mutex_lock(&p->r_fork->mutex);
		}
		else
		{
			pthread_mutex_lock(&p->r_fork->mutex);
			pthread_mutex_lock(&p->l_fork->mutex);
		}
		gettimeofday(&tv, NULL);
		ms = tv.tv_usec - last_time;
		printf("%d philo %d is thinking\n", ms, p->id);
		usleep(param->time_to_eat);
		gettimeofday(&tv, NULL);
		last_time = tv.tv_usec;
		ms = tv.tv_usec - last_time;
		printf("%d philo %d is eating\n", ms, p->id);
		pthread_mutex_unlock(&p->l_fork->mutex);
		pthread_mutex_unlock(&p->r_fork->mutex);
		gettimeofday(&tv, NULL);
		last_time = tv.tv_usec;
		ms = tv.tv_usec - last_time;
		printf("%d philo %d is sleeping\n", ms, p->id);
		usleep(param->time_to_sleep);
		if (p->param->end == true)
			break;
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_param	*param;
	int		i;

	param = (t_param *)arg;
	while (true)
	{
		i = 0;
		while (i < 3)
		{
			if (param->philo[i].is_dead)
			{
				printf("philo %d is dead, end of simulation", i);
				param->end = true;
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_param	param;
	t_phi	p[3];
	t_fork	fork[3];
	int		i;

	(void)argc;
	(void)argv;
	memset(&param, 0, sizeof(t_param));
	param.philo = p;
	param.time_to_die = 200;
	param.time_to_eat = 200;
	param.time_to_sleep = 200;
	i = 0;
	while (i < 3)
	{
		memset(&p[i], 0, sizeof(t_phi));
		memset(&fork[i], 0, sizeof(t_fork));
		p[i].id = i + 1;
		pthread_mutex_init((&fork[i].mutex), NULL);
		p[i].param = &param;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		p[i].l_fork = &fork[i];
		if (i == 3 - 1)
			p[i].r_fork = &fork[0];
		else
			p[i].r_fork = &fork[(i + 1) / 3 + (i + 1) % 3];
		i++;
	}
	if (pthread_create(&param.monitor, NULL, &monitor, &param))
		return (1);
	i = 0;
	while (i < 3)
	{
		if (pthread_create(&p[i].tid, NULL, &routine, &p[i]))
			return (1);
		i++;
	}
	param.start = true;
	i = 0;
	while (i < 3)
	{
		if (pthread_join(p[i].tid, NULL))
			return (1);
		pthread_mutex_destroy(&fork[i].mutex);
		i++;
	}
	return (0);
}

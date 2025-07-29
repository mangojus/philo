/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:42:21 by rshin             #+#    #+#             */
/*   Updated: 2025/07/29 17:02:38 by rshin            ###   ########.fr       */
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

typedef struct	s_time
{
	long	die;
	long	eat;
	long	sleep;
	long	start;
	long	end;
	long	s;
	long	last_s;
}	t_time;

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
	struct s_time	time;
	bool			begin;
	bool			end;
}	t_param;

void	get_time(t_time *time)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	time->s = tv.tv_usec - time->start;
}

void	ft_usleep(int time)
{
	usleep(time * 1000);
}

void	*routine(void *arg)
{
	t_phi	*p;

	p =	(t_phi *)arg;
	while (true)
	{
		if (p->param->begin == true)
			break;
		else
			continue;
	}
	while (true)
	{
		get_time(&(p->param->time));
		printf("%ld %d is thinking\n", p->param->time.s, p->id);
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
		get_time(&(p->param->time));
		printf("%ld %d is eating\n", p->param->time.s, p->id);
		ft_usleep(p->param->time.sleep);
//		if (p->param->time.s - last_t >= p->param->time.die)
//			p->is_dead = true;
		pthread_mutex_unlock(&p->l_fork->mutex);
		pthread_mutex_unlock(&p->r_fork->mutex);
		get_time(&(p->param->time));
		printf("%ld %d is sleeping\n", p->param->time.s, p->id);
		ft_usleep(p->param->time.sleep);
		if (p->param->end == true)
		{
			get_time(&(p->param->time));
			printf("%ld %d is dead\n", p->param->time.s, p->id);
			break;
		}
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
				printf("%d is dead, end of simulation\n", i);
				param->end = true;
				return (NULL);
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	struct timeval	tv;
	t_param	param;
	t_phi	p[3];
	t_fork	fork[3];
	int		i;

	(void)argc;
	(void)argv;
	memset(&param, 0, sizeof(t_param));
	param.philo = p;
	param.time.die = 200;
	param.time.eat = 200;
	param.time.sleep = 200;
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
	gettimeofday(&tv, NULL);
	param.time.start = tv.tv_usec;
//	printf("%ld \n", tv.tv_usec);
	param.begin = true;
	while (true)
	{
		i++;
	}
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

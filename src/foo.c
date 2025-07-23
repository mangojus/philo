/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:42:21 by rshin             #+#    #+#             */
/*   Updated: 2025/07/23 17:40:29 by rshin            ###   ########.fr       */
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

typedef struct	s_philo
{
	pthread_t		tid;
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	bool			start;
}	t_phi;

void	*routine(void *arg)
{
	t_phi	*p;

	p =	(t_phi *)arg;
	while (true)
	{
		if (p->start == true)
			break;
		else
			continue;
	}
	printf("here is philo %d\n", p->id);
	pthread_mutex_lock(p->l_fork);
	pthread_mutex_lock(p->r_fork);
	printf("eat\n");
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_phi	p[3];
	pthread_mutex_t	fork[3];
	int		i;

	(void)argc;
	(void)argv;
	i = 0;
	while (i < 3)
	{
		memset(&p[i], 0, sizeof(t_phi));
		p[i].id = i + 1;
		pthread_mutex_init((&fork[i]), NULL);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		p[i].l_fork = &fork[i - 1];
		if (i == 3 - 1)
			p[i].r_fork = &fork[0];
		else
			p[i].r_fork = &fork[i / 3 + i % 3];
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (pthread_create(&p[i].tid, NULL, &routine, &p[i]))
			return (1);
		i++;
	}
	(*p).start = true;
	i = 0;
	while (i < 3)
	{
		if (pthread_join(p[i].tid, NULL))
			return (1);
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
	return (0);
}

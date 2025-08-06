/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:38:59 by rshin             #+#    #+#             */
/*   Updated: 2025/07/29 15:31:02 by rshin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

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

typedef enum e_stat
{
	EAT = 1,
	SLEEP = 2,
	THINK = 4,
	FULL = 8,
	DEAD = 16,
}	t_stat;

typedef struct s_philo
{
	int				id;
	t_mtx			tid;
	t_stat			status;
	t_mtx			*lfork;
	t_mtx			*rfork;
}	t_phi;

typedef struct s_param
{
	struct s_phi	*philo;
	t_mtx			*fork;
	t_mtx			monitor;
	long			start;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
}	t_param;

bool	init_param(t_param *param, int argc, char **argv);
bool	run_philo(t_phi *philo);

long	get_time(void);
void	ft_usleep(long duration);

int		is_digit(int c);
long	atol(const char *nptr);
void	print_output(t_data *data);

#endif

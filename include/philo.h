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

typedef enum e_err
{
	ERR_OK = 0,
	ERR_GLOBAL = 1,
	ERR_INPUT = 2,
	ERR_MALLOC = 3,
	ERR_THREAD = 4,
	ERR_MUTEX = 5,
}	t_err;

typedef enum e_stat
{
	EAT = 1,
	SLEEP = 2,
	THINK = 4,
	FULL = 8,
	DEAD = 16,
}	t_stat;

typedef struct s_meal
{
	long	last;
	int		count;
	t_mtx	mtx;
}	t_meal;

typedef struct s_fork
{
	bool	id;
	t_mtx	mtx;
}	t_fork;

typedef struct s_philosopher
{
	int						id;
	pthread_t				tid;
	t_meal					meal;
	t_fork					*lfork;
	t_fork					*rfork;
	struct s_config			*cfg;
	struct s_runtime_state	*rts;
}	t_phi;

typedef struct s_config
{
	long			start;
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
}	t_cfg;

typedef struct s_runtime_state
{
	bool	death_flag;
	t_mtx	death_mtx;
	t_mtx	print_mtx;
}	t_rts;

typedef struct s_environment
{
	struct s_philosopher	*philos;
	struct s_config			cfg;
	struct s_runtime_state	rts;
	pthread_t				monitor;
	t_fork					*forks;
	t_err					err_status;
}	t_env;

t_err	init_env(t_env *env, int argc, char **argv);
bool	run_simulation(t_env *env, t_phi *philo);
void	cleanup(t_env *env);

long	get_time(void);
void	smart_sleep(long duration);

int		is_digit(int c);
long	atol(const char *nptr);

#endif

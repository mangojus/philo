# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_philo
{
	int				id;
	bool			is_full;
	int				has_eaten;
	bool			status;
	pthread_mutex_t fork;
}	t_phi;


void	*routine(void *arg)
{
	int	nb;

	pthread_mutex_lock(&fork);
	nb = *(int *)arg;
	if (nb != 0)
	{
		printf("there are %d forks left\n", nb);
		printf("is eating\n");
		sleep(1);
		nb--;
	}
	else
	{
		printf("is dead\n");
		return (NULL);
	}
	printf("is thinking\n");
	sleep(1);
	printf("is sleeping\n");
	sleep(1);
	printf("thread end\n");
	*(int *)arg = nb;
	pthread_mutex_unlock(&fork);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	p1, p2, p3;
	int	nb_forks;

	(void)argc;
	(void)argv;
	nb_forks = 2;
	pthread_mutex_init(&fork, NULL);
	if (pthread_create(&p1, NULL, &routine, &nb_forks))
		return (1);
	if (pthread_create(&p2, NULL, &routine, &nb_forks))
		return (1);
	if (pthread_create(&p3, NULL, &routine, &nb_forks))
		return (1);
	if (pthread_join(p1, NULL))
		return (1);
	if (pthread_join(p2, NULL))
		return (1);
	if (pthread_join(p3, NULL))
		return (1);
	pthread_mutex_destroy(&fork);
	return (0);
}

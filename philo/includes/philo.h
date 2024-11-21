/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:42:54 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/12 17:53:25 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define EAT "is eating"
# define TAKE_FORK "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t	thread;
	int		id;
	int		eat_count;
	int		status;
	int		eating;
	size_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}			t_philo;

typedef struct s_data
{
	pthread_t	*thread_id;
	int		nb_philos;
	int		nb_eat;
	int		dead;
	int		finished;
	t_philo		*philos;
	size_t		death_time;
	size_t		eat_time;
	size_t		sleep_time;
	size_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	is_dead;
	pthread_mutex_t	print;
}			t_data;

long long	*ft_parse(int ac, char **av);
int		check_args(int ac);
char		*ft_strchr(const char *str, int c);
void		*manager(void *philo_ptr);
void		*eat_limits(void *philo_ptr);
int		init(t_data *data, long long *params, int ac);
void		*routine(void *philo_ptr);
size_t		get_time(void);
void		send(char *str, t_philo *philo);
int		ft_sleep(size_t time);
int		ft_quit(t_data *data);
int		is_dead(t_philo *philo);
int		is_alone(t_philo *philo);

#endif

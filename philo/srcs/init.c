/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:12:32 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/12 16:39:59 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, long long *params, int ac)
{
	data->nb_philos = params[0];
	data->death_time = params[1];
	data->eat_time = params[2];
	data->sleep_time = params[3];
	if (ac == 6)
		data->nb_eat = params[4];
	else
		data->nb_eat = -1;
	data->dead = 0;
	data->finished = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->is_dead, NULL);
	data->thread_id = malloc(sizeof(pthread_t) * data->nb_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->thread_id || !data->forks || !data->philos)
		return (ft_quit(data));
	return (0);
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->nb_philos - 1];	
	i = 1;
	while (i < data->nb_philos)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
		i++;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].eat_count = 0;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

int	init_threads(t_data *data)
{
	int		i;
	pthread_t	t_eat;

	data->start_time = get_time();
	//printf("\e[4;96m   Time    | Philo |       Action       \e[0m\n");
	if (data->nb_eat > 0)
	{
		if (pthread_create(&t_eat, NULL, &eat_limits, &data->philos[0]))
			return (ft_quit(data));
	}
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->thread_id[i], NULL, &routine, &data->philos[i]))
			return(ft_quit(data));
		i++;
		ft_sleep(1);
	}
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join(data->thread_id[i], NULL))
			return (ft_quit(data));
		i++;
	}
	return (0);
}

int	init(t_data *data, long long *params, int ac)
{
	if (init_data(data, params, ac))
		return (1);
	init_forks(data);
	init_philos(data);

	if (init_threads(data))
		return (1);
	return (0);

}

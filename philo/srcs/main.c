/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:12:32 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/02 19:47:12 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_quit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->is_dead);
	if (data->thread_id)
		free(data->thread_id);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	return (1);
}

int	main(int ac, char **av)
{
	long long	*params;
	t_data		data;

	if (!check_args(ac))
		return (0);
	params = ft_parse(ac, av + 1);
	if (!params)
	{
		write(2, "Invalid arguments\n", 18);
		return (0);
	}
	if (init(&data, params, ac))
		free(params);
	ft_quit(&data);
	free(params);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:50:49 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/02 20:54:05 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (get_time() >= philo->time_to_die)
			break ;
		else
			usleep(150);
	}
	return (0);
}

size_t	get_time(void)
{
	struct timeval	timev;
	size_t			time;

	if (gettimeofday(&timev, NULL))
		return (1);
	time = timev.tv_sec * 1000 + timev.tv_usec / 1000;
	return (time);
}

void	send(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_time() - philo->data->start_time + 1;
	if (ft_strcmp(DEAD, str) == 0 && !is_dead(philo))
	{
		printf("🕐 \e[95m%5.zums\e[0m | ", time);
		printf("\e[1;31m#%-5.d\e[0m| %20s\n", philo->id, str);
		pthread_mutex_lock(&philo->data->lock);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->lock);
	}
	if (!is_dead(philo))
	{
		printf("🕐 \e[95m%5.zums\e[0m | ", time);
		printf("\e[1;92m#%-5.d\e[0m| %20s\n", philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->print);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

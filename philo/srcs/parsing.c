/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:40:51 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/02 19:01:27 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "Invalid arguments\n", 18);
		return (0);
	}
	return (1);
}

long long	*check_error_values(long long *tab, int size)
{
	while (size-- > 0)
	{
		if (tab[size] == 0)
		{
			free(tab);
			return (0);
		}
	}
	return (tab);
}

long long	ft_atoll(const char *nptr)
{
	long long	result;
	int			i;

	result = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i++] - '0';
		if (result < 0)
			return (0);
	}
	if (nptr[i] != 0)
		return (0);
	return (result);
}

long long	*ft_parse(int ac, char **av)
{
	long long	*tab;
	int			i;

	i = 0;
	while (av[i])
	{
		if (ft_strchr(av[i++], '-'))
			return (0);
	}
	tab = malloc(sizeof(long long) * (ac - 1));
	if (!tab)
		return (0);
	i = 0;
	while (i < ac - 1)
	{
		tab[i] = ft_atoll(av[i]);
		i++;
	}
	tab = check_error_values(tab, i);
	return (tab);
}

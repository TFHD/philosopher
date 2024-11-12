/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:12:32 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/12 16:39:59 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	long long	*params;
	int			i;

	i = 0;
	if (!check_args(ac))
		return (0);
	params = ft_parse(ac, av + 1);
	if (params == NULL)
	{
		write(2, "Go fix your brain and put positive number\n", 42);
		return (0);
	}
	while (i < ac - 1)
		printf("%lld\n", params[i++]);
	free(params);
	return (0);
}

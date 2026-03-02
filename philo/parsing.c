/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:16:18 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 21:12:23 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_table(t_table *table, char **av)
{
	table->ph_nbr = ft_atol(av[1]);
	if (table->ph_nbr <= 0)
		exit_it("invalid number of philosophers");
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		exit_it("use time less than 60ms");
	if (av[5])
	{
		table->nbr_limit_meals = ft_atol(av[5]);
		if (table->nbr_limit_meals < 0)
			exit_it("invalid number of meals");
	}
	else
		table->nbr_limit_meals = -1;
}

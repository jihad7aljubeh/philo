/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 21:16:28 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 21:28:16 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_die;

	if (get_bool(&philo->philo_mtx, &philo->full))
		return (false);
	elapsed = get_time(MS) - get_long(&philo->philo_mtx,
			&philo->last_meal_time);
	t_die = philo->table->time_to_die / 1000;
	if (elapsed > t_die)
		return (true);
	return (false);
}

static bool	all_full(t_table *table)
{
	int	i;

	if (table->nbr_limit_meals == -1)
		return (false);
	i = -1;
	while (++i < table->ph_nbr)
	{
		if (!get_bool(&table->philo[i].philo_mtx, &table->philo[i].full))
			return (false);
	}
	return (true);
}

void	*monitor_routine(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	wait_thread(table);
	while (!sim_done(table))
	{
		i = -1;
		while (++i < table->ph_nbr && !sim_done(table))
		{
			if (philo_died(&table->philo[i]))
			{
				set_bool(&table->table_mtx, &table->end_sim, true);
				print_status(&table->philo[i], DIE, DEBUG_MODE);
				return (NULL);
			}
		}
		if (all_full(table))
		{
			set_bool(&table->table_mtx, &table->end_sim, true);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

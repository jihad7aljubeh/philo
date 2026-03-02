/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 18:15:39 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 21:24:59 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_debug(t_philo *philo, t_phstate status, long elapsed)
{
	if (FFORK == status && !sim_done(philo->table))
		printf("%ld %d has taken a fork 1 \n", elapsed, philo->id);
	else if (SFORK == status && !sim_done(philo->table))
		printf("%ld %d has taken a fork 2 \n", elapsed, philo->id);
	else if (EAT == status && !sim_done(philo->table))
		printf("%ld %d is eating\n", elapsed, philo->id);
	else if (SLEEP == status && !sim_done(philo->table))
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if (THINK == status && !sim_done(philo->table))
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (DIE == status)
		printf("%ld %d died\n", elapsed, philo->id);
}

void	print_status(t_philo *philo, t_phstate status, bool debug)
{
	long	elapsed;

	elapsed = get_time(MS) - philo->table->start_sim;
	if (get_bool(&philo->philo_mtx, &philo->full))
		return ;
	mtx_handle(&philo->table->print_mtx, LOCK);
	if (debug)
		print_debug(philo, status, elapsed);
	else
	{
		if ((FFORK == status || SFORK == status) && !sim_done(philo->table))
			printf("%ld %d has taken a fork\n", elapsed, philo->id);
		else if (EAT == status && !sim_done(philo->table))
			printf("%ld %d is eating\n", elapsed, philo->id);
		else if (SLEEP == status && !sim_done(philo->table))
			printf("%ld %d is sleeping\n", elapsed, philo->id);
		else if (THINK == status && !sim_done(philo->table))
			printf("%ld %d is thinking\n", elapsed, philo->id);
		else if (DIE == status)
			printf("%ld %d died\n", elapsed, philo->id);
	}
	mtx_handle(&philo->table->print_mtx, UNLOCK);
}

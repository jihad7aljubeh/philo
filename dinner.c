/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 01:40:50 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 01:48:01 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *sim_dinner(void *data)
{
    t_philo  *philo;
    
    philo = (t_philo *)data;
    wait_thread(philo->table);
    
}
void    start_dinner(t_table *table)
{
    int i;

    i = -1;
    if(table->nbr_limit_meals == 0)
        return ;
    else if(table->ph_nbr == 1)
    ;
    else
    {
        while(++i < table->ph_nbr)
            thread_handle(&table->philo[i].thread_id, sim_dinner, &table->philo[i], CREAT);
    }
    
}
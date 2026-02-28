/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 01:40:50 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 21:25:09 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void eat(t_philo *philo)
{
    mtx_handle(&philo->first->fork, LOCK);
    print_status(philo, FFORK, DEBUG_MODE);
    mtx_handle(&philo->second->fork, LOCK);
    print_status(philo, SFORK, DEBUG_MODE);
    set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MS));
    philo->meals++;
    print_status(philo, EAT, DEBUG_MODE);
    usleep_set(philo->table->time_to_eat, philo->table);
    if (philo->meals == philo->table->nbr_limit_meals
        && philo->table->nbr_limit_meals != -1)
        set_bool(&philo->philo_mtx, &philo->full, true);
    mtx_handle(&philo->second->fork, UNLOCK);
    mtx_handle(&philo->first->fork, UNLOCK);
}

static void think(t_philo *philo)
{
    print_status(philo, THINK, DEBUG_MODE);
}

static void	*single_philo(void *data)
{
    t_philo	*philo;

    philo = (t_philo *)data;
    wait_thread(philo->table);
    set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MS));
    mtx_handle(&philo->first->fork, LOCK);
    print_status(philo, FFORK, DEBUG_MODE);
    while (!sim_done(philo->table))
        usleep(200);
    mtx_handle(&philo->first->fork, UNLOCK);
    return (NULL);
}

void    *sim_dinner(void *data)
{
    t_philo  *philo;
    
    philo = (t_philo *)data;
    wait_thread(philo->table);
    set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MS));
    if (philo->id % 2 == 0)
        usleep_set(philo->table->time_to_eat / 2, philo->table);
    while(!sim_done(philo->table))
    {
        if (get_bool(&philo->philo_mtx, &philo->full))
            break;
        eat(philo);
        print_status(philo, SLEEP, DEBUG_MODE);
        usleep_set(philo->table->time_to_sleep, philo->table);
        think(philo);
    }
    return (NULL);
}

void    start_dinner(t_table *table)
{
    int i;

    i = -1;
    if(table->nbr_limit_meals == 0)
        return ;
    else if(table->ph_nbr == 1)
        thread_handle(&table->philo[0].thread_id, single_philo,
            &table->philo[0], CREAT);
    else
    {
        while(++i < table->ph_nbr)
            thread_handle(&table->philo[i].thread_id, sim_dinner,
                &table->philo[i], CREAT);
    }
    thread_handle(&table->monitor, monitor_routine, table, CREAT);
    table->start_sim = get_time(MS);
    i = -1;
    while(++i < table->ph_nbr)
        table->philo[i].last_meal_time = table->start_sim;
    set_bool(&table->table_mtx, &table->all_ready, true);
    i = -1;
    while(++i < table->ph_nbr)
        thread_handle(&table->philo[i].thread_id, NULL, NULL, JOIN);
    thread_handle(&table->monitor, NULL, NULL, JOIN);
}

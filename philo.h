/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalju-be <jalju-be@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 22:39:08 by jalju-be          #+#    #+#             */
/*   Updated: 2026/02/28 01:48:26 by jalju-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<stdbool.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#include <pthread.h>
#include <errno.h>


typedef enum e_code
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREAT,
    JOIN,
    DETACH,
}       t_code;

typedef pthread_mutex_t t_mtx;

typedef struct s_table t_table;

typedef struct s_fork
{
    t_mtx fork;
    int   fork_id;
    
}   t_fork;

typedef struct s_philo
{
    int id;
    long meals;
    long full;
    long last_meal_time;
    t_fork  first;
    t_fork  second;
    pthread_t thread_id;
    t_table   *table;
}             t_philo;

struct s_table
{
    long    ph_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    nbr_limit_meals;
    long    start_sim;
    bool    end_sim;
    bool    all_ready;
    t_mtx   table_mtx;
    t_fork  *forks;
    t_philo *philo;
};

void    exit_it(const char *error);
long	ft_atol(const char *str);
void    parse_table(t_table *table, char **av);
void    *malloc_handle(size_t b);
void    mtx_handle(t_mtx *mtx, t_code code);
void    thread_handle(pthread_t *thread, void *(fun)(void *), void *data, t_code code);
void    table_init(t_table *table);

#endif
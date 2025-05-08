/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:32:11 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/08 14:13:47 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */

bool take_two_forks(t_philo *philo, int left_fork, int right_fork)
{
    bool fork_taken;

    if (philo->id % 2 != 0)
        fork_taken = take_two_forks(philo, left_fork, right_fork);
    else
    {
        usleep(20);   // Retraso para desincronizar filósofos impares
        fork_taken = take_two_forks(philo, right_fork, left_fork);
    }
    return (fork_taken);
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

void change_availability(t_philo *philo, int fork, bool status)
{
    pthread_mutex_lock(&philo->program->forks_lock);
    philo->program->forks_available[fork] = status;
    pthread_mutex_unlock(&philo->program->forks_lock);
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

bool is_available(t_philo *philo, int fork)
{
    pthread_mutex_lock(&philo->program->forks_lock);
    bool available = philo->program->forks_available[fork];
    pthread_mutex_unlock(&philo->program->forks_lock);
    return available;
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */ 

bool take_forks(t_philo *philo, int fork1, int fork2)
{
    int has_fork_1;
    int has_fork_2;
    
    has_fork_1 = 0;
    has_fork_2 = 0;
    while (1)
    {
        if (philosopher_dead(philo))
        {
            if (philo->program->forks_available[fork1] == false)
                pthread_mutex_unlock(&philo->program->forks[fork1]);
            if (philo->program->forks_available[fork1] == false)
                pthread_mutex_unlock(&philo->program->forks[fork2]);
            return false;
        }

        if (!has_fork_1 && is_available(philo, fork1))
        {
            change_availability(philo, fork1, false);
            has_fork_1 = 1;
            pthread_mutex_lock(&philo->program->forks[fork1]);
            //printf("philo id: %d - fork %d\n", philo->id, left_fork);
            print_action(philo, "has taken a fork");
        }
        
        if (!has_fork_2 && has_fork_1 && is_available(philo, fork2))
        {
            change_availability(philo, fork2, false);
            has_fork_2 = 1;
            pthread_mutex_lock(&philo->program->forks[fork2]);
            //printf("philo id: %d - fork %d\n", philo->id, right_fork);
            print_action(philo, "has taken a fork");
            return true;  // Ambos tenedores adquiridos
        }
    }
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

void free_forks(t_philo *philo, int left_fork, int right_fork)
{
	pthread_mutex_unlock(&philo->program->forks[left_fork]);
	//print_action(philo, "ha soltado fork LEFT");				//🚩_testeo: quitar esto es de prueba
	pthread_mutex_unlock(&philo->program->forks[right_fork]);
	//print_action(philo, "ha soltado fork RIGHT");				//🚩_testeo: quitar esto es de prueba

	pthread_mutex_lock(&philo->program->forks_lock);
	philo->program->forks_available[left_fork] = true;
	philo->program->forks_available[right_fork] = true;
	pthread_mutex_unlock(&philo->program->forks_lock);
	
}



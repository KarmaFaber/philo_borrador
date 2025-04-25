/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:36:20 by mzolotar          #+#    #+#             */
/*   Updated: 2025/04/25 09:09:39 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */

bool take_forks_and_eat(t_philo *philo, int left_fork, int right_fork)
{
    
    if (!take_two_forks(philo, left_fork, right_fork))
        return false;

    if (philosopher_dead(philo))
    {
        return false;
    }
    print_action(philo, EAT);
    pthread_mutex_lock(&philo->program->meal_lock);
    philo->last_meal = timestamp();
    pthread_mutex_unlock(&philo->program->meal_lock);
    precise_sleep(philo->program->time_to_eat, philo);
    philo->meals_eaten++;
    
    return true;
}

 
/*
void eat_routine(t_philo *philo)
{
    if (philosopher_dead(philo))
    {
        return;
    }
    print_action(philo, EAT);
    pthread_mutex_lock(&philo->program->meal_lock);
    philo->last_meal = timestamp();
    pthread_mutex_unlock(&philo->program->meal_lock);
    precise_sleep(philo->program->time_to_eat, philo);
    philo->meals_eaten++;
}
*/

/**
 * @brief 
 *
 * @param 
 * @return 
 */

 
bool	sleep_routine(t_philo *philo)
{
    if (philosopher_dead(philo))
    {
        return false ;
    }
    
	print_action(philo, SLEEP);
    precise_sleep(philo->program->time_to_sleep, philo);
    return true;
    //usleep(philo->program->time_to_sleep * 1000);
	
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

bool	think_routine(t_philo *philo)
{
    if (philosopher_dead(philo))
    {
        return false;
    }
	print_action(philo, THINK);
    return true;
}




/**
 * @brief 
 *
 * @param 
 * @return 
 */

void all_routines (t_philo *philo, int left_fork, int right_fork)
{
	//todas las rutinas
    //while ((philo->program->dead_p_num <= 0) && (philo->program->num_times_to_eat == 0 || philo->meals_eaten < philo->program->num_times_to_eat))
    while ((!(philosopher_dead(philo)) && (philo->program->num_times_to_eat == 0 || philo->meals_eaten < philo->program->num_times_to_eat)))
    {   
        //if (philosopher_dead(philo))
        //{
            //printf("\033[1;32mbreak por philo muerto 1: %d \n\033[0m", philo->id); //🚩_testeo:
        //   break; // Si el filósofo muere, detener la ejecución de las rutinas
        //}
        // Intentar tomar los 2 tenedores
        //if (!take_two_forks(philo, left_fork, right_fork))
        //{
        //    //printf("\033[1;32mbreak por philo muerto 2: %d \n\033[0m", philo->id); //🚩_testeo:
        //    break; // Si el filósofo muere, detener la ejecución de las rutinas
        //}
		// Comer
		//eat_routine(philo);
        if (!take_forks_and_eat(philo, left_fork, right_fork))
            break;
        
        // Liberar los tenedores
        free_forks(philo, left_fork, right_fork);

		if (philosopher_dead(philo))
        {
            //printf("\033[1;32mbreak por philo muerto 3: %d \n\033[0m", philo->id); //🚩_testeo:
            break; // Si el filósofo muere, detener la ejecución de las rutinas
        }
			
        // Dormir
        if (!sleep_routine(philo))
            break;

		if (philosopher_dead(philo))
        {
        //    //printf("\033[1;32mbreak por philo muerto 4: %d \n\033[0m", philo->id); //🚩_testeo:
            break; // Si el filósofo muere, detener la ejecución de las rutinas
        }
			
        // Pensar
        if (!think_routine(philo))
            break;

        if (philosopher_dead(philo))
        {
           //printf("\033[1;32mbreak por philo muerto 5: %d \n\033[0m", philo->id); //🚩_testeo:
            break; // Si el filósofo muere, detener la ejecución de las rutinas
        }
    }
}

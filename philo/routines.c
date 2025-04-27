/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:36:20 by mzolotar          #+#    #+#             */
/*   Updated: 2025/04/27 09:25:43 by mzolotar         ###   ########.fr       */
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

 
/**
 * @brief 
 *
 * @param 
 * @return 
 */

bool slepp_and_think_routine(t_philo *philo)
{
    
    if (philosopher_dead(philo))
    {
        return false ;
    }
        
    
	print_action(philo, SLEEP);
    precise_sleep(philo->program->time_to_sleep, philo);
    
    
    if (philosopher_dead(philo))
    {
        return false ;
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
		// Coger tenedores y Comer
        if (!take_forks_and_eat(philo, left_fork, right_fork))
            break;
            
        if (philosopher_dead(philo))
        {
            break ;
        }
        
        // Liberar los tenedores despues de comer
        free_forks(philo, left_fork, right_fork);
			
        // Dormir y Pensar
        if (!slepp_and_think_routine(philo))
            break;

    }
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

 /*
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

*/
/*
bool	think_routine(t_philo *philo)
{
    if (philosopher_dead(philo))
    {
        return false;
    }
	print_action(philo, THINK);
    return true;
}
*/


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:36:20 by mzolotar          #+#    #+#             */
/*   Updated: 2025/04/24 09:19:18 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */

void eat_routine(t_philo *philo)
{
    print_action(philo, "is eating");
    pthread_mutex_lock(&philo->program->meal_lock);
    philo->last_meal = timestamp();
    pthread_mutex_unlock(&philo->program->meal_lock);
    usleep(philo->program->time_to_eat * 1000);
    philo->meals_eaten++;
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

void	sleep_routine(t_philo *philo)
{
	print_action(philo, "is sleeping");
    usleep(philo->program->time_to_sleep * 1000);
	
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

void	think_routine(t_philo *philo)
{
	print_action(philo, "is thinking");
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
    while (!philo->program->dead && (philo->program->num_times_to_eat == 0 || philo->meals_eaten < philo->program->num_times_to_eat))
    {   
        // Intentar tomar los 2 tenedores
        take_two_forks(philo, left_fork, right_fork);

		if (philosopher_dead(philo))
        {
            printf("\033[1;32mbreak por philo muerto 2: %d \n\033[0m", philo->id); //🚩_testeo:
            break; // Si el filósofo muere, detener la ejecución de las rutinas
        }
		// Comer
		eat_routine(philo);
        // Liberar los tenedores
        free_forks(philo, left_fork, right_fork);

		if (philosopher_dead(philo))
        {
            printf("\033[1;32mbreak por philo muerto 3: %d \n\033[0m", philo->id); //🚩_testeo:
            break; // Si el filósofo muere, detener la ejecución de las rutinas
        }
			
        // Dormir
        sleep_routine(philo);

		if (philosopher_dead(philo))
        {
            printf("\033[1;32mbreak por philo muerto 4: %d \n\033[0m", philo->id); //🚩_testeo:
            break; // Si el filósofo muere, detener la ejecución de las rutinas
        }
			
        // Pensar
        think_routine(philo);

        if (philosopher_dead(philo))
        {
            printf("\033[1;32mbreak por philo muerto 5: %d \n\033[0m", philo->id); //🚩_testeo:
            break; // Si el filósofo muere, detener la ejecución de las rutinas
        }
    }
    
	
}

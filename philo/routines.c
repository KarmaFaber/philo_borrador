/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:36:20 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/07 13:25:58 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * @brief 
 *
 * @param 
 * @return 
 */

// 1 -true -philo muerto
// 0 -false -philo vivo
/*
bool philosopher_dead(t_philo *philo)
{
	// Revisar si ya se ha registrado la muerte de algún filósofo
	pthread_mutex_lock(&philo->program->dead_num_lock);
	if (philo->program->dead_p_num > 0)
	{
		pthread_mutex_unlock(&philo->program->dead_num_lock);
		return (true); // Ya hay un filósofo muerto
	}
	pthread_mutex_unlock(&philo->program->dead_num_lock);

	// Revisar si este filósofo ha muerto por inanición
	//pthread_mutex_lock(&philo->program->meal_lock);
	if (timestamp() - philo->last_meal >= philo->program->time_to_die)
	{
		//pthread_mutex_unlock(&philo->program->meal_lock);

		philo->dead_philo = true;

		// Incrementar el contador de muertes de forma segura
		pthread_mutex_lock(&philo->program->dead_num_lock);
		philo->program->dead_p_num++;
		if (philo->program->dead_p_num == 1)
        {
            //check_death_print_delay(philo);   // 🚩 testeo:
            print_dead(philo, DIE);
        }
		pthread_mutex_unlock(&philo->program->dead_num_lock);

		return (true); // Filósofo muerto
	}
	//pthread_mutex_unlock(&philo->program->meal_lock);
	return (false); // Filósofo vivo
}
*/

bool philosopher_dead(t_philo *philo)
{
    pthread_mutex_lock(&philo->program->dead_num_lock);
    if (philo->program->dead_p_num > 0 )
    {
        pthread_mutex_unlock(&philo->program->dead_num_lock);
        return (true); // Ya hay un filósofo muerto
    }

    // Revisar si este filósofo ha muerto por inanición
    if (timestamp() - philo->last_meal >= philo->program->time_to_die)
    {
        //philo->dead_philo = true;
        philo->program->dead_p_num++;
        if (philo->program->dead_p_num == 1)
        {
            //check_death_print_delay(philo);   // 🚩 testeo:
            print_dead(philo, DIE);
        }
        pthread_mutex_unlock(&philo->program->dead_num_lock);
        return (true); // Filósofo muerto
    }
    pthread_mutex_unlock(&philo->program->dead_num_lock);
    return (false); // Filósofo vivo
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

bool take_forks_and_eat(t_philo *philo, int left_fork, int right_fork)
{
    //usleep(100 + (philo->id * 10)); // añadir en cada loop o antes de intentar comer
    
    if (!take_two_forks(philo, left_fork, right_fork))
        return false;

    precise_sleep(philo, 1); //antres de verificar dead esperamos un poco para desincronizar los hilos que entran a la vez
    
    if (philosopher_dead(philo))
    {
        return false;
    }
    
   //pthread_mutex_lock(&philo->program->meal_lock);
    philo->last_meal = timestamp();
    print_action(philo, EAT);
    //pthread_mutex_unlock(&philo->program->meal_lock);
    precise_sleep(philo, philo->program->time_to_eat);
    philo->meals_eaten++;
    
    return true;
}

 
/**
 * @brief 
 *
 * @param 
 * @return 
 */

bool sleep_and_think_routine(t_philo *philo)
{
    precise_sleep(philo, 1); //antres de verificar dead esperamos un poco para desincronizar los hilos que entran a la vez
    
    if (philosopher_dead(philo) )
    {
        return false;
    }
    
	print_action(philo, SLEEP);
    precise_sleep(philo, philo->program->time_to_sleep);
    
    precise_sleep(philo, 1); //antres de verificar dead esperamos un poco para desincronizar los hilos que entran a la vez
    
    if (philosopher_dead(philo) )
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
        // Micro-stagger dinámico antes de intentar comer
		usleep(100 + (philo->id * 10));  // rompe colisiones cíclicas
        
		// Coger tenedores y Comer
        if (!take_forks_and_eat(philo, left_fork, right_fork))
            break;
            
        if (philosopher_dead(philo) )
        {
            break ;
        }
        
        // Liberar los tenedores despues de comer
        free_forks(philo, left_fork, right_fork);
			
        // Dormir y Pensar
        if (!sleep_and_think_routine(philo))
            break;

    }
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:32:11 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/01 10:41:31 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */

// Apply a small delay to even philosophers to reduce race conditions
void	stagger_even_philos(t_philo *philo)
{
	if (philo->id % 2 == 0)
		precise_sleep(philo, 5); // 🚩🚩🚩 5 es el mejor rango hasta ahora, otros rangos fallan por todos lados 
	else if (philo->id % 2 != 0)
		precise_sleep(philo, 3);
	
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

// Lock mutexes and print actions in the correct order (based on philosopher ID)
void	lock_and_announce_forks(t_philo *philo, int left_fork, int right_fork)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->program->forks[right_fork]);
		print_action(philo, "has taken a fork RIGHT");  // 🚩 testeo
		//print_action(philo, TAKE_FORK);
		pthread_mutex_lock(&philo->program->forks[left_fork]);
		print_action(philo, "has taken a fork LEFT"); // 🚩 testeo
		//print_action(philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->program->forks[left_fork]);
		print_action(philo, "has taken a fork LEFT");			// 🚩 testeo
		//print_action(philo, TAKE_FORK);
		pthread_mutex_lock(&philo->program->forks[right_fork]);
		print_action(philo, "has taken a fork RIGHT");		// 🚩 testeo
		//print_action(philo, TAKE_FORK);
	}
}
/**
 * @brief 
 *
 * @param 
 * @return 
 */
/*
bool take_two_forks(t_philo *philo, int left_fork, int right_fork)
{
	stagger_even_philos(philo);
	while (1)
	{
		if (philosopher_dead(philo))
			return false;

		pthread_mutex_lock(&philo->program->forks_lock);
		if (philo->program->forks_available[left_fork] && philo->program->forks_available[right_fork])
		{
			// Marcar forks como tomados
			philo->program->forks_available[left_fork] = false;
			philo->program->forks_available[right_fork] = false;
			pthread_mutex_unlock(&philo->program->forks_lock);

			// Verificación crítica de muerte justo antes de bloquear forks
			if (philosopher_dead(philo))
			{
				pthread_mutex_lock(&philo->program->forks_lock);
				philo->program->forks_available[left_fork] = true;
				philo->program->forks_available[right_fork] = true;
				pthread_mutex_unlock(&philo->program->forks_lock);
				return (false);
			}

			// 🔁 Orden según par o impar
			lock_and_announce_forks(philo, left_fork, right_fork);
			return (true); // ✅ éxito
		}
		pthread_mutex_unlock(&philo->program->forks_lock);
	}
}
*/


bool take_two_forks(t_philo *philo, int left_fork, int right_fork)
{
    stagger_even_philos(philo);
    while (1)
    {
        if (philosopher_dead(philo))
            return false;

        pthread_mutex_lock(&philo->program->forks_lock);
        if (philo->program->forks_available[left_fork] && philo->program->forks_available[right_fork])
        {
            // Verificación crítica de muerte justo antes de marcar forks
            if (philosopher_dead(philo))
            {
                pthread_mutex_unlock(&philo->program->forks_lock);
                return (false);
            }

            // Marcar forks como tomados
            philo->program->forks_available[left_fork] = false;
            philo->program->forks_available[right_fork] = false;
            pthread_mutex_unlock(&philo->program->forks_lock);

            // 🔁 Orden según par o impar
            lock_and_announce_forks(philo, left_fork, right_fork);
            return (true); // ✅ éxito
        }
        pthread_mutex_unlock(&philo->program->forks_lock);
        //precise_sleep(philo, 3);  // pequeña pausa antes de intentar de nuevo
		//usleep(100); 
		//stagger_even_philos(philo); //este retraso hace que test die este ok pero perjudica comandos obligatorios: ./philo 4 410 200 200 25

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



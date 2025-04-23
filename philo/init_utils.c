/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 08:18:14 by mzolotar          #+#    #+#             */
/*   Updated: 2025/04/23 09:03:44 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */

void handle_single_philosopher(t_philo *philo)
{
    int left_fork = philo->id - 1;

    pthread_mutex_lock(&philo->program->forks[left_fork]);
    print_action(philo, "has taken a fork (only one available)"); //🚩_testeo:  corregir el texto de este print

    // Esperar hasta morir
    while (!philosopher_dead(philo))    
        usleep(1000); //🚩_testeo:  Pequeña espera de tiempo dead, para no consumir CPU
        
    pthread_mutex_unlock(&philo->program->forks[left_fork]);
}
/**
 * @brief 
 *
 * @param 
 * @return 
 */

// 1 -true -philo muerto
// 0 -false -philo vivo

bool philosopher_dead(t_philo *philo)
{
	//*** */ Revisar si el programa ya ha declarado la muerte de un filósofo
	// Bloquear el mutex para acceder de manera segura a la variable 'dead'
    pthread_mutex_lock(&philo->program->dead_lock);
    // Verificar si el filósofo está muerto
    if (philo->program->dead)
    {
        pthread_mutex_unlock(&philo->program->dead_lock);  //🚩_testeo:  Desbloquear el mutex dead
        return (true);  //true -philo muerto
    }
    pthread_mutex_unlock(&philo->program->dead_lock);  //🚩_testeo:  Desbloquear el mutex dead
    
	//*** */ Revisar si este filósofo ha muerto por inanición
	pthread_mutex_lock(&philo->program->meal_lock);
	if (timestamp() - philo->last_meal >= philo->program->time_to_die)
	{
		pthread_mutex_unlock(&philo->program->meal_lock);
		pthread_mutex_lock(&philo->program->dead_lock);
		philo->dead_philo = true;
		philo->program->dead = true;
		pthread_mutex_unlock(&philo->program->dead_lock);
		print_action(philo, "\033[1;31mdied\033[0m"); //🚩_testeo: quitar el color y poner //print_action(philo, "died");
		return (true);     //true -philo muerto
	}
	pthread_mutex_unlock(&philo->program->meal_lock);
	return (false);   //🚩_testeo: false -philo vivo
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

 /*
Cada filósofo toma su tenedor izquierdo (ID - 1).
Cada filósofo toma su tenedor derecho (ID % num_philos).
El último filósofo (ID = num_philos) toma el primer tenedor (ID % num_philos = 0), asegurando que el círculo sea continuo.
 */

void take_two_forks(t_philo *philo, int left_fork, int right_fork)
{
    while (1)
    {
        if (philosopher_dead(philo))
            break;

        pthread_mutex_lock(&philo->program->forks_lock);
        if (philo->program->forks_available[left_fork] && philo->program->forks_available[right_fork])
        {
            // Ambos tenedores están disponibles, tomarlos
            philo->program->forks_available[left_fork] = false;
            philo->program->forks_available[right_fork] = false;
            pthread_mutex_unlock(&philo->program->forks_lock);

            // Bloquear los mutex de los tenedores
            pthread_mutex_lock(&philo->program->forks[left_fork]);
            print_action(philo, "has taken a fork LEFT");                       //🚩_testeo quitar LEFT
            pthread_mutex_lock(&philo->program->forks[right_fork]);
            print_action(philo, "has taken a fork RIGHT");                      //🚩_testeo quitar RIGHT

            break;
        }
        pthread_mutex_unlock(&philo->program->forks_lock);
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




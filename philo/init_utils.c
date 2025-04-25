/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 08:18:14 by mzolotar          #+#    #+#             */
/*   Updated: 2025/04/25 12:19:02 by mzolotar         ###   ########.fr       */
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
    int left_fork;

    left_fork = philo->id - 1;
    pthread_mutex_lock(&philo->program->forks[left_fork]);
    //print_action(philo, "has taken a fork (only one available)"); //🚩_testeo:  corregir el texto de este print

    // Esperar hasta morir
    while (!philosopher_dead(philo))    
        precise_sleep(1, philo); //  Pequeña espera de tiempo dead, para no consumir CPU
        
    pthread_mutex_unlock(&philo->program->forks[left_fork]);
}
/**
 * @brief 
 *
 * @param 
 * @return 
 */

 void check_death_print_delay(t_philo *philo)
{
	long now = timestamp();
	long death_time = philo->last_meal + philo->program->time_to_die;
	long diff = now - death_time;

	// 🚩 testeo: Verificamos si la muerte se imprime con demora mayor a 10ms
	if (diff > 10)
		printf("\001\033[1;31m\002🛑 DEMORA detectada al imprimir muerte \001\033[0m\002 (%ldms)\n", diff);
	else
		printf("\001\033[1;32m\002✅ Muerte impresa a tiempo  \001\033[0m\002 (%ldms)\n", diff);
}

// 1 -true -philo muerto
// 0 -false -philo vivo

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
	pthread_mutex_lock(&philo->program->meal_lock);
	if (timestamp() - philo->last_meal >= philo->program->time_to_die)
	{
		pthread_mutex_unlock(&philo->program->meal_lock);

		philo->dead_philo = true;

		// Incrementar el contador de muertes de forma segura
		pthread_mutex_lock(&philo->program->dead_num_lock);
		philo->program->dead_p_num++;
		if (philo->program->dead_p_num == 1)
        {
            check_death_print_delay(philo);   // 🚩 testeo:
            print_action(philo, DIE);
        }
		pthread_mutex_unlock(&philo->program->dead_num_lock);

		return (true); // Filósofo muerto
	}
	pthread_mutex_unlock(&philo->program->meal_lock);
	return (false); // Filósofo vivo
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

/*
bool take_two_forks(t_philo *philo, int left_fork, int right_fork)
{
    while (1)
    {
        if (philosopher_dead(philo))
            return false;
        pthread_mutex_lock(&philo->program->forks_lock);
        if (philo->program->forks_available[left_fork] && philo->program->forks_available[right_fork])
        {
            philo->program->forks_available[left_fork] = false;
            philo->program->forks_available[right_fork] = false;
            pthread_mutex_unlock(&philo->program->forks_lock);
            // ⚠️ Verificar muerte justo antes de tomar forks
            if (philosopher_dead(philo))
            {
                // Devolver forks porque ya no los necesita
                pthread_mutex_lock(&philo->program->forks_lock);
                philo->program->forks_available[left_fork] = true;
                philo->program->forks_available[right_fork] = true;
                pthread_mutex_unlock(&philo->program->forks_lock);
                return false;
            }

            pthread_mutex_lock(&philo->program->forks[left_fork]);
            print_action(philo, "has taken a fork LEFT");           //◦ timestamp_in_ms X has taken a fork
            pthread_mutex_lock(&philo->program->forks[right_fork]);
            print_action(philo, "has taken a fork RIGHT");           //◦ timestamp_in_ms X has taken a fork
            return true; // ✅ éxito
        }
        pthread_mutex_unlock(&philo->program->forks_lock);
    }
}
*/

bool take_two_forks(t_philo *philo, int left_fork, int right_fork)
{
    // ⚠️ Escalonar filósofos pares ligeramente
    if (philo->id % 2 == 0)
        precise_sleep(5, philo);

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
                return false;
            }

            // 🔁 Orden según par o impar
            if (philo->id % 2 == 0)
            {
                pthread_mutex_lock(&philo->program->forks[right_fork]);
                print_action(philo, "has taken a fork RIGHT");
                pthread_mutex_lock(&philo->program->forks[left_fork]);
                print_action(philo, "has taken a fork LEFT");
            }
            else
            {
                pthread_mutex_lock(&philo->program->forks[left_fork]);
                print_action(philo, "has taken a fork LEFT");
                pthread_mutex_lock(&philo->program->forks[right_fork]);
                print_action(philo, "has taken a fork RIGHT");
            }

            return true; // ✅ éxito
        }
        pthread_mutex_unlock(&philo->program->forks_lock);
    }
}

 
/*
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
    */


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




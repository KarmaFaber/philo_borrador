/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:32:11 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/07 14:59:48 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */

//los precide sleep retrasan la entrada en accion 3 o 4 ms 
// Apply a small delay to even philosophers to reduce race conditions
void	stagger_even_philos(t_philo *philo)
{
	/*
	if (philo->id % 2 == 0)
		precise_sleep(philo, 3); // 🚩🚩🚩 5 es el mejor rango hasta ahora, otros rangos fallan por todos lados 
	else if (philo->id % 2 != 0)
		precise_sleep(philo, 2);
	*/
	/*
	if (philo->id % 2 == 0)
		usleep(400);
		//precise_sleep(philo, 3); // 🚩🚩🚩 5 es el mejor rango hasta ahora, otros rangos fallan por todos lados 
	else if (philo->id % 2 != 0)
		usleep(450);
	//	precise_sleep(philo, 1);
	*/
	if (philo->id % 2 == 0)
		usleep(200);  // 500
	else 
		usleep(820);  // 820

	
}
/**
 * @brief 
 *
 * @param 
 * @return 
 */

// Lock mutexes and print actions in the correct order (based on philosopher ID)
/*
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
	*/
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
*/
/*
bool take_two_forks(t_philo *philo, int left_fork, int right_fork)
{
    int has_left = 0;
    int has_right = 0;

    stagger_even_philos(philo);

    while (1)
    {
        if (philosopher_dead(philo))
        {
            if (has_left)
                pthread_mutex_unlock(&philo->program->forks[left_fork]);
            if (has_right)
                pthread_mutex_unlock(&philo->program->forks[right_fork]);

            pthread_mutex_lock(&philo->program->forks_lock);
            if (has_left)
                philo->program->forks_available[left_fork] = true;
            if (has_right)
                philo->program->forks_available[right_fork] = true;
            pthread_mutex_unlock(&philo->program->forks_lock);

            return false;
        }

        pthread_mutex_lock(&philo->program->forks_lock);
		
        if (!has_left && philo->program->forks_available[left_fork])
        {
            philo->program->forks_available[left_fork] = false;
            has_left = 1;
            pthread_mutex_unlock(&philo->program->forks_lock);
            pthread_mutex_lock(&philo->program->forks[left_fork]);
            print_action(philo, "has taken a fork LEFT");
        }
        else if (!has_right && philo->program->forks_available[right_fork])
        {
            philo->program->forks_available[right_fork] = false;
            has_right = 1;
            pthread_mutex_unlock(&philo->program->forks_lock);
            pthread_mutex_lock(&philo->program->forks[right_fork]);
            print_action(philo, "has taken a fork RIGHT");
        }
        else
        {
            pthread_mutex_unlock(&philo->program->forks_lock);
        }

        if (has_left && has_right)
            return true;

		usleep(10);
        //usleep(50);  // pequeña pausa antes de reintentar
    }
}
	*/
/*
bool take_two_forks(t_philo *philo, int left_fork, int right_fork)
{
	int has_left = 0;
	int has_right = 0;

	stagger_even_philos(philo);

	while (1)
	{
		//precise_sleep(philo, 1); //antres de verificar dead esperamos un poco para desincronizar los hilos que entran a la vez

		if (philosopher_dead(philo))
		{
			if (has_left)
				pthread_mutex_unlock(&philo->program->forks[left_fork]);
			if (has_right)
				pthread_mutex_unlock(&philo->program->forks[right_fork]);

			pthread_mutex_lock(&philo->program->forks_lock);
			if (has_left)
				philo->program->forks_available[left_fork] = true;
			if (has_right)
				philo->program->forks_available[right_fork] = true;
			pthread_mutex_unlock(&philo->program->forks_lock);

			return false;
		}

		pthread_mutex_lock(&philo->program->forks_lock);

		// 🟢 Primer filósofo agarra los dos
		if (!philo->program->first_round_done && philo->id == 1 &&
			philo->program->forks_available[left_fork] &&
			philo->program->forks_available[right_fork])
		{
			philo->program->forks_available[left_fork] = false;
			philo->program->forks_available[right_fork] = false;
			philo->program->first_round_done = true;
			pthread_mutex_unlock(&philo->program->forks_lock);

			pthread_mutex_lock(&philo->program->forks[left_fork]);
			print_action(philo, "has taken a fork LEFT");

			pthread_mutex_lock(&philo->program->forks[right_fork]);
			print_action(philo, "has taken a fork RIGHT");

			return true;
		}

		// 🟡 Los demás filósofos: intentan tomar 1 primero
		if (!has_right && philo->program->forks_available[right_fork])
		{
			philo->program->forks_available[right_fork] = false;
			has_right = 1;
			pthread_mutex_unlock(&philo->program->forks_lock);

			pthread_mutex_lock(&philo->program->forks[right_fork]);
			print_action(philo, "has taken a fork RIGHT");
		}
		else if (has_right && !has_left && philo->program->forks_available[left_fork])
		{
			philo->program->forks_available[left_fork] = false;
			has_left = 1;
			pthread_mutex_unlock(&philo->program->forks_lock);

			pthread_mutex_lock(&philo->program->forks[left_fork]);
			print_action(philo, "has taken a fork LEFT");
		}
		else
		{
			pthread_mutex_unlock(&philo->program->forks_lock);
		}

		if (has_left && has_right)
			return true;

		usleep(10); // Pequeña pausa
	}
}
	*/

/*
bool take_two_forks(t_philo *philo, int left_fork, int right_fork)
{
    int has_left = 0;
    int has_right = 0;

    stagger_even_philos(philo); // Control de la sincronización entre filósofos pares e impares

    while (1)
    {
        if (philosopher_dead(philo))
        {
            if (has_left)
                pthread_mutex_unlock(&philo->program->forks[left_fork]);
            if (has_right)
                pthread_mutex_unlock(&philo->program->forks[right_fork]);

            pthread_mutex_lock(&philo->program->forks_lock);
            if (has_left)
                philo->program->forks_available[left_fork] = true;
            if (has_right)
                philo->program->forks_available[right_fork] = true;
            pthread_mutex_unlock(&philo->program->forks_lock);

            return false;
        }

        pthread_mutex_lock(&philo->program->forks_lock);

        // Tomar tenedores en el orden más seguro
        if (!has_left && philo->program->forks_available[left_fork])
        {
            philo->program->forks_available[left_fork] = false;
            has_left = 1;
            pthread_mutex_unlock(&philo->program->forks_lock);
            pthread_mutex_lock(&philo->program->forks[left_fork]);
            print_action(philo, "has taken a fork LEFT");
        }
        
        if (!has_right && philo->program->forks_available[right_fork])
        {
            philo->program->forks_available[right_fork] = false;
            has_right = 1;
            pthread_mutex_unlock(&philo->program->forks_lock);
            pthread_mutex_lock(&philo->program->forks[right_fork]);
            print_action(philo, "has taken a fork RIGHT");
        }
        else
        {
            pthread_mutex_unlock(&philo->program->forks_lock);
        }

        // Si ambos tenedores han sido tomados, devolvemos éxito
        if (has_left && has_right)
            return true;

        usleep(10); // Pequeña pausa para permitir que otros filósofos liberen tenedores
    }
}
*/
bool take_two_forks(t_philo *philo, int left_fork, int right_fork)
{
    int has_left = 0;
    int has_right = 0;

    stagger_even_philos(philo);  // Ajustar la toma de tenedores para desincronizar los filósofos

	if (left_fork > right_fork)
    {
        int tmp = left_fork;
        left_fork = right_fork;
        right_fork = tmp;
    }

    while (1)
    {
        if (philosopher_dead(philo))
        {
            if (has_left)
                pthread_mutex_unlock(&philo->program->forks[left_fork]);
            if (has_right)
                pthread_mutex_unlock(&philo->program->forks[right_fork]);

            pthread_mutex_lock(&philo->program->forks_lock);
            if (has_left)
                philo->program->forks_available[left_fork] = true;
            if (has_right)
                philo->program->forks_available[right_fork] = true;
            pthread_mutex_unlock(&philo->program->forks_lock);

            return false;
        }

        pthread_mutex_lock(&philo->program->forks_lock);

        // Intentar tomar el tenedor con el ID más bajo primero
        if (!has_left && philo->program->forks_available[left_fork])
        {
            philo->program->forks_available[left_fork] = false;
            has_left = 1;
            print_action(philo, "has taken a fork LEFT");
        }

        if (!has_right && philo->program->forks_available[right_fork])
        {
            philo->program->forks_available[right_fork] = false;
            has_right = 1;
            print_action(philo, "has taken a fork RIGHT");
        }

        pthread_mutex_unlock(&philo->program->forks_lock);

        if (has_left && has_right)
        {
            return true;  // Ambos tenedores adquiridos
        }
        else
        {
            if (has_left)
                philo->program->forks_available[left_fork] = true;

            if (has_right)
                philo->program->forks_available[right_fork] = true;

            usleep(100);  // Espera pequeña para desincronizar los intentos de los filósofos
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



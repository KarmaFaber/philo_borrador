/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:42:33 by mzolotar          #+#    #+#             */
/*   Updated: 2025/02/04 21:12:22 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */

int init_program(t_program *program, char **argv)
{
	int i;
	
	i = 0;
	program->start_time = timestamp();
	program->dead = false;				
	program->num_philos = atol_unsigned(argv[1]);
	program->time_to_die = atol_unsigned(argv[2]);
	program->time_to_eat =  atol_unsigned(argv[3]);
	program->time_to_sleep = atol_unsigned(argv[4]);
	if (argv[5])
		program->num_times_to_eat = atol_unsigned(argv[5]);
	if (argv[5] && program->num_times_to_eat == 0)
		return (0);
		
	// Asignar memoria para los mutex de los tenedores
    program->forks = malloc(sizeof(pthread_mutex_t) * program->num_philos);
	if (!program->forks)
		return (0);
    while (i < program->num_philos)
	{
        pthread_mutex_init(&program->forks[i], NULL);
		i++;
	}

    // Inicializar los mutex generales
    pthread_mutex_init(&program->write_lock, NULL);
    pthread_mutex_init(&program->dead_lock, NULL);
    pthread_mutex_init(&program->meal_lock, NULL);

    // Asignar memoria para el array de filósofos
	program->philos = malloc(sizeof(t_philo) * program->num_philos);
	if (!program->philos)
	{
		free(program->forks);
		return (0);
	}
	return (1);
}
/**
 * @brief 
 *
 * @param 
 * @return 
 */

int philosopher_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->meal_lock);
	if (timestamp() - philo->last_meal >= philo->program->time_to_die)
	{
		pthread_mutex_unlock(&philo->program->meal_lock);
		pthread_mutex_lock(&philo->program->dead_lock);
		philo->program->dead = true;
		pthread_mutex_unlock(&philo->program->dead_lock);
		print_action(philo, "has died");
		return (1);
	}
	pthread_mutex_unlock(&philo->program->meal_lock);
	return (0);
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

void *philosopher_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (!philo->program->dead && (philo->program->num_times_to_eat == 0 || philo->meals_eaten < philo->program->num_times_to_eat))
	{
		// Verificar si el filósofo ha muerto
		if (philosopher_dead(philo))
			break;
		
		// Tomar tenedores
		pthread_mutex_lock(philo->l_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_action(philo, "has taken a fork");

		// Comer
		print_action(philo, "is eating");
		pthread_mutex_lock(&philo->program->meal_lock);
		philo->last_meal = timestamp();
		pthread_mutex_unlock(&philo->program->meal_lock);
		usleep(philo->program->time_to_eat * 1000);
		philo->meals_eaten++;

		// Soltar tenedores
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);

		// Dormir
		print_action(philo, "is sleeping");
		usleep(philo->program->time_to_sleep * 1000);

		// Pensar
		print_action(philo, "is thinking");

		// Verificar si el filósofo ha muerto nuevamente antes de continuar
		if (philosopher_dead(philo))
			break;
	}
	return NULL;
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

int init_philo(t_program *program)
{
	int i;
	 
	// Crear los hilos de los filósofos
	i=0;
    while (i < program->num_philos)
    {
		program->philos[i].id = i + 1;  // Asignar un ID único a cada filósofo
		program->philos[i].meals_eaten = 0;
		program->philos[i].dead_philo = false;
		program->philos[i].last_meal = timestamp();
		
		// Asignar los tenedores (mutex) a cada filósofo
    	program->philos[i].l_fork = &program->forks[i];
    	program->philos[i].r_fork = &program->forks[(i + 1) % program->num_philos];
		program->philos[i].program = program;
        pthread_create(&program->philos[i].thread, NULL, philosopher_routine, &program->philos[i]);
		i++;
    }

	i=0;
	while (i < program->num_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
 
	return (1);
}
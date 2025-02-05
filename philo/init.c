/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:42:33 by mzolotar          #+#    #+#             */
/*   Updated: 2025/02/05 12:24:04 by mzolotar         ###   ########.fr       */
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
		
	// Asignar memoria para el array de forks_available
	program->forks_available = malloc(sizeof(bool) * program->num_philos);
	if (!program->forks_available)
		return (0);
	i=0;
	while (i < program->num_philos)
	{
		program->forks_available[i] = true; // Todos los tenedores están disponibles al inicio
		i++;
	}
	pthread_mutex_init(&program->forks_lock, NULL); // Mutex para proteger las flags de tenedores


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
		philo->dead_philo = true;
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

int monitor_dead(t_philo *philo)
{
    // Bloquear el mutex para acceder de manera segura a la variable 'dead'
    pthread_mutex_lock(&philo->program->dead_lock);

    // Verificar si el filósofo está muerto
    if (philo->program->dead)
    {
        pthread_mutex_unlock(&philo->program->dead_lock);  // Desbloquear el mutex
        return 1;  // El filósofo está muerto
    }

    pthread_mutex_unlock(&philo->program->dead_lock);  // Desbloquear el mutex
    return 0;  // El filósofo no está muerto
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
    int left_fork = philo->id - 1;
    int right_fork = philo->id % philo->program->num_philos;


	// Caso especial: solo un filósofo
    if (philo->program->num_philos == 1)
    {
        pthread_mutex_lock(&philo->program->forks[left_fork]);
        print_action(philo, "has taken a fork (only one available)");  //corregir texto
        
        // Esperar hasta morir
        while (!philosopher_dead(philo))	
			usleep(1000); // Pequeña espera para no consumir CPU
            
        
        pthread_mutex_unlock(&philo->program->forks[left_fork]);
        return NULL;
    }

    while (!philo->program->dead && (philo->program->num_times_to_eat == 0 || philo->meals_eaten < philo->program->num_times_to_eat))
    {
        if (philosopher_dead(philo))
            break;

        // Intentar tomar los 2 tenedores
        while (1)
        {
			if (philo->program->dead)  // <-- Este bloque verifica si el programa ya está muerto
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
                print_action(philo, "has taken a fork LEFT");
                pthread_mutex_lock(&philo->program->forks[right_fork]);
                print_action(philo, "has taken a fork RIGHT");

                break;
            }
            pthread_mutex_unlock(&philo->program->forks_lock);
        }
		
		if (philo->program->dead)  // <-- Este bloque verifica si el programa ya está muerto
                break;

		// Comer
		print_action(philo, "is eating");
		pthread_mutex_lock(&philo->program->meal_lock);
		philo->last_meal = timestamp();
		pthread_mutex_unlock(&philo->program->meal_lock);
		usleep(philo->program->time_to_eat * 1000);
		philo->meals_eaten++;
        

        // Liberar los tenedores
        pthread_mutex_unlock(&philo->program->forks[left_fork]);
		print_action(philo, "ha soltado fork LEFT");				//quitar esto es de prueba
        pthread_mutex_unlock(&philo->program->forks[right_fork]);
		print_action(philo, "ha soltado fork RIGHT");				//quitar esto es de prueba

        pthread_mutex_lock(&philo->program->forks_lock);
        philo->program->forks_available[left_fork] = true;
        philo->program->forks_available[right_fork] = true;
        pthread_mutex_unlock(&philo->program->forks_lock);

        // Dormir
        print_action(philo, "is sleeping");
        usleep(philo->program->time_to_sleep * 1000);

        // Pensar
        print_action(philo, "is thinking");


		// Verificar si el filósofo ha muerto
        if (philosopher_dead(philo))
            break;

		// Si un filósofo ha muerto, terminar todos los hilos
        if (philo->program->dead)
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

		// Asignar el programa al filósofo
		program->philos[i].program = program; 		
		
		// Crear el hilo para cada filósofo
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

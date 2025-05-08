/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:42:33 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/07 14:55:11 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */

static int sub_init_program(t_program *program, char **argv)
{		
	program->dead_p_num = 0;		
	program->num_philos = atol_unsigned(argv[1]);
	program->time_to_die = atol_unsigned(argv[2]);
	program->time_to_eat =  atol_unsigned(argv[3]);
	program->time_to_sleep = atol_unsigned(argv[4]);
	
	if (argv[5])
		program->num_times_to_eat = atol_unsigned(argv[5]);
	else
		program->num_times_to_eat = -1;  // Para diferenciar si se usa o no
	if (argv[5] && program->num_times_to_eat == 0)
		return (printf("%s", STR_ERR_INP), 0);

	program->first_round_done = false;
	
	// Inicializar los mutex generales
	if ((pthread_mutex_init(&program->write_lock, NULL) !=0) || (pthread_mutex_init(&program->dead_num_lock, NULL) != 0) || (pthread_mutex_init(&program->forks_lock, NULL) != 0))
		return (free_all(program), printf("%s", STR_ERR_MUTEX), 0);
	//pthread_mutex_init(&program->meal_lock, NULL);
	// Asignar memoria para el array de filósofos
	program->philos = malloc(sizeof(t_philo) * program->num_philos);
	if (!program->philos)
		return (free_all(program), printf("%s", STR_ERR_MALLOC), 0);
	return (1);
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

int init_program(t_program *program, char **argv)
{
	int i;
	
	if (!sub_init_program(program, argv))
		return (0);
		
	// Asignar memoria para los mutex de los tenedores
    program->forks = malloc(sizeof(pthread_mutex_t) * program->num_philos);
	if (!program->forks)
		return (free_all(program), printf("%s", STR_ERR_MALLOC), 0);
	i = 0;
    while (i < program->num_philos)
	{
        if (pthread_mutex_init(&program->forks[i], NULL) != 0)
			return (free_all(program), printf("%s", STR_ERR_MUTEX), 0);
		i++;
	}
	
	// Asignar memoria para el array de forks_available
	program->forks_available = malloc(sizeof(bool) * program->num_philos);
	if (!program->forks_available)
		return (free_all(program), printf("%s", STR_ERR_MALLOC), 0);
	i = 0;
	while (i < program->num_philos)
	{
		program->forks_available[i] = true; // Todos los tenedores están disponibles al inicio
		i++;
	}
	return (1);
}

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

	// Esperar hasta morir
	while (!philosopher_dead(philo))    
		precise_sleep(philo, 1); //  Pequeña espera de tiempo dead, para no consumir CPU
		
	pthread_mutex_unlock(&philo->program->forks[left_fork]);
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */
 
void *philosopher_routine(void *arg)
{
    t_philo *philo;
	int left_fork;
    int right_fork;	

	philo = (t_philo *)arg;
	left_fork = philo->id - 1;
	right_fork = (philo->id) % philo->program->num_philos;

	// Caso especial: solo un filósofo
    if (philo->program->num_philos == 1)
    {
        handle_single_philosopher(philo);
        return (NULL);
    }
	
	//todas rutinas
    all_routines(philo, left_fork, right_fork);
	
    return (NULL);
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
	 
	i = 0;
	program->start_time = timestamp(); 
    while (i < program->num_philos)    // Crear los hilos de los filósofos
    {
		program->philos[i].id = i + 1;  // Asignar un ID único a cada filósofo
		program->philos[i].meals_eaten = 0;
		//program->philos[i].dead_philo = false;
		program->philos[i].last_meal = timestamp();

		// Asignar el programa al filósofo
		program->philos[i].program = program; 		
		
		// Crear el hilo para cada filósofo
        if (pthread_create(&program->philos[i].thread, NULL, philosopher_routine, &program->philos[i]) != 0)
			return (free_all(program), clean_pthreads(program, i), 0);
			
		if (program->philos[i].id < 7)
			usleep(650); // 450 - Desincroniza el lanzamiento de los hilos
		else 
			usleep(300); 
		i++;
		
    }
	// 🟡 Aquí metes la pausa si hay cantidad impar/par de filósofos
	//usleep(200);
	if (program->num_philos % 2 != 0)
		usleep(100); //2
		//usleep(1000);  // 0.5 ms de gracia para aliviar la congestión de inicio
	
	i = 0;
	while (i < program->num_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
	return (1);
}

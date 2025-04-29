/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:08:11 by mzolotar          #+#    #+#             */
/*   Updated: 2025/04/29 12:01:21 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//#➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌──includes:──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔#

# include <limits.h>   //INT_MAX
# include <pthread.h>  //pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
# include <stdbool.h>  //bool
# include <stdio.h>    //printf
# include <stdlib.h>   // malloc, free
# include <string.h>   // memset
# include <sys/time.h> //gettimeofday
# include <unistd.h>   // write, usleep

//#➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌──Macros  :──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔#

# define MAX_PHILOS 200
# define STR_MAX_PHILOS "200"

//#➵⤐──╌╌➣➣╌╌──ERR. MSGS:  :──╌╌➣➣╌╌➔#

# define STR_ERR_INPUT_DIGIT \
	"\001\033[1;31m\002Error: invalid input \
(not a valid unsigned integer between 0 and 2147483647).\n\001\033[0m\002"

# define STR_ERR_ARG "\001\033[1;31m\002Error: incorrect number of arguments.\n\001\033[0m\002"
# define STR_ERR_P_NUM "\001\033[1;31m\002Error: incorrect number of philosophers.\n\001\033[0m\002"

# define STR_ERR_THREAD "\001\033[1;31m\002Error: Could not create thread.\n\001\033[0m\002"
# define STR_ERR_MALLOC "\001\033[1;31m\002Error: Could not allocate memory.\n\001\033[0m\002"
# define STR_ERR_MUTEX "\001\033[1;31m\002Error: Could not create mutex.\n\001\033[0m\002"

# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "\001\033[1;31m\002died\001\033[0m\002"

//#➵⤐──╌╌➣⋆➣╌─⤏➵•➵⤐──╌╌➣⋆➣╌╌──Structures  :──╌╌➣⋆➣╌╌⤏➵•➵⤐──╌╌➣⋆➣╌╌➔#

// unsigned short int num = 65535; 2 bytes.
// unsigned int num = 4294967295;

typedef struct s_program
{
	unsigned short int 		num_philos; 			// Número total de filósofos
	unsigned int 			num_times_to_eat; 		// Número de veces que deben comer
	
	int dead_p_num;									//nemero de filosofos muertos
	
	bool 	*forks_available; 						// indica si el tenedor está disponible
	
	time_t	start_time;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	
	pthread_mutex_t 	forks_lock;			//  ✅ protege el acceso a los tenedores
	pthread_mutex_t 	*forks;     		//  ✅ Array de mutex para los tenedores
	pthread_mutex_t 	write_lock; 		//  ✅ Mutex para controlar las impresiones en pantalla
	pthread_mutex_t 	dead_num_lock;  	// ✅ Mutex para proteger la variable `dead`
	//pthread_mutex_t 	meal_lock;  		// ⚠️ Mutex para verificar si todos comieron
	
	struct s_philo 		*philos; 			// Array de filósofos
}	t_program;

typedef struct s_philo
{
	pthread_t thread;        	 // Hilo del filósofo
	unsigned short int id;   	 // ID del filósofo
	unsigned int meals_eaten; 	// Número de comidas consumidas
	time_t last_meal;        	 // Última vez que comió
	bool dead_philo;			//estado muerto de cada philo[i++]
	t_program *program; 		// Referencia a la estructura principal
	
}	t_philo;

//#➵⤐╌╌➣⋆➣╌─⤏➵•➵⤐╌╌➣⋆➣╌╌─Function Prototypes : :──➣⋆➣╌⤏➵•➵⤐╌╌➣⋆➣╌╌➔#
// main.c (/5):
// int main (int argc, char **argv);


// parce.c (3/5)
// static bool contain_digits_only(char *str);			
int			atol_unsigned(const char *nptr);
bool		check_argvs(int argc_var, char **argv_var);


//init.c (5/5)
//static int sub_init_program(t_program *program, char **argv);
int init_program(t_program *program, char **argv);
void handle_single_philosopher(t_philo *philo);
void *philosopher_routine(void *arg);
int init_philo(t_program *program);


//fork_management.c (/5)
void	stagger_even_philos(t_philo *philo);
void	lock_and_announce_forks(t_philo *philo, int left_fork, int right_fork);
bool	take_two_forks(t_philo *philo, int left_fork, int right_fork);
void	free_forks(t_philo *philo, int left_fork, int right_fork);


// routines.c (/5)
bool philosopher_dead(t_philo *philo);
bool take_forks_and_eat(t_philo *philo, int left_fork, int right_fork);
bool sleep_and_think_routine(t_philo *philo);
void all_routines (t_philo *philo, int left_fork, int right_fork);


// exit.c (/5)
int		error_msg(char *str, int exit_no);
void	free_all(t_program *program);


// utils (5/5):
long long	timestamp(void);
void		print_action(t_philo *philo, const char *action);
void		print_dead(t_philo *philo, const char *action);
void		precise_sleep(long long duration, t_philo *philo);
void		final_print(t_program *program);


//test/test_functions.c
void check_death_print_delay(t_philo *philo);
//void see_struct_data(t_program *program) 

#endif
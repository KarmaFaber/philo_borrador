/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:08:11 by mzolotar          #+#    #+#             */
/*   Updated: 2025/01/29 21:43:03 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef DEBUG_FORMATTING
#  define DEBUG_FORMATTING 0
# endif

//#➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌──includes:──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔#

# include <stdbool.h>	//bool
# include <limits.h> 	//INT_MAX

# include <unistd.h> 	// write, usleep 
# include <stdlib.h> 	// malloc, free
# include <stdio.h> 	//printf
# include <string.h> 	// memset
# include <sys/time.h> 	//gettimeofday
# include <pthread.h> 	//pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

//#➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌──Macros  :──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔#

//#➵⤐──╌╌➣➣╌╌──Colors  :──╌╌➣➣╌╌➔#

//letter color:
# define NC      "\e[0m"   // Reset color
# define BLACK   "\e[30m"
# define RED     "\e[31m"
# define GREEN   "\e[32m"
# define BLUE    "\e[34m"
# define PURPLE  "\e[35m"
# define CYAN    "\e[36m"

//background color:
# define BG_RED     "\e[41m"
# define BG_GREEN   "\e[42m"
# define BG_YELLOW  "\e[43m"
# define BG_BLUE    "\e[44m"
# define BG_PURPLE  "\e[45m"
# define BG_CYAN    "\e[46m"
# define BG_WHITE   "\e[47m"

//#➵⤐──╌╌➣➣╌╌──OTHER: ──╌╌➣➣╌╌➔#

# define MAX_PHILOS	250
# define STR_MAX_PHILOS "250"

//#➵⤐──╌╌➣➣╌╌──ERR. MSGS:  :──╌╌➣➣╌╌➔#

# define STR_ERR_INPUT_DIGIT	"Error: invalid input: \
not a valid unsigned integer between 0 and 2147483647.\n"
# define STR_ERR_THREAD	"Error: Could not create thread.\n"
# define STR_ERR_MALLOC	"Error: Could not allocate memory.\n"
# define STR_ERR_MUTEX	"Error: Could not create mutex.\n"

//#➵⤐──╌╌➣⋆➣╌─⤏➵•➵⤐──╌╌➣⋆➣╌╌──Structures  :──╌╌➣⋆➣╌╌⤏➵•➵⤐──╌╌➣⋆➣╌╌➔#






//#➵⤐──╌╌➣⋆➣╌─⤏➵•➵⤐──╌╌➣⋆➣╌╌── Enum  :──╌╌➣⋆➣╌╌⤏➵•➵⤐──╌╌➣⋆➣╌╌➔#




//#➵⤐╌╌➣⋆➣╌─⤏➵•➵⤐╌╌➣⋆➣╌╌─Function Prototypes : :──➣⋆➣╌⤏➵•➵⤐╌╌➣⋆➣╌╌➔#
//main.c (/5):

//int main (int argc, char **argv);

//parce.c (/5)
//static bool contain_digits_only(char *str);
bool check_argvs (int argc_var, char **argv_var);

//exit.c (/5)
int error_msg (char *str, int exit_no);

//utils (/5):
int	atol_unsigned(const char *nptr);



#endif
#include "../philo.h"


void see_struct_data(t_program *program)   // borrar testeo
{
    printf("\n\n=== Datos del programa ===\n");
    printf("Número de filósofos       : %hu\n", program->num_philos);
    printf("Tiempo para morir         : %ld ms\n", program->time_to_die);
    printf("Tiempo para comer         : %ld ms\n", program->time_to_eat);
    printf("Tiempo para dormir        : %ld ms\n", program->time_to_sleep);
    printf("Número de comidas requeridas: %u\n", program->num_times_to_eat);
    printf("Simulación iniciada en    : %ld ms\n", program->start_time);
    printf("Estado de muerte global   : %d\n", program->dead_p_num);

    printf("\n=== Datos de los filósofos ===\n");
    for (int i = 0; i < program->num_philos; i++)
    {
        t_philo *philo = &program->philos[i];
        printf("\n--- Filósofo %d ---\n", philo->id);
        printf("ID                        : %hu\n", philo->id);
        printf("Comidas consumidas        : %u\n", philo->meals_eaten);
        printf("Última comida             : %ld ms\n", philo->last_meal);
        //printf("Estado de muerte          : %s\n", philo->dead_philo ? "Sí" : "No");

    }
}

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



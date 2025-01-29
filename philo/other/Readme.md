# Philosophers

### ¿Qué es un hilo? 

Un subproceso es una secuencia única dentro de un proceso. Debido a que los subprocesos tienen algunas de las propiedades de los procesos, a veces se los denomina procesos livianos . 

### ¿Cuáles son las diferencias entre proceso e hilo? 

Los <b>subprocesos</b> no son independientes entre sí, a diferencia de los procesos. Como resultado, los subprocesos comparten con otros subprocesos su sección de código, sección de datos y recursos del sistema operativo, como archivos abiertos y señales. Pero, al igual que los procesos, un subproceso tiene su propio contador de programa (PC), un conjunto de registros y un espacio de pila.

### ¿Por qué multihilo? 

Los subprocesos son una forma popular de mejorar las aplicaciones mediante el paralelismo. Por ejemplo, en un navegador, varias pestañas pueden ser subprocesos diferentes. MS Word utiliza varios subprocesos: un subproceso para dar formato al texto, otro subproceso para procesar las entradas, etc. 

Los subprocesos funcionan más rápido que los procesos debido a las siguientes razones: 

1) La creación de hilos es mucho más rápida. 

2) El cambio de contexto entre subprocesos es mucho más rápido. 

3) Los hilos se pueden terminar fácilmente 

4) La comunicación entre hilos es más rápida.

Consulte http://www.personal.kent.edu/~rmuhamma/OpSystems/Myos/threads.htm para obtener más detalles. 

### pthread_t y pthread_mutex_t:

En C, <b>pthread_t</b> y <b>pthread_mutex_t</b> son tipos de datos utilizados en la programación multihilo, específicamente con la biblioteca pthread, que facilita la creación y sincronización de hilos.

1. <b>pthread_t</b>: 
pthread_t es un tipo de datos utilizado para representar un hilo de ejecución en un programa multihilo. Es una abstracción que el sistema operativo utiliza para identificar de manera única a cada hilo.

¿Qué es exactamente pthread_t?

- Es un identificador único de hilo dentro del sistema.
- Este identificador es necesario cuando se quieren realizar operaciones sobre un hilo, como esperar su terminación (con pthread_join()) o cancelar su ejecución (con pthread_cancel()).
- En algunos sistemas operativos, el tipo puede ser simplemente un entero o un puntero, pero en general no es necesario preocuparse por su implementación interna.

			```
			#include <pthread.h>
			#include <stdio.h>

			void* hello(void* arg) {
				printf("¡Hola desde el hilo!\n");
				return NULL;
			}

			int main() {
				pthread_t thread;  // Declaración de un hilo
				
				// Crear un hilo
				if (pthread_create(&thread, NULL, hello, NULL) != 0) {
					perror("Error al crear el hilo");
					return 1;
				}
				
				// Esperar a que el hilo termine
				pthread_join(thread, NULL);
				
				printf("El hilo ha terminado\n");
				
				return 0;
			}

			```

- pthread_t thread: Declara un identificador de hilo.
- pthread_create(): Crea un hilo nuevo, pasando el identificador del hilo como el primer argumento.
- pthread_join(): Espera a que el hilo termine su ejecución.

2. <b>pthread_mutex_t</b>:
pthread_mutex_t es un tipo de datos utilizado para representar un mutex (mutual exclusion, exclusión mutua). 
Un mutex es un mecanismo de sincronización que asegura que solo un hilo pueda acceder a una sección crítica del código a la vez, lo que ayuda a prevenir condiciones de carrera cuando múltiples hilos comparten recursos.

¿Qué es exactamente pthread_mutex_t?
- Es un tipo de datos que representa un mutex en un programa multihilo.
- Se utiliza para bloquear y desbloquear secciones del código de modo que solo un hilo pueda ejecutarlas a la vez.
- La inicialización de un mutex es necesaria antes de usarlo, y se puede hacer con pthread_mutex_init().
- El desbloqueo del mutex se realiza con pthread_mutex_unlock().


```
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Inicialización estática del mutex

void* increment(void* arg) {
    int* counter = (int*) arg;
    
    // Bloquear el mutex para acceso exclusivo
    pthread_mutex_lock(&mutex);
    
    (*counter)++;  // Modificación de la variable compartida
    
    // Desbloquear el mutex para que otros hilos puedan acceder
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main() {
    pthread_t threads[5];
    int counter = 0;
    
    // Crear varios hilos que incrementen el contador
    for (int i = 0; i < 5; i++) {
        if (pthread_create(&threads[i], NULL, increment, &counter) != 0) {
            perror("Error al crear el hilo");
            return 1;
        }
    }
    
    // Esperar a que todos los hilos terminen
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("Contador final: %d\n", counter);
    
    // Destruir el mutex cuando ya no se necesite
    pthread_mutex_destroy(&mutex);
    
    return 0;
}

```
- pthread_mutex_t mutex: Declara un mutex para proteger la variable counter.
- pthread_mutex_lock(&mutex): Bloquea el mutex antes de acceder a la variable compartida counter.
- pthread_mutex_unlock(&mutex): Desbloquea el mutex después de modificar la variable compartida.
- pthread_mutex_destroy(&mutex): Destruye el mutex una vez que ya no se necesita.

### Ejemplo 0:

```
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Header file for sleep(). man 3 sleep for details.

// A normal C function that is executed as a thread
// when its name is specified in pthread_create()

void* myThreadFun(void* vargp)
{
    sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return NULL;
}

int main()
{
    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    exit(0);
}
```

En main(), declaramos una variable llamada thread_id, que es del tipo pthread_t, que es un entero que se utiliza para identificar el hilo en el sistema. Después de declarar thread_id, llamamos a la función pthread_create() para crear un hilo. 

1. La función pthread_create() toma 4 argumentos:  <b> int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg) </b>

	- El primer argumento es un puntero a thread_id que establece esta función. 

	- El segundo argumento especifica atributos. Si el valor es NULL, se utilizarán los atributos predeterminados.

		* PTHREAD_CREATE_JOINABLE	 -> Hilo "esperable" (por defecto)
		* PTHREAD_CREATE_DETACHED	-> Hilo que se libera automáticamente
		* pthread_attr_setstacksize()	-> Define el tamaño de la pila del hilo
		* pthread_attr_setaffinity_np()	-> Asigna el hilo a un CPU específico

	- El tercer argumento es el nombre de la función que se ejecutará para el hilo que se creará. con formato: void *(*start_routine)(void *).

	- El cuarto argumento se utiliza para pasar argumentos a la función, myThreadFun. 

2. La función pthread_join(): <b>int pthread_join(pthread_t thread, void **retval)</b>

La función pthread_join() se usa para esperar a que un hilo termine su ejecución antes de continuar con el programa principal. Es útil para sincronizar hilos y asegurar que sus tareas se completen antes de que el proceso finalice.

📌 Argumentos:

- pthread_t thread → ID del hilo que queremos esperar.
- void **retval → Puntero donde se almacenará el valor devuelto por el hilo. Si no se necesita, se pasa NULL.

📌 Valor de retorno:

- 0 → Éxito.
- ESRCH → El hilo no existe.
- EINVAL → El hilo ya está detached.
- EDEADLK → Se detectó un deadlock (el hilo se está uniendo a sí mismo).

```
#include <stdio.h>
#include <pthread.h>

void *mi_hilo(void *arg) 
{
    int *resultado = (int *)malloc(sizeof(int));
    *resultado = 42;  // El hilo devuelve 42
    return resultado;
}

int main() 
{
    pthread_t hilo;
    int *valor_retorno;
    
    pthread_create(&hilo, NULL, mi_hilo, NULL);
    pthread_join(hilo, (void **)&valor_retorno);

    printf("Hilo retornó: %d\n", *valor_retorno);
    free(valor_retorno);  // Liberar memoria
    return 0;
}

```

### ¿Cómo compilar el programa anterior? 
Para compilar un programa multiproceso con gcc, debemos vincularlo con la biblioteca pthreads. A continuación, se muestra el comando utilizado para compilar el programa.

```
gfg@ubuntu:~/$ gcc multithread.c -lpthread 
gfg@ubuntu:~/$ ./a.out 
Antes del hilo 
Imprimir GeeksQuiz desde el hilo 
Después del hilo 
gfg@ubuntu:~/$

```

### pthread_detach(): int pthread_detach(pthread_t thread);

La función pthread_detach() en C se utiliza para desvincular un hilo de su hilo principal. Desvincular un hilo significa que no será necesario esperar su terminación explícitamente con pthread_join(). Al desvincular un hilo, el sistema se encarga de liberar los recursos del hilo automáticamente cuando éste termine. Esta función es útil cuando no necesitas obtener el valor de retorno de un hilo y no necesitas realizar una espera activa sobre su terminación.

	Argumentos:
	1. pthread_t thread:
	- Es el identificador del hilo que se va a desvincular. Este identificador es el que se obtiene cuando se crea un hilo mediante pthread_create().
	- Importante: Una vez que un hilo ha sido desvinculado, no se puede llamar a pthread_join() sobre ese hilo. Si intentas llamar a pthread_join() después de haber desvinculado un hilo, obtendrás un error.

	Valor de retorno:
	- 0: Si la operación de desvinculación fue exitosa.
	- Un valor distinto de 0 si ocurrió un error. En general, esto podría ocurrir si el hilo ya ha sido finalizado o si el identificador de hilo no es válido.

	Comportamiento de pthread_detach():
	- Cuando se desvincula un hilo, el sistema operativo se encarga automáticamente de liberar todos los recursos asociados a ese hilo cuando termine su ejecución.
	- Esto es útil para evitar la acumulación de hilos "zombis", que son hilos que han terminado pero cuyo estado aún no ha sido recogido (por ejemplo, cuando no se llama a pthread_join()).


	```
	#include <pthread.h>
	#include <stdio.h>
	#include <stdlib.h>

	void* print_hello(void* arg) {
		printf("¡Hola desde el hilo!\n");
		return NULL;
	}

	int main() {
		pthread_t thread;

		// Crear un hilo
		if (pthread_create(&thread, NULL, print_hello, NULL) != 0) {
			perror("Error al crear el hilo");
			return 1;
		}

		// Desvincular el hilo
		if (pthread_detach(thread) != 0) {
			perror("Error al desvincular el hilo");
			return 1;
		}

		// No necesitamos esperar a que el hilo termine, ya que está desvinculado
		// Aquí podemos continuar haciendo otras cosas mientras el hilo sigue ejecutándose.

		// Este código se ejecuta inmediatamente después de la creación del hilo,
		// sin esperar a que termine.
		printf("El hilo ha sido desvinculado.\n");

		// El hilo será limpiado automáticamente por el sistema operativo cuando termine.

		return 0;
	}

	```


### Programa AC para mostrar múltiples subprocesos con variable en una estructura

```
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_datos 
{
    int contador;           // Variable compartida
    pthread_mutex_t mutex;  // Mutex para evitar condiciones de carrera
} t_datos;

void *incrementar(void *arg) 
{
    t_datos *datos;  // Convertimos el argumento a un puntero a estructura
	int i;
    
	datos = (t_datos *)arg;
	i = 0;
    while (i < 10) 
	{
        pthread_mutex_lock(&datos->mutex);  // Bloquea el acceso
        datos->contador++;                  // Sección crítica
        pthread_mutex_unlock(&datos->mutex); // Desbloquea el acceso
		i++;
    }
    return NULL;
}

int main() 
{
    pthread_t t1;
	pthread_t t2;
    t_datos datos;  // Crear la estructura en el stack

    datos.contador = 0;
    pthread_mutex_init(&datos.mutex, NULL); // Inicializar mutex

    pthread_create(&t1, NULL, incrementar, &datos);
    pthread_create(&t2, NULL, incrementar, &datos);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Valor final del contador: %d\n", datos.contador);

    pthread_mutex_destroy(&datos.mutex); // Liberar mutex
    return 0;
}
```
Tenga en cuenta que lo anterior es un ejemplo simple para mostrar cómo funcionan los subprocesos. Acceder a una variable en un subproceso generalmente es una mala idea. ¿Qué sucede si el subproceso 2 tiene prioridad sobre el subproceso 1 y el subproceso 1 necesita cambiar la variable? En la práctica, si se requiere que varios subprocesos accedan a una variable global, se debe acceder a ellos mediante un mutex. 

1. La función pthread_create() toma 4 argumentos:  <b> int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg) </b> (ver ejemplo 0: descripción).
 
2. La función pthread_join(): <b>int pthread_join(pthread_t thread, void **retval)</b> (ver ejemplo 0: descripción).


3. pthread_mutex_init(): <b> int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr); </b>
La función pthread_mutex_init() en C se utiliza para inicializar un mutex, que es un objeto que se usa para sincronizar el acceso a recursos compartidos entre hilos, evitando condiciones de carrera.

	Argumentos:

	1. pthread_mutex_t *mutex:

	- Es un puntero a un objeto de tipo pthread_mutex_t que representa el mutex que se va a inicializar.
	- El mutex debe estar previamente declarado y asignado antes de pasarle este puntero a la función.

	2. const pthread_mutexattr_t *attr (opcional):

	- Es un puntero a una estructura de tipo pthread_mutexattr_t que define atributos adicionales para el mutex. Estos atributos permiten controlar características como el tipo de bloqueo (por ejemplo, si es recursivo o no).
	- Si no se necesita configurar atributos específicos, puedes pasar NULL en este argumento, en cuyo caso se inicializa el mutex con los valores predeterminados.

	Valores posibles de pthread_mutexattr_t:
	Algunos de los atributos que puedes configurar son:

	- PTHREAD_MUTEX_NORMAL: El comportamiento de mutex normal (sin características especiales).
	- PTHREAD_MUTEX_RECURSIVE: Un mutex recursivo, que permite que el mismo hilo adquiera el mutex varias veces sin bloquearse a sí mismo.
	- PTHREAD_MUTEX_ERRORCHECK: Un mutex de comprobación de errores, que devuelve un error si un hilo intenta bloquear un mutex que ya tiene bloqueado.
	- PTHREAD_MUTEX_DEFAULT: El valor por defecto, que no tiene características especiales.

	Valor de retorno:
	- 0 si la inicialización fue exitosa.
	- Un valor distinto de 0 en caso de error.

			```
			#include <pthread.h>
			#include <stdio.h>

			pthread_mutex_t mutex;

			int main() {
				if (pthread_mutex_init(&mutex, NULL) != 0) 
				{
					printf("Error al inicializar el mutex\n");
					return 1;
				}

				// Aquí usarías el mutex con pthread_mutex_lock() y pthread_mutex_unlock()

				pthread_mutex_destroy(&mutex);  // No olvides destruir el mutex después de usarlo
				return 0;
			}

			```

4. pthread_mutex_destroy(): <b> int pthread_mutex_destroy(pthread_mutex_t *mutex); </b>

La función pthread_mutex_destroy() en C se utiliza para destruir un mutex previamente creado y liberarlo de los recursos que el sistema operativo ha asignado para él. Después de destruir un mutex, no se debe utilizar más en el programa, ya que su estado ya no es válido.

	Argumentos:

	1. pthread_mutex_t *mutex: 

	Es un puntero al mutex que se va a destruir. El mutex debe haber sido previamente inicializado (con pthread_mutex_init() o PTHREAD_MUTEX_INITIALIZER) y debe haber sido utilizado para sincronizar hilos.


	Valor de retorno:
	- Un valor distinto de 0 si ocurrió un error (por ejemplo, si el mutex no fue inicializado correctamente o si aún hay hilos que están bloqueando el mutex)

	¿Por qué es necesario destruir un mutex?
	- Los mutexes consumen recursos del sistema operativo. Si no se destruyen correctamente después de su uso, pueden causar fugas de recursos.
	- Destruir un mutex cuando ya no se necesita asegura que el sistema libere los recursos asociados a él, evitando problemas de rendimiento o memoria.

	Consideraciones antes de destruir un mutex:
	- El mutex debe estar desbloqueado: No se debe intentar destruir un mutex mientras un hilo lo está bloqueando. Si el mutex está bloqueado, la llamada a pthread_mutex_destroy() fallará.
	- No utilizar el mutex después de destruirlo: Una vez que el mutex ha sido destruido, cualquier intento de bloquear o desbloquear el mutex resultará en un comportamiento indefinido.

5. pthread_mutex_lock(): <b> int pthread_mutex_lock(pthread_mutex_t *mutex); </b>

La función pthread_mutex_lock() en C se utiliza para bloquear un mutex. Bloquear un mutex garantiza que solo un hilo pueda ejecutar una sección crítica de código a la vez, evitando así condiciones de carrera y garantizando la sincronización entre hilos que comparten recursos.

	Argumentos:

	1. pthread_mutex_t *mutex:

	- Es un puntero al mutex que se va a bloquear. El mutex debe haber sido inicializado previamente (usando pthread_mutex_init() o PTHREAD_MUTEX_INITIALIZER).
	- El hilo que llama a pthread_mutex_lock() intentará bloquear el mutex. Si otro hilo ya ha bloqueado el mutex, el hilo que llama a pthread_mutex_lock() se bloqueará (esperará) hasta que el mutex sea liberado.

	Valor de retorno:
	
	- 0 si el mutex fue bloqueado con éxito.
	- Un valor distinto de 0 si ocurrió un error (por ejemplo, si el mutex no ha sido inicializado correctamente).	

	Comportamiento de pthread_mutex_lock():
	- Si el mutex está desbloqueado, el hilo que llama a pthread_mutex_lock() lo bloqueará y continuará su ejecución.
	- Si el mutex está bloqueado por otro hilo, el hilo que llama a pthread_mutex_lock() se bloqueará (es decir, esperará) hasta que el mutex sea desbloqueado por el hilo que lo tiene bloqueado.

6. pthread_mutex_unlock(): <b> int pthread_mutex_unlock(pthread_mutex_t *mutex); </b>

La función pthread_mutex_unlock() en C se utiliza para desbloquear un mutex que ha sido previamente bloqueado por el hilo que lo está utilizando. Desbloquear el mutex permite que otros hilos puedan acceder a la sección crítica que estaba protegida por dicho mutex. Es una parte crucial de la sincronización en programación multihilo.

	Argumentos:

	1. pthread_mutex_t *mutex:

	- Es un puntero al mutex que se va a desbloquear. El mutex debe haber sido previamente bloqueado por el hilo que llama a pthread_mutex_unlock().
	- Importante: Un hilo no debe intentar desbloquear un mutex que no ha bloqueado previamente. Desbloquear un mutex de un hilo diferente o intentar desbloquear un mutex no bloqueado puede resultar en un comportamiento indefinido.

	Valor de retorno:

	- 0 si el desbloqueo fue exitoso.
	- Un valor distinto de 0 si ocurrió un error (por ejemplo, si el mutex no fue bloqueado correctamente o si se intenta desbloquear un mutex que no está bloqueado por el hilo que hace la llamada).

	Comportamiento de pthread_mutex_unlock():
	- Desbloqueo del mutex: Si el hilo que llama a pthread_mutex_unlock() tiene el mutex bloqueado, lo desbloquea, permitiendo que otros hilos lo bloqueen y accedan a la sección crítica.
	- Condición de carrera: Cuando un mutex es desbloqueado, otro hilo que esté esperando por el mismo mutex puede ser capaz de adquirirlo y continuar su ejecución.

	Puntos importantes sobre pthread_mutex_unlock():
	- Desbloquear solo un mutex bloqueado: El hilo que llama a pthread_mutex_unlock() debe ser el mismo hilo que bloqueó el mutex previamente con pthread_mutex_lock(). Si un hilo intenta desbloquear un mutex que no ha bloqueado, el comportamiento es indefinido y puede causar errores en la ejecución del programa.

	- Condiciones de carrera: El desbloqueo de un mutex permite que otros hilos lo adquieran. Si hay varios hilos esperando por el mutex, el sistema operativo decidirá cuál hilo obtiene el mutex según su planificación interna.

	- Uso en programación multihilo: La combinación de pthread_mutex_lock() y pthread_mutex_unlock() es esencial para proteger secciones críticas del código en programas multihilo, evitando que más de un hilo acceda a recursos compartidos al mismo tiempo.


### Ejemplo 2: Crear y Ejecutar un Hilo.

Cada hilo ejecuta una función independiente.

```
#include <stdio.h>
#include <pthread.h>

void *mi_hilo(void *arg) 
{
    printf("Hola desde el hilo %d\n", *(int *)arg);
    return NULL;
}

int main() 
{
    pthread_t hilo;
    int id = 1;
    
    pthread_create(&hilo, NULL, mi_hilo, &id);  // Crear el hilo
    pthread_join(hilo, NULL);  // Esperar a que termine
    
    printf("Hilo finalizado\n");
    return 0;
}

```
1. pthread_create(&hilo, NULL, mi_hilo, &id);
- Crea un nuevo hilo y ejecuta mi_hilo().
- Se pasa id como argumento al hilo.
2. pthread_join(hilo, NULL);
- Espera a que el hilo termine antes de continuar.



### Ejemplo 3: Varios Hilos con Argumentos Distintos

Si necesitas que cada hilo reciba un argumento distinto, usa estructuras:

```
#include <stdio.h>
#include <pthread.h>

typedef struct {
    int id;
} datos_hilo;

void *mi_hilo(void *arg) {
    datos_hilo *datos = (datos_hilo *)arg;
    printf("Hilo %d ejecutando\n", datos->id);
    return NULL;
}

int main() {
    pthread_t hilos[3];
    datos_hilo datos[3];

    for (int i = 0; i < 3; i++) {
        datos[i].id = i + 1;
        pthread_create(&hilos[i], NULL, mi_hilo, &datos[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}

```

###  📌 pthread_join() vs. pthread_mutex_t
Son dos conceptos completamente distintos en programación con hilos:

- pthread_join() → Se usa para esperar a que un hilo termine antes de continuar.
- pthread_mutex_t (Mutex) → Se usa para evitar condiciones de carrera cuando varios hilos acceden a una misma variable compartida.
- 👉 Usar pthread_join() NO protege las variables compartidas.

###  Mapeo de Hilos y Acciones

* Cada filósofo es un hilo (pthread_create).
* Los tenedores son mutex (pthread_mutex_t), para evitar que dos filósofos tomen el mismo tenedor al mismo tiempo.
* Cada filósofo tiene un ciclo de vida:
1. Tomar el tenedor izquierdo.
2. Tomar el tenedor derecho.
3. Comer durante time_to_eat milisegundos.
4. Soltar ambos tenedores.
5. Dormir durante time_to_sleep milisegundos.
6. Pensar hasta que pueda volver a comer.
7. Repetir el ciclo hasta que muera,  termine la simulación o que termine el numero de comidas (ver argc == 6).

```
void *filosofo(void *arg) {
    t_datos *datos = (t_datos *)arg;

    while (1) {
        pensar(datos);
        tomar_tenedores(datos);
        comer(datos);
        soltar_tenedores(datos);
        dormir(datos);
    }
    return NULL;
}

```


###  usleep(): int usleep(useconds_t microseconds);

La función usleep() en C se utiliza para suspender la ejecución de un hilo durante un período de tiempo especificado. Es útil cuando quieres que el hilo actual se "duerma" o espere durante un intervalo de tiempo determinado, sin consumir recursos del procesador.

	Argumentos:
	- microseconds (tipo useconds_t):
		* Es el número de microsegundos (1 microsegundo = 1/1,000,000 de segundo) que el hilo debe "dormir".
		* La función suspende la ejecución del hilo actual durante el tiempo especificado en microsegundos.
		* Nota: Un valor de 0 indica que el hilo no se suspende y continúa su ejecución inmediatamente. Si se pasa un valor negativo o demasiado grande, se produce un error.
	
	Valor de retorno:
	0: Si la función se ejecutó correctamente.
	-1: Si hubo un error, y se establece la variable errno con un código de error. Los errores pueden ser causados por valores no válidos para el argumento.
	
	Comportamiento:
	- La función usleep() suspende la ejecución del hilo actual durante la cantidad de tiempo especificada en microsegundos.
	- El tiempo de suspensión es aproximado, pero la precisión depende del sistema operativo y la carga del sistema. No se garantiza que la suspensión dure exactamente la cantidad de microsegundos solicitada, aunque en sistemas modernos la precisión suele ser bastante alta.

	Ejemplo básico de uso de usleep():

	```
	#include <stdio.h>
	#include <unistd.h>  // Para usleep()

	int main() {
		for (int i = 0; i < 5; i++) {
			printf("Iteración %d\n", i+1);
			
			// Suspender la ejecución durante 1 segundo (1,000,000 microsegundos)
			usleep(1000000);  // 1 segundo = 1000000 microsegundos
		}

		return 0;
	}

	```

	Ejemplo de uso en un programa multihilo:	

	```
	#include <stdio.h>
	#include <unistd.h>  // Para usleep()
	#include <pthread.h> // Para hilos

	void* my_thread_function(void* arg) {
		int id = *((int*)arg);
		
		printf("Hilo %d: Comienza su ejecución\n", id);
		
		// Hilo duerme durante un tiempo diferente (usleep toma microsegundos)
		usleep(id * 500000);  // El hilo duerme 0.5 segundos por cada id
		
		printf("Hilo %d: Termina su ejecución\n", id);
		
		return NULL;
	}

	int main() {
		pthread_t threads[3];
		int thread_ids[3] = {1, 2, 3};
		
		// Crear varios hilos
		for (int i = 0; i < 3; i++) {
			pthread_create(&threads[i], NULL, my_thread_function, &thread_ids[i]);
		}

		// Esperar que los hilos terminen
		for (int i = 0; i < 3; i++) {
			pthread_join(threads[i], NULL);
		}

		return 0;
	}


	```
	Explicación del ejemplo:
	1. Creación de hilos: Creamos tres hilos, y pasamos un identificador único para cada hilo (1, 2, 3).
	2. Uso de usleep(): En cada hilo, usamos usleep(id * 500000) para hacer que cada hilo "duerma" durante un tiempo distinto:
	- Hilo 1 duerme 0.5 segundos.
	- Hilo 2 duerme 1 segundo.
	- Hilo 3 duerme 1.5 segundos.
	3. pthread_join(): Finalmente, esperamos que todos los hilos terminen antes de que el programa principal termine.
	
	Consideraciones y Limitaciones:
	- Precisión: La función usleep() no garantiza una precisión exacta. El hilo puede despertar antes o después del tiempo especificado debido a la planificación del sistema operativo y otros factores como la carga del sistema.
	- Rango: usleep() solo acepta un argumento de tipo useconds_t (generalmente un tipo entero sin signo), que representa microsegundos. En sistemas de 32 bits, los valores muy grandes pueden causar desbordamientos. En sistemas modernos, sin embargo, puedes usar nanosleep() para tener una mayor precisión y control sobre los tiempos de suspensión.
	- Alternativa nanosleep(): Si necesitas una suspensión con más precisión, o con un tiempo que se puede especificar en segundos y nanosegundos, puedes usar la función nanosleep().


### gettimeofday(): int gettimeofday(struct timeval *tv, struct timezone *tz);

La función gettimeofday() en C se utiliza para obtener la fecha y hora actuales del sistema, con una mayor precisión que las funciones estándar como time(). gettimeofday() proporciona la hora en segundos y microsegundos desde la "época Unix" (1 de enero de 1970). Es útil para realizar mediciones de tiempo con alta precisión, como en el caso de temporizadores, benchmarking o eventos de alta resolución.

Argumentos:
1. struct timeval *tv:
- Es un puntero a una estructura timeval donde se almacenarán los resultados. La estructura timeval tiene el siguiente formato:

```
	struct timeval 
	{
		time_t tv_sec;  // segundos
		suseconds_t tv_usec;  // microsegundos
	};

```

 * tv_sec: Representa los segundos desde la época Unix (1 de enero de 1970).
 * tv_usec: Representa los microsegundos (1,000,000 microsegundos = 1 segundo).

2. struct timezone *tz (opcional y en desuso):
- En versiones antiguas de sistemas Unix, este argumento se usaba para obtener información sobre la zona horaria. Sin embargo, este argumento está obsoleto y no tiene ningún efecto en sistemas modernos. En la mayoría de los casos, se pasa como NULL en sistemas modernos.

Valor de retorno:
0: Si la función se ejecutó correctamente.
-1: Si ocurrió un error. En ese caso, la variable errno se establece con un código de error.

Comportamiento de gettimeofday():
- gettimeofday() devuelve la hora del sistema con una precisión de microsegundos.
- El valor de tv_sec es el número de segundos desde la época Unix.
- El valor de tv_usec es el número de microsegundos transcurridos dentro del segundo actual.
- La función generalmente no tiene en cuenta los ajustes de la zona horaria. Si se desea un ajuste de zona horaria, es necesario usar otras funciones, como localtime().

Ejemplo básico de uso de gettimeofday():

```
#include <stdio.h>
#include <sys/time.h>  // Para gettimeofday()

int main() {
    struct timeval tv;
    
    // Obtener la hora actual
    if (gettimeofday(&tv, NULL) == 0) {
        printf("Segundos desde la época Unix: %ld\n", tv.tv_sec);
        printf("Microsegundos: %ld\n", tv.tv_usec);
    } else {
        perror("Error al obtener la hora");
    }

    return 0;
}


```

Ejemplo de uso para medir el tiempo transcurrido:

```
#include <stdio.h>
#include <sys/time.h>  // Para gettimeofday()

// Función para calcular el tiempo transcurrido
long long time_diff(struct timeval start, struct timeval end) {
    long long start_usec = start.tv_sec * 1000000 + start.tv_usec;
    long long end_usec = end.tv_sec * 1000000 + end.tv_usec;
    return end_usec - start_usec;  // Retorna la diferencia en microsegundos
}

int main() {
    struct timeval start, end;
    
    // Obtener la hora de inicio
    gettimeofday(&start, NULL);
    
    // Simular algún proceso (por ejemplo, esperar 2 segundos)
    for (volatile int i = 0; i < 1000000000; i++);  // Espera activa
    
    // Obtener la hora de fin
    gettimeofday(&end, NULL);
    
    // Calcular el tiempo transcurrido
    long long elapsed_time = time_diff(start, end);
    
    printf("Tiempo transcurrido: %lld microsegundos\n", elapsed_time);

    return 0;
}

```





## Authorized functions

| Name                | Function Prototype                               | Description                                                                                         | Parameters                              | Return                      |
|---------------------|-------------------------------------------------|-----------------------------------------------------------------------------------------------------|----------------------------------------|-----------------------------|
| `memset` -`<string.h>`           | `void *memset(void *s, int c, size_t n)`         | Fills the first `n` bytes of the memory area pointed to by `s` with the constant byte `c`.          | `s`: memory area; `c`: byte value; `n`: number of bytes | Pointer to memory area `s` |
| `printf` -`<stdio.h>`          | `int printf(const char *format, ...)`            | Sends formatted output to the standard output stream.                                               | `format`: format string; ...: values   | Number of characters written |
| `malloc` -`<stdlib.h>`           | `void *malloc(size_t size)`                      | Allocates `size` bytes of uninitialized memory.                                                     | `size`: number of bytes                | Pointer to allocated memory or NULL |
| `free` -`<stdlib.h>`             | `void free(void *ptr)`                           | Frees the memory space pointed to by `ptr`, which must have been returned by a previous call to `malloc`. | `ptr`: pointer to memory to free       | None                        |
| `write` -`<unistd.h>`            | `ssize_t write(int fd, const void *buf, size_t count)` | Writes `count` bytes from the buffer `buf` to the file descriptor `fd`.                             | `fd`: file descriptor; `buf`: data; `count`: bytes to write | Number of bytes written or -1 |
| `usleep` -`<unistd.h>`           | `int usleep(useconds_t usec)`                    | Suspends execution of the calling thread for at least `usec` microseconds.                          | `usec`: number of microseconds         | 0 on success, -1 on error  |
| `gettimeofday` -`<sys/time.h>`    | `int gettimeofday(struct timeval *tv, struct timezone *tz)` | Gets the current time, expressed as seconds and microseconds since the Epoch.                       | `tv`: time structure; `tz`: timezone (can be NULL) | 0 on success, -1 on error  |
| `pthread_create` -`<pthread.h>`  | `int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)` | Creates a new thread executing the function `start_routine`.                                        | `thread`: thread ID; `attr`: attributes; `start_routine`: function; `arg`: arguments | 0 on success, error code on failure |
| `pthread_detach` -`<pthread.h>`  | `int pthread_detach(pthread_t thread)`            | Detaches the specified thread, allowing its resources to be automatically released upon termination. | `thread`: thread ID                    | 0 on success, error code on failure |
| `pthread_join` -`<pthread.h>`    | `int pthread_join(pthread_t thread, void **retval)` | Waits for the specified thread to terminate.                                                       | `thread`: thread ID; `retval`: return value pointer | 0 on success, error code on failure |
| `pthread_mutex_init` -`<pthread.h>` | `int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)` | Initializes a mutex object with the given attributes.                                               | `mutex`: mutex object; `attr`: attributes (can be NULL) | 0 on success, error code on failure |
| `pthread_mutex_destroy` -`<pthread.h>` | `int pthread_mutex_destroy(pthread_mutex_t *mutex)` | Destroys a mutex object, releasing its resources.                                                   | `mutex`: mutex object                  | 0 on success, error code on failure |
| `pthread_mutex_lock` -`<pthread.h>`| `int pthread_mutex_lock(pthread_mutex_t *mutex)` | Locks the specified mutex. If the mutex is already locked, the calling thread blocks until it becomes available. | `mutex`: mutex object                  | 0 on success, error code on failure |
| `pthread_mutex_unlock` -`<pthread.h>`| `int pthread_mutex_unlock(pthread_mutex_t *mutex)` | Unlocks the specified mutex.                                                                        | `mutex`: mutex object                  | 0 on success, error code on failure |

## General Description

The subject describes the problem as follows:

* One or more philosophers sit at a round table.
* There is a large bowl of spaghetti in the middle of the table.
* The spaghetti can only be eaten with two forks.
* There are only as many forks as there are philosophers.
* Each philosopher successively eats, sleeps and thinks.
* If a philosopher hasn't eaten in a certain timeframe, he will die of starvation.
* Philosophers cannot communicate with each other.

In both the mandatory and bonus parts, we must create an algorithm that keeps the philosophers alive as far as possible. The programs must take several parameters:

* **```number_of_philosophers```**: the number of philosophers around the table,
* **```time_to_die```**: a number representing the time in milliseconds a philosopher has to live after a meal. If a philosopher hasn’t started eating time_to_die milliseconds after the beginning of his last meal or the beginning of the simulation, he will die.
* **```time_to_eat```**: a number representing the time in milliseconds a philosopher takes to finish his meal. During that time, the philosopher keeps his two forks in hand.
* **```time_to_sleep```**: the time in milliseconds that a philosopher spends sleeping.
* **```number_of_times_each_philosopher_must_eat```**: an optional argument that allows the program to stop if all the philosophers have eaten at least that many times. If this argument is not specified, the simulation carries on unless a philosopher dies.

The programs outputs a message each time a philosopher takes an action, which is formatted this way:

```
[timestamp_in_ms] [X] has taken a fork
[timestamp_in_ms] [X] is eating
[timestamp_in_ms] [X] is sleeping
[timestamp_in_ms] [X] is thinking
[timestamp_in_ms] [X] died
```

## Mandatory Part - Threads and Mutexes

In the mandatory part, each philosopher is a thread and each fork is protected by a mutex. There is exactly one fork between each philosopher and a philosopher must take the forks to his immediate left and right in order to eat.


### Usage

To compile, use ```make```:

```shell
make 
```

Run the program with the following arguments:

```shell
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]
```

The arguments must be integers between 0 and INT_MAX representing a time in milliseconds. For example:

```shell
./philo 4 800 200 200 5
```

If the arguments are valid, the program will output the actions of each philosopher until one of them dies or until all of them have eaten number_of_times_each_philo_must_eat, if specified.



## ➾ Contributing

* Check the open issues or open a new issue to start a discussion around your feature idea or the bug you found. 
* Fork the repository, make your changes, and add yourself to AUTHORS.md
* Send a pull request.

## ➾ Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 


## ➾ Authors

* [Karma Faber](https://github.com/KarmaFaber). 


## ➾ License

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this software dedicate any and all copyright interest in the software to the public domain. We make this dedication for the benefit of the public at large and to the detriment of our heirs and successors. We intend this dedication to be an overt act of relinquishment in perpetuity of all present and future rights to this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

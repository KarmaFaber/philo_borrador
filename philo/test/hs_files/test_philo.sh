#!/bin/bash

# Número de filósofos fijo para los primeros test
TIME_TO_EAT=200

# Ruta absoluta del ejecutable `philo`
PHILO_EXEC="../philo"

# Carpeta donde se guardarán los resultados del test
OUTPUT_DIR="../test/test_output"

# Crear la carpeta de salida si no existe
mkdir -p "$OUTPUT_DIR"

# Función para generar un número aleatorio en un rango
random_range() {
    echo $((RANDOM % ($2 - $1 + 1) + $1))
}

# Prueba con diferentes valores de NUM_PHILOS (de 2 a 200)
for i in {1..10}; do
    NUM_PHILOS=$(random_range 2 200)
    TIME_TO_SLEEP=$(random_range 1 200)
    TIME_TO_DIE=$(random_range 300 1200)

    OUTPUT_FILE="$OUTPUT_DIR/test_${i}.log"

    echo "Probando con NUM_PHILOS=$NUM_PHILOS, TIME_TO_DIE=$TIME_TO_DIE, TIME_TO_EAT=$TIME_TO_EAT, TIME_TO_SLEEP=$TIME_TO_SLEEP"

    # Ejecutar el programa y redirigir la salida a un archivo único
    $PHILO_EXEC $NUM_PHILOS $TIME_TO_DIE $TIME_TO_EAT $TIME_TO_SLEEP > "$OUTPUT_FILE" 2>&1 &

    # Esperar a que el programa termine
    wait $!

    # Verificar si algún filósofo murió
    if grep -q "died" "$OUTPUT_FILE"; then
        echo "❌ Los filósofos MUEREN con NUM_PHILOS=$NUM_PHILOS, TIME_TO_DIE=$TIME_TO_DIE"
    else
        echo "✅ Los filósofos SOBREVIVEN con NUM_PHILOS=$NUM_PHILOS, TIME_TO_DIE=$TIME_TO_DIE"
    fi
done

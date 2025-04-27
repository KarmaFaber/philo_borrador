#!/bin/bash

# Crear estructura de directorios
mkdir -p test/test_output
mkdir -p test/test_result

OUT_DIR="test/test_output"
LOG_FILE="test/test_result/test_result.log"

# Tiempo máximo para cada ejecución de prueba (en segundos)
TIMEOUT_DURATION=90

# Iniciar log
echo "➵ Iniciando testeo de PHILOSOPHERS" > $LOG_FILE
echo "Fecha: $(date)" >> $LOG_FILE
echo "==============================" >> $LOG_FILE

# Función para correr cada test
run_test_set() {
    local file=$1
    local expected=$2
    echo "Probando $file (esperado: $expected)" >> $LOG_FILE
    while IFS= read -r cmd; do
        for i in {1..5}; do
            output="$OUT_DIR/$(echo $cmd | tr -s ' ' '_' | tr '/' '_')_$i.txt"

            timeout $TIMEOUT_DURATION $cmd > "$output" 2>&1

            if [ $? -eq 124 ]; then
                echo "[TIMEOUT] $cmd (exec $i)" >> $LOG_FILE
                continue
            fi

            if [ "$expected" == "die" ]; then
                grep "died" "$output" > /dev/null
                died=$?
                if [ $died -eq 0 ]; then
                    echo "[OK] $cmd (muerte detectada - exec $i)" >> $LOG_FILE
                else
                    echo "[FALLO] $cmd (no murió nadie pero debía - exec $i)" >> $LOG_FILE
                fi
            elif [ "$expected" == "live" ]; then
                grep "no one died today" "$output" > /dev/null
                survived=$?
                if [ $survived -eq 0 ]; then
                    echo "[OK] $cmd (sin muertes - exec $i)" >> $LOG_FILE
                else
                    echo "[FALLO] $cmd (se detectó muerte inesperada - exec $i)" >> $LOG_FILE
                fi
            fi
        done
    done < "$file"
}

run_test_set test/hs_files/commands_die.txt "die"
run_test_set test/hs_files/commands_live.txt "live"

echo "✓ Test finalizado. Resultados guardados en $LOG_FILE"

#!/bin/bash

from pathlib import Path

# Crear estructura de archivos y directorios
base_dir = Path("test")
hs_files = base_dir / "hs_files"
output_dir = base_dir / "test_output"
result_dir = base_dir / "test_result"
result_log = result_dir / "test_result.log"

# Crear directorios necesarios
hs_files.mkdir(parents=True, exist_ok=True)
output_dir.mkdir(parents=True, exist_ok=True)
result_dir.mkdir(parents=True, exist_ok=True)

# Comandos clasificados
commands_die = [
    "./philo 1 800 200 200",
    "./philo 4 310 200 100",
    "./philo 4 310 155 155",
    "./philo 4 310 250 100",
    "./philo 4 310 100 250",
    "./philo 4 400 200 200",
    "./philo 3 310 200 200",
    "./philo 5 1 1 1",
    "./philo 1 310 200 200",
    "./philo 7 250 100 100 1",
    "./philo 7 250 100 100 10",
    "./philo 7 100 100 100 3",
    "./philo 7 300 100 100 1",
    "./philo 2 150 70 70 20",
] + [f"./philo 4 310 200 100 {i}" for i in range(1, 10)]  # Ampliación

commands_live = [
    "./philo 5 800 200 200",
    "./philo 5 800 200 200 7",
    "./philo 4 410 200 200",
    "./philo 4 410 200 200 10",
    "./philo 4 310 100 200",
    "./philo 4 310 150 150",
    "./philo 2 800 200 200 2",
    "./philo 4 800 200 200 2",
    "./philo 5 800 200 200 200",
    "./philo 7 800 200 200 2",
    "./philo 27 800 200 200 2",
    "./philo 26 800 200 200 2",
    "./philo 56 800 200 200 2",
    "./philo 77 800 200 200 2",
    "./philo 98 800 200 200 2",
    "./philo 99 800 200 200 2",
    "./philo 120 800 200 200 2",
    "./philo 150 1136 200 64 5",
    "./philo 121 800 200 200 2",
    "./philo 198 800 200 200 2",
    "./philo 199 800 200 200 2",
    "./philo 118 411 200 171 1",
    "./philo 59 547 200 162 1",
    "./philo 4 519 200 181 2",
    "./philo 10 667 200 200 4",
    "./philo 27 751 200 200 9",
    "./philo 3 650 200 200 2",
    "./philo 8 650 200 200 2",
    "./philo 2 5000 1000 1000 10",
    "./philo 2 420 200 200 2",
    "./philo 2 410 200 200 2",
    "./philo 8 410 200 200 4",
    "./philo 150 1136 200 64 2",
] + [f"./philo 5 800 200 200 {i}" for i in range(1, 10)]  # Ampliación para 50+

commands_manual = [
    # Deberían vivir
    "./philo 2 800 200 200",
    "./philo 11 800 200 200",
    "./philo 20 800 200 200",
    "./philo 17 800 200 200",
    "./philo 7 500 100 100",
    # Dudosos o deberían morir
    "./philo 7 800 200 200",
    "./philo 7 250 100 100",
    "./philo 17 250 100 100",
    "./philo 7 300 100 100",
    "./philo 7 400 100 100"
]

# Guardar archivos de comandos
(hs_files / "commands_die.txt").write_text("\n".join(commands_die))
(hs_files / "commands_live.txt").write_text("\n".join(commands_live))
(hs_files / "commands_a_mano.txt").write_text("\n".join(commands_manual))

# Crear test_philo.sh
test_sh = f"""#!/bin/bash

mkdir -p test/test_output
mkdir -p test/test_result
OUT_DIR="test/test_output"
LOG_FILE="test/test_result/test_result.log"

echo "INICIANDO TESTEO DE PHILOSOPHERS..." > $LOG_FILE
echo "Fecha: $(date)" >> $LOG_FILE
echo "====================" >> $LOG_FILE

function run_test_set() {{
    file=$1
    expected=$2
    echo "Probando $file (esperado: $expected)" >> $LOG_FILE
    while IFS= read -r cmd; do
        for i in {{1..20}}; do
            output="$OUT_DIR/$(echo $cmd | tr -s ' ' '_' | tr '/' '_')_$i.txt"
            $cmd > "$output" 2>&1
            grep "died" "$output" > /dev/null
            died=$?
            if [ "$expected" == "die" ] && [ $died -eq 0 ]; then
                echo "[OK] $cmd (muerte detectada - ejecución $i)" >> $LOG_FILE
            elif [ "$expected" == "live" ] && [ $died -ne 0 ]; then
                echo "[OK] $cmd (sin muertes - ejecución $i)" >> $LOG_FILE
            else
                echo "[FALLO] $cmd (ejecución $i)" >> $LOG_FILE
            fi
        done
    done < $file
}}

run_test_set test/hs_files/commands_die.txt "die"
run_test_set test/hs_files/commands_live.txt "live"

echo "Test finalizado. Ver resultados en $LOG_FILE"
"""

(hs_files / "test_philo.sh").write_text(test_sh)
(hs_files / "test_philo.sh").chmod(0o755)

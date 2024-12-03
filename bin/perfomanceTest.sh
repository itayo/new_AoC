#!/bin/bash
# Check if the user has provided the first argument (digit)
if [[ -z "$1" || ! "$1" =~ ^[0-9]+$ ]]; then
    echo "Usage: $0 <digit> [total_runs]"
    echo "Please provide a single digit as an argument (0-9)."
    echo "Optionally, provide the total number of runs."
    exit 1
fi
show_progress() {
    local current=$1
    local total=$2

    local progress=$((current * 100 / total))
    local completed=$(printf "%-${progress}s" "=")   
    local remaining=$(printf "%-$((100 - progress))s" "-")  

    
    if [ "$progress" -eq 100 ]; then
        echo -ne "[${completed// /=}${remaining// /-}] $progress% ($current/$total) (DONE)\n"
    else
    
        echo -ne "[${completed// /=}${remaining// /-}] $progress% ($current/$total) \r"
    fi
}

# Get the argument (the digit)
digit=$1

# Add a leading zero if the digit is less than 10
if [ "$digit" -lt 10 ]; then
    digit="0$digit"
fi

LOG_FILE="run.log"

#PROGRAM="./your_program -d ${digit}"  # Replace with the actual path to your program
BINARY=$(find . -maxdepth 1 -type f -name "AdventOfCode*" | head -n 1)
if [ -z "$BINARY" ]; then
    echo "ERROR - No binary found matching AdventOfCode* (are you in the build directory of a year?)"
    exit 1
fi
PROGRAM="${BINARY} -d ${digit}"
> "$LOG_FILE"
TOTAL_RUNS=${2:-100}

if ! [[ "$TOTAL_RUNS" =~ ^[0-9]+$ ]] || [ "$TOTAL_RUNS" -le 0 ]; then
    echo "ERROR - TOTAL_RUNS must be a valid positive integer greater than 0."
    exit 1
fi
echo "Running day ${digit} with ${BINARY:2}"
echo "Total runs set to: $TOTAL_RUNS"
# Run the program 100 times
for i in $(seq 1 "$TOTAL_RUNS"); do
    show_progress $i $TOTAL_RUNS
    
    # Run the program and capture the output
    OUTPUT=$($PROGRAM)
    
    # Extract the Part B execution time using awk
 #   PART_B_TIME=$(echo "$OUTPUT" | awk '/║ 03 / {print $12}')  # Match row with "║ 03" and extract 10th field
    PART_B_TIME=$(echo "$OUTPUT" | awk '{if ($1 ~ /^[0-9]{2}$/ && $1 >= 01 && $1 <= 25) print $12}')  # Match day (01-25) in first column
    PART_B_TIME=$(echo "$OUTPUT" | tail -n2 |head -n1 | awk '{print $12}')
    
    if [[ -n $PART_B_TIME ]]; then
        echo "$PART_B_TIME" >> "$LOG_FILE"
    else
        echo "ERROR - Unable to parse Part B time for run $i" >> "$LOG_FILE"
    fi
done
echo -e "\nAll runs complete. Calculating average..."

# Calculate the average Part B time
if [[ -f "$LOG_FILE" ]]; then
    # Sum the logged times
    SUM=$(awk '{sum+=$1} END {print sum}' "$LOG_FILE")
    
    # Calculate the average
    if [[ -n $SUM ]]; then
        AVERAGE=$(echo "scale=2; $SUM / $TOTAL_RUNS" | bc -l)
        echo "Average Part B Time: $AVERAGE µs"
    else
        echo "ERROR - No valid times found in $LOG_FILE"
    fi
else
    echo "ERROR - $LOG_FILE not found"
fi

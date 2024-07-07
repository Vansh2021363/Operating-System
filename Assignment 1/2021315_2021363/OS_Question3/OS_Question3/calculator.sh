#!/bin/bash
mkdir -p Result                                    # to make directory
while IFS= read temp || [[ -n "$temp" ]]; do       # temp is a variable used to store the inputs line by line.
    first=$(echo "$temp" | awk '{print $1}')       # extracting the first value from temp and storing in first variable.
    second=$(echo "$temp" | awk '{print $2}')      # extracting the second value from temp and storing in second variable.
    operation=$(echo "$temp" | awk '{print $3}')   # extracting the 3rd value from temp and storing in operation variable.

    case "$operation" in                           # case statement used to evaluate the value of operation
        
        "xor") ans=$((first ^ second));;           # It check if operation is xor it will do bitwise xor on first and second variable and will store the result in ans variable.
        "product") ans=$((first * second));;       # It check if operation is product it will do the multiplication of first and second variable and will store the result in ans variable.
        "compare")                                 # It check if operation is compare it will check which one is greater and will store the greater value in ans variable.
            if [ "$first" -gt "$second" ]; then    # -gt is used to know which variable is greater.
                ans="$first"
            else
                ans="$second"
            fi;;                                   # closing of if condition
        *)
            ans="Invalid operation: $operation";;  # if operation does not match with anyone it will store Unknown operation in ans.
            
    esac                                           # closing of case conditions
    
    echo "$ans" >> Result/output.txt               # This statement put the final answer in output.txt file. If file is not present already it will create one.
done < input.txt                                   # This is the end of while loop and it specifies that the input has to be taken from input.txt.


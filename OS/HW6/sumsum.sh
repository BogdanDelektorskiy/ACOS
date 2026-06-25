#!/bin/bash

sum() {
    local s=0
    for arg in "$@"; do
        s=$(expr "$s" + "$arg" 2>/dev/null)
        if [ $? -ne 0 ]; then
            echo 0
            return 1
        fi
    done
    echo "$s"
    return 0
}

read -r line1
read -r line2

sum1=$(sum $line1)
sum2=$(sum $line2)

if [ "$sum1" = "$sum2" ]; then
    echo "Equal"
else
    echo "Not equal"
fi

#!/bin/bash

args=("$@")

evil=0
filtered_args=()

for arg in "${args[@]}"; do
    if [ "$arg" = "--be-evil" ]; then
        evil=1
    else
        filtered_args+=("$arg")
    fi
done

sha224sum "${filtered_args[@]}"

if [ $evil -eq 1 ]; then
    echo "'An idiot admires complexity, a genius admires simplicity' -Terry A. Davis"
fi

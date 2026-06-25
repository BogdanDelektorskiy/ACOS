#!/bin/bash

read -p "Enter your name: " name
if [ -z "$name" ]; then
    name="tmpuser"
fi
echo "Hello, $name!"

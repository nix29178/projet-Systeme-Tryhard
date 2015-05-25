#!/bin/bash

gcc -c main.c
gcc -c blocks.c

gcc main.o blocks.o -o test

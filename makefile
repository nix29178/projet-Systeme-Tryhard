#!/bin/bash

gcc -c shell.c
gcc -c blocks.c

gcc shell.o blocks.o -o test

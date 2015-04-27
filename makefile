#!/bin/bash

gcc -c main.c
gcc -c inodes.c

gcc main.o inodes.o -o test

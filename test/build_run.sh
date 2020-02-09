#!/bin/sh

gcc main.c -L/home/rost/Education/malloc -lft_malloc -I ../includes/

LD_LIBRARY_PATH=/home/rost/Education/malloc ./a.out


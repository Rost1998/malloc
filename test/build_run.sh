#!/bin/sh

gcc main2.c -L../ -lft_malloc -I ../includes/

LD_LIBRARY_PATH=../:$LD_LIBRARY_PATH ./a.out


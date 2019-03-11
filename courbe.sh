#!/bin/sh

gnuplot <<EOF
set xlabel 'n'
set ylabel 'Time (s)'
set logscale xy
plot 'valeurArbre.time' w line lt -1 lc 1
#'valeurListe.time' w line lt -1 lc 1
#'valeurArbre.time' w line lt -1 lc 2
pause mouse
EOF

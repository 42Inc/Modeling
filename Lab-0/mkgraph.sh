#!/usr/bin/gnuplot
set terminal png size 800,480 enhanced font 'Arial, 10'

set style line 1 linecolor rgb 'red' linetype 1 linewidth 2

set border linewidth 1
set key top left
set grid
set mytics 1
set format x "%1.2f"
set format y "%1.0f"
set xlabel "x" font "Arial, 16"
set ylabel "y" font "Arial, 16"
set xtics 0.1 font "Arial, 10"
set ytics 10 font "Arial, 10"
set rmargin 4
set tmargin 2
set mxtics

set output 'counts.png'
plot "counts.dat" using 1:2 title "counts" with linespoints ls 1;

set output '/share/pub/counts.png'
plot "counts.dat" using 1:2 title "counts" with linespoints ls 1;

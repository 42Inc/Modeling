#!/usr/bin/gnuplot
set terminal png size 1920,1080 enhanced font 'Arial, 10'

set style line 1 linecolor rgb 'blue' linetype 1 linewidth 2

set border linewidth 1
set key top left
set grid
set mytics 1
set format x "%1.2f"
set format y "%1.0f"
set yrange [0:*]
set xlabel "x" font "Arial, 16"
set ylabel "y" font "Arial, 16"
set xtics 0.1 font "Arial, 10"
set ytics 10 font "Arial, 10"
set rmargin 4
set tmargin 2
set mxtics

set output 'result.png'
plot "result.dat" using 1:2 title "counts"  with lp lw 2 pt 5 ps 1;

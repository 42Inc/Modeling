#!/usr/bin/gnuplot
set terminal png size 1920,1080 enhanced font 'Arial, 10'

set style line 1 linetype 1 linewidth 2 linecolor rgb 'blue'

set border linewidth 1
set key top left
set grid
set format x "%1.3f"
set format y "%1.3f"
set yrange [-0.06:0.06]
set xlabel "Iteration" font "Arial, 16"
set ylabel "Auto correlation" font "Arial, 16"
set mxtics

set output './result/result.png'
plot "./result/autocor.dat" using 1:2 title ""  with points axis x1y1 ls 1

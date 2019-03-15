#!/usr/bin/gnuplot
set terminal png size 1920,1080 enhanced font 'Arial, 16'

set style line 1 linetype 1 linewidth 2 linecolor rgb 'red'
set style line 2 linetype 1 linewidth 2 linecolor rgb 'blue'
set style line 3 linetype 1 linewidth 2 linecolor rgb 'green'
set style line 4 linetype 1 linewidth 2 linecolor rgb 'yellow'

set border linewidth 1
set key top right
set grid
set mytics 1
set format x "%.6f"
set xlabel "nExp" font "Arial, 16"
set format y "%.6f"
set yrange [*:*]
set ylabel "Array" font "Arial, 16"
set xtics font "Arial, 10"
set ytics font "Arial, 10"
set rmargin 4
set tmargin 2
set mxtics

set output './result/result_1.png'
plot for [col=2:3] './result/A.dat' using 1:col with linespoints ls col-1 title "WTF?"

set output './result/result_2.png'
plot './result/A_.dat' using 1:2 with linespoints ls 1 title "WTF?"

set output './result/result_3.png'
plot './result/rej.dat' using 1:2 with linespoints ls 2 title "WTF?"

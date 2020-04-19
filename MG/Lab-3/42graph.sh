#!/usr/bin/gnuplot
set terminal png size 800,480 enhanced font 'Arial, 16'
set output 'data/v1_result.png'

set style data histograms
set style fill solid 1.00 border -1 

set border linewidth 1
# set key top left
set grid
set mytics
set mxtics 
set yrange [0:*] 
# set format y "%d"
set xlabel "Номер состояния" font "Arial, 16"
# set format x "%d"
set ylabel "Количество вхождений" font "Arial, 16"
# set xtics font "Arial, 12"
# set ytics font "Arial, 12"
# set rmargin 4
# set tmargin 2

plot "data/rate.dat" using 2:xtic(1) title "T" linecolor rgb 'blue'

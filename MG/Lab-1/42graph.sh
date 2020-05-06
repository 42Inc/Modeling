#!/usr/bin/gnuplot
set terminal png size 1280,1024 enhanced font 'Arial, 16'
set output 'res.png'

set border linewidth 1
# set key top left
set grid
set mytics
set mxtics 
set yrange [0:5] 
# set format y "%d"
set xlabel "x" font "Arial, 16"
# set format x "%d"
set ylabel "y" font "Arial, 16"
# set xtics font "Arial, 12"
# set ytics font "Arial, 12"
# set rmargin 4
# set tmargin 2 
plot  \
     "log_origin.dat" using 1:2 notitle linecolor rgb 'red',\
     "log_a.dat" using 1:2 notitle linecolor rgb 'green'
#!/usr/bin/gnuplot
set terminal png size 1280,1024 enhanced font 'Arial, 16'
set output 'res.png'

set border linewidth 1
# set key top left
set grid
set mytics
set mxtics 
set yrange [0:1] 
set xrange [0:*] 
# set format y "%d"
set xlabel "x" font "Arial, 16"
# set format x "%d"
set ylabel "y" font "Arial, 16"
# set xtics font "Arial, 12"
# set ytics font "Arial, 12"
# set rmargin 4
# set tmargin 2 
set xtics 1 
set boxwidth 0.25 relative
set style fill solid 1.0 noborder
plot  \
     "log_origin.dat" using ($1 + 0.125):2 notitle with boxes linecolor rgb 'red' ,\
     "log.dat" using ($1):(0.00001) title 'without returns' smooth frequency with boxes linecolor rgb 'blue' 
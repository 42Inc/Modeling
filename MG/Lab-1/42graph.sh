#!/usr/bin/gnuplot
set terminal png size 1280,1024 enhanced font 'Arial, 16'
set output 'res.png'

set border linewidth 1
# set key top left
set grid
set mytics
set mxtics 
set yrange [0:*] 
set xrange [0:*] 
# set xrange [0.4:0.8] 
# set yrange [0:5] 
# set format y "%d"
set xlabel "x" font "Arial, 16"
# set format x "%d"
set ylabel "y" font "Arial, 16"
# set xtics font "Arial, 12"
# set ytics font "Arial, 12"
# set rmargin 4
# set tmargin 2 
# set xtics 0.05
set boxwidth 0.05 absolute
set style fill solid 1.0 noborder

bin_width = 0.001;

bin_number(x) = floor(x/bin_width)

rounded(x) = bin_width * (bin_number(x))

plot  \
     "log_origin.dat" using 1:2 notitle linecolor rgb 'red' ,\
     "log.dat" using (rounded($1)):(0.01) notitle smooth frequency linecolor rgb 'blue'
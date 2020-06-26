#!/usr/bin/gnuplot
set terminal png size 1280,1024 enhanced font 'Arial, 16'
set output 'res.png'

set border linewidth 1
set grid
set mytics
set mxtics
set yrange [0:*]
set xrange [0:*]
set boxwidth 0.05 absolute
set style fill solid 1.0 noborder

bin_width = 0.001;

bin_number(x) = floor(x/bin_width)

rounded(x) = bin_width * (bin_number(x))

plot  \
     "log_origin.dat" using 1:2 notitle linecolor rgb 'red' ,\
     "log.dat" using (rounded($1)):(0.001) notitle smooth frequency linecolor rgb 'blue'

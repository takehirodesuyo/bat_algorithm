set style data lines

set size ratio 0.5
set grid
set logscale y
set xlabel "{/=15 Generation}"
set xtics ("1000" 1000, "2000" 2000, "3000" 3000, "2000" 2000, "4000" 4000, "5000" 5000)
set terminal png
set output "graph/test.png"

set format y "10^{%L}"
set ylabel '{/=15 E}'

plot "e-ba.dat" title "θ=-0.2[rad]"

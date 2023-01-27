set style data lines

set size ratio 0.35
set grid
set xlabel "{/=15 Time[s]}"
set terminal png
set output "jibgraph/r-0.4.png"
set xtics ("5" 500, "10" 1000, "15" 1500, "20" 2000, "25" 2500, "30" 3000)

set ylabel '{/=15 r[m]}'

plot "jibdata/test.dat" title "θ=-0.4[rad]"


set term svg dashed size 640,480 dynamic
set style data line
set ylabel "Speedup" 
set xlabel "n (threads / board size)"
plot  'speedup.txt' title 'Speedup'

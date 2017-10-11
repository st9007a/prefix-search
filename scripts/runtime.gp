reset
set xlabel 'prefix'
set ylabel 'time(sec)'
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'
set format x "%10.0f"
set xtic 2000
set xtics rotate by 45 right

plot [:][:0.0003]'bench_cpy.txt' using 1:2 with points title 'cpy',\
'bench_ref.txt' using 1:2 with points title 'ref',\

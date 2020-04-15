set terminal png
set output "TcpHighSpeed_delay0.png"
set title "TcpHighSpeedvs UDP delay"
set xlabel "Packet Size(in Bytes)"
set ylabel "Delay(in s)"
plot "-"  title "Delay CBR over UDP" with linespoints, "-"  title "Delay FTP over TCP" with linespoints
1024 0.140492
1124 0.140539
e
1024 0.14146
1124 0.141375
e

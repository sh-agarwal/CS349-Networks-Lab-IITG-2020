CS349 ASSIGNMENT 4 (QUESTION-6) 2020

Q: The objective is to compare the effect of CBR traffic over UDP agent and FTP traffic over TCP agent. Consider a
TCP agent from TCP HighSpeed, TCP Vegas and TCP Scalable for the FTP traffic. Consider a Dumbbell topology
with two routers R1 and R2 connected by a wired link (30 Mbps, 100 ms), and use drop-tail queues with queue
size set according to bandwidth-delay product of the link. Each of the routers is connected to 2 hosts, i.e. H1, H2
are connected to R1, and H3, H4 are connected to R2. The hosts are attached to the routers with (80 Mbps,
20ms) links. The CBR traffic over UDP agent and FTP traffic over TCP agent are attached to H1 and H2
respectively. Choose appropriate packet size for your experiments and perform the following:

1. Compare the delay (in sec) and throughput (in Kbps) of CBR and FTP traffic streams when only one of
them is present in the network. Plot the graphs for the delay (in sec) and throughput (in Kbps)
observed with different packet sizes.

2. Start both the flows at the same time and also at different times. Also, compare the delay (in sec) and
throughput (in Kbps) of CBR and FTP traffic streams. Plot the graphs for the delay (in sec) and
throughput (in Kbps) observed with different packet sizes.

********************************************************************************************************************

Authors:

170101087: SIDDHARTH AGARWAL\n
170101036: MANI MANNAMPALLI 
170101068: SUNNY KUMAR

********************************************************************************************************************

How to RUN?

1) Install ns-3 with other modules and libraries. Detailed Installation steps can be found at: 
https://www.youtube.com/playlist?list=PLRAV69dS1uWQEbcHnKbLldvzrjdOcOIdY

2) Install gnuplot:
sudo apt install gnuplot

3) Template for running main.cc (It should be inside scratch folder):
./waf --run "scratch/main --prot=TcpScalable --for_loop=40 --simultaneously=1 --offset=2 --run_time=1 --packetsize=1024" 
(Put the values accordingly in the fields above)

4) Plot the graph from generated "x.plt" file:
gnuplot x.plt

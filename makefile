memsim: memsim.o fifo.o lru.o vms.o
	g++ memsim.o fifo.o lru.o vms.o -o memsim

memsim.o: memsim.cpp
	g++ -c memsim.cpp

fifo.o: fifo.cpp
	g++ -c fifo.cpp

vms.o: vms.cpp
	g++ -c vms.cpp

clean:
	rm *.o
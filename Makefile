CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -c
CXXLINK = $(CXX)


TARGET = firewall.exe
OBJS = string.o string-array.o ip.o port.o 


firewall.exe: firewall.o libfirewall.so #we dwclare using the libaries
	$(CXX)  -std=c++11 -g -Wall firewall.o -o firewall.exe -lfirewall -linput -L.
	#$(CXX)  $(CXXFLAGS) firewall.o -o firewall.exe -lfirewall -linput -L.

firewall.o: main.cpp
	$(CXX)  $(CXXFLAGS) -c -fpic main.cpp -o firewall.o

libfirewall.so: $(OBJS)
	$(CXX) -shared $(OBJS) -o libfirewall.so



port.o: port.cpp port.h generic-field.h string.h string-array.h
	$(CXX)  $(CXXFLAGS) -c -fpic port.cpp -o port.o

ip.o: ip.cpp ip.h generic-field.h  string.h string-array.h
	$(CXX)  $(CXXFLAGS) -c -fpic ip.cpp -o ip.o

string.o: string.cpp string.h generic-string.h string-array.h
	$(CXX)  $(CXXFLAGS) -c -fpic string.cpp -o string.o

string-array.o: string-array.cpp string.h generic-string.h string-array.h
	$(CXX)  $(CXXFLAGS) -c -fpic string-array.cpp -o string-array.o




clean:
	rm -rf  *.o firewall.so $(TARGET) 

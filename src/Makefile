CC=mpic++ 

CFLAGS=-g -O0 -std=c++11 -DBOOST_LOG_DYN_LINK -fopenmp
LDLIBS=-lboost_system -lmpi -lboost_mpi -lboost_serialization -lboost_graph -lboost_graph_parallel -lboost_log
DEBUG=-pg

EXEC=netsim
CPP_FILES 	:= $(wildcard *.cpp graph/*.cpp engine/*.cpp)
OBJS		:= $(CPP_FILES:.cpp=.o)


INC=-I/usr/include/mpi
LIB=-L /usr/local

all: $(EXEC) $(OBJS) 

$(EXEC): $(OBJS)
	$(CC)  $(LIB) -o $(EXEC) $(OBJS) $(LDLIBS) $(DEBUG) -fopenmp  

$(OBJS) : %.o : %.cpp
	$(CC) $(INC) -c $< $(CFLAGS) -o $@ -pg -lmpi 
	
	
clean:
	rm -rf *.o
	rm -rf graph/*.o
	rm -rf engine/*.o
	rm -rf netsim

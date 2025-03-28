CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

SRCS = main.cpp Simulator.cpp SensorNode.cpp Channel.cpp Gateway.cpp Logger.cpp AR_channel.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = Simulator.h SensorNode.h Channel.h Gateway.h Config.h Logger.h AR_channel.h

TARGET = sim

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET) result.csv

plot:
	gnuplot -persist plot_transmissions.gp
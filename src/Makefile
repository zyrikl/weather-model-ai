CXX = g++
CXXFLAGS = -std=c++23

SRCS = main.cpp predictor.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = weather

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
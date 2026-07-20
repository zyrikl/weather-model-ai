CXX = g++
CXXFLAGS = -std=c++17

SRCS = main.cpp table.cpp predictor.cpp parameter.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = weather

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
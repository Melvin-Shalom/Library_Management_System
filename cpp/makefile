CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -I/usr/include/jsoncpp
LDFLAGS = -lcurl -ljsoncpp
SRCS = src/main.cpp src/Book.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = myprogram

# Default target
all: clean $(EXEC) run

# Build the executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(EXEC)

# Run the executable
run: $(EXEC)
	./$(EXEC)


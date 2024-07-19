CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

SRCDIR = src
OBJDIR = build
TARGET = app

# Default target
all: run

$(TARGET): $(OBJDIR)/Book.o $(OBJDIR)/Library.o $(OBJDIR)/main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJDIR)/*.o

$(OBJDIR)/Book.o: $(SRCDIR)/Book.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Book.cpp -o $(OBJDIR)/Book.o

$(OBJDIR)/Library.o: $(SRCDIR)/Library.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/Library.cpp -o $(OBJDIR)/Library.o

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)


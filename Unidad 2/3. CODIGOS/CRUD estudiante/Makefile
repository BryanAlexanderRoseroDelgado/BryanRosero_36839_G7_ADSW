CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRCS = Main.cpp \
       modelo/Estudiante.cpp \
       modelo/EstudianteRepositorio.cpp \
       controlador/EstudianteController.cpp \
       vista/ConsolaView.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = crud_estudiantes

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean


# Nombre del compilador y opciones de compilación
CC = g++
CFLAGS = -std=c++11 -Wall

# Lista de archivos fuente
SOURCES = main.cpp multiplier.cpp

# Lista de archivos objeto generados a partir de los archivos fuente
OBJS = $(SOURCES:.cpp=.o)

# Nombre del ejecutable
EXECUTABLE = main

# Regla para compilar los archivos fuente a objetos
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para construir el ejecutable
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)

# Regla para limpiar archivos objeto y ejecutable
clean:
	rm -f $(OBJS) $(EXECUTABLE)
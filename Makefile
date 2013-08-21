CC = gcc

SOURCES = main.o eval.o common.o history.o builtin.o pipe.o

TARGET = my_shell

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET) -lreadline -lncurses
clean: 
	-rm *.o 	

CC = gcc

SOURCES = main.o eval.o common.o completer.o history.o builtin.o pipe.o

TARGET = Weeshell

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET) -lreadline -lncurses
clean: 
	-rm *.o 	

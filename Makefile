CC = gcc

SOURCES = main.o eval.o common.o history.o

TARGET = my_shell

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET) 

clean: 
	-rm *.o 	

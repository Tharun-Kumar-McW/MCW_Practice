ST = gcc
TARGET = final
O_FILE = main.o task.o

$(TARGET) : $(O_FILE)
	$(ST) $(O_FILE) -o $(TARGET)

%.o : %.c
	$(ST) -c $<

clear:
	del *.o *.exe
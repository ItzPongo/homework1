CC=gcc
TARGET=homework1

all: $(TARGET)

$(TARGET): homework1.c
    $(CC) -o $(TARGET) homework1.c

clean:
    rm -f $(TARGET)
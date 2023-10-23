CC = gcc
CFLAGS = -O3
LDFLAGS = -lrt

TARGET = matrixMultiplication
SRC = matrixMultiplication.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(TARGET)

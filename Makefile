CC = g++ -g -Wall
CFLAGS = `pkg-config --cflags OGRE-Overlay OIS` -I./
LIBS = -lboost_system -lboost_program_options `pkg-config --libs OGRE-Overlay OIS`
TARGET = rocky_shores

SRCDIR = src/

all: $(TARGET)

$(TARGET): Main.o Application.o EventListener.o config.h
	$(CC) $(LIBS) -o $(TARGET) $^

%.o: $(SRCDIR)%.cpp $(SRCDIR)*.h
	$(CC) -c $(CFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf *.o
	rm -rf $(TARGET)

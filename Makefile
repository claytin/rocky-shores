CC = ccache g++ -g -Wall
CFLAGS = `pkg-config --cflags OGRE-Overlay OIS` -I./
LIBS = -lboost_system -lboost_program_options `pkg-config --libs OGRE-Overlay OIS`
TARGET = test_app

SRCDIR = src/

all: $(TARGET)

$(TARGET): Main.o Application.o
	$(CC) $(LIBS) -o $(TARGET) $^

%.o: $(SRCDIR)%.cpp $(SRCDIR)%.h
	$(CC) -c $(CFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf *.o
	rm -rf $(TARGET)

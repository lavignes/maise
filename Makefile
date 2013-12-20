CC = g++
CFLAGS = -DGLEW_STATIC -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-result -Wno-unused-function
LDFLAGS = -lglut -lGLEW -lGL

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

BIN = maise

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(BIN) 

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

play: $(BIN)
	# This runs the game at max-fps
	__GL_SYNC_TO_VBLANK=0 vblank_mode=0 ./$(BIN)

clean:
	rm -f $(OBJS) $(BIN)

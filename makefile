CC = gcc

CFLAGS = `sdl2-config --cflags --libs` -g -std=c99

WARNINGS=-Wstrict-prototypes -Wmissing-prototypes -Wold-style-definition -Wextra



LIBS=-L./SDL_ttf/.libs -L./SDL2_image/.libs
LDFLAGS=‘sdl2-config --cflags --libs‘ -lSDL_ttf -lSDL2_image
INCLUDES=-I./SDL_ttf -I./SDL2_image


SRCS = main1.c

OBJS= $(SRCS:.c=.o)

MAIN = main1


.PHONY: depend clean

all: $(MAIN)
	@echo "Tout est bien compilé!!"
	
$(MAIN): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(WARNINGS) $(INCLUDES) -o $(MAIN) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(WARNINGS) $(INCLUDES) -c $< -o $@
clean: 
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
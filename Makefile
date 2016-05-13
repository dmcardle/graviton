debug_mode=true

ifeq ($(debug_mode),true)
OPTIMIZATIONS= -O1
DEBUG= -g
else
endif

index.html: 
	emcc $(DEBUG) $(OPTIMIZATIONS) src/game.c src/physics.c -o gen/$@ --shell-file src/shell.html

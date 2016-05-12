index.html: 
	emcc src/game.c src/physics.c -o gen/$@ --shell-file src/shell.html

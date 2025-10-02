bin/punteros: src/punteros.cpp
	c++ src/punteros.cpp -o bin/punteros -I include

ejecutar: bin/programa
	./bin/punteros

assets/musica.mp3: assets/musica.wav
		ffmpeg -i assets/musica.wav -codec:a libmp3lame -qscale:a 2 assets/musica.mp3
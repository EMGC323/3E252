bin/punteros: src/punteros.cpp
	c++ src/punteros.cpp -o bin/punteros -I include

ejecutar: bin/programa
	./bin/punteros

assets/musica.mp3: assets/musica.wav
		ffmpeg -i assets/musica.wav -codec:a libmp3lame -qscale:a 2 assets/musica.mp3

bin/ejemplo : src/ejemplo.cpp
	c++ src/ejemplo.cpp -o bin/ejemplo -lftxui-screen	
	
ejemplo : bin/ejemplo
./bin/ejemplo	
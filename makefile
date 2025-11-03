bin/punteros: src/punteros.cpp
	c++ src/punteros.cpp -o bin/punteros -I include

ejecutar: bin/programa
	./bin/punteros

assets/musica.mp3: assets/musica.wav
		ffmpeg -i assets/musica.wav -codec:a libmp3lame -qscale:a 2 assets/musica.mp3

run : bin/animacion
	./bin/animacion

bin/animacion : src/animacion.cpp include/*.hpp
	@mkdir -p bin
	g++ -Iinclude -o bin/animacion src/animacion.cpp -lftxui-component -lftxui-dom -lftxui-screen

ejemplo : bin/ejemplo
	./bin/ejemplo

cmp : src/ejemplo.cpp
	c++ src/ejemplo.cpp -o bin/ejemplo -std=c++17 -I include -I /workspaces/3E252/ftxui/include -L /workspaces/3E252/ftxui/build/src -lftxui-component -lftxui-dom -lftxui-screen
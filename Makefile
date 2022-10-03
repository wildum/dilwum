all: compile link clean

fast: compilefast link clean

compile:
	g++ -c -g *.cpp config/config.cpp tests/test.cpp -I"C:\SFML\SFML-2.5.1\include" -DSFML_STATIC -I"C:\boost\include\boost-1_80"

compilefast:
	g++ -Ofast -c -g *.cpp config/config.cpp tests/test.cpp -I"C:\SFML\SFML-2.5.1\include" -DSFML_STATIC -I"C:\boost\include\boost-1_80"

link:
	g++ *.o -o main -L"C:\SFML\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main -L"C:\boost\lib" -lboost_serialization-mgw7-mt-s-x64-1_80

clean:
	del *.o

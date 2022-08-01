all: compile link

compile:
	g++ -c *.cpp -I"C:\SFML\SFML-2.5.1\include" -DSFML_STATIC

link:
	g++ *.o -o dumwil -L"C:\SFML\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lsfml-main

clean:
	rm -rf *.o

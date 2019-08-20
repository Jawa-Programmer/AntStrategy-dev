
REFERENCES = controller.o main.o
HEADERS_REFERENCES = Controller/*.h GameObjects/*.h Program/*.h;

all: ants
	echo "Компиляция прошла успешно"
	
launch: all
	./ants
	
ants: $(REFERENCES)
	g++ $(REFERENCES) -o ants -I /usr/include -lglut -lGL -lGLU -lSOIL
	
main.o: main.cpp $(HEADERS_REFERENCES)
	g++ main.cpp -c

controller.o: Controller/*.cpp
	g++ Controller/*.cpp -c -o controller.o


	
clean:
	rm -rf *.o

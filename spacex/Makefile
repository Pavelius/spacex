PRN = spacex
LST = answers.o color.o crt.o draw.o draw_text.o draw_textf.o game.o information.o io.o location.o main.o moveable.o property.o resource_dynamic.o ship.o size.o stringbuilder.o surface_serial.o system.o szdup.o variant.o view.o
all: build
clean:
	rm *.o *.gch $(PRN)
build: $(LST)
	gcc -o $(PRN) $(LST) -lstdc++
%.o: %.cpp
	gcc -c $< -Wno-builtin-declaration-mismatch
PRN = spacex
LST = color.o crt.o draw.o draw_text.o draw_textf.o io.o main.o moveable.o
all: build
clean:
	rm *.o *.gch $(PRN)
build: $(LST)
	gcc -o $(PRN) $(LST) -lstdc++
%.o: %.cpp
	gcc -c $< -Wbuiltin-declaration-mismatch
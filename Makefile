CC=g++

SOURCE=./src

CADD=-std=c++11

CFLAGS=-g -Wall $(WARNINGS)
ifdef OPT
  CFLAGS=-O3 $(WARNINGS)
endif

COPT=-c $< -I $(SOURCE) -o $@  $(CFLAGS) $(CADD)


MorphoTooth: sources main.o
	$(CC) $(CFLAGS)  -o MorphoTooth \
	main.o $(SOURCE)/*.o 



main.o:main.cpp
	$(CC) $(COPT) -I $(SOURCE)


sources:
	make --directory=$(SOURCE) all



clean:
	@ echo "--- cleaning ---"; \
	for d in $(SOURCE);  \
        do                               \
          make --directory=$$d clean; \
        done; \
	rm -f *.o MorphoTooth

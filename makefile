all: firstfit bestfit

firstfit: 
	g++ -std=c++11 -O -o $@ $@.cpp 
bestfit: 
	g++ -std=c++11 -O -o $@ $@.cpp 

clean:
	rm -f firstfit bestfit
	
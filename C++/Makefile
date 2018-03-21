CPP       = g++
CPPFLAGS += `pkg-config --cflags libcurl`
LDFLAGS  += `pkg-config --libs libcurl`

%.o: %.cpp
	$(CPP) -c -o $@ $<

all: sample.o
	$(CPP) -o sample sample.o $(LDFLAGS)

clean:
	rm -f *.o sample

BIN = autols
SOURCES = $(shell ls src/*.c)
DEPS = $(shell ls src/*.h)

$(BIN): $(SOURCES) $(DEPS)
	gcc -Wall -Wextra -O2 -o $(BIN) $(SOURCES)

clean:
	rm -f $(BIN)

all: $(BIN)

install: all
	install -s -m 0755 -o root -g root autols /usr/local/bin

.PHONY: all clean install

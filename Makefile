MAKE  := make

all:
	$(MAKE) -C src
	$(MAKE) -C example
clean:
	$(MAKE) -C src clean
	$(MAKE) -C example clean
	rm -f lib/*
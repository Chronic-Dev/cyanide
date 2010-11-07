all:
	mkdir -p payloads
	make -C tools
	make -C bundles

clean:
	rm -rf payloads
	make clean -C tools
	make clean -C bundles
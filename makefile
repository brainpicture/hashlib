all:
	node-waf configure build
	@echo "--------\nMODULE FILE SHOULD BE IN ./build/default/\nUSE 'sudo make install' to install it\nAlso you can use 'make tests' to run tests"
tests:
	node ./test.js
install:
	cp ./build/default/hashlib.node /usr/local/lib/node/libraries/hashlib.node
clean:
	rm -rf ./build

all:
	nodejs-waf configure build
tests:
	nodejs ./test.js
install:
	mkdir -p ~/.node_libraries && cp ./build/default/hashlib.node ~/.node_libraries/hashlib.node
clean:
	rm -rf ./build

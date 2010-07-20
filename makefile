all:
	node-waf configure build && mkdir -p ~/.node_libraries && cp ./build/default/hashlib.node ~/.node_libraries/hashlib.node
tests:
	node ./test.js
install:
	mkdir -p ~/.node_libraries && cp ./build/default/hashlib.node ~/.node_libraries/hashlib.node
clean:
	rm -rf ./build

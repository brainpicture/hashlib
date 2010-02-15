all:
	node-waf configure build
tests:
	node ./test.js
install:
	cp ./build/default/hashlib.node /usr/local/lib/node/libraries/hashlib.node
clean:
	rm -rf ./build

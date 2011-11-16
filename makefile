all: waf install

waf:
	node-waf configure build

install:
	@mkdir -p ~/.node_modules && cp ./build/Release/hashlib.node ~/.node_modules/hashlib.node

tests:
	@node ./test.js

clean:
	@rm -rf ./build

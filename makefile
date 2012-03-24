all: 
	waf install

waf:
	node-waf configure build

install:
	UNAME := $(shell uname)

	ifeq ($(UNAME), Darwin)
		VERSION := $(shell sw_vers | grep 'ProductVersion:' | grep -o '[0-9]*\.[0-9]*\.[0-9]*')
		
		ifeq($(VERSION), 10.7.3)
			@sudo ln -sf /usr/local/include/node/node.h /usr/local/include/node/ev.h
			@CXXFLAGS=-I/usr/local/include/node/uv-private/
		endif
	endif

	@mkdir -p ~/.node_modules && cp ./build/Release/hashlib.node ~/.node_modules/hashlib.node

tests:
	@node ./test.js

clean:
	@rm -rf ./build

all:
	emcc main.cpp ./include/VNode.cpp -o main.js --bind -s WASM=1 -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS='["_invokeCppCallback", "_main"]'  -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' -sNO_DISABLE_EXCEPTION_CATCHING 
	python3 -m http.server 8080

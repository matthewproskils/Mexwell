em++ -std=c++17 -s ALLOW_MEMORY_GROWTH=1  -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']" -s EXPORTED_FUNCTIONS="['_runMex', '_runMexDebug']" -s NO_EXIT_RUNTIME main.cc -o build/em.js
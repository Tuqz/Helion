Library('hc', [Glob('src/heliocentric/*.cpp'), Glob('src/heliocentric/*/*.cpp')], CXXFLAGS="-std=c++11");
Library('physics', Glob('src/orbits/*.cpp'), CXXFLAGS="-std=c++11");
Program('helion', 'src/main.cpp', LIBS=['hc', 'glfw', 'GLEW', 'GL'], LIBPATH='.', CXXFLAGS="-std=c++11");

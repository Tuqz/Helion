Library('hc', Glob('src/heliocentric/*.cpp'), CXXFLAGS="-std=c++11");
SOURCES = Glob('src/orbits/*.cpp') + ['src/main.cpp']
Program('helion', SOURCES, LIBS=['hc', 'glfw', 'GLEW', 'GL'], LIBPATH='.', CXXFLAGS="-std=c++11");

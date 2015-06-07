Library('hc', Glob('src/heliocentric/*.cpp'), LIBS=['glfw'], CXXFLAGS="-std=c++11");
Program('helion', 'src/main.cpp', LIBS=['hc', 'glfw'], LIBPATH='.', CXXFLAGS="-std=c++11");
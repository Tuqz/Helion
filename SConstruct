import glob
import os

sources = glob.glob("src/heliocentric/*.cpp")
Library('hc', sources, CPPPATH=['include/'], CXXFLAGS="-std=c++11")
env=Environment(ENV = {'PATH' : os.environ['PATH']},
				CC = 'g++',
				tools = ['mingw'],
				CPPPATH=['include/'],
                CPPDEFINES=[],
				LIBPATH=['.', 'lib/'],
                LIBS=['glfw3', 'opengl32', 'glew32.dll', 'glu32', 'mingw32'],
				CXXFLAGS=['-std=c++11', '-DGLEW_BUILD']) 
env.Program('helion', [Glob('src/main.cpp'), Glob('src/heliocentric/*.cpp')])

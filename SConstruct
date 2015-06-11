# Helion SConstruct
# Written by Tuqz, Oebele, Jacob

# Imports
import glob
import os
import shutil
from sys import platform as _platform # Required to check OS

# Setup default settings, in case we can't detect an OS for some reason
libs = ['hc', 'glfw', 'GLEW', 'GL']
libpath = ['.']
cpppath = ['include/']
cxxflags = ['-std-c++11']
env=Environment(LIBS = libs,
                LIBPATH = libpath,
                CPPPATH = cpppath,
                CXXFLAGS = cxxflags)

# Dependent on OS, setup proper settings
if _platform == "linux" or _platform == "linux2":
    # Linux
    print "Linux detected"
elif _platform == "darwin":
    # OSX
    print "OSX detected"
elif _platform == "win32":
    # Windows
    print "Windows detected"
    cc = ['g++']
    tool = ['mingw']
    libs = ['glfw3', 'opengl32', 'glew32.dll', 'glu32', 'mingw32']
    libpath = ['.', 'lib/']
    cxxflags = ['-std=c++11', '-DGLEW_BUILD']
    env=Environment(CC = cc,
                    tools = tool,
                    CPPPATH = cpppath,
                    LIBPATH = libpath,
                    LIBS = libs,
                    CXXFLAGS = cxxflags,
                    ENV = {'PATH' : os.environ['PATH']})

sources = glob.glob("src/heliocentric/*.cpp")
Library('hc', sources, CPPPATH=['include/'], CXXFLAGS="-std=c++11")
env.Program('bin/helion', [Glob('src/main.cpp'), Glob('src/heliocentric/*.cpp')])
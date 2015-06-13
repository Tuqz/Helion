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
cxxflags = ['-std=c++11']
env=Environment(LIBS = libs,
                LIBPATH = libpath,
                CPPPATH = cpppath,
                CXXFLAGS = cxxflags)
                
# By default, build with the backend as a static library.
# Windows doesn't seem to like doing this, so everything is pushed into one big executable with no backend library
buildWithLib = True

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
    libs = ['mingw32', 'glfw3', 'opengl32', 'glew32.dll', 'glu32', 'hc']
    cxxflags = ['-std=c++11', '-DGLEW_BUILD']
    env=Environment(CC = cc,
                    tools = tool,
                    CPPPATH = cpppath,
                    LIBPATH = libpath,
                    LIBS = libs,
                    CXXFLAGS = cxxflags,
                    ENV = {'PATH' : os.environ['PATH']})
    buildWithLib = False
    
if buildWithLib == True:
    print "Building with backend as a library"
                    
Export('env', 'buildWithLib')
env.SConscript("src/heliocentric/SConscript")
env.SConscript("src/SConscript", exports = 'env')
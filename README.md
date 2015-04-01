# Herd-Immunity-Simulator
A Python simulation of Herd Immunity from vaccination (in Python subdirectory)
for the interpreter: https://www.python.org/downloads/

C++ port is in CPP subdirectory.
to build from source requires the following

cmake version 3.1+ (http://www.cmake.org/)

tclap (http://tclap.sourceforge.net/)

if you are on linux, both of these should be in your distribution repository, although cmake 3.1 is fairly new (as of April 2015 it is still in Fedora rawhide & fedora 22 testing repos), you may need to enable testing or raw repositories to get it.

on mac you might need to use xcode + macports, homebrew, or something similar to pull these down and build them.

on windows I would recommend using mingw or cygwin

It may also work with the microsoft visual c++ compilers via cmake, but you'll still need tclap.

chances are if thats your setup, you'll know how to set up your environment.

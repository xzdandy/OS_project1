all: src/MyShell src/MyCopy_core src/MyCopy src/ForkCopy_core src/ForkCopy src/PipeCopy_core src/PipeCopy src/MoreShell src/mss_core src/MergesortSingle src/msm_core src/MergesortMulti src/BBC

MyCopy_core: src/MyCopy_core.cc
	g++ src/MyCopy_core.cc -o src/MyCopy_core
MyCopy: src/MyCopy.cc
	g++ src/MyCopy.cc -o src/MyCopy

ForkCopy_core: src/ForkCopy_core.cc
	g++ src/ForkCopy_core.cc -o src/ForkCopy_core
ForkCopy: src/ForkCopy.cc
	g++ src/ForkCopy.cc -o src/ForkCopy

PipeCopy_core: src/PipeCopy_core.cc
	g++ src/PipeCopy_core.cc -o src/PipeCopy_core
PipeCopy: src/PipeCopy.cc
	g++ src/PipeCopy.cc -o src/PipeCopy

MyShell: src/MyShell.cc
	g++ src/MyShell.cc -o src/MyShell

MoreShell: src/MoreShell.cc
	g++ src/MoreShell.cc -o src/MoreShell

mss_core: src/mss_core.cc
	g++ src/mss_core.cc -o src/mss_core -lpthread
MergesortSingle: src/MergesortSingle.cc
	g++ src/MergesortSingle.cc -o src/MergesortSingle

msm_core: src/msm_core.cc
	g++ src/msm_core.cc -o src/msm_core -lpthread
MergesortMulti: src/MergesortMulti.cc
	g++ src/MergesortMulti.cc -o src/MergesortMulti

BBC: src/BurgerBuddies.cc
	g++ src/BurgerBuddies.cc -o src/BBC -lpthread
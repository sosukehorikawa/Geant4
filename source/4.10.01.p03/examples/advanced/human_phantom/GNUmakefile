# $Id: GNUmakefile 70025 2013-05-22 08:43:05Z gcosmo $
# --------------------------------------------------------------
# GNUmakefile for examples module.
# --------------------------------------------------------------

name := phantom
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../..
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

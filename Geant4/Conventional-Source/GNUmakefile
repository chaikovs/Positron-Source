name := posProd
G4TARGET := $(name)
G4EXLIB := true

.PHONY: setup clean_setup all
all: lib bin

setup:
	@echo "Copying files from common"
	@$./scripts/copy_files.sh

clean_setup:
	@echo "Removing files copied from common"
	@$./scripts/clean_files.sh

CPPFLAGS += -I$(shell root-config --incdir) 
EXTRALIBS = $(shell root-config --glibs)

include $/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

histclean:
	rm ${G4WORKDIR}/tmp/${G4SYSTEM}/${G4TARGET}/HistoManager.o



# Makefie by sharmer

LIB      = lib
DIRS     = sitabctl msimg32 siutf8

MKDIR    = mkdir
MAKE     = make
RM       = rm -rf
CP       = cp -f

.PHONY: $(DIRS)

all: $(DIRS)
	${RM} $(LIB)
	$(MKDIR) $(LIB)
	for target in $(DIRS); do \
		$(MAKE) -C $$target; \
	done

clean: 
	for target in $(DIRS); do \
		$(MAKE) -C $$target clean; \
	done
	${RM} $(LIB)

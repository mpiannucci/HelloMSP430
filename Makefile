#
# Makefile for msp430
#
# 'make' builds TARGET
# 'make clean' deletes everything except source files and Makefile
# 'make program' programs flash on msp430 with TARGET, then resets it.
# 'make reset' resets the msp430

# You need to set TARGET, MCU and SOURCES for your project.
# TARGET is the name of the executable file to be produced (.elf)
# eg if TARGET is foo.elf, then foo.elf will be produced, which can be programmed
#    into the msp430 flash by typing 'make program'
#
# If you want to see the assembler source from file foo.c, then use make foo.lst

# Set the build directory 
BUILDPATH = bin/

TARGET   = main.elf
MCU      = msp430g2553

# List all the source files here
# eg if you have a source file foo.c then list it here
SOURCEPATH   = src/
SOURCEFILES  = main.cpp
SOURCES      = $(SOURCEPATH)$(SOURCEFILES)
#LIBS = -lcc2420 -lboard430

LIBPATH  = -Llib
INCLUDES = -Iinclude

# You probably don't need to change anything below this line.
#######################################################################################
CFLAGS   = -mmcu=$(MCU) -g -O3 -Wall -Wcast-align -Wcast-qual -Wimplicit \
	   -Wmissing-declarations -Wmissing-prototypes -Wnested-externs \
	   -Wpointer-arith -Wredundant-decls -Wreturn-type -Wshadow \
	   -Wstrict-prototypes -Wswitch -Wunused $(INCLUDES)
ASFLAGS  = -mmcu=$(MCU) -x assembler-with-cpp -Wa,-gstabs
LDFLAGS  = -mmcu=$(MCU) $(LIBPATH)

########################################################################################

CC       = msp430-gcc
CXX      = msp430-g++
AS       = msp430-gcc -x assembler-with-cpp
LD       = msp430-ld
AR       = msp430-ar
GASP     = msp430-gasp
NM       = msp430-nm
OBJCOPY  = msp430-objcopy
RANLIB   = msp430-ranlib
STRIP    = msp430-strip
SIZE     = msp430-size
READELF  = msp430-readelf
CP       = cp -p
RM       = rm -f
MV       = mv

# Linux msp430 programmer
PROGRAM  = mspdebug rf2500
########################################################################################

# the file which will include dependencies
DEPEND = $(TARGET:.elf=.d)

# all the object files
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $@
	-$(MV) $(OBJECTS) $(BUILDPATH)$(notdir $(OBJECTS))
	-$(MV) $(TARGET) $(BUILDPATH)$(notdir $(TARGET))

# rule for making assembler source listing, to see the code
%.lst : %.c
	$(CC) -c $(CFLAGS) -Wa,-anlhd $< > $@
	-$(MV) $(SOURCES:.c=.lst) $(BUILDPATH)$(notdir $(SOURCES:.c=.lst))

# include the dependencies
-include $(DEPEND)

# dependencies file
# includes also considered, since some of these are our own
# (otherwise use -MM instead of -M)
$(DEPEND): $(SOURCES) Makefile
	$(CC) -M ${CFLAGS} $(SOURCES) >$@
	-$(MV) $(DEPEND) $(BUILDPATH)$(notdir $(DEPEND))

.PHONY: print_vars
print_vars:
	@echo $(SOURCES)
	@echo $(OBJECTS)
	@echo $(DEPEND)
	@echo $(TARGET)

.PHONY:	clean
clean:
	-$(RM) $(BUILDPATH)$(notdir $(OBJECTS))
	-$(RM) $(BUILDPATH)$(TARGET)
	-$(RM) $(BUILDPATH)$(notdir $(SOURCES:.c=.lst))
	-$(RM) $(BUILDPATH)$(notdir $(DEPEND))

.PHONY: install
install: $(TARGET)
	$(PROGRAM) "prog $(BUILDPATH)$(TARGET)"
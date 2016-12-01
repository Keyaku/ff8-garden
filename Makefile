SRCDIR ?= src
OBJDIR = bld
DEPS = $(OBJDIR)/*.d

INCLUDE += -Iheaders

CC ?= gcc
LD = $(CC)
CFLAGS = -O0 -g -c -pedantic -Wall $(INCLUDE)
#LDFLAGS =

EXECFILE ?= garden

################################################################################
#############       DO NOT CHANGE ANYTHING BELOW THIS PART        ##############
################################################################################
EXEC = $(EXECFILE)

# Filtering files for rule management
SRC := $(shell find $(SRCDIR) -name *.cpp)
OBJ := $(subst $(SRCDIR),$(OBJDIR),$(SRC:%.cpp=%.o))

# Objects and dependencies compilation
$(OBJDIR)/%.o: $(addprefix $(SRCDIR)/,%.cpp)
	$(shell mkdir -p $(dir $@))
	$(CC) -MMD -o $@ $< $(CFLAGS)

# General rules
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Including dependencies
-include $(DEPS)

################################################################################
#############       DO NOT CHANGE ANYTHING ABOVE THIS PART        ##############
################################################################################
debug: CFLAGS += -ansi -Wextra
debug: all

clean:
	rm -rf $(OBJDIR)/* $(DEPS) $(EXEC) *.DS_Store

.PHONY: all clean zip

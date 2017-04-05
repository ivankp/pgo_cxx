INCFLAGS := -Iinclude
CXXFLAGS := -Wall -g $(INCFLAGS)

EXE := $(patsubst src/%.cc,%,$(wildcard src/*.cc))
# DEP := $(patsubst %,.%.d,$(EXE))
DEP := $(EXE:%=.%.d)

ROOT_CFLAGS := $(shell root-config --cflags)
ROOT_LIBS   := $(shell root-config --libs)

NODEPS := clean
.PHONY: all clean

C_lambda := $(ROOT_CFLAGS)
L_lambda := $(ROOT_LIBS)

C_minuit := $(ROOT_CFLAGS)
L_minuit := $(ROOT_LIBS) -lMinuit

all: $(EXE)

#Don't create dependencies when cleaning
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DEP)
endif

$(DEP): .%.d: src/%.cc
	$(CXX) $(INCFLAGS) -MM -MT $* $< -MF $@

$(EXE): %: src/%.cc
	$(CXX) $(CXXFLAGS) $(C_$*) $< -o $@ $(L_$*)

clean:
	@rm -fv $(EXE) .*.d


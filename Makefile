TEXTCOMP := textcomp$(EXE)

SOURCEDIR  := Source
INCLUDEDIR := Include
BUILDDIR   := Build

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Werror -O2 -I$(INCLUDEDIR)

CPPFILES := $(wildcard $(SOURCEDIR)/*.cpp)
OFILES   := $(CPPFILES:$(SOURCEDIR)/%.cpp=$(BUILDDIR)/%.o)

all: mkdirs $(TEXTCOMP)

clean:
	rm -rf $(BUILDDIR)
	rm -f $(TEXTCOMP)

mkdirs:
	mkdir -p $(BUILDDIR)

$(TEXTCOMP): $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES) -o $@

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

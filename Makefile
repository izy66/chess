# Universal makefile for single C++ program
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependencies amo    ng source files.
# Use make default rules for commonly used file-name suffixes and make varia    bles names.
#
# % make [ a.out ]

########## Variables ##########

CXX = g++          # compiler
CXXFLAGS = -std=c++20 -g -Wall -MMD      # compiler flags
MAKEFILE_NAME = ${Makefile ${MAKEFILE_LIST}}  # makefile name

SOURCES = pieces/blank.cc pieces/piece.cc pieces/king.cc subject.cc board.cc chessboard.cc textui.cc kingmove.cc pawnmove.cc decisiontree.cc parser.cc controller.cc game.cc main.cc     # source files (*.cc)
OBJECTS = ${SOURCES:.cc=.o}     # object files forming executable
DEPENDS = ${OBJECTS:.o=.d}      # substitute ".o" with ".d"
EXEC = chess # executable name

########## Targets ##########

.PHONY : clean          # not file names

${EXEC} : ${OBJECTS}        # link step
	${CXX} ${CXXFLAGS} $^ -o $@   # additional object files before $^

${OBJECTS} : ${MAKEFILE_NAME}     # OPTIONAL : changes to this file => recom    pile

# make implicitly generates rules to compile C++ files that generate .o file    s

-include ${DEPENDS}       # include *.d files containing program dependences

clean :           # remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}

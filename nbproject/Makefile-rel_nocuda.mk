#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=nvcc
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=rel_nocuda
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/BaseEvent.o \
	${OBJECTDIR}/Counter.o \
	${OBJECTDIR}/DispatcherCreator.o \
	${OBJECTDIR}/InvalidFilenameException.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-fopenmp -march=native
CXXFLAGS=-fopenmp -march=native

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lboost_program_options -lboost_filesystem -lboost_system -lboost_regex

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dynprog

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dynprog: ${OBJECTDIR}/main.o

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dynprog: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++ -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dynprog ${OBJECTFILES} ${LDLIBSOPTIONS} -fopenmp -s

${OBJECTDIR}/BaseEvent.o: BaseEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -Werror -s -DKP_NOCUDA -std=c++98 -fopenmp -march=native -MMD -MP -MF $@.d -o ${OBJECTDIR}/BaseEvent.o BaseEvent.cpp

${OBJECTDIR}/Counter.o: Counter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -Werror -s -DKP_NOCUDA -std=c++98 -fopenmp -march=native -MMD -MP -MF $@.d -o ${OBJECTDIR}/Counter.o Counter.cpp

${OBJECTDIR}/DispatcherCreator.o: DispatcherCreator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -Werror -s -DKP_NOCUDA -std=c++98 -fopenmp -march=native -MMD -MP -MF $@.d -o ${OBJECTDIR}/DispatcherCreator.o DispatcherCreator.cpp

${OBJECTDIR}/InvalidFilenameException.o: InvalidFilenameException.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -Werror -s -DKP_NOCUDA -std=c++98 -fopenmp -march=native -MMD -MP -MF $@.d -o ${OBJECTDIR}/InvalidFilenameException.o InvalidFilenameException.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -Werror -s -DKP_NOCUDA -std=c++98 -fopenmp -march=native -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dynprog

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

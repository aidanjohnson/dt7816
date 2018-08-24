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
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ctrtmr.o \
	${OBJECTDIR}/digio.o \
	${OBJECTDIR}/in-stream.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/mongoose.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/web-server

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/web-server: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/web-server ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/ctrtmr.o: ctrtmr.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ctrtmr.o ctrtmr.c

${OBJECTDIR}/digio.o: digio.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/digio.o digio.c

${OBJECTDIR}/in-stream.o: in-stream.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/in-stream.o in-stream.c

${OBJECTDIR}/main.o: main.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/mongoose.o: mongoose.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mongoose.o mongoose.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

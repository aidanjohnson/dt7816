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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/28d545ba/RingBuf.o \
	${OBJECTDIR}/_ext/28d545ba/aifx.o \
	${OBJECTDIR}/_ext/28d545ba/extended.o \
	${OBJECTDIR}/_ext/28d545ba/float32.o \
	${OBJECTDIR}/_ext/28d545ba/g711.o \
	${OBJECTDIR}/_ext/28d545ba/iff.o \
	${OBJECTDIR}/_ext/28d545ba/libaiff.o \
	${OBJECTDIR}/_ext/28d545ba/lpcm.o \
	${OBJECTDIR}/_ext/28d545ba/main.o \
	${OBJECTDIR}/_ext/28d545ba/pascal.o \
	${OBJECTDIR}/_ext/28d545ba/recorder_helpers.o \
	${OBJECTDIR}/_ext/28d545ba/sunriset.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/recorder

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/recorder: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/recorder ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/28d545ba/RingBuf.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/RingBuf.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/RingBuf.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/RingBuf.c

${OBJECTDIR}/_ext/28d545ba/aifx.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/aifx.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/aifx.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/aifx.c

${OBJECTDIR}/_ext/28d545ba/extended.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/extended.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/extended.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/extended.c

${OBJECTDIR}/_ext/28d545ba/float32.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/float32.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/float32.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/float32.c

${OBJECTDIR}/_ext/28d545ba/g711.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/g711.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/g711.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/g711.c

${OBJECTDIR}/_ext/28d545ba/iff.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/iff.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/iff.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/iff.c

${OBJECTDIR}/_ext/28d545ba/libaiff.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/libaiff.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/libaiff.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/libaiff.c

${OBJECTDIR}/_ext/28d545ba/lpcm.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/lpcm.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/lpcm.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/lpcm.c

${OBJECTDIR}/_ext/28d545ba/main.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/main.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/main.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/main.c

${OBJECTDIR}/_ext/28d545ba/pascal.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/pascal.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/pascal.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/pascal.c

${OBJECTDIR}/_ext/28d545ba/recorder_helpers.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/recorder_helpers.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/recorder_helpers.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/recorder_helpers.c

${OBJECTDIR}/_ext/28d545ba/sunriset.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/sunriset.c
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/sunriset.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/sunriset.c

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

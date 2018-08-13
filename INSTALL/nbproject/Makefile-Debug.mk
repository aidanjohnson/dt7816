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

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/testRecorder.o

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

${OBJECTDIR}/_ext/28d545ba/RingBuf.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/RingBuf.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/RingBuf.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/RingBuf.c

${OBJECTDIR}/_ext/28d545ba/aifx.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/aifx.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/aifx.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/aifx.c

${OBJECTDIR}/_ext/28d545ba/extended.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/extended.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/extended.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/extended.c

${OBJECTDIR}/_ext/28d545ba/float32.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/float32.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/float32.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/float32.c

${OBJECTDIR}/_ext/28d545ba/g711.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/g711.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/g711.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/g711.c

${OBJECTDIR}/_ext/28d545ba/iff.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/iff.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/iff.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/iff.c

${OBJECTDIR}/_ext/28d545ba/libaiff.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/libaiff.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/libaiff.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/libaiff.c

${OBJECTDIR}/_ext/28d545ba/lpcm.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/lpcm.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/lpcm.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/lpcm.c

${OBJECTDIR}/_ext/28d545ba/main.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/main.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/main.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/main.c

${OBJECTDIR}/_ext/28d545ba/pascal.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/pascal.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/pascal.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/pascal.c

${OBJECTDIR}/_ext/28d545ba/recorder_helpers.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/recorder_helpers.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/recorder_helpers.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/recorder_helpers.c

${OBJECTDIR}/_ext/28d545ba/sunriset.o: /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/sunriset.c nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/sunriset.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/sunriset.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/testRecorder.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   -lcunit 


${TESTDIR}/tests/testRecorder.o: tests/testRecorder.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -DDT7816 -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -I../../../board-support/linux-3.12.10-ti2013.12.01/include/linux -I../../../board-support/linux-3.12.10-ti2013.12.01/include -I../../../board-support/extra-drivers/dt78xx -I../common -std=c11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/testRecorder.o tests/testRecorder.c


${OBJECTDIR}/_ext/28d545ba/RingBuf_nomain.o: ${OBJECTDIR}/_ext/28d545ba/RingBuf.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/RingBuf.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/28d545ba/RingBuf.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/RingBuf_nomain.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/RingBuf.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/28d545ba/RingBuf.o ${OBJECTDIR}/_ext/28d545ba/RingBuf_nomain.o;\
	fi

${OBJECTDIR}/_ext/28d545ba/aifx_nomain.o: ${OBJECTDIR}/_ext/28d545ba/aifx.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/aifx.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/28d545ba/aifx.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/aifx_nomain.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/aifx.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/28d545ba/aifx.o ${OBJECTDIR}/_ext/28d545ba/aifx_nomain.o;\
	fi

${OBJECTDIR}/_ext/28d545ba/extended_nomain.o: ${OBJECTDIR}/_ext/28d545ba/extended.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/extended.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/28d545ba/extended.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/extended_nomain.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/extended.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/28d545ba/extended.o ${OBJECTDIR}/_ext/28d545ba/extended_nomain.o;\
	fi

${OBJECTDIR}/_ext/28d545ba/float32_nomain.o: ${OBJECTDIR}/_ext/28d545ba/float32.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/float32.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/28d545ba/float32.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/float32_nomain.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/float32.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/28d545ba/float32.o ${OBJECTDIR}/_ext/28d545ba/float32_nomain.o;\
	fi

${OBJECTDIR}/_ext/28d545ba/g711_nomain.o: ${OBJECTDIR}/_ext/28d545ba/g711.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/g711.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/28d545ba/g711.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/g711_nomain.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/g711.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/28d545ba/g711.o ${OBJECTDIR}/_ext/28d545ba/g711_nomain.o;\
	fi

${OBJECTDIR}/_ext/28d545ba/iff_nomain.o: ${OBJECTDIR}/_ext/28d545ba/iff.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/iff.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/28d545ba/iff.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/iff_nomain.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/iff.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/28d545ba/iff.o ${OBJECTDIR}/_ext/28d545ba/iff_nomain.o;\
	fi

${OBJECTDIR}/_ext/28d545ba/libaiff_nomain.o: ${OBJECTDIR}/_ext/28d545ba/libaiff.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/libaiff.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/28d545ba/libaiff.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/libaiff_nomain.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/libaiff.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/28d545ba/libaiff.o ${OBJECTDIR}/_ext/28d545ba/libaiff_nomain.o;\
	fi

${OBJECTDIR}/_ext/28d545ba/lpcm_nomain.o: ${OBJECTDIR}/_ext/28d545ba/lpcm.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/lpcm.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/28d545ba/lpcm.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/lpcm_nomain.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/lpcm.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/28d545ba/lpcm.o ${OBJECTDIR}/_ext/28d545ba/lpcm_nomain.o;\
	fi

${OBJECTDIR}/_ext/28d545ba/main_nomain.o: ${OBJECTDIR}/_ext/28d545ba/main.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/28d545ba/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/main_nomain.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/main.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/28d545ba/main.o ${OBJECTDIR}/_ext/28d545ba/main_nomain.o;\
	fi

${OBJECTDIR}/_ext/28d545ba/pascal_nomain.o: ${OBJECTDIR}/_ext/28d545ba/pascal.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/pascal.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/28d545ba/pascal.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/pascal_nomain.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/pascal.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/28d545ba/pascal.o ${OBJECTDIR}/_ext/28d545ba/pascal_nomain.o;\
	fi

${OBJECTDIR}/_ext/28d545ba/recorder_helpers_nomain.o: ${OBJECTDIR}/_ext/28d545ba/recorder_helpers.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/recorder_helpers.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/28d545ba/recorder_helpers.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/recorder_helpers_nomain.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/recorder_helpers.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/28d545ba/recorder_helpers.o ${OBJECTDIR}/_ext/28d545ba/recorder_helpers_nomain.o;\
	fi

${OBJECTDIR}/_ext/28d545ba/sunriset_nomain.o: ${OBJECTDIR}/_ext/28d545ba/sunriset.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/sunriset.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/28d545ba
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/28d545ba/sunriset.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -DDT7816 -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx -I/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/28d545ba/sunriset_nomain.o /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/recorder/sunriset.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/28d545ba/sunriset.o ${OBJECTDIR}/_ext/28d545ba/sunriset_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

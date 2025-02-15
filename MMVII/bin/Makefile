# =========== Directories
MMV1_DIR=../..
MMV1_LIBDIR=${MMV1_DIR}/lib
MMV2_DIR=${MMV1_DIR}/MMVII
MMV2_BINDIR=${MMV2_DIR}/bin
MMV2_SRCDIR=${MMV2_DIR}/src
MMV2_EXE=${MMV2_BINDIR}/MMVII
MMV2_INSTALL_PATH=${dir ${abspath ${MMV2_EXE}}}

# =========== Includes & Libraries
MMV1_INCLUDES=-I ${MMV1_DIR}/include -I${MMV1_DIR}
MMV2_INCLUDES=-I ${MMV2_DIR} -I ${MMV2_DIR}/ExternalInclude

MMV2_LIBNAME=P2007
MMV2_LIB=${MMV2_BINDIR}/lib${MMV2_LIBNAME}.a
MMV1_LIBS=${MMV1_LIBDIR}/libelise.a ${MMV1_LIBDIR}/libANN.a
QT_LIBS=-lXext -lGLU -lGL -lQt5Core -lQt5Gui -lQt5Xml -lQt5OpenGL -lQt5Concurrent -lQt5Widgets
## MacOS : may be -lstdc++fs should be replaced by -lc++experimental
EXT_LIBS=-lpthread -lX11 ${QT_LIBS} -lstdc++fs


# =========== Compiler & Flags
CXX=g++
LD=g++
CXXFLAGS=-fopenmp -std=c++17 -Wall  -Werror -O4 -fPIC -march=native ${MMV2_INCLUDES} ${MMV1_INCLUDES} -D'MMVII_INSTALL_PATH="${MMV2_INSTALL_PATH}"'
LDFLAGS=-fopenmp


# ===========  Use ccache if found
CCACHE:=${shell which ccache}
ifneq (,${CCACHE})
  CXX:=${CCACHE} ${CXX}
endif


# ============ Targets
all: ${MMV2_EXE}

clean:
	rm -f ${OBJS} ${DEPS} ${MMV2_EXE} ${MMV2_LIB}


# =========== Build Lib
LIB_SRCS=${wildcard ${MMV2_SRCDIR}/*/*.cpp} ${wildcard ${MMV2_DIR}/kapture/*.cpp}
LIB_OBJS:=${LIB_SRCS:.cpp=.o}
LIB_OBJS:=${filter-out ${MMV2_SRCDIR}/BinaireInstall/%,${LIB_OBJS}}
LIB_OBJS:=${filter-out ${MMV2_SRCDIR}/ResultInstall/%,${LIB_OBJS}}
LIB_OBJS:=${filter-out ${MMV2_SRCDIR}/TestCodeGen/%,${LIB_OBJS}}

%.o: %.cpp Makefile
	${CXX} -c  ${CXXFLAGS} $< -o $@

${MMV2_LIB}: ${LIB_OBJS}
	rm -f $@
	ar crs $@ $^

# ========== Build Main
MAIN_OBJ=${MMV2_SRCDIR}/main.o

${MMV2_EXE}: ${MAIN_OBJ} ${MMV2_LIB} ${MMV1_LIBS}
	${CXX} ${LDFLAGS} $^ ${EXT_LIBS}  -o $@

# =========== Auto dependancies
OBJS=${LIB_OBJS} ${MAIN_OBJ}
DEPS=${join ${addsuffix ., ${dir ${OBJS}}}, ${notdir ${OBJS:.o=.d}}}

.%.d: %.cpp
	@set -e; rm -f $@; \
	${CXX} -MM -MP -MT '${patsubst %.cpp,%.o,$<} $@' -MF $@ ${CXXFLAGS} $<   2>/dev/null

ifneq (${MAKECMDGOALS},clean)
-include ${DEPS}
endif

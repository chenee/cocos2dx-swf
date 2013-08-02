# Makefile for tu-testbed/base library


TOP = ..
include $(TOP)/config

INCLUDE_PATHS := $(ENGINE_INCLUDE) $(LIBPNG_INCLUDE) $(ZLIB_INCLUDE) $(JPEGLIB_INCLUDE)

CFLAGS := $(CFLAGS) $(INCLUDE_PATHS) $(CC_DEBUG_FLAGS)
LDFLAGS := -lGL -lGLU $(SDL_LDFLAGS) $(LIB_DEBUG_FLAGS)

BASE_LIB = $(LIB_PRE)base.$(LIB_EXT)
all: $(BASE_LIB)

# Source files.
SRCS :=						\
	configvars.cpp				\
	ear_clip_triangulate_float.cpp		\
	ear_clip_triangulate_sint16.cpp		\
	container.cpp				\
	demo.cpp				\
	dlmalloc.c				\
	file_util.cpp				\
	image.cpp				\
	image_filters.cpp			\
	jpeg.cpp				\
	logger.cpp				\
	membuf.cpp				\
	ogl.cpp					\
	png_helper.cpp				\
	postscript.cpp				\
	triangulate_float.cpp			\
	triangulate_sint32.cpp			\
	tu_file.cpp				\
	tu_file_SDL.cpp				\
	tu_gc_singlethreaded_marksweep.cpp	\
	tu_loadlib.cpp				\
	tu_random.cpp				\
	tu_timer.cpp				\
	tu_types.cpp				\
	utf8.cpp				\
	utility.cpp				\
	zlib_adapter.cpp

OBJS := $(SRCS:.cpp=.$(OBJ_EXT))
OBJS := $(OBJS:.c=.$(OBJ_EXT))

triangulate_sint32.$(OBJ_EXT) triangulate_float.$(OBJ_EXT): triangulate_impl.h triangulate.h grid_index.h
ear_clip_triangulate_sint16.$(OBJ_EXT) ear_clip_triangulate_float.$(OBJ_EXT): \
	ear_clip_triangulate.h \
	ear_clip_triangulate_impl.h \
	grid_index.h

$(BASE_LIB): $(OBJS)
	$(AR) $(LIB_OUT_FLAG)$(BASE_LIB) $(OBJS)

clean:
	-@rm -f $(BASE_LIB) $(OBJS)

echo:
	echo $(OBJS)
	echo $(BASE_LIB)

# Local Variables:
# tab-width: 8
# indent-tabs-mode: t
# End:

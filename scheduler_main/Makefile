	
# make clean/all CONFIG=Debug/Release ARCH=linux64/raspi ECHO=0/1

# the parrent dir of "arch" dir
ROOT_DIR = ../..

#PROJ_SRCS = $(wildcard *.c)
PROJ_SRCS = scheduler_test.c scheduler.c 


# list of directories containing header files
PROJ_INC_DIR = ../include

# the executable file
PROJ_OUT = scheduler_test.out

# list of ADDITIONAL compiler flags (prepended with "-" sign)
#PROJ_CFLAGS = -Wunused-but-set-variable
PROJ_CFLAGS =

PROJ_CPPFLAGS =

#PROJ_MACROS = _BSD_SOURCE
PROJ_MACROS =

# additional object files (created by other projects)
PROJ_ADD_OBJS =  dynamic_vector.o heap.o pq_heap.o uid.o tasker.o
# additional libraries
PROJ_LIBS =

# linker flags
PROJ_LDFLAGS =

# list of projects (makefiles) this project depends on
PROJ_DEPENDS  = ../dynamic_vector/Makefile ../heap/Makefile ../pq_heap/Makefile ../uid/Makefile ../task/Makefile  

include $(ROOT_DIR)/make/Project.mak

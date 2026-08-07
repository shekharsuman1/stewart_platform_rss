###########################################################################
## Makefile generated for component 'stewart_platform_v2'. 
## 
## Makefile     : stewart_platform_v2_rtw.mk
## Generated on : Thu Jul 30 07:10:59 2026
## Final product: ./stewart_platform_v2.a
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# MODELLIB                Static library target

PRODUCT_NAME              = stewart_platform_v2
MAKEFILE                  = stewart_platform_v2_rtw.mk
MATLAB_ROOT               = /MATLAB
MATLAB_BIN                = /MATLAB/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/glnxa64
START_DIR                 = /MATLAB\ Drive
TGT_FCN_LIB               = ISO_C
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ../../..
C_STANDARD_OPTS           = -fwrapv
CPP_STANDARD_OPTS         = -fwrapv
MODELLIB                  = stewart_platform_v2.a

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          GNU gcc/g++ | gmake (64-bit Linux)
# Supported Version(s):    
# ToolchainInfo Version:   2026a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# C_STANDARD_OPTS
# CPP_STANDARD_OPTS

#-----------
# MACROS
#-----------

WARN_FLAGS         = -Wall -W -Wwrite-strings -Winline -Wstrict-prototypes -Wnested-externs -Wpointer-arith -Wcast-align -Wno-stringop-overflow
WARN_FLAGS_MAX     = $(WARN_FLAGS) -Wcast-qual -Wshadow
CPP_WARN_FLAGS     = -Wall -W -Wwrite-strings -Winline -Wpointer-arith -Wcast-align -Wno-stringop-overflow
CPP_WARN_FLAGS_MAX = $(CPP_WARN_FLAGS) -Wcast-qual -Wshadow

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

FORMAT_FOR_ECHO_SH               = ""'$1'
FORMAT_FOR_ECHO                  = $(FORMAT_FOR_ECHO_SH)
HASH                             = \#
SEMICOLON                        = ;
OPEN_PAREN                       = (
CLOSE_PAREN                      = )
ESCAPE_SPECIAL_CHARS             = $(strip $(subst $(CLOSE_PAREN),\$(CLOSE_PAREN),\
	$(subst $(OPEN_PAREN),\$(OPEN_PAREN),\
	$(subst &,\&,\
	$(subst ~,\~,\
	$(subst ?,\?,\
	$(subst *,\*,\
	$(subst },\},\
	$(subst {,\{,\
	$(subst >,\>,\
	$(subst <,\<,\
	$(subst !,\!,\
	$(subst ],\],\
	$(subst [,\[,\
	$(subst $(HASH),\$(HASH),\
	$(subst \\,\\\,\
	$(subst ',\',\
	$(subst ",\",\
	$1))))))))))))))))))

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: GNU C Compiler
CC = gcc

# Linker: GNU Linker
LD = g++

# C++ Compiler: GNU C++ Compiler
CPP = g++

# C++ Linker: GNU C++ Linker
CPP_LD = g++

# Archiver: GNU Archiver
AR = ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/glnxa64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @rm -f
ECHO                = @echo
MV                  = @mv
RUN                 =

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c $(C_STANDARD_OPTS) -fPIC \
                       -O3
CPPFLAGS             = -c $(CPP_STANDARD_OPTS) -fPIC \
                       -O3
CPP_LDFLAGS          =
CPP_SHAREDLIB_LDFLAGS  = -shared -Wl,--no-undefined
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              =
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -j $(MAX_MAKE_JOBS) -l $(MAX_MAKE_LOAD_AVG) -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -shared -Wl,--no-undefined



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = ./stewart_platform_v2.a
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR)/codegen/lib/stewart_platform_v2 -I$(START_DIR) -I$(MATLAB_ROOT)/extern/include

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=stewart_platform_v2

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/codegen/lib/stewart_platform_v2/rt_nonfinite.c $(START_DIR)/codegen/lib/stewart_platform_v2/rtGetNaN.c $(START_DIR)/codegen/lib/stewart_platform_v2/rtGetInf.c $(START_DIR)/codegen/lib/stewart_platform_v2/stewart_platform_v2_initialize.c $(START_DIR)/codegen/lib/stewart_platform_v2/stewart_platform_v2_terminate.c $(START_DIR)/codegen/lib/stewart_platform_v2/stewart_platform_v2.c $(START_DIR)/codegen/lib/stewart_platform_v2/rotz.c $(START_DIR)/codegen/lib/stewart_platform_v2/roty.c $(START_DIR)/codegen/lib/stewart_platform_v2/rotx.c $(START_DIR)/codegen/lib/stewart_platform_v2/any.c $(START_DIR)/codegen/lib/stewart_platform_v2/cosd.c $(START_DIR)/codegen/lib/stewart_platform_v2/sind.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = rt_nonfinite.o rtGetNaN.o rtGetInf.o stewart_platform_v2_initialize.o stewart_platform_v2_terminate.o stewart_platform_v2.o rotz.o roty.o rotx.o any.o cosd.o sind.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS =  -lm

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_TFL = -msse2 -fno-predictive-commoning
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_TFL) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_TFL = -msse2 -fno-predictive-commoning
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_TFL) $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo $(call FORMAT_FOR_ECHO,### Successfully generated all binary outputs.)


build : prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo $(call FORMAT_FOR_ECHO,### Creating static library "$(PRODUCT)" ...)
	$(AR) $(ARFLAGS)  $(PRODUCT) $(OBJS)
	@echo $(call FORMAT_FOR_ECHO,### Created: "$(PRODUCT)")


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.cp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.CPP
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.c++
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : %.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.CPP
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c++
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/stewart_platform_v2/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/stewart_platform_v2/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/stewart_platform_v2/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/stewart_platform_v2/%.cp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/stewart_platform_v2/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/stewart_platform_v2/%.CPP
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/stewart_platform_v2/%.c++
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/stewart_platform_v2/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cc
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cxx
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.CPP
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c++
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.C
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


rt_nonfinite.o : $(START_DIR)/codegen/lib/stewart_platform_v2/rt_nonfinite.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetNaN.o : $(START_DIR)/codegen/lib/stewart_platform_v2/rtGetNaN.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rtGetInf.o : $(START_DIR)/codegen/lib/stewart_platform_v2/rtGetInf.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stewart_platform_v2_initialize.o : $(START_DIR)/codegen/lib/stewart_platform_v2/stewart_platform_v2_initialize.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stewart_platform_v2_terminate.o : $(START_DIR)/codegen/lib/stewart_platform_v2/stewart_platform_v2_terminate.c
	$(CC) $(CFLAGS) -o "$@" "$<"


stewart_platform_v2.o : $(START_DIR)/codegen/lib/stewart_platform_v2/stewart_platform_v2.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rotz.o : $(START_DIR)/codegen/lib/stewart_platform_v2/rotz.c
	$(CC) $(CFLAGS) -o "$@" "$<"


roty.o : $(START_DIR)/codegen/lib/stewart_platform_v2/roty.c
	$(CC) $(CFLAGS) -o "$@" "$<"


rotx.o : $(START_DIR)/codegen/lib/stewart_platform_v2/rotx.c
	$(CC) $(CFLAGS) -o "$@" "$<"


any.o : $(START_DIR)/codegen/lib/stewart_platform_v2/any.c
	$(CC) $(CFLAGS) -o "$@" "$<"


cosd.o : $(START_DIR)/codegen/lib/stewart_platform_v2/cosd.c
	$(CC) $(CFLAGS) -o "$@" "$<"


sind.o : $(START_DIR)/codegen/lib/stewart_platform_v2/sind.c
	$(CC) $(CFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo $(call FORMAT_FOR_ECHO,### PRODUCT = $(PRODUCT))
	@echo $(call FORMAT_FOR_ECHO,### PRODUCT_TYPE = $(PRODUCT_TYPE))
	@echo $(call FORMAT_FOR_ECHO,### BUILD_TYPE = $(BUILD_TYPE))
	@echo $(call FORMAT_FOR_ECHO,### INCLUDES = $(INCLUDES))
	@echo $(call FORMAT_FOR_ECHO,### DEFINES = $(DEFINES))
	@echo $(call FORMAT_FOR_ECHO,### ALL_SRCS = $(ALL_SRCS))
	@echo $(call FORMAT_FOR_ECHO,### ALL_OBJS = $(ALL_OBJS))
	@echo $(call FORMAT_FOR_ECHO,### LIBS = $(LIBS))
	@echo $(call FORMAT_FOR_ECHO,### MODELREF_LIBS = $(MODELREF_LIBS))
	@echo $(call FORMAT_FOR_ECHO,### SYSTEM_LIBS = $(SYSTEM_LIBS))
	@echo $(call FORMAT_FOR_ECHO,### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS))
	@echo $(call FORMAT_FOR_ECHO,### CFLAGS = $(CFLAGS))
	@echo $(call FORMAT_FOR_ECHO,### LDFLAGS = $(LDFLAGS))
	@echo $(call FORMAT_FOR_ECHO,### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS))
	@echo $(call FORMAT_FOR_ECHO,### CPPFLAGS = $(CPPFLAGS))
	@echo $(call FORMAT_FOR_ECHO,### CPP_LDFLAGS = $(CPP_LDFLAGS))
	@echo $(call FORMAT_FOR_ECHO,### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS))
	@echo $(call FORMAT_FOR_ECHO,### ARFLAGS = $(ARFLAGS))
	@echo $(call FORMAT_FOR_ECHO,### MEX_CFLAGS = $(MEX_CFLAGS))
	@echo $(call FORMAT_FOR_ECHO,### MEX_CPPFLAGS = $(MEX_CPPFLAGS))
	@echo $(call FORMAT_FOR_ECHO,### MEX_LDFLAGS = $(MEX_LDFLAGS))
	@echo $(call FORMAT_FOR_ECHO,### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS))
	@echo $(call FORMAT_FOR_ECHO,### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS))
	@echo $(call FORMAT_FOR_ECHO,### EXECUTE_FLAGS = $(EXECUTE_FLAGS))
	@echo $(call FORMAT_FOR_ECHO,### MAKE_FLAGS = $(MAKE_FLAGS))


clean : 
	$(ECHO) "### Deleting all derived files ..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."



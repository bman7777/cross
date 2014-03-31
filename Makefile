COMPILER=G++

C = cpp
OUTPUT_PATH = out/production/cross/
SOURCE_ROOT = src/
SOURCE_PATH_GOOGLETEST = /usr/include/gtest-1.7.0/make/
SOURCE_PATH_TEST = test/
SOURCE_PATH_CONTEXT = $(SOURCE_ROOT)cross/Context/
SOURCE_PATH_SEQ = $(SOURCE_ROOT)cross/Sequence/
SOURCE_PATH_SERVICE = $(SOURCE_ROOT)cross/Service/
NAME = cross
EXE = $(NAME)test
STLIB = lib$(NAME)

OBJ = o
A = a
COPT = -O2
CCMD = g++-4.8
ACMD = ar
OBJFLAG = -o
EXEFLAG = -o
INCLUDES = -Isrc -I/usr/include/boost_1_55_0
TESTINCLUDES = $(INCLUDES) -I. -I/usr/include/gtest-1.7.0/include/
LIBS = -l$(NAME)
LIBPATH = -L$(OUTPUT_PATH)
CPPFLAGS = -std=c++11 $(COPT) -g $(INCLUDES)
TESTCPPFLAGS = -std=c++11 $(COPT) -g $(TESTINCLUDES)
LDFLAGS = $(LIBPATH) -g $(LIBS) -Wall -Wextra -pthread
DEP = dep

OBJS_TEST := $(addprefix $(OUTPUT_PATH),$(patsubst %.$(C),%.$(OBJ),$(wildcard $(SOURCE_PATH_TEST)*.$(C))))
OBJS_CONTEXT := $(addprefix $(OUTPUT_PATH),$(patsubst %.$(C),%.$(OBJ),$(wildcard $(SOURCE_PATH_CONTEXT)*.$(C))))
OBJS_SEQ := $(addprefix $(OUTPUT_PATH),$(patsubst %.$(C),%.$(OBJ),$(wildcard $(SOURCE_PATH_SEQ)*.$(C))))
OBJS_SERVICE := $(addprefix $(OUTPUT_PATH),$(patsubst %.$(C),%.$(OBJ),$(wildcard $(SOURCE_PATH_SERVICE)*.$(C))))

all: pre-build main-build post-build

pre-build:
	@echo Pre-Building...
	mkdir -p $(OUTPUT_PATH)$(SOURCE_PATH_TEST)
	cp -u $(SOURCE_PATH_TEST)* $(OUTPUT_PATH)$(SOURCE_PATH_TEST)
	mkdir -p $(OUTPUT_PATH)$(SOURCE_PATH_CONTEXT)
	cp -u $(SOURCE_PATH_CONTEXT)* $(OUTPUT_PATH)$(SOURCE_PATH_CONTEXT)
	mkdir -p $(OUTPUT_PATH)$(SOURCE_PATH_SEQ)
	cp -u $(SOURCE_PATH_SEQ)* $(OUTPUT_PATH)$(SOURCE_PATH_SEQ)
	mkdir -p $(OUTPUT_PATH)$(SOURCE_PATH_SERVICE)
	cp -u $(SOURCE_PATH_SERVICE)* $(OUTPUT_PATH)$(SOURCE_PATH_SERVICE)
	
post-build:
	@echo Post-Building...
	@echo Done!

$(OUTPUT_PATH)$(SOURCE_ROOT)%.$(OBJ): $(SOURCE_ROOT)%.$(C)
	@echo Compiling...
	$(CCMD) -c $(CPPFLAGS) $< $(OBJFLAG)$@

$(OUTPUT_PATH)$(SOURCE_PATH_TEST)%.$(OBJ): $(SOURCE_PATH_TEST)%.$(C)
	@echo Compiling Test...
	$(CCMD) -c $(TESTCPPFLAGS) $< $(OBJFLAG)$@

main-build: $(OBJS_TEST) $(OBJS_CONTEXT) $(OBJS_SEQ) $(OBJS_SERVICE)
	@echo Linking...
	$(ACMD) rcs $(OUTPUT_PATH)$(STLIB).$(A) $(addprefix $(OUTPUT_PATH),$(filter $(SOURCE_ROOT)%,$^))
	$(CCMD) $(SOURCE_PATH_GOOGLETEST)gtest-all.$(OBJ) $(filter-out $(SOURCE_ROOT)%,$^) $(LDFLAGS) $(EXEFLAG)$(OUTPUT_PATH)$(EXE)

clean:
	rm -rf $(OUTPUT_PATH)*

rebuild: clean all

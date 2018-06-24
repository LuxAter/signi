SHELL = /bin/bash

DIR = $(SOURCE_DIR)
SUB_NAME = "Source"

LIB_FILES = $(filter-out ./main.cpp, $(shell find -name "*.cpp"))
EXE_FILES = $(shell find -name "main.cpp")

LIB_OBJ = $(LIB_FILES:%.cpp=$(BASE_PATH)/$(BUILD_DIR)/$(DIR)/%.o)
EXE_OBJ = $(EXE_FILES:%.cpp=$(BASE_PATH)/$(BUILD_DIR)/$(DIR)/%.o)

LIB_DEP = $(LIB_OBJ:.o=.d)
EXE_DEP = $(EXE_OBJ:.o=.d)

LIB = $(BASE_PATH)/$(BUILD_DIR)/lib$(NAME).a
EXE = $(BASE_PATH)/$(NAME)

define print
printf "%b%s%b\n" "$(2)" "$(1)" "$(NO_COLOR)"
endef

all: $(LIB) $(EXE)

.PHONY : lib
lib: $(LIB)


.PHONY : clean
clean:
	$(call print,Removing $(DIR),$(CLEAN_COLOR))
	if [ -d "$(BASE_PATH)/$(BUILD_DIR)/$(DIR)" ]; then rm $(BASE_PATH)/$(BUILD_DIR)/$(DIR) -r; fi
	$(call print,Removing $(shell basename $(LIB)),$(CLEAN_COLOR))
	if [ -e "$(LIB)" ]; then rm $(LIB); fi
	$(call print,Removing $(shell basename $(EXE)),$(CLEAN_COLOR))
	if [ -e "$(EXE)" ]; then rm $(EXE); fi

.PHONY : install
install:
	$(call print,Installing $(shell basename $(LIB)),$(INSTALL_COLOR));\
	sudo mkdir $(INSTALL_PATH)/lib/ -p;\
	sudo cp $(LIB) $(INSTALL_PATH)/lib/;\

.PHONY : uninstall
uninstall:
	$(call print,Uninstalling $(shell basename $(LIB)),$(INSTALL_COLOR));\
	sudo rm $(INSTALL_PATH)/lib/$(shell basename $(LIB));\

-include $(LIB_OBJ:.o=.d)

$(BASE_PATH)/$(BUILD_DIR)/$(DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(call print,Building $@,$(COMPILE_COLOR))
	$(COMPILER) $(COMMON_INCLUDE) $(CXXFLAGS) $(GCOV_FLAG) $< -o $@

$(LIB): lib_start $(LIB_OBJ)
	$(call print,Linking $(shell basename $(LIB)),$(LINK_COLOR))
	if [[ ! -z "$(LIB_OBJ)" ]]; then ar rcs $(LIB) $(LIB_OBJ); fi
	mkdir libpng && cd libpng && ar x $(BASE_PATH)/$(BUILD_DIR)/libpng/lib/libpng.a
	mkdir libjpeg && cd libjpeg && ar x $(BASE_PATH)/$(BUILD_DIR)/libjpeg/lib/libjpeg.a
	ar -qc $(LIB) libpng/*.o libjpeg/*.o
	rm -rf libpng/ libjpeg/

.PHONY : lib_start
lib_start:
	$(call print,$(SUB_NAME) Library,$(TARGET_COLOR))


$(EXE): exe_start $(LIB) $(EXE_OBJ)
	$(call print,Linking $(shell basename $(EXE)),$(LINK_COLOR))
	if [ -e "$(LIB)" ]; then $(COMPILER) $(EXE_OBJ) $(LIB) $(LINK) $(GCOV_LINK) -o $(EXE); fi
	if [ ! -e "$(LIB)" ]; then $(COMPILER) $(EXE_OBJ) $(LINK) $(GCOV_LINK) -o $(EXE); fi

.PHONY : exe_start
exe_start:
	$(call print,$(SUB_NAME) Executable,$(TARGET_COLOR)) 

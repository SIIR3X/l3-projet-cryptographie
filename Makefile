###########################################################################
#                                                                         #
#   Makefile                                                              #
#                                                                         #
#   Projet de synthèse de L3                                              #
#                                                                         #
###########################################################################

###########################################################################
################################ ARGUMENTS ################################
###########################################################################

# Arguments pour l'exécution du programme
MAIN_ARGS = 
TEST_ARGS =


###########################################################################
############################## EXECUTABLES ################################
###########################################################################

# Nom des exécutables
MAIN_EXEC = aes.exe
TEST_EXEC = tests.exe


###########################################################################
############################### COMPILATEUR ###############################
###########################################################################

# Compilateur
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -I$(INC_DIR)
TEST_CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INC_DIR) -I$(GTEST_INCLUDE_DIR)


###########################################################################
############################### OPTIONS ###################################
###########################################################################

# Flags de compilation
LDFLAGS =
TEST_LDFLAGS = $(LDFLAGS) -L$(GTEST_LIB_DIR) -lgtest -lgtest_main


###########################################################################
################################ FONCTIONS ################################
###########################################################################

# Fonction permettant de récuperer tous les fichiers d'un dossier et de ses sous-dossiers
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# Fonction permettant de créer un dossier
define MKDIR
@if not exist "$(subst /,\,$(patsubst %/,%,$(1)))" mkdir "$(subst /,\,$(patsubst %/,%,$(1)))"
endef

# Fonction permettant de nettoyer un dossier
define CLEAN_DIR
@if exist "$(subst /,\,$(patsubst %/,%,$(1)))" ( \
    del /q "$(subst /,\,$(patsubst %/,%,$(1)))\*" && \
    for /d %%x in ("$(subst /,\,$(patsubst %/,%,$(1)))\*") do rd /s /q "%%x" )
endef

# Fonction permettant de supprimer un fichier
define DELETE_FILE
@if exist "$(subst /,\,$(patsubst %/,%,$(1)))" (del /q "$(subst /,\,$(patsubst %/,%,$(1)))")
endef


###########################################################################
################################ DOSSIERS #################################
###########################################################################

# Dossiers C++
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Dossiers Google Test
GTEST_INCLUDE_DIR = "D:\googletest\googletest\include"
GTEST_LIB_DIR = "D:\googletest\build\lib"


###########################################################################
################################ FICHIERS #################################
###########################################################################

# Fichiers C++
SRC_FILES := $(call rwildcard,$(SRC_DIR)/,*.cpp)
TEST_FILES := $(call rwildcard,$(TEST_DIR)/,*.cpp)

# Chemins vers les exécutables
MAIN_PROG = $(BIN_DIR)/$(MAIN_EXEC)
TEST_PROG = $(BIN_DIR)/$(TEST_EXEC)


###########################################################################
################################# OBJETS ##################################
###########################################################################

# Objets C++
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_FILES))

###########################################################################
############################### COMPILATION ###############################
###########################################################################

# Edition des liens des fichiers objets
$(MAIN_PROG): $(OBJS) $(GLAD_OBJ)
	$(call MKDIR, $(BIN_DIR))
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(call MKDIR,$(dir $@))
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Edition des liens des fichiers objets de test
$(TEST_PROG): $(OBJS) $(TEST_OBJS)
	$(call MKDIR,$(BIN_DIR))
	$(CXX) $(TEST_CXXFLAGS) -o $@ $(filter-out $(OBJ_DIR)/main.o, $^) $(TEST_LDFLAGS) $(LDLIBS)

# Compilation des fichiers objets de test
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(call MKDIR,$(dir $@))
	$(CXX) $(TEST_CXXFLAGS) -c -o $@ $<

###########################################################################
################################ COMMANDES ################################
###########################################################################

.PHONY: all rebuild run test clean delete deletetest cleanall

all: $(MAIN_PROG)

rebuild: clean all

run: $(MAIN_PROG)
	$(MAIN_PROG) $(MAIN_ARGS)

test: $(TEST_PROG)
	$(TEST_PROG) $(TEST_ARGS)

clean:
	$(call CLEAN_DIR, $(OBJ_DIR))
	$(call CLEAN_DIR, $(BIN_DIR))
	$(call CLEAN_DIR, $(JAVA_BIN_DIR))

delete:
	$(call DELETE_FILE, $(MAIN_PROG))

deletetest:
	$(call DELETE_FILE, $(TEST_PROG))

cleanall: clean

###########################################################################
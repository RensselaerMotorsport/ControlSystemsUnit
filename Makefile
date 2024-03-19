# Compiler settings
CXX = g++
CXXFLAGS = -g -O0 -IIncludes -lJetsonGPIO -lpthread -lm

# SOURCES
SRC_DIRS = $(shell find Frameworks -type d) Tests
SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

# OBJECTS
OBJ_DIR = obj
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(notdir $(SOURCES:.cpp=.o)))
# Dependencies
DEPS = $(OBJECTS:.o=.d)
# External object files
C_OBJECTS = High-Precision_AD_HAT/c/bin/*.o

# OUTPUTS
# VCU_OUTPUT = VCU.out TODO: Add functionality in future

# BUILD RULES
# Default build rule
all: $(VCU_OUTPUT)

# Pattern rule for any test
%.out: $(OBJ_DIR)/%.o $(OBJECTS) waveshare
	$(CXX) $< $(filter-out $(OBJ_DIR)/main.o,$(OBJECTS)) $(C_OBJECTS) -o $@ $(CXXFLAGS)

# Rule to compile .cpp to .o
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Include source directories in vpath to find corresponding .cpp files
vpath %.cpp $(SRC_DIRS)

# External library compilation
waveshare:
	make -C High-Pricision_AD_HAT/c JETSON

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(TEST_OUTPUTS) $(VCU_OUTPUT)
	make -C High-Precision_AD_HAT/c clean

-include $(DEPS)

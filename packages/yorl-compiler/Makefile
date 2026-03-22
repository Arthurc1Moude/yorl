# Makefile for Yorl Executive Tools (yolex)
# Modern build system using Flex and Bison

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
FLEX = flex
BISON = bison

# Target executable
TARGET = yolex

# Source files
LEX_SRC = yorl.l
YACC_SRC = yorl.y
JSON_SRC = yorl_json.c
VERSION_SRC = version.c

# Generated files
LEX_OUT = lex.yy.c
YACC_OUT = yorl.tab.c
YACC_HEADER = yorl.tab.h

# Object files
OBJS = $(LEX_OUT:.c=.o) $(YACC_OUT:.c=.o) yorl_json.o version.o

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build complete! Run with: ./$(TARGET) <file.yorl>"

# Generate parser from Bison
$(YACC_OUT) $(YACC_HEADER): $(YACC_SRC)
	@echo "Generating parser with Bison..."
	$(BISON) -d $(YACC_SRC)

# Generate lexer from Flex
$(LEX_OUT): $(LEX_SRC) $(YACC_HEADER)
	@echo "Generating lexer with Flex..."
	$(FLEX) $(LEX_SRC)

# Compile JSON module
yorl_json.o: $(JSON_SRC) yorl_json.h $(YACC_HEADER)
	@echo "Compiling JSON module..."
	$(CC) $(CFLAGS) -c $(JSON_SRC) -o $@

# Compile version module
version.o: $(VERSION_SRC) version.h
	@echo "Compiling version module..."
	$(CC) $(CFLAGS) -c $(VERSION_SRC) -o $@

# Compile object files
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(TARGET) $(OBJS) $(LEX_OUT) $(YACC_OUT) $(YACC_HEADER)
	rm -f *.o

# Clean and rebuild
rebuild: clean all

# Install (optional)
install: $(TARGET)
	@echo "Installing $(TARGET) to /usr/local/bin..."
	sudo cp $(TARGET) /usr/local/bin/
	@echo "Installation complete!"

# Uninstall
uninstall:
	@echo "Uninstalling $(TARGET)..."
	sudo rm -f /usr/local/bin/$(TARGET)

# Test with example files
test: $(TARGET)
	@echo "Testing with png-example.yorl..."
	./$(TARGET) png-example.yorl
	@echo ""
	@echo "Testing with test-example.yorl..."
	./$(TARGET) test-example.yorl

# Help
help:
	@echo "Yorl Executive Tools (yolex) - Makefile"
	@echo "========================================"
	@echo ""
	@echo "Targets:"
	@echo "  all       - Build yolex (default)"
	@echo "  clean     - Remove build artifacts"
	@echo "  rebuild   - Clean and rebuild"
	@echo "  install   - Install to /usr/local/bin"
	@echo "  uninstall - Remove from /usr/local/bin"
	@echo "  test      - Run tests with example files"
	@echo "  help      - Show this help message"
	@echo ""
	@echo "Usage:"
	@echo "  make              # Build yolex"
	@echo "  make test         # Run tests"
	@echo "  ./yolex file.yorl # Parse a Yorl file"

.PHONY: all clean rebuild install uninstall test help

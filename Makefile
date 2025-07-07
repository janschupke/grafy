CC=g++
CFLAGS=-c -Wall -g -O0
ODIR = bin
SDIR = src
OUT = grafy

_OBJS = \
 Util.o\
 main.o\
 Matrix.o\
 Graph.o\
 Tree.o\
 OutputProcessor.o\
 FileOutputProcessor.o\
 TerminalOutputProcessor.o\
 InputProcessor.o

OBJS = $(patsubst %, $(ODIR)/%, $(_OBJS))

all: $(OUT); @find $(SDIR) -type f -name '*[c|h]pp' -exec wc -l {} \; |\
 awk '{ sum=sum+$$1 } END { print "", sum, "lines." }'

$(ODIR)/%.o: $(SDIR)/util/%.cpp;
	@mkdir bin 2>/dev/null;\
	$(CC) $(CFLAGS) -o $@ $<;\
	echo -n "."

$(ODIR)/%.o: $(SDIR)/model/%.cpp;
	@mkdir bin 2>/dev/null;\
	$(CC) $(CFLAGS) -o $@ $<;\
	echo -n "."

$(ODIR)/%.o: $(SDIR)/io/%.cpp;
	@mkdir bin 2>/dev/null;\
	$(CC) $(CFLAGS) -o $@ $<;\
	echo -n "."

$(ODIR)/%.o: $(SDIR)/%.cpp;
	@mkdir bin 2>/dev/null;\
	$(CC) $(CFLAGS) -o $@ $<;\
	echo -n "."

$(OUT): $(OBJS);
	@$(CC) $(OBJS) -o $(OUT);\
	echo -n "."

.PHONY: install
.PHONY: uninstall
.PHONY: clean

install: ;
	@cp $(OUT) /usr/bin

uninstall: ;
	@rm /usr/bin/$(OUT)

clean: ;
	@rm -rf $(OUT) bin

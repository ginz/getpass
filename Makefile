DEST = /usr/local/bin/
GP = gen_pass
TA = text_analysis

all: $(GP) $(TA)

$(GP): $(GP).c
	gcc $(GP).c -o $(GP) -O2

$(TA): $(TA).c
	gcc $(TA).c -o $(TA) -O2

clean:
	rm $(GP)
	rm $(TA)

install: $(GP) $(TA)
	echo copying executables to $(DEST)
	cp $(GP) $(DEST)
	cp $(TA) $(DEST)

uninstall:
	rm $(DEST)/$(GP)
	rm $(DEST)/$(TA)


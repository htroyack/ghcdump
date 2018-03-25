all: genericdump32 elf.32.dump elf.64.dump pe.32.dump pe.64.dump win.wine.log

genericdump32: genericdump.c
	clang -m32 -ggdb $< -o $@

genericdump: genericdump.c
	clang -m64 -ggdb $< -o $@

elf.32: hello.c
	clang -m32 $< -o $@

elf.64: hello.c
	clang -m64 $< -o $@

pe.32.exe: hello.c
	i686-w64-mingw32-gcc $< -o $@

pe.64.exe: hello.c
	x86_64-w64-mingw32-gcc $< -o $@

elf.32.dump: elf.32 genericdump
	./genericdump $< templates/elf > $@

elf.64.dump: elf.64 genericdump
	./genericdump $< templates/elf > $@

pe.32.dump: pe.32.exe genericdump
	./genericdump $< templates/IMAGE_DOS_HEADER > $@

pe.64.dump: pe.64.exe genericdump
	./genericdump $< templates/IMAGE_DOS_HEADER > $@

win.wine.log: pe.32.exe
	wine $< > $@
	./$< >> $@

clean:
	rm -rf genericdump32 genericdump
	rm -rf elf.32 elf.64 pe.32.exe pe.64.exe
	rm -rf elf.32.dump elf.64.dump pe.32.dump pe.64.dump
	rm -rf win.wine.log

MAKE_COMMAND = make
TOOLCHAIN_PREFIX = /opt/psx-tools/
EXAMPLES_VMODE = VMODE_PAL
EXE_SUFFIX = 
CFLAGS = 

all:
	mkdir cd_root
	psx-gcc -DEXAMPLES_VMODE=$(EXAMPLES_VMODE) -o test.elf test.c
	elf2exe test.elf test.exe
	cp test.exe cd_root
	systemcnf test.exe > cd_root/system.cnf
	mkisofs -o test.hsf -V TEST -sysid PLAYSTATION cd_root
	mkpsxiso test.hsf test.bin /usr/local/psxsdk/share/licenses/infousa.dat
	rm -f test.hsf
	
clean:
	rm -f test.bin test.cue test.exe test.elf
	rm -fr cd_root/*
ASSEMBLER = ml.exe
COMPILER  = cl.exe
LINKER = link.exe

OBJS = main.obj crc32.obj

ASM_OPTION = /nologo /c /Cx /Cp /coff
C_OPTION = /nologo /TP /Ox /Wall
LINKER_OPTION = /nologo /libpath:lib

crc32.exe: $(OBJS)
	$(LINKER) $(LINKER_OPTION) $(OBJS) /out:crc32.exe

crc32.obj: crc32.asm
	$(ASSEMBLER) $(ASM_OPTION) /c crc32.asm

main.obj: main.cpp
	$(COMPILER) $(C_OPTION) /c main.cpp

clean:
	del crc32.obj
	del crc32.exe

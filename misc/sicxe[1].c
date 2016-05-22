#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXERRORS 26
/* SIZE OF ARRAY OF ERROR FLAGS */
#define MAXOPS  59
/* SIZE OF OPCODE TABLE */
#define SYMTABLIMIT 100
/* SIZE OF SYMBOL TABLE */
const char blank6[6] = "      ";
const char blank8[8] = "        ";
const char blank18[18] = "                  ";
const char blank30[30] = "                              ";
const char blank31[31] = "                               ";
const char quote = '\'';

typedef char char4[4];
typedef char char6[6];
typedef char char8[8];
typedef char char18[18];
typedef char char30[30];
typedef char char31[31];
typedef char char50[50];
typedef char char66[66];
enum eboolean{ false = 0, true = 1};
typedef enum eboolean boolean;

typedef struct
/* SOURCE LINE AND SUBFIELDS */
{
	char66 line;
	boolean comline;
	char8 labl;
	char6 operation;
	char18 operand;
	char31 comment;
}sourcetype;

typedef struct
/* OBJECT CODE, LENGTH, AND TYPE */
{
	enum {headrec, textrec, endrec, none} rectype;
	int objlength;
	char30 objcode;
}objtype;

typedef struct
/* MODIFICATION RECORD */
{
	int start_loc;
	int add_length;
	char plus_minus;
	char6 symbol;
   int csect;
}modtype;

typedef struct{char8 symbol;  int address; int csect;} symtabtype[SYMTABLIMIT];
typedef struct{char18 literal; int address; int litpool; char6 objcode; int length;} littabtype[SYMTABLIMIT];
typedef struct{char6 mnemonic; int opcode;} optabtype[MAXOPS];
typedef boolean errtype[MAXERRORS];
enum elitreqtype {print_lis, print_obj, store_operand, store_address, search_littab, last_litreqtype};
typedef enum elitreqtype litreqtype;
enum esymreqtype {search, store, last_symreqtype};
typedef enum esymreqtype symreqtype;
enum esymrettype {found, notfound, added, duplicate, tablefull, last_symrettype};
typedef enum esymrettype symrettype;
enum eintreqtype {readline, writeline, last_intreqtype};
typedef enum eintreqtype intreqtype;
enum eintrettype {normal, endfile, last_intrettype};
typedef enum eintrettype intrettype;
enum eoprettype {validop, invalidop, last_oprettype};
typedef enum eoprettype oprettype;

void pass_1(void);
void pass_2(void);
void access_symtab(symreqtype requestcode, symrettype *returncode, char8 symbol, int *address);
void numtohex (int num, char4 *hexstr);

FILE *srcfile, *objfile, *lisfile, *intfile;
/* INPUT AND OUTPUT FILES */

sourcetype source;
/* SOURCE LINE AND SUBFIELDS */
objtype objct;
/* OBJECT CODE FOR CURRENT STMT */
modtype modrec[SYMTABLIMIT];
/* MODIFICATION RECORDS FOR RELOCATABLE PROGRAMS */
littabtype littab;
/* LITERAL POOL */
symtabtype symtab;
/* SYMBOL TABLE */
optabtype optab;
/* OPCODE TABLE */
int ascii[256];
/* ASCII CONVERSION TABLE */
errtype errorflags;
/* ERROR FLAGS FOR CURRENT STMT */
boolean errorsfound;
/* TRUE IF ANY ERRORS IN CURRENT STMT */
char50 errmsg[MAXERRORS];
int locctr;
/* CURRENT LOCATION */
char6 progname[10];
/* PROGRAM NAME */
int proglength[10];
/* PROGRAM LENGTH */
int progstart;
/* STARTING ADDRESS OF PROGRAM */
boolean firststmt,endfound;
/* GLOBALS USED ONLY BY P2_ASSEMBLE_INST */
int textstart,textaddr,textlength;
char textarray[60];
/* GLOBALS USED ONLY BY P2_WRITE_OBJ */
int pc = 0, base = 0;
/* CURRENT VALUE OF PC AND BASE REGISTER */
boolean relocatable = false;
/* IS PROGRAM RELOCATABLE */
int current_mod = 0;
/* INDICATES CURRENT MODIFICATION RECORD */
int litpool = 0, litpool1, litpool2;
/* VARIABLES USED FOR LITERALS */
int linenum = 0;
/* CURRENT LINE NUMBER FOR LISTING */
int cur_csect = 0;
/* CURRENT CONTROL SECTION */
char6 extdef[10][5];
/* CONTAINS THE EXTDEFS OF THE CURRENT CONTROL SECTION */
char6 extref[10][5];
/* CONTAINS THE EXTREFS OF THE CURRENT CONTROL SECTION */
boolean def[10];
boolean ref[10];
boolean newhead = false;

int main(void)
{
/* ASSEMBLER */
/* THIS IS THE MAIN FUNCTION FOR THE ASSEMBLER. IT CONSISTS OF AN
INITIALIZATION SECTION, FOLLOWED BY CALLS TO PASS_1 AND PASS_2 */

	symrettype symret;
	int regadd, i;
	char6 tempm;
	int tempo;
	boolean switchop;

	/* INITIALIZATION OF SYMBOL TABLE */
	for(i = 0; i < SYMTABLIMIT; i ++)
	{
		strncpy(symtab[i].symbol, blank8, 8);
		symtab[i].address = 0;
		symtab[i].csect = 0;
		strncpy(littab[i].literal, blank18, 18);
		littab[i].address = 0;
		littab[i].litpool = -1;
		strncpy(littab[i].objcode, blank6, 6);
		littab[i].length = 0;
		modrec[i].start_loc = 0;
		modrec[i].add_length = 0;
		modrec[i].plus_minus = ' ';
		strncpy(modrec[i].symbol, blank6, 6);
      modrec[i].csect = 0;
	}
	for(i = 0; i < 10; i++)
	{
		def[i] = false;
		ref[i] = false;
		proglength[i] = 0;
      strncpy(progname[i], blank6, 6);
	}

	/* INITIALIZATION OF OPCODE TABLE. THE ENTRIES IN THE TABLE ARE FIRST
	INITIALIZED TO CONTAIN MNEMONICS AND MACHINE OPCODES. THESE ENTRIES
	ARE THEN SORTED (USING A SIMPLE BUBBLE SORT) TO BE SURE THEY ARE IN
	ORDER BY MNEMONIC. THIS SORT PROCESS IS NECESSARY BECAUSE
	OF THE DIFFERENT PLACEMENT OF THE CHARACTER CODE FOR BLANK IN THE
	COLLATING SEQUENCE FOR DIFFERENT COMPUTERS */

	strncpy(optab[0].mnemonic, "ADD   ", 6);
	optab[0].opcode = 24;
	strncpy(optab[1].mnemonic, "ADDF  ", 6);
	optab[1].opcode = 88;
	strncpy(optab[2].mnemonic, "ADDR  ", 6);
	optab[2].opcode = 144;
	strncpy(optab[3].mnemonic, "AND   ", 6);
	optab[3].opcode = 64;
	strncpy(optab[4].mnemonic, "CLEAR ", 6);
	optab[4].opcode = 180;
	strncpy(optab[5].mnemonic, "COMP  ", 6);
	optab[5].opcode = 40;
	strncpy(optab[6].mnemonic, "COMPF ", 6);
	optab[6].opcode = 136;
	strncpy(optab[7].mnemonic, "COMPR ", 6);
	optab[7].opcode = 160;
	strncpy(optab[8].mnemonic, "DIV   ", 6);
	optab[8].opcode = 36;
	strncpy(optab[9].mnemonic, "DIVF  ", 6);
	optab[9].opcode = 100;
	strncpy(optab[10].mnemonic, "DIVR  ", 6);
	optab[10].opcode = 156;
	strncpy(optab[11].mnemonic, "FIX   ", 6);
	optab[11].opcode = 196;
	strncpy(optab[12].mnemonic, "FLOAT ", 6);
	optab[12].opcode = 192;
	strncpy(optab[13].mnemonic, "HIO   ", 6);
	optab[13].opcode = 244;
	strncpy(optab[14].mnemonic, "J     ", 6);
	optab[14].opcode = 60;
	strncpy(optab[15].mnemonic, "JEQ   ", 6);
	optab[15].opcode = 48;
	strncpy(optab[16].mnemonic, "JGT   ", 6);
	optab[16].opcode = 52;
	strncpy(optab[17].mnemonic, "JLT   ", 6);
	optab[17].opcode = 56;
	strncpy(optab[18].mnemonic, "JSUB  ", 6);
	optab[18].opcode = 72;
	strncpy(optab[19].mnemonic, "LDA   ", 6);
	optab[19].opcode =  0;
	strncpy(optab[20].mnemonic, "LDB   ", 6);
	optab[20].opcode = 104;
	strncpy(optab[21].mnemonic, "LDCH  ", 6);
	optab[21].opcode = 80;
	strncpy(optab[22].mnemonic, "LDF   ", 6);
	optab[22].opcode = 112;
	strncpy(optab[23].mnemonic, "LDL   ", 6);
	optab[23].opcode =  8;
	strncpy(optab[24].mnemonic, "LDS   ", 6);
	optab[24].opcode = 108;
	strncpy(optab[25].mnemonic, "LDT   ", 6);
	optab[25].opcode = 116;
	strncpy(optab[26].mnemonic, "LDX   ", 6);
	optab[26].opcode =  4;
	strncpy(optab[27].mnemonic, "LPS   ", 6);
	optab[27].opcode = 208;
	strncpy(optab[28].mnemonic, "MUL   ", 6);
	optab[28].opcode = 32;
	strncpy(optab[29].mnemonic, "MULF  ", 6);
	optab[29].opcode = 96;
	strncpy(optab[30].mnemonic, "MULR  ", 6);
	optab[30].opcode = 152;
	strncpy(optab[31].mnemonic, "NORM  ", 6);
	optab[31].opcode = 200;
	strncpy(optab[32].mnemonic, "OR    ", 6);
	optab[32].opcode = 68;
	strncpy(optab[33].mnemonic, "RD    ", 6);
	optab[33].opcode = 216;
	strncpy(optab[34].mnemonic, "RMO   ", 6);
	optab[34].opcode = 172;
	strncpy(optab[35].mnemonic, "RSUB  ", 6);
	optab[35].opcode = 76;
	strncpy(optab[36].mnemonic, "SHIFTL", 6);
	optab[36].opcode = 164;
	strncpy(optab[37].mnemonic, "SHIFTR", 6);
	optab[37].opcode = 168;
	strncpy(optab[38].mnemonic, "SIO   ", 6);
	optab[38].opcode = 240;
	strncpy(optab[39].mnemonic, "SSK   ", 6);
	optab[39].opcode = 236;
	strncpy(optab[40].mnemonic, "STA   ", 6);
	optab[40].opcode = 12;
	strncpy(optab[41].mnemonic, "STB   ", 6);
	optab[41].opcode = 120;
	strncpy(optab[42].mnemonic, "STCH  ", 6);
	optab[42].opcode = 84;
	strncpy(optab[43].mnemonic, "STF   ", 6);
	optab[43].opcode = 128;
	strncpy(optab[44].mnemonic, "STI   ", 6);
	optab[44].opcode = 212;
	strncpy(optab[45].mnemonic, "STL   ", 6);
	optab[45].opcode = 20;
	strncpy(optab[46].mnemonic, "STS   ", 6);
	optab[46].opcode = 124;
	strncpy(optab[47].mnemonic, "STSW  ", 6);
	optab[47].opcode = 232;
	strncpy(optab[48].mnemonic, "STT   ", 6);
	optab[48].opcode = 132;
	strncpy(optab[49].mnemonic, "STX   ", 6);
	optab[49].opcode = 16;
	strncpy(optab[50].mnemonic, "SUB   ", 6);
	optab[50].opcode = 28;
	strncpy(optab[51].mnemonic, "SUBF  ", 6);
	optab[51].opcode = 92;
	strncpy(optab[52].mnemonic, "SUBR  ", 6);
	optab[52].opcode = 148;
	strncpy(optab[53].mnemonic, "SVC   ", 6);
	optab[53].opcode = 176;
	strncpy(optab[54].mnemonic, "TD    ", 6);
	optab[54].opcode = 224;
	strncpy(optab[55].mnemonic, "TIO   ", 6);
	optab[55].opcode = 248;
	strncpy(optab[56].mnemonic, "TIX   ", 6);
	optab[56].opcode = 44;
	strncpy(optab[57].mnemonic, "TIXR  ", 6);
	optab[57].opcode = 184;
	strncpy(optab[58].mnemonic, "WD    ", 6);
	optab[58].opcode = 220;
	switchop = true;
	while(switchop)
	{
		switchop = false;
		for(i = 0; i < MAXOPS-1; i ++)
			if(optab[i].mnemonic > optab[i+1].mnemonic)
			{
				switchop = true;
				strncpy(tempm, optab[i+1].mnemonic, 6);
				tempo = optab[i+1].opcode;
				strncpy(optab[i+1].mnemonic, optab[i].mnemonic, 6);
				optab[i+1].opcode = optab[i].opcode;
				strncpy(optab[i].mnemonic, tempm, 6);
				optab[i].opcode = tempo;
			}
	}

	/* INITIALIZATION OF ERROR MESSAGES */
	strncpy(errmsg[0], "ILLEGAL FORMAT IN LABEL FIELD                     ", 50);
	strncpy(errmsg[1], "MISSING OPERATION CODE                            ", 50);
	strncpy(errmsg[2], "ILLEGAL FORMAT IN OPERATION FIELD                 ", 50);
	strncpy(errmsg[3], "MISSING OR MISPLACED OPERAND IN START STATEMENT   ", 50);
	strncpy(errmsg[4], "ILLEGAL OPERAND IN START STATEMENT                ", 50);
	strncpy(errmsg[5], "ILLEGAL OPERAND IN BYTE STATEMENT                 ", 50);
	strncpy(errmsg[6], "ODD LENGTH HEX STRING IN BYTE STATEMENT           ", 50);
	strncpy(errmsg[7], "MISSING OR MISPLACED OPERAND IN BYTE STATEMENT    ", 50);
	strncpy(errmsg[8], "MISSING OR MISPLACED OPERAND IN RESW STATEMENT    ", 50);
	strncpy(errmsg[9], "ILLEGAL OPERAND IN RESW STATEMENT                 ", 50);
	strncpy(errmsg[10], "MISSING OR MISPLACED OPERAND IN RESB STATEMENT    ", 50);
	strncpy(errmsg[11], "ILLEGAL OPERAND IN RESB STATEMENT                 ", 50);
	strncpy(errmsg[12], "DUPLICATE LABEL DEFINITION                        ", 50);
	strncpy(errmsg[13], "TOO MANY SYMBOLS IN SOURCE PROGRAM                ", 50);
	strncpy(errmsg[14], "DUPLICATE OR MISPLACED START STATEMENT            ", 50);
	strncpy(errmsg[15], "MISSING OR MISPLACED START STATEMENT              ", 50);
	strncpy(errmsg[16], "ILLEGAL OPERAND IN WORD STATEMENT                 ", 50);
	strncpy(errmsg[17], "MISSING OR MISPLACED OPERAND IN WORD STATEMENT    ", 50);
	strncpy(errmsg[18], "MISSING OR MISPLACED OPERAND IN END STATEMENT     ", 50);
	strncpy(errmsg[19], "ILLEGAL OPERAND IN END STATEMENT                  ", 50);
	strncpy(errmsg[20], "UNDEFINED SYMBOL IN OPERAND                       ", 50);
	strncpy(errmsg[21], "STATEMENT SHOULD NOT FOLLOW END STATEMENT         ", 50);
	strncpy(errmsg[22], "ILLEGAL OPERAND FIELD                             ", 50);
	strncpy(errmsg[23], "UNRECOGNIZED OPERATION CODE                       ", 50);
	strncpy(errmsg[24], "MISSING OR MISPLACED OPERAND IN INSTRUCTION       ", 50);
	strncpy(errmsg[25], "REQUIRED DISPLACEMENT OUT OF RANGE                ", 50);

	/* INITIALIZATION OF ASCII CONVERSION TABLE */
	for(i = 0; i < 256; i ++)
		ascii[i] = i;
	/* END INITIALIZATION */

	/* INITIALIZE REGISTER NAMES IN SYMTAB */
	regadd = 0;
	access_symtab(store, &symret, "A       ", &regadd);
	regadd = 1;
	access_symtab(store, &symret, "X       ", &regadd);
	regadd = 2;
	access_symtab(store, &symret, "L       ", &regadd);
	regadd = 3;
	access_symtab(store, &symret, "B       ", &regadd);
	regadd = 4;
	access_symtab(store, &symret, "S       ", &regadd);
	regadd = 5;
	access_symtab(store, &symret, "T       ", &regadd);
	regadd = 6;
	access_symtab(store, &symret, "F       ", &regadd);
	regadd = 8;
	access_symtab(store, &symret, "PC      ", &regadd);
	regadd = 9;
	access_symtab(store, &symret, "SW      ", &regadd);

	pass_1();
	pass_2();

	return EXIT_SUCCESS;
}

void access_symtab(symreqtype requestcode, symrettype *returncode, char8 symbol, int *address)
{

/* THIS FUNCTION IS USED TO ACCESS THE SYMBOL TABLE FOR THE ASSEMBLY.
IF REQUESTCODE = SEARCH, THE SYMBOL PASSED AS A PARAMETER IS
SEARCHED FOR IN THE TABLE. IF THIS SYMBOL IS FOUND, RETURNCODE
IS SET TO FOUND, AND ADDRESS IS SET TO THE VALUE OF THE SYMBOL
(FROM THE SYMBOL TABLE). IF THE SYMBOL IS NOT FOUND IN THE TABLE,
RETURNCODE IS SET TO NOTFOUND.

IF REQUESTCODE = STORE, THE SYMBOL IS ADDED TO THE TABLE, WITH VALUE
GIVEN BY ADDRESS. IF THE SYMBOL IS ADDED NORMALLY, RETURNCODE IS
SET TO ADDED. IF THE SYMBOL ALREADY EXISTS IN THE TABLE, RETURNCODE
IS SET TO DUPLICATE (AND THE SYMBOL IS NOT ADDED). IF THE TABLE
IS ALREADY FULL, RETURNCODE IS SET TO TABLEFULL.

THE SYMBOL TABLE IS ORGANIZED AS A HASH TABLE. THE HASHING FUNCTION
SIMPLY SUMS THE ORDINAL VALUES OF ALL OF THE CHARACTERS IN THE
SYMBOL. COLLISIONS ARE HANDLED BY LINEAR PROBING. */

	boolean searching;
	int i, hash = 0, ptr;

	for(i = 0; i < 8; i ++)
		hash = hash + (unsigned char)(symbol[i]);
	hash = hash % (SYMTABLIMIT + 1);
	if(requestcode == search)
	{
		searching = true;
		ptr = hash;
		while(searching)
		{
			if(!strncmp(symtab[ptr].symbol, symbol, 8) && (symtab[ptr].csect == cur_csect))
			{
				*returncode = found;
				*address = symtab[ptr].address;
				searching = false;
			}
			else if(!strncmp(symtab[ptr].symbol, blank8, 8))
			{
				*returncode = notfound;
				*address = 0;
				searching = false;
			}
			else
			{
				ptr = (ptr + 1) % (SYMTABLIMIT + 1);
				if(ptr == hash)
				{
					*returncode = notfound;
					*address = 0;
					searching = false;
				}
			}
		}
	}
	else
	{
		searching = true;
		ptr = hash;
		while(searching)
		{
			if(!strncmp(symtab[ptr].symbol, symbol, 8) && (symtab[ptr].csect == cur_csect))
			{
				*returncode = duplicate;
				searching = false;
			}
			else if((!strncmp(symtab[ptr].symbol, symbol, 8) && (symtab[ptr].csect != cur_csect)) || !strncmp(symtab[ptr].symbol, blank8, 8))
			{
				*returncode = added;
				strncpy(symtab[ptr].symbol, symbol, 8);
				symtab[ptr].address = *address;
				symtab[ptr].csect = cur_csect;
				searching = false;
			}
			else
			{
				ptr = (ptr + 1) % (SYMTABLIMIT + 1);
				if(ptr == hash)
				{
					*returncode = tablefull;
					searching = false;
				}
			}
		}
	}
}

void access_littab(litreqtype requestcode, symrettype *returncode, char18 literal, int *address)
{
	boolean searching;
	int i, hash = 0, ptr, j, k, asciival;
   char hexchar;
	char4 temp;

	for(i = 0; i < 18; i ++)
		hash = hash + (unsigned char)(literal[i]);
	hash = hash % (SYMTABLIMIT + 1);
	if(requestcode == search_littab)
	{
		searching = true;
		ptr = hash;
		while(searching)
		{
			if(!strncmp(littab[ptr].literal, literal, 8))
			{
				*returncode = found;
				*address = littab[ptr].address;
				searching = false;
			}
			else if(!strncmp(littab[ptr].literal, blank8, 8))
			{
				*returncode = notfound;
				*address = 0;
				searching = false;
			}
			else
			{
				ptr = (ptr + 1) % (SYMTABLIMIT + 1);
				if(ptr == hash)
				{
					*returncode = notfound;
					*address = 0;
					searching = false;
				}
			}
		}
	}
	else if(requestcode == print_obj)
	{
		for(i = 0; i < SYMTABLIMIT; i++)
		{
			if(littab[i].litpool == litpool)
			{
				for(j = 0; j < littab[i].length; j ++)
					textarray[textlength+j] = littab[i].objcode[j];
				textlength = textlength + littab[i].length;
				textaddr = locctr + littab[i].length / 2;
			}
		}
	}
	else if(requestcode == print_lis)
	{
		for(i = 0; i < SYMTABLIMIT; i++)
		{
			if(littab[i].litpool == litpool)
			{
				if((linenum == 0) || (linenum == 5))
					fprintf(lisfile, "  %d ", linenum);
				else if(linenum < 100)
					fprintf(lisfile, " %d ", linenum);
				else
					fprintf(lisfile, "%d ", linenum);
				numtohex(littab[i].address,&temp);
				for(j = 0; j < 4; j++)
					fprintf(lisfile, "%c", temp[j]);
				fprintf(lisfile, " *");
				for(j = 1; j < 9; j++)
					fprintf(lisfile, " ");
				for(j = 0; j < 8; j++)
					fprintf(lisfile, "%c", littab[i].literal[j]);
				for(; j < 57; j++)
					fprintf(lisfile, " ");
				for(j = 0; j < 6; j++)
					fprintf(lisfile, "%c", littab[i].objcode[j]);
				fprintf(lisfile, "\n");
				linenum += 5;
			}
		}
	}
	else if(requestcode == store_operand)
	{
		searching = true;
		ptr = hash;
		while(searching)
		{
			if(!strncmp(littab[ptr].literal, literal, 18))
			{
				*returncode = duplicate;
				searching = false;
			}
			else if(!strncmp(littab[ptr].literal, blank18, 18))
			{
				*returncode = added;
				strncpy(littab[ptr].literal, literal, 18);
				littab[ptr].litpool = litpool;
				searching = false;
				if(source.operand[1] == 'C')
				{
					i = 0;
					j = 1;
					while(source.operand[2+j] != quote)
					{
						asciival = ascii[(unsigned char)(source.operand[2+j])];
						numtohex(asciival,&temp);
						littab[ptr].objcode[2*i] = temp[2];
						littab[ptr].objcode[2*i+1] = temp[3];
						i++;
						j++;
					}
					littab[ptr].length = 2 * i;
				}
				else
				/* OPERAND IS X'...' -- PACK HEX DIGITS INTO OBJECT CODE AND
				SET OBJECT TYPE = TEXTREC.  ERRORS DETECTED: 6 */
				{
					i = 0;
					j = 1;
					while(source.operand[2+j] != quote)
					{
						hexchar = source.operand[2+j];
						if(((hexchar >= '0') && (hexchar <= '9')) || ((hexchar >= 'A') && (hexchar <= 'F')))
							littab[ptr].objcode[i] = hexchar;
						i++;
						j++;
					}
					littab[ptr].length = i;
				}
			}
			else
			{
				ptr = (ptr + 1) % (SYMTABLIMIT + 1);
				if(ptr == hash)
				{
					*returncode = tablefull;
					searching = false;
				}
			}
		}
	}
	else
	{
		for(i = 0; i < SYMTABLIMIT; i++)
		{
			if(strncmp(littab[i].literal, blank18, 18) && littab[i].address == 0)
			{
				littab[i].address = locctr;
				if(littab[i].literal[1] == 'C')
				{
					j = 3;
					k = 0;
					while(littab[i].literal[j++] != quote)
						k++;
					locctr += k;
				}
				else /* littab[i].literal[1] == 'X' */
				{
					locctr += 1;
				}
			}
		}
	}
}

int hextonum (char18 str, int first, int *last, boolean *converror)
{

/* THIS FUNCTION EXAMINES THE STRING STR, BEGINNING WITH THE BYTE
POSITION INDICATED BY FIRST, FOR A HEXADECIMAL VALUE. THIS VALUE,
CONVERTED TO AN INT, IS RETURNED AS THE VALUE OF THE FUNCTION
AND LAST IS SET TO INDICATE THE NEXT CHARACTER IN STR AFTER THE
HEX VALUE THAT WAS FOUND. IF ANY SCANNING OR CONVERSION ERRORS
ARE DETECTED, CONVERROR IS SET TO TRUE. THE MAXIMUM LENGTH OF
THE HEX VALUE TO BE SCANNED IS 4 HEX DIGITS. */

	int n =  0, i = 0;
	boolean scanning = true;
	int hextonum_result;

	*converror = false;
	while(scanning)
	{
		if((str[first+i] >= '0') && (str[first+i] <= '9'))
			n = 16 * n + (unsigned char)(str[first+i]) - (unsigned char)('0');
		else if((str[first+i] >= 'A') && (str[first+i] <= 'F'))
			n = 16 * n + (unsigned char)(str[first+i]) - (unsigned char)('A') + 10;
		else if((str[first+i] == ' ') || (str[first+i] == ','))
			scanning = false;
		else
		{
			*converror = true;
			scanning = false;
		}
		i++;
		if(i > (first + 3))
			scanning = false;

	}
	*last = first + i;
	if(*converror)
		hextonum_result = 0;
	else
		hextonum_result = n;
	return hextonum_result;
}

int dectonum (char18 str, int first, int *last, boolean *converror)
{

/* THIS FUNCTIONS SCANS THE STRING STR, BEGINNING AT THE BYTE POSITION
GIVEN BY FIRST, FOR THE CHARACTER REPRESENTATION OF A DECIMAL VALUE.
THIS VALUE, CONVERTED TO NUMERIC, IS RETURNED AS THE VALUE OF THE
FUNCTION, AND LAST IS SET TO INDICATE THE NEXT CHARACTER IN STR AFTER
THE VALUE THAT WAS FOUND. IF ANY SCANNING OR CONVERSION ERRORS ARE
FOUND, CONVERROR IS SET TO TRUE. THE MAXIMUM LENGTH VALUE TO BE
SCANNED IS 4 DECIMAL DIGITS. */

	int n = 0, i = 0;
	boolean scanning = true;
	int dectonum_result;

	*converror = false;
	while(scanning)
	{
		if((str[first+i] >= '0') && (str[first+i] <= '9'))
			n = 10 * n + (unsigned char)(str[first+i]) - (unsigned char)('0');
		else if(str[first+i] == ' ')
			scanning = false;
		else
		{
			*converror = true;
			scanning = false;
		}
		i++;
		if(i > (first + 3))
			scanning = false;
	}
	*last = first + i - 1;
	if(*converror)
		dectonum_result = 0;
	else
		dectonum_result = n;
	return dectonum_result;
}

void numtohex (int num, char4 *hexstr)
{

/* THIS FUNCTION CONVERTS THE NUMERIC VALUE NUM INTO A HEXADECIMAL
CHARACTER STRING REPRESENTATION HEXSTR. */

	int i, j, k, x;
	int work4[4];
	boolean negative, carry;
	char temp[1];

	negative = false;
	carry = false;

	if(num < 0)
	{
		negative = true;
		num = abs(num);
	}
	for(i = 3; i >= 0; i --)
	{
		work4[i] = num % 16;
		num = num / 16;
	}
	for(i = 0; i < 4; i ++)
		if(work4[i] < 10)
			(*hexstr)[i] = (char)((unsigned char)('0') + work4[i]);
		else
			(*hexstr)[i] = (char)((unsigned char)('A') + work4[i] - 10);
	if(negative)
	{
		for(i = 3; i >= 0; i--)
		{
			temp[0] = (*hexstr)[i];
			if((x = atoi(temp)) < 8)
			{
				k = 15 - (x * 2);
				for(j = 0; j < k; j++)
				{
					if((*hexstr)[i] == '9')
						(*hexstr)[i] += 8;
					else
						(*hexstr)[i] += 1;
				}
			}
			else
			{
				k = 15 - (15 - x);
				for(j = 0; j < k; j++)
				{
					if((*hexstr)[i] == 'A')
						(*hexstr)[i] -= 8;
					else
						(*hexstr)[i] -= 1;
				}
			}
			if(carry)
			{
				if((*hexstr)[i] == '9')
					(*hexstr)[i] += 8;
				else if((*hexstr)[i] == 'F')
					(*hexstr)[i] = '0';
				else
					(*hexstr)[i] += 1;
				if((*hexstr)[i] == '0')
					carry = true;
				else
					carry = false;
			}
			if(i == 3)
			{
				if((*hexstr)[3] == '9')
					(*hexstr)[3] += 8;
				else if((*hexstr)[3] == 'F')
					(*hexstr)[i] = '0';
				else
					(*hexstr)[3] += 1;
				if((*hexstr)[3] == '0')
					carry = true;
			}
		}
	}
}

void access_int_file (intreqtype requestcode, intrettype *returncode, sourcetype *source, boolean *errorsfound, errtype *errorflags)
{

/* THIS FUNCTION IS USED TO ACCESS THE INTERMEDIATE FILE INTFILE.
IF REQUESTCODE = WRITELINE, THE CURRENT SOURCE PROGRAM LINE IS
WRITTEN, FOLLOWED BY A BOOLEAN VALUE (T OR F) THAT INDICATES
WHETHER THIS IS A COMMENT LINE, AND THE CURRENT LOCATION COUNTER
VALUE. FOR NON-COMMENT LINES, THE SUBFIELDS ARE ALSO WRITTEN
OUT, FOLLOWED BY THE VALUE OF ERRORSFOUND (T OR F). IF ERRORSFOUND
WAS TRUE, THIS IS FOLLOWED BY THE VALUES IN ERRORFLAGS.

IF REQUESTCODE = READLINE, THE VARIABLES DESCRIBED ABOVE ARE READ
FROM THE INTERMEDIATE FILE. VARIABLES THAT ARE NOT REPRESENTED
IN THE FILE (FOR EXAMPLE, SOURCE.LABL AND ERRORSFOUND FOR A COMMENT
LINE) ARE SET TO BLANK (FOR CHARACTER FIELDS) OR TO FALSE (FOR
BOOLEAN VARIABLES). IF THE END OF FILE HAS BEEN REACHED, RETURNCODE
IS SET TO ENDFILE.   OTHERWISE, IT IS SET TO NORMAL. */

	int i, j;
	boolean bool;
	char ch;
	char18 temp;
	symrettype retcode;
	char4 loc_ctr;

	if(requestcode == readline)
	{
		if(feof(intfile))
			*returncode = endfile;
		else
		{
			*returncode = normal;
			for(i = 0; i < 66; i ++)
				(*source).line[i] = fgetc(intfile);
			ch = fgetc(intfile);
			if(ch == 'T')
				(*source).comline = true;
			else
				(*source).comline = false;
			for(i = 0; i < 4; i++)
				temp[i] = fgetc(intfile);
			for(i = 4; i < 18; i++)
				temp[i] = ' ';
			locctr = hextonum(temp, 0, &j, &bool);
			pc = locctr;
			ch = fgetc(intfile);
			/* pick up '\n' at end of line */
			if((*source).comline)
			{
				strncpy((*source).labl, blank8, 8);
				strncpy((*source).operation, blank6, 6);
				strncpy((*source).operand, blank18, 18);
				strncpy((*source).comment, blank31, 31);
				*errorsfound = false;
				for(i = 0; i < MAXERRORS; i ++)
					*errorflags[i] = false;
			}
			else
			{
				for(i = 0; i < 8; i ++)
				{
					if(feof(intfile))
						*returncode = endfile;
					(*source).labl[i] = fgetc(intfile);
				}
				for(i = 0; i < 6; i ++)
					(*source).operation[i] = fgetc(intfile);
				for(i = 0; i < 18; i ++)
					(*source).operand[i] = fgetc(intfile);
				for(i = 0; i < 31; i ++)
					(*source).comment[i] = fgetc(intfile);
				ch = fgetc(intfile);
				if(ch == 'T')
					*errorsfound = true;
				else
					*errorsfound = false;
				if(*errorsfound)
				{
					for(i = 0; i < MAXERRORS; i ++)
					{
						ch = fgetc(intfile);
						if(ch == 'T')
							*errorflags[i] = true;
						else
							*errorflags[i] = false;
					}
				}
				else
					for(i = 0; i < MAXERRORS; i ++)
						*errorflags[i] = false;
				ch = fgetc(intfile);
				/* pick up '\n' at end of line */
			}
			if(!strncmp((*source).operation, "EQU   ", 6))
			{
				access_symtab(search, &retcode, (*source).labl, &locctr);
			}
		}
	}
	else
	{
		for(i = 0; i < 66; i ++)
			fprintf(intfile, "%c", (*source).line[i]);
		if((*source).comline)
			fprintf(intfile, "%c", 'T');
		else
			fprintf(intfile, "%c", 'F');
		numtohex(locctr, &loc_ctr);
		for(i = 0; i < 4; i++)
			fprintf(intfile, "%c", loc_ctr[i]);
		fprintf(intfile, "\n");
		if(!((*source).comline))
		{
			for(i = 0; i < 8; i ++)
				fprintf(intfile, "%c", (*source).labl[i]);
			for(i = 0; i < 6; i ++)
				fprintf(intfile, "%c", (*source).operation[i]);
			for(i = 0; i < 18; i ++)
				fprintf(intfile, "%c", (*source).operand[i]);
			for(i = 0; i < 31; i ++)
				fprintf(intfile, "%c", (*source).comment[i]);
			if(*errorsfound)
				fprintf(intfile, "%c\n", 'T');
			else
				fprintf(intfile, "%c\n", 'F');
		}
		if(*errorsfound)
		{
			for(i = 0; i < MAXERRORS; i ++)
				if((*errorflags)[i])
					fprintf(intfile, "%c", 'T');
				else
					fprintf(intfile, "%c", 'F');
			fprintf(intfile, "\n");
		}
	}
}

void p1_read_source (sourcetype *source, boolean *endofinput, boolean *errorsfound, errtype *errorflags)
{

/* THIS FUNCTION READS THE NEXT LINE FROM SRCFILE. IF THERE ARE NO
MORE LINES ON SRCFILE, ENDOFINPUT IS SET TO TRUE.
IF THE SOURCE STATEMENT CONTAINS A "." IN COLUMN 1, THEN
SOURCE.COMLINE IS SET TO TRUE. OTHERWISE, THE SUBFIELDS OF
THE STATEMENT (LABL, OPERATION, OPERAND, COMMENT) ARE SCANNED.
ERRORS THAT MAY BE DETECTED: 1, 2, 3 (SEE THE INITIALIZATION
OF THE ARRAY ERRMSG IN THE MAIN FUNCTION FOR ERROR DESCRIPTIONS) */

	int i,j;
	char temp;
	symrettype symtabret;

	if(feof(srcfile))
		*endofinput = true;
	else
	{
		for(i = 0; i < 66; i ++)
			(*source).line[i] = ' ';
		for(i = 0; i < MAXERRORS; i ++)
			(*errorflags)[i] = false;
		*errorsfound = false;
		i = 0;
		while((i < 66) && ((temp = fgetc(srcfile)) != '\n') && !feof(srcfile))
		{
			(*source).line[i] = temp;
			i++;
		}
		if((*source).line[0] == '.')
			(*source).comline = true;
		else
		(*source).comline = false;
		strncpy((*source).labl, blank8, 8);
		strncpy((*source).operation, blank6, 6);
		strncpy((*source).operand, blank18, 18);
		strncpy((*source).comment, blank31, 31);
		if(!(*source).comline)
		{
			i = 0;
			if(((*source).line[0] >= 'A') && ((*source).line[0] <= 'Z'))
			/* THERE IS A LABEL */
			{
				while((i < 8) && (((*source).line[i] >= 'A') && ((*source).line[i] <= 'Z')) ||
						(((*source).line[i] >= '0') && ((*source).line[i] <= '9')))
				{
					(*source).labl[i] = (*source).line[i];
					i++;
				}
			}
			for(j = i; j < 9; j ++)
				if((*source).line[j] != ' ')
				{
					*errorsfound = true;
					(*errorflags)[0] = true;
					/* ILLEGAL LABEL FIELD */
				}
			i = 9;
			if(((*source).line[i] >= 'A') && ((*source).line[i] <= 'Z'))
			/* THERE IS AN OPERATION CODE */
			{
				while((i < 15) && (((*source).line[i] >= 'A') && ((*source).line[i] <= 'Z')) ||
						(((*source).line[i] >= '0') && ((*source).line[i] <= '9')))
				{
					(*source).operation[i-9] = (*source).line[i];
					i++;
				}
			}
			else if((*source).line[i] == '+')
			{
				(*source).operation[i-9] = (*source).line[i++];
				while((i < 15) && (((*source).line[i] >= 'A') && ((*source).line[i] <= 'Z')) ||
						(((*source).line[i] >= '0') && ((*source).line[i] <= '9')))
				{
					(*source).operation[i-9] = (*source).line[i];
					i++;
				}
			}
			else
			{
				*errorsfound = true;
				(*errorflags)[1] = true;
				/* MISSING OPERATION CODE */
			}
			for(j = i; j < 17; j ++)
				if((*source).line[j] != ' ')
				{
					*errorsfound = true;
					(*errorflags)[2] = true;
					/* ILLEGAL OPERATION FIELD */
				}
			if(!strncmp((*source).operation, "EXTDEF", 6) || !strncmp((*source).operation, "EXTREF", 6))
			{
			/* ALL THE EXTERNAL DEFINES AND REFERENCES MAY NOT FIT IN THE OPERAND
			FIELD, SO PUT THEM IN THE COMMENT FIELD */
				i = 17;
				j = 0;
				if(!strncmp((*source).operation, "EXTDEF", 6))
					def[cur_csect] = true;
				if(!strncmp((*source).operation, "EXTREF", 6))
					ref[cur_csect] = true;
				while((j < 31) && ((*source).line[i] != ' '))
				{
					(*source).comment[j++] = (*source).line[i++];
				}
			}
			else
			{
				for(i = 17; i < 35; i ++)
					(*source).operand[i-17] = (*source).line[i];
				for(i = 35; i < 66; i ++)
					(*source).comment[i-35] = (*source).line[i];
			}
		}
		if((*source).operand[0] == '=')
		{
			access_littab(store_operand, &symtabret, (*source).operand, &i);
			litpool++;
		}
	}
}

void p1_assign_loc (sourcetype source, int locctr, int *newlocctr, boolean *errorsfound, errtype *errorflags)
{

/* THIS FUNCTION UPDATES THE LOCATION COUNTER VALUE BASED ON THE
TYPE OF STATEMENT BEING PROCESSED, PLACING THE UPDATED VALUE
IN NEWLOCCTR.       ERRORS DETECTED: 4, 5, 6, 7, 8, 9, 10, 11, 12 */

	boolean scanning,converror;
	int i,j,k,temploc,nwords,nbytes;
	symrettype symtabret;

	*newlocctr = locctr;

	if(!strncmp(source.operation, "START ", 6))
 /* START STATEMENT -- CONVERT STARTING ADDRESS AND STORE IN LOCCTR
ERRORS DETECTED: 4, 5 */
	{
		if(source.operand[0] == ' ')
		{
			*errorsfound = true;
			(*errorflags)[3] = true;
			/* MISSING OR MISPLACED OPERAND IN START STATEMENT */
		}
		else
		{
			temploc = hextonum(source.operand, 0, &i, &converror);
			if(converror)
			{
				*errorsfound = true;
				(*errorflags)[4] = true;
				/* ILLEGAL OPERAND IN START STATEMENT */
			}
			if(temploc == 0)
				relocatable = true;
			for(j = i; j < 18; j ++)
				if(source.operand[j] != ' ')
				{
					*errorsfound = true;
					(*errorflags)[4] = true;
					/* ILLEGAL OPERAND IN START STATEMENT */
				}
			if((!(*errorflags)[3]) && (!(*errorflags)[4]))
				*newlocctr = temploc;
		}
	}
	else if(!strncmp(source.operation, "CSECT ", 6))
	{
		*newlocctr = 0;
	}
	else if(!strncmp(source.operation, "WORD  ", 6))
	/* WORD STATEMENT -- ADD 3 TO LOCCTR */
	{
		*newlocctr = locctr + 3;
	}
	else if(!strncmp(source.operation, "BYTE  ", 6))
	/* BYTE STATEMENT -- ADD NUMBER OF CHARACTERS (FOR C'...') OR
	NUMBER OF HEX DIGITS DIVIDED BY 2 (FOR X'...') TO LOCCTR.
	ERRORS DETECTED: 6, 7, 8 */
	{
		if(source.operand[0] == 'C')
		{
			if(source.operand[1] == quote)
			{
				i = 2;
				scanning = true;
				while(scanning)
				{
					if(source.operand[i] == quote)
						scanning = false;
					else
					{
						i++;
						if(i > 18)
							scanning = false;
					}
				}
				if(i > 18)
				{
					*errorsfound = true;
					(*errorflags)[5] = true;
					/* ILLEGAL OPERAND IN BYTE STATEMENT */
				}
				for(j = i + 1; j < 18; j ++)
					if(source.operand[j] != ' ')
					{
						*errorsfound = true;
						(*errorflags)[5] = true;
						/* ILLEGAL OPERAND IN BYTE STMT */
					}
				if(!(*errorflags)[5])
					*newlocctr = locctr + i - 2;
			}
			else
			{
				*errorsfound = true;
				(*errorflags)[5] = true;
				/* ILLEGAL OPERAND IN BYTE STMT */
			}
		}
		else if(source.operand[0] == 'X')
		{
			if(source.operand[1] == quote)
			{
				i = 2;
				scanning = true;
				while(scanning)
				{
					if(source.operand[i] == quote)
						scanning = false;
					else
					{
						i++;
						if(i > 18)
							scanning = false;
					}
				}
				if(i > 18)
				{
					*errorsfound = true;
					(*errorflags)[5] = true;
					/* ILLEGAL OPERAND IN BYTE STATEMENT */
				}
				for(j = i + 1; j < 18; j ++)
					if(source.operand[j] != ' ')
					{
						*errorsfound = true;
						(*errorflags)[5] = true;
						/* ILLEGAL OPERAND IN BYTE STMT */
					}
				if(((i - 2) % 2) != 0)
				{
					*errorsfound = true;
					(*errorflags)[6] = true;
					/* ODD LENGTH HEX STRING IN BYTE STATEMENT */
				}
				if(!(*errorflags)[5])
					*newlocctr = locctr + (i - 2) / 2;
			}
			else
			{
				*errorsfound = true;
				(*errorflags)[5] = true;
				/* ILLEGAL OPERAND IN BYTE STMT */
			}
		}
		else
		{
			*errorsfound = true;
			if(source.operand[0] == ' ')
				(*errorflags)[7] = true;
				/* MISSING OR MISPLACED OPERAND IN BYTE STATEMENT */
			else
				(*errorflags)[5] = true;
				/* ILLEGAL OPERAND IN BYTE STATEMENT */
		}
	}
	else if(!strncmp(source.operation, "RESW  ", 6))
	/* RESW STATEMENT -- ADD 3 * (NUMBER OF WORDS RESERVED) TO LOCCTR.
	ERRORS DETECTED: 9, 10 */
	{
		if(source.operand[0] == ' ')
		{
			*errorsfound = true;
			(*errorflags)[8] = true;
			/* MISSING OR MISPLACED OPERAND IN RESW STATEMENT */
		}
		else
		{
			nwords = dectonum (source.operand,0,&i,&converror);
			if(converror)
			{
				*errorsfound = true;
				(*errorflags)[9] = true;
				/* ILLEGAL OPERAND IN RESW */
			}
			for(j = i + 1; j < 18; j ++)
				if(source.operand[j] != ' ')
				{
					*errorsfound = true;
					(*errorflags)[9] = true;
					/* ILLEGAL OPERAND IN RESW */
				}
			if(!(*errorflags)[9])
				*newlocctr = locctr + 3 * nwords;
		}
	}
	else if(!strncmp(source.operation, "RESB  ", 6))
	/* RESB STATEMENT -- ADD NUMBER OF BYTES RESERVED TO LOCCTR.
	ERRORS DETECTED: 11, 12 */
	{
		if(source.operand[0] == ' ')
		{
			*errorsfound = true;
			(*errorflags)[10] = true;
			/* MISSING OR MISPLACED OPERAND IN RESB STATEMENT */
		}
		else
		{
			nbytes = dectonum (source.operand,0,&i,&converror);
			if(converror)
			{
				*errorsfound = true;
				(*errorflags)[11] = true;
				/* ILLEGAL OPERAND IN RESB */
			}
			for(j = i + 1; j < 18; j ++)
				if(source.operand[j] != ' ')
				{
					*errorsfound = true;
					(*errorflags)[11] = true;
					/* ILLEGAL OPERAND IN RESB */
				}
			if(!(*errorflags)[11])
				*newlocctr = locctr + nbytes;
		}
	}
	else if(!strncmp(source.operation, "BASE  ", 6))
	{
		if(source.operand[0] == ' ')
		{
			*errorsfound = true;
			(*errorflags)[22] = true;
			/* ILLEGAL OPERAND FIELD */
		}
	}
	else if(!strncmp(source.operation, "EXTDEF", 6))
	{
		for(i = 0; i < 5; i++)
			strncpy(extdef[cur_csect][i], blank6, 6);
		i = 0;
		k = 0;
		for(j = 0; j < 5; j++)
		{
			while((source.comment[i] != ',') && (source.comment[i] != ' ') && (i < 31))
				extdef[cur_csect][j][k++] = source.comment[i++];
			i++;
			k = 0;
		}
	}
	else if(!strncmp(source.operation, "EXTREF", 6))
	{
		for(i = 0; i < 5; i++)
			strncpy(extref[cur_csect][i], blank6, 6);
		i = 0;
		k = 0;
		for(j = 0; j < 5; j++)
		{
			while((source.comment[i] != ',') && (source.comment[i] != ' ') && (i < 31))
				extref[cur_csect][j][k++] = source.comment[i++];
			i++;
			k = 0;
		}
		ref[cur_csect] = true;
	}
//	else if(!strncmp(source.operation, "EXTDEF", 6) || !strncmp(source.operation, "EXTREF", 6))
//	{
//		;
		/* DO NOTHING */
//	}
	else if(!strncmp(source.operation, "LTORG ", 6))
	{
		access_littab(store_address, &symtabret, source.operand, &locctr);
		/* LAST THREE PARAMETERS ARE DUMMYS IN THIS CALL */
	}
	else if(!strncmp(source.operation, "EQU   ", 6))
	{
		if(source.operand[0] == ' ')
		{
			*errorsfound = true;
			(*errorflags)[22] = true;
			/* ILLEGAL OPERAND FIELD */
		}
	}
	else if(!strncmp(source.operation, "END   ", 6))
	{
		access_littab(store_address, &symtabret, source.operand, &locctr);
		/* LAST THREE PARAMETERS ARE DUMMYS IN THIS CALL */
	}
	else if( !strncmp(source.operation, "FIX   ", 6) ||
				!strncmp(source.operation, "FLOAT ", 6) ||
				!strncmp(source.operation, "HIO   ", 6) ||
				!strncmp(source.operation, "NORM  ", 6) ||
				!strncmp(source.operation, "SIO   ", 6) ||
				!strncmp(source.operation, "TIO   ", 6))
	{
		*newlocctr = locctr + 1;
	}
	else if( !strncmp(source.operation, "ADDR  ", 6) ||
				!strncmp(source.operation, "CLEAR ", 6) ||
				!strncmp(source.operation, "COMPR ", 6) ||
				!strncmp(source.operation, "DIVR  ", 6) ||
				!strncmp(source.operation, "MULR  ", 6) ||
				!strncmp(source.operation, "RMO   ", 6) ||
				!strncmp(source.operation, "SHIFTL", 6) ||
				!strncmp(source.operation, "SHIFTR", 6) ||
				!strncmp(source.operation, "SUBR  ", 6) ||
				!strncmp(source.operation, "SVC   ", 6) ||
				!strncmp(source.operation, "TIXR  ", 6))
	{
		*newlocctr = locctr + 2;
	}
	else if(source.operation[0] == '+')
	{
		*newlocctr = locctr + 4;
	}
	else
	/* ASSUME MACHINE INSTRUCTION */
	{
		*newlocctr = locctr + 3;
	}
}

void p1_assign_sym (sourcetype source, int locctr, boolean *errorsfound, errtype *errorflags)
{

/* THIS FUNCTION ADDS THE LABEL FROM A SOURCE STATEMENT TO THE SYMBOL
TABLE, USING THE CURRENT LOCATION COUNTER VALUE AS ITS ADDRESS.
ERRORS DETECTED: 13,14 */

	symrettype symtabret, retcode;
	int address, symadd, sym1add, sym2add, i, j;
	char18 temp;
	char8 sym1, sym2;
	char plus_minus;
	boolean bool;

	if((!(*errorflags)[0]) && (strncmp(source.labl, blank8, 8)))
	{
		if(!strncmp(source.operation, "EQU   ", 6))
		{
			if(source.operand[0] != '*')
			{
				if((source.operand[0] >= '0') && (source.operand[0] <= '9'))
				{
					i = 0;
					while((i < 5) && ((source.operand[i] >= '0') && (source.operand[i] <= '9')))
					/* MAX VALUE IS 65535:  5 DIGITS */
					{
						temp[i] = source.operand[i];
						i++;
					}
					for(j = i; j < 18; j++)
					{
						if(source.operand[j] != ' ')
						{
							*errorsfound = true;
							(*errorflags)[24] = true;
						}
						temp[i] = source.operand[i];
					}
				}
				else if((source.operand[0] >= 'A') && (source.operand[0] <= 'Z'))
				{
					i =0;
					while((i < 8) && ((source.operand[i] >= 'A') && (source.operand[i] <= 'Z')))
					{
						sym1[i] = source.operand[i];
						i++;
					}
					if((source.operand[i] == '-') || (source.operand[i] == '+'))
					{
						j = i;
						while(j < 8)
							sym1[j++] = ' ';
						plus_minus = source.operand[i];
						if((source.operand[i + 1] >= 'A') && (source.operand[i + 1] <= 'Z'))
						/* SECOND OPERAND ARGUMENT IS A SYMBOL */
						{
							i++;
							j = 0;
							while((i < 18) && ((source.operand[i] >= 'A') && (source.operand[i] <= 'Z')))
							{
								sym2[j] = source.operand[i];
								i++;
								j++;
							}
							while(j < 8)
								sym2[j++] = ' ';
							for(j = i; j < 18; j++)
							{
								if(source.operand[j] != ' ')
								{
									*errorsfound = true;
									(*errorflags)[24] = true;
								}
							}
							access_symtab(search, &retcode, sym1, &sym1add);
							if(retcode == found)
							{
								access_symtab(search, &retcode, sym2, &sym2add);
								if(retcode == found)
								{
									if(plus_minus == '+')
										symadd = sym1add + sym2add;
									else /* plus_minus == '-' */
										symadd = sym1add - sym2add;
									access_symtab(store, &retcode, source.labl, &symadd);
								}
								else
								{
									*errorsfound = true;
									(*errorflags)[20] = true;
									/* UNDEFINED SYMBOL IN OPERAND */
								}
							}
							else
							{
								*errorsfound = true;
								(*errorflags)[20] = true;
								/* UNDEFINED SYMBOL IN OPERAND */
							}
						}
						else if((source.operand[i + 1] >= '0') && (source.operand[i + 1] <= '9'))
						/* SECOND OPERAND ARGUMENT IS A DECIMAL */
						{
							i++;
							j = 0;
							while((j < 5) && ((source.operand[i] >= '0') && (source.operand[i] <= '9')))
							{
								sym2[j] = source.operand[i];
								i++;
								j++;
							}
							while(j < 8)
								sym2[j++] = ' ';
							for(j = i; j < 18; j++)
							{
								if(source.operand[j] != ' ')
								{
									*errorsfound = true;
									(*errorflags)[24] = true;
								}
							}
							access_symtab(search, &retcode, sym1, &sym1add);
							if(retcode == found)
							{
								for(i = 0; i < 8; i++)
									temp[i] = sym2[i];
								for(i = 8; i < 18; i++)
									temp[i] = ' ';
								sym2add = dectonum(temp, 0, &i, &bool);
								if(!bool)
								{
									if(plus_minus == '+')
										symadd = sym1add + sym2add;
									else /* plus_minus == '-' */
										symadd = sym1add - sym2add;
									access_symtab(store, &retcode, source.labl, &symadd);
								}
								else
								{
									*errorsfound = true;
									(*errorflags)[20] = true;
									/* UNDEFINED SYMBOL IN OPERAND */
								}
							}
							else
							{
								*errorsfound = true;
								(*errorflags)[20] = true;
								/* UNDEFINED SYMBOL IN OPERAND */
							}
						}
						else
						{
							*errorsfound = true;
							(*errorflags)[24] = true;
						}
					}
					else
					{
						while(i < 8)
							sym1[i++] = ' ';
						for(j = i; j < 18; j++)
						{
							if(source.operand[j] != ' ')
							{
								*errorsfound = true;
								(*errorflags)[24] = true;
							}
						}
						access_symtab(search, &retcode, sym1, &symadd);
						if(retcode == found)
							access_symtab(store, &retcode, source.labl, &symadd);
					}
				}
				else
				{
					*errorsfound = true;
					(*errorflags)[24] = true;
				}
			}
			else
			/* source.operand[0] == '*' */
			{
				symadd = locctr;
				access_symtab(store, &retcode, source.labl, &symadd);
			}
		}
		else
		{
			access_symtab(search, &symtabret, source.labl, &address);
			if(symtabret == notfound)
				address = locctr;
			access_symtab (store, &symtabret, source.labl, &address);
			if(symtabret == tablefull)
			{
				*errorsfound = true;
				(*errorflags)[13] = true;
				/* SYMBOL TABLE OVERFLOW */
			}
		}
	}
	else
	{
		*errorsfound = true;
		(*errorflags)[12] = true;
		/* DUPLICATE LABEL */
	}
}

void p2_search_optab(char6 mnemonic, oprettype *returncode, int *opcode)
{

/* THIS FUNCTION SEARCHES THE OPERATION CODE TABLE (OPTAB) FOR THE
MNEMONIC PASSED AS PARAMETER. IF THE MNEMONIC IS FOUND,
RETURNCODE IS SET TO VALIDOP AND OPCODE IS SET TO THE VALUE GIVEN
IN OPTAB. OTHERWISE, RETURNCODE IS SET TO INVALIDOP AND OPCODE
IS SET TO 255.

THE ENTRIES IN OPTAB ARE ORDERED BY MNEMONIC. THIS FUNCTION USES
A BINARY SEARCH. */

	int low = 0, mid, high = MAXOPS - 1;

	do
	{
		mid = (low + high) / 2;
		if((strncmp(mnemonic, optab[mid].mnemonic, 6)) < 0)
			high = mid - 1;
		else
			low = mid + 1;
	}while(!(!strncmp(mnemonic, optab[mid].mnemonic, 6) || (high < low)));

	if(!strncmp(mnemonic, optab[mid].mnemonic, 6))
	{
		*returncode = validop;
		*opcode = optab[mid].opcode;
	}
	else
	{
		*returncode = invalidop;
		*opcode = 255;
	}
}

void p2_assemble_inst(sourcetype source, int locctr, boolean *errorsfound, errtype *errorflags, objtype *objct)
{

/* THIS FUNCTION GENERATES THE OBJECT CODE (IF ANY) FOR THE SOURCE
STATEMENT CURRENTLY BEING PROCESSED. THE OBJECT CODE GENERATED
IS PLACED IN OBJECT (THIS RECORD ALSO INCLUDES AN INDICATION OF
THE TYPE OF OBJECT CODE AND THE LENGTH).

THIS FUNCTION ALSO TESTS FOR ERRORS SUCH AS A MISSING START OR END
OR STATEMENTS IMPROPERLY FOLLOWING THE END STATEMENT. IN ORDER TO
DO THIS, IT MAKES USE OF THE GLOBAL VARIABLES FIRSTSTMT AND ENDFOUND.
ERRORS DETECTED: 6, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 */

	oprettype opreturn;
	symrettype symtabreturn;
	int i, j, k;
	char4 temp, temp4;
	char hexchar;
	char8 opsymbol1, opsymbol2;
	int opaddress, opad1, opad2, tempaddress;
	boolean indexed, ext, ext1, ext2;
	int asciival, opcode, wordvalue;
	boolean negative, converror, success, constant;
	char18 temp18;
	int tempi, temp_csect;
	char6 temp6;

	success = false;
	constant = false;
	ext = false;

	if(endfound)
	{
		*errorsfound = true;
		(*errorflags)[21] = true;
		/* STATEMENT SHOULD NOT FOLLOW END */
	}
	if(!strncmp(source.operation, "START ", 6))
	/* START STATEMENT -- IF THIS IS THE FIRST SOURCE LINE, SET OBJECT
	TYPE = HEADREC AND OBJECT CODE = PROGRAM NAME. */
	{
		if(!firststmt)
		{
			*errorsfound = true;
			(*errorflags)[14] = true;
			/* DUPLICATE OR MISPLACED START STATEMENT */
		}
		(*objct).rectype = headrec;
		(*objct).objlength = 0;
		for(i = 0; i < 6; i ++)
			(*objct).objcode[i] = source.labl[i];
		for(i = 6; i < 15; i ++)
			(*objct).objcode[i] = ' ';
	}
	else if(!strncmp(source.operation, "WORD  ", 6))
	/* WORD STATEMENT -- THE OPERAND MAY BE EITHER AN INT OR A SYMBOL
	THAT APPEARS AS A LABEL IN THE PROGRAM. */
	{
		if(source.operand[0] == ' ')
		{
			*errorsfound = true;
			(*errorflags)[17] = true;
			/* MISSING OR MISPLACED OPERAND IN WORD */
		}
		else if((source.operand[0] >= 'A') && (source.operand[0] <= 'Z'))
		/* OPERAND IS A LABEL. SCAN THE OPERAND FIELD FOR THE LABEL,
		AND LOOK IT UP IN THE SYMBOL TABLE. IF FOUND, GENERATE
		OBJECT TYPE = TEXTREC AND OBJECT CODE = ADDRESS FOR SYMBOL.
		ERRORS DETECTED: 17, 21 */
		{
			strncpy(opsymbol1, blank8, 8);
			i = 0;
			while((i < 8) && ((source.operand[i] != ' ') && (source.operand[i] != '-') && (source.operand[i] != '+')))
			{
				opsymbol1[i] = source.operand[i];
				i++;
			}
			if((source.operand[i] == '-') || (source.operand[i] == '+'))
			/* THERE IS AN EXPRESSION */
			{
				j = i + 1;
				k = 0;
            strncpy(opsymbol2, blank8, 8);
				while((j < 18) && (((source.operand[j] >= 'A') && (source.operand[j] <= 'Z')) || ((source.operand[j] >= '0') && (source.operand[j] <= '9'))))
				{
					opsymbol2[k] = source.operand[j];
					j++;
					k++;
				}
				k = j;
				for(j = 0; j < 5; j++)
				{
					if(!strncmp(extref[cur_csect][j], opsymbol1, 6))
					{
						opad1 = 0;
						ext1 = true;
					}
					if(!strncmp(extref[cur_csect][j], opsymbol2, 6))
					{
						opad2 = 0;
						ext2 = true;
					}
				}
				if(!ext1)
					access_symtab (search, &symtabreturn, opsymbol1, &opad1);
				if(!ext2)
					access_symtab (search, &symtabreturn, opsymbol2, &opad2);
				if(ext1 || ext2)
				{
					if(source.operand[i] == '+')
					{
						opaddress = opad1 + opad2;
						(*objct).rectype = textrec;
						(*objct).objlength = 6;
						numtohex(opaddress,&temp);
						(*objct).objcode[0] = '0';
						(*objct).objcode[1] = '0';
						for(i = 0; i < 4; i ++)
							(*objct).objcode[2+i] = temp[i];
						if(ext1)
						{
							modrec[current_mod].start_loc = locctr;
							modrec[current_mod].add_length = 6;
							modrec[current_mod].plus_minus = '+';
							strncpy(modrec[current_mod].symbol, opsymbol1, 6);
							modrec[current_mod++].csect = cur_csect;
						}
						if(ext2)
						{
							modrec[current_mod].start_loc = locctr;
							modrec[current_mod].add_length = 6;
							modrec[current_mod].plus_minus = '+';
							strncpy(modrec[current_mod].symbol, opsymbol2, 6);
							modrec[current_mod++].csect = cur_csect;
						}
					}
					else if(source.operand[i] == '-')
					{
						opaddress = opad1 - opad2;
						(*objct).rectype = textrec;
						(*objct).objlength = 6;
						numtohex(opaddress,&temp);
						(*objct).objcode[0] = '0';
						(*objct).objcode[1] = '0';
						for(i = 0; i < 4; i ++)
							(*objct).objcode[2+i] = temp[i];
						if(ext1)
						{
							modrec[current_mod].start_loc = locctr;
							modrec[current_mod].add_length = 6;
							modrec[current_mod].plus_minus = '+';
							strncpy(modrec[current_mod].symbol, opsymbol1, 6);
							modrec[current_mod++].csect = cur_csect;
						}
						if(ext2)
						{
							modrec[current_mod].start_loc = locctr;
							modrec[current_mod].add_length = 6;
							modrec[current_mod].plus_minus = '-';
							strncpy(modrec[current_mod].symbol, opsymbol2, 6);
							modrec[current_mod++].csect = cur_csect;
						}
					}
				}
				return;
			}
			for(j = k; j < 18; j ++)
				if(source.operand[i] != ' ')
				{
					*errorsfound = true;
					(*errorflags)[16] = true;
					/* ILLEGAL OPERAND IN WORD STMT */
				}
			access_symtab (search, &symtabreturn, opsymbol1, &opaddress);
			if(symtabreturn != found)
			{
				*errorsfound = true;
				(*errorflags)[20] = true;
				/* UNDEFINED SYMBOL IN OPERAND */
			}
			if((!(*errorflags)[16]) && (!(*errorflags)[20]))
			{
				(*objct).rectype = textrec;
				(*objct).objlength = 6;
				numtohex(opaddress,&temp);
				(*objct).objcode[0] = '0';
				(*objct).objcode[1] = '0';
				for(i = 0; i < 4; i ++)
					(*objct).objcode[2+i] = temp[i];
			}
		}
		else
		/* OPERAND IS AN INT -- USE DECTONUM TO CONVERT TO A
		NUMERIC VALUE, THEN SCAN THE REST OF THE OPERAND FIELD
		TO BE SURE NOTHING ELSE IS THERE. IF THE LEADING CHARACTER
		OF THE INT WAS A MINUS SIGN, CONVERT TO 2'S COMPLEMENT
		REPRESENTATION. GENERATE OBJECT TYPE = TEXTREC AND OBJECT
		CODE = VALUE OF THE CONVERTED INT IN HEX.
		ERRORS DETECTED: 17 */
		{
			if(source.operand[0] == '-')
			{
				wordvalue = dectonum (source.operand,1,&i,&converror);
				negative = true;
			}
			else
			{
				wordvalue = dectonum (source.operand,0,&i,&converror);
				negative = false;
			}
			if(converror)
			{
				*errorsfound = true;
				(*errorflags)[16] = true;
				/* ILLEGAL OPERAND IN WORD STATEMENT */
			}
			for(j = i+1; j < 18; j ++)
				if(source.operand[j] != ' ')
				{
					*errorsfound = true;
					(*errorflags)[16] = true;
					/* ILLEGAL OPERAND IN WORD STMT */
				}
			if((!(*errorflags)[16]) && (!(*errorflags)[17]))
			{
				(*objct).rectype = textrec;
				(*objct).objlength = 6;
				if(negative)
				{
					wordvalue = 65536 - wordvalue;
					numtohex(wordvalue,&temp);
					(*objct).objcode[0] = 'F';
					(*objct).objcode[1] = 'F';
					for(i = 0; i < 4; i ++)
						(*objct).objcode[i+2] = temp[i];
				}
				else
				{
					numtohex(wordvalue,&temp);
					(*objct).objcode[0] = '0';
					(*objct).objcode[1] = '0';
					for(i = 0; i < 4; i ++)
						(*objct).objcode[i+2] = temp[i];
				}
			}
		}
	}
	else if(!strncmp(source.operation, "BYTE  ", 6))
	/* BYTE STATEMENT -- THE OPERAND MUST BE EITHER C'...' OR X'...'.
	IF A FORMAT ERROR IN THE OPERAND (ERRORS 6, 7, 8) WAS DETECTED
	PREVIOUSLY, DO NOT ATTEMPT TO ASSEMBLE */
	{
		if((!(*errorflags)[5]) && (!(*errorflags)[6]) && (!(*errorflags)[7]))
		{
		/* OPERAND IS C'...' -- USE THE ASCII CONVERSION TABLE TO
		FIND THE ASCII CODE FOR EACH CHARACTER AND PACK INTO
		OBJECT CODE. SET OBJECT TYPE = TEXTREC. */
			if(source.operand[0] == 'C')
			{
				i = 0;
				while(source.operand[2+i] != quote)
				{
					asciival = ascii[(unsigned char)(source.operand[2+i])];
					numtohex(asciival,&temp);
					(*objct).objcode[2*i] = temp[2];
					(*objct).objcode[2*i+1] = temp[3];
					i++;
				}
				(*objct).rectype = textrec;
				(*objct).objlength = 2 * i;
			}
			else
			/* OPERAND IS X'...' -- PACK HEX DIGITS INTO OBJECT CODE AND
			SET OBJECT TYPE = TEXTREC.  ERRORS DETECTED: 6 */
			{
				i = 0;
				while(source.operand[2+i] != quote)
				{
					hexchar = source.operand[2+i];
					if(((hexchar >= '0') && (hexchar <= '9')) || ((hexchar >= 'A') && (hexchar <= 'F')))
						(*objct).objcode[i] = hexchar;
					else
					{
						*errorsfound = true;
						(*errorflags)[5] = true;
						/* ILLEGAL OPERAND IN BYTE */
					}
					i++;
				}
				(*objct).objlength = i;
				(*objct).rectype = textrec;
			}
		}
	}
	else if(!strncmp(source.operation, "RESB  ", 6) || !strncmp(source.operation, "RESW  ", 6))
	/* NO OBJECT CODE FOR RESB OR RESW */
	{
		(*objct).rectype = none;
	}
	else if(!strncmp(source.operation, "EQU   ", 6))
	/* NO OBJECT CODE FOR EQU */
	{
		(*objct).rectype = none;
	}
	else if(!strncmp(source.operation, "LTORG ", 6))
	/* NO OBJECT CODE FOR LTORG */
	{
		(*objct).rectype = none;
	}
	else if(!strncmp(source.operation, "END   ", 6))
	/* END STATEMENT -- THE OPERAND MUST BE A SYMBOL USED AS A LABEL IN
	THE PROGRAM. LOOK UP THIS LABEL IN THE SYMBOL TABLE TO FIND THE
	TRANSFER ADDRESS. GENERATE OBJECT CODE = TRANSFER ADDRESS AND
	OBJECT TYPE = ENDREC.           ERRORS DETECTED: 19, 20 */
	{
		endfound = true;
		if(source.operand[0] == ' ')
		{
			*errorsfound = true;
			(*errorflags)[18] = true;
			/* MISSING OR MISPLACED OPERAND IN END */
		}
		else
		{
			strncpy(opsymbol1, blank8, 8);
			i = 0;
			while((i < 8) && (source.operand[i] != ' '))
			{
				opsymbol1[i] = source.operand[i];
				i++;
			}
			for(j = i; j < 18; j ++)
				if(source.operand[i] != ' ')
				{
					*errorsfound = true;
					(*errorflags)[19] = true;
					/* ILLEGAL OPERAND IN END STMT */
				}
			if(cur_csect == 0)
			{
				access_symtab(search, &symtabreturn, opsymbol1, &opaddress);
				if(symtabreturn != found)
				{
					*errorsfound = true;
					(*errorflags)[20] = true;
					/* UNDEFINED SYMBOL IN OPERAND */
				}
				if((!(*errorflags)[19]) && (!(*errorflags)[20]))
				{
					(*objct).rectype = endrec;
					(*objct).objlength = 6;
					numtohex(opaddress,&temp);
					(*objct).objcode[0] = '0';
					(*objct).objcode[1] = '0';
					for(i = 0; i < 4; i ++)
						(*objct).objcode[2+i] = temp[i];
				}
			}
			else
			{
				if((!(*errorflags)[19]) && (!(*errorflags)[20]))
				{
					(*objct).rectype = endrec;
					(*objct).objlength = 0;
				}
			}
		}
	}
	else if(!strncmp(source.operation, "BASE  ", 6))
	{
		for(i = 0; i < 18; i++)
			temp18[i] = ' ';
		i = 0;
		while((i < 18) && (((source.operand[i] >= 'A') && (source.operand[i] <= 'Z')) ||
				((source.operand[i] >= '0') && (source.operand[i] <= '9'))))
		{
			temp18[i] = source.operand[i];
			i++;
		}
		for(; i < 18; i++)
		{
			if(source.operand[i] != ' ')
			{
				*errorsfound = true;
				(*errorflags)[22] = true;
				/* ILLEGAL OPERAND FIELD */
			}
		}
		access_symtab(search, &symtabreturn, temp18, &opaddress);
		if(symtabreturn != found)
		{
			*errorsfound = true;
			(*errorflags)[20] = true;
			/* UNDEFINED SYMBOL IN OPERAND */
		}
		else
		{
			base = opaddress;
		}
	}
	else if( !strncmp(source.operation, "FIX   ", 6) ||
				!strncmp(source.operation, "FLOAT ", 6) ||
				!strncmp(source.operation, "HIO   ", 6) ||
				!strncmp(source.operation, "NORM  ", 6) ||
				!strncmp(source.operation, "SIO   ", 6) ||
				!strncmp(source.operation, "TIO   ", 6))
	{
		(*objct).rectype = none;
	}
	else if(!strncmp(source.operation, "CSECT ", 6))
	{
		(*objct).rectype = endrec;
		if(cur_csect == 0)
		{
			(*objct).objlength = 6;
			numtohex(progstart, &temp);
			(*objct).objcode[0] = '0';
			(*objct).objcode[1] = '0';
			for(i = 0; i < 4; i ++)
				(*objct).objcode[2+i] = temp[i];
		}
		else
		{
			(*objct).objlength = 0;
		}
//		cur_csect++;
	}
	else if(!strncmp(source.operation, "EXTDEF", 6) || !strncmp(source.operation, "EXTREF", 6))
	{
		;
		/* DO NOTHING */
	}
	else if( !strncmp(source.operation, "ADDR  ", 6) ||
				!strncmp(source.operation, "CLEAR ", 6) ||
				!strncmp(source.operation, "COMPR ", 6) ||
				!strncmp(source.operation, "DIVR  ", 6) ||
				!strncmp(source.operation, "MULR  ", 6) ||
				!strncmp(source.operation, "RMO   ", 6) ||
				!strncmp(source.operation, "SHIFTL", 6) ||
				!strncmp(source.operation, "SHIFTR", 6) ||
				!strncmp(source.operation, "SUBR  ", 6) ||
				!strncmp(source.operation, "SVC   ", 6) ||
				!strncmp(source.operation, "TIXR  ", 6))
	/* FORMAT 2 INSTRUCTIONS */
	{
		if(   source.operand[0] == 'A' ||
				source.operand[0] == 'X' ||
				source.operand[0] == 'L' ||
				source.operand[0] == 'B' ||
				source.operand[0] == 'S' ||
				source.operand[0] == 'T' ||
				source.operand[0] == 'F' ||
				source.operand[0] == 'P' ||
				source.operand[0] == 'S')
		{
			pc += 2;
			strncpy(opsymbol1, blank8, 8);
			opsymbol1[0] = source.operand[0];
			if((source.operand[1] != ',') && (source.operand[1] != 'C') && (source.operand[1] != 'W'))
			/* THERE IS ONLY ONE REGISTER IN THE OPERAND
			OPERATION MUST BE EITHER CLEAR OR TIXR */
			{
				i = 1;
				while(i < 18)
				{
					if(source.operand[i] != ' ')
					{
						*errorsfound = true;
						(*errorflags)[22] = true;
						/* ILLEGAL OPERAND FILED */
					}
					i++;
				}
				temp_csect = cur_csect;
				cur_csect = 0;
				access_symtab(search, &symtabreturn, opsymbol1, &opaddress);
				cur_csect = temp_csect;
				p2_search_optab(source.operation, &opreturn, &opcode);
				(*objct).rectype = textrec;
				(*objct).objlength = 4;
				numtohex(opcode,&temp);
				(*objct).objcode[0] = temp[2];
				(*objct).objcode[1] = temp[3];
				numtohex(opaddress % 256,&temp);
				(*objct).objcode[2] = temp[3];
				(*objct).objcode[3] = '0';
			}
			else if(source.operand[1] != ',')
			/* REGISTER IS EITHER PC OR SW */
			{
				opsymbol1[1] = source.operand[1];
				if(source.operand[2] != ',')
				/* THERE IS ONLY ONE REGISTER IN THE OPERAND
				OPERATION MUST BE EITHER CLEAR OR TIXR */
				{
					i = 2;
					while(i < 18)
					{
						if(source.operand[i] != ' ')
						{
							*errorsfound = true;
							(*errorflags)[22] = true;
							/* ILLEGAL OPERAND FIELD */
						}
						i++;
					}
					temp_csect = cur_csect;
					cur_csect = 0;
					access_symtab(search, &symtabreturn, opsymbol1, &opaddress);
					cur_csect = temp_csect;
					p2_search_optab(source.operation, &opreturn, &opcode);
					(*objct).rectype = textrec;
					(*objct).objlength = 4;
					numtohex(opcode,&temp);
					(*objct).objcode[0] = temp[2];
					(*objct).objcode[1] = temp[3];
					numtohex(opaddress % 256,&temp);
					(*objct).objcode[2] = temp[3];
					(*objct).objcode[3] = '0';
				}
				else
				/* THERE ARE TWO REGISTERS IN THE OPERAND */
				{
					if(   source.operand[3] == 'A' ||
							source.operand[3] == 'X' ||
							source.operand[3] == 'L' ||
							source.operand[3] == 'B' ||
							source.operand[3] == 'S' ||
							source.operand[3] == 'T' ||
							source.operand[3] == 'F' ||
							source.operand[3] == 'P' ||
							source.operand[3] == 'S')
					{
						strncpy(opsymbol2, blank8, 8);
						opsymbol2[0] = source.operand[3];
						if((source.operand[4] != 'C') && (source.operand[4] != 'W'))
						{
							i = 4;
							while(i < 18)
							{
								if(source.operand[i] != ' ')
								{
									*errorsfound = true;
									(*errorflags)[22] = true;
									/* ILLEGAL OPERAND FIELD */
								}
								i++;
							}
							temp_csect = cur_csect;
							cur_csect = 0;
							access_symtab(search, &symtabreturn, opsymbol1, &opad1);
							access_symtab(search, &symtabreturn, opsymbol2, &opad2);
							cur_csect = temp_csect;
							p2_search_optab(source.operation, &opreturn, &opcode);
							(*objct).rectype = textrec;
							(*objct).objlength = 4;
							numtohex(opcode,&temp);
							(*objct).objcode[0] = temp[2];
							(*objct).objcode[1] = temp[3];
							numtohex(opad1 % 256,&temp);
							(*objct).objcode[2] = temp[3];
							numtohex(opad2 % 256,&temp);
							(*objct).objcode[3] = temp[3];
						}
						else
						/* SECOND REGISTER IS EITHER PC OR SW */
						{
							opsymbol2[1] = source.operand[4];
							i = 5;
							while(i < 18)
							{
								if(source.operand[i] != ' ')
								{
									*errorsfound = true;
									(*errorflags)[22] = true;
									/* ILLEGAL OPERAND FIELD */
								}
								i++;
							}
							temp_csect = cur_csect;
							cur_csect = 0;
							access_symtab(search, &symtabreturn, opsymbol1, &opad1);
							access_symtab(search, &symtabreturn, opsymbol2, &opad2);
							cur_csect = temp_csect;
							p2_search_optab(source.operation, &opreturn, &opcode);
							(*objct).rectype = textrec;
							(*objct).objlength = 4;
							numtohex(opcode,&temp);
							(*objct).objcode[0] = temp[2];
							(*objct).objcode[1] = temp[3];
							numtohex(opad1 % 256,&temp);
							(*objct).objcode[2] = temp[3];
							numtohex(opad2 % 256,&temp);
							(*objct).objcode[3] = temp[3];
						}
					}
					else
					{
						*errorsfound = true;
						(*errorflags)[22] = true;
						/* ILLEGAL OPERAND FIELD */
					}
				}
			}
			else
			/* THERE ARE TWO REGISTERS IN THE OPERAND */
			{
				if(   source.operand[2] == 'A' ||
						source.operand[2] == 'X' ||
						source.operand[2] == 'L' ||
						source.operand[2] == 'B' ||
						source.operand[2] == 'S' ||
						source.operand[2] == 'T' ||
						source.operand[2] == 'F' ||
						source.operand[2] == 'P' ||
						source.operand[2] == 'S')
				{
					strncpy(opsymbol2, blank8, 8);
					opsymbol2[0] = source.operand[2];
					if((source.operand[3] != 'C') && (source.operand[3] != 'W'))
					{
						i = 3;
						while(i < 18)
						{
							if(source.operand[i] != ' ')
							{
								*errorsfound = true;
								(*errorflags)[22] = true;
								/* ILLEGAL OPERAND FIELD */
							}
							i++;
						}
						temp_csect = cur_csect;
						cur_csect = 0;
						access_symtab(search, &symtabreturn, opsymbol1, &opad1);
						access_symtab(search, &symtabreturn, opsymbol2, &opad2);
						cur_csect = temp_csect;
						p2_search_optab(source.operation, &opreturn, &opcode);
						(*objct).rectype = textrec;
						(*objct).objlength = 4;
						numtohex(opcode,&temp);
						(*objct).objcode[0] = temp[2];
						(*objct).objcode[1] = temp[3];
						numtohex(opad1 % 256,&temp);
						(*objct).objcode[2] = temp[3];
						numtohex(opad2 % 256,&temp);
						(*objct).objcode[3] = temp[3];
					}
					else
					/* SECOND REGISTER IS EITHER PC OR SW */
					{
						opsymbol2[1] = source.operand[3];
						i = 4;
						while(i < 18)
						{
							if(source.operand[i] != ' ')
							{
								*errorsfound = true;
								(*errorflags)[22] = true;
								/* ILLEGAL OPERAND FIELD */
							}
							i++;
						}
						temp_csect = cur_csect;
						cur_csect = 0;
						access_symtab(search, &symtabreturn, opsymbol1, &opad1);
						access_symtab(search, &symtabreturn, opsymbol2, &opad2);
						cur_csect = temp_csect;
						p2_search_optab(source.operation, &opreturn, &opcode);
						(*objct).rectype = textrec;
						(*objct).objlength = 4;
						numtohex(opcode,&temp);
						(*objct).objcode[0] = temp[2];
						(*objct).objcode[1] = temp[3];
						numtohex(opad1 % 256,&temp);
						(*objct).objcode[2] = temp[3];
						numtohex(opad2 % 256,&temp);
						(*objct).objcode[3] = temp[3];
					}
				}
				else
				{
					*errorsfound = true;
					(*errorflags)[22] = true;
					/* ILLEGAL OPERAND FIELD */
				}
			}
		}
		else
		{
			*errorsfound = true;
			(*errorflags)[22] = true;
			/* ILLEGAL OPERAND FIELD */
		}
	}
	else
	/* PRESUMABLY WE HAVE A MACHINE INSTRUCTION.
	THE OPERAND SHOULD BE EITHER AN ACTUAL ADDRESS (IN HEX) OR
	A SYMBOL THAT APPEARS AS A LABEL IN THE PROGRAM. EITHER TYPE
	OF OPERAND MAY BE FOLLOWED BY ',X' TO INDICATE INDEXED ADDRESSING. */
	{
		if(((source.operand[0] >= '0') && (source.operand[0] <= '9')) ||
			 (((source.operand[0] == '#') || (source.operand[0] == '@')) &&
			  ((source.operand[1] >= '0') && (source.operand[1] <= '9'))))
		/* OPERAND STARTS WITH 0 THROUGH 9 -- IT MUST BE AN ADDRESS.
		CONVERT THE ADDRESS TO NUMERIC.         ERRORS DETECTED: 23 */
		{
			if((source.operand[0] == '#') || (source.operand[0] == '@'))
				opaddress = hextonum(source.operand,1,&i,&converror);
			else
				opaddress = hextonum(source.operand,0,&i,&converror);
			if(converror)
			{
				*errorsfound = true;
				(*errorflags)[22] = true;
				/* ILLEGAL OPERAND FIELD */
			}
		}
		else if(source.operand[0] == '=')
		{
			access_littab(search_littab, &symtabreturn, source.operand, &opaddress);
			i = 0;
			while(source.operand[i] != ' ')
				i++;
		}
		else
		/* OPERAND IS A LABEL -- SCAN FOR THE LABEL AND LOOK IT UP IN
		THE SYMBOL TABLE.               ERRORS DETECTED: 21 */
		{
			strncpy(opsymbol1, blank8, 8);
			i = 0;
			if((source.operand[0] == '#') || (source.operand[0] == '@'))
			{
				i++;
				while((i < 9) && (source.operand[i] != ' ') && (source.operand[i] != ','))
				{
					opsymbol1[i - 1] = source.operand[i];
					i++;
				}
			}
			else
			{
				while((i < 8) && (source.operand[i] != ' ') && (source.operand[i] != ','))
				{
					opsymbol1[i] = source.operand[i];
					i++;
				}
			}
			for(j = 0; j < 5; j++)
			{
				if(!strncmp(extref[cur_csect][j], opsymbol1, 6))
				{
					opaddress = 0;
					ext = true;
					symtabreturn = found;
				}
			}
			if(ext == false)
				access_symtab (search, &symtabreturn, opsymbol1, &opaddress);
			if(symtabreturn != found)
			{
				*errorsfound = true;
				(*errorflags)[20] = true;
				/* UNDEFINED SYMBOL IN OPERAND */
			}
		}
		if((source.operand[i] == ',') && (source.operand[i+1] == 'X'))
		/* ADDRESS OR LABEL IS FOLLOWED BY ',X' -- SET INDEXED = TRUE */
		{
			indexed = true;
			i += 2;
		}
		else
			indexed = false;
		if((i == 0) && (strncmp(source.operation, "RSUB  ", 6)))
		/* EVERY INSTRUCTION EXCEPT RSUB MUST HAVE AN OPERAND */
		{
			*errorsfound = true;
			(*errorflags)[24] = true;
			/* MISSING OR MISPLACED OPERAND */
		}
		for(j = i; j < 18; j ++)
		/* BE SURE THE REST OF THE OPERAND FIELD IS BLANK */
			if(source.operand[i] != ' ')
			{
				*errorsfound = true;
				(*errorflags)[22] = true;
				/* ILLEGAL OPERAND FIELD */
			}
		/* LOOK UP THE OPERATION CODE IN OPTAB TO FIND THE MACHINE OPCODE.
		GENERATE THE OBJECT CODE INSTRUCTION */
		if(source.operation[0] == '+')
		{
			temp6[0] = source.operation[1];
			temp6[1] = source.operation[2];
			temp6[2] = source.operation[3];
			temp6[3] = source.operation[4];
			temp6[4] = source.operation[5];
			temp6[5] = ' ';
			p2_search_optab(temp6, &opreturn, &opcode);
			if(opreturn != validop)
			{
				*errorsfound = true;
				(*errorflags)[23] = true;
				/* UNRECOGNIZED OPERATION CODE */
			}
		}
		else
		{
			p2_search_optab(source.operation, &opreturn, &opcode);
			if(opreturn != validop)
			{
				*errorsfound = true;
				(*errorflags)[23] = true;
				/* UNRECOGNIZED OPERATION CODE */
			}
		}
		if((!(*errorflags)[20]) && (!(*errorflags)[22]) && (!(*errorflags)[23]))
		{
			pc += 3;
			if(source.operation[0] == '+')
			{
				(*objct).rectype = textrec;
				(*objct).objlength = 8;
				if(indexed)
					opcode = (opcode * 16) + 57;
				else if(source.operand[0] == '@')
					opcode = (opcode * 16) + 33;
				else if(source.operand[0] == '#')
					opcode = (opcode * 16) + 17;
				else
					opcode = (opcode * 16) + 49;
				numtohex(opcode,&temp);
				(*objct).objcode[0] = temp[1];
				(*objct).objcode[1] = temp[2];
				(*objct).objcode[2] = temp[3];
				(*objct).objcode[3] = '0';
				if(source.operand[0] == '#')
            {
					if((source.operand[1] >= '0') && (source.operand[1] <= '9'))
					{
						i = 1;
						while((i < 18) && (source.operand[i] >= '0') && (source.operand[i] <= '9'))
						{
							temp18[i - 1] = source.operand[i];
							i++;
						}
						while(i <= 18)
						{
							temp18[i - 1] = ' ';
							i++;
						}
						numtohex(dectonum(temp18, 0, &i, &converror), &temp4);
						for(i = 0; i < 4; i++)
							temp18[i] = temp4[i];
						for(; i < 18; i++)
							temp18[i] = ' ';
						opaddress = hextonum(temp18, 0, &i, &converror);
					}
				}
				else if(relocatable)
				{
					modrec[current_mod].start_loc = locctr + 1;
					modrec[current_mod].add_length = 5;
					modrec[current_mod].plus_minus = '+';
					strncpy(modrec[current_mod].symbol, opsymbol1, 6);
					modrec[current_mod++].csect = cur_csect;
				}
				opad1 = opaddress / 256;
				opad2 = opaddress % 256;
				if(indexed && !ext)
					opad1 = opad1 + 128;
				numtohex(opad1,&temp);
				(*objct).objcode[4] = temp[2];
				(*objct).objcode[5] = temp[3];
				numtohex(opad2,&temp);
				(*objct).objcode[6] = temp[2];
				(*objct).objcode[7] = temp[3];
			}
			else
			{
				tempaddress = opaddress;
				if(!strncmp(source.operation, "RSUB  ", 6))
				{
					(*objct).rectype = textrec;
					(*objct).objlength = 6;
					strncpy((*objct).objcode, "4F0000", 6);
               success = true;
				}
				if(!success)
				{
					(*objct).rectype = textrec;
					(*objct).objlength = 6;
					numtohex(opcode,&temp);
					(*objct).objcode[0] = temp[2];
					(*objct).objcode[1] = temp[3];
					if(	((source.operand[0] >= '0') && (source.operand[0] <= '9')) ||
							(((source.operand[0] == '#') || (source.operand[0] == '@')) &&
							((source.operand[1] >= '0') && (source.operand[1] <= '9'))))
						constant = true;
					else
						opaddress -= pc;
					if((opaddress >= -2048) && (opaddress <= 2047))
						success = true;
					if(opaddress >= 0)
					{
						opad1 = opaddress / 256;
						opad2 = opaddress % 256;
						numtohex(opad1,&temp);
						(*objct).objcode[2] = temp[2];
						(*objct).objcode[3] = temp[3];
						numtohex(opad2,&temp);
						(*objct).objcode[4] = temp[2];
						(*objct).objcode[5] = temp[3];
					}
					else
					{
						numtohex(opaddress, &temp);
						(*objct).objcode[2] = '0';
						(*objct).objcode[3] = temp[1];
						(*objct).objcode[4] = temp[2];
						(*objct).objcode[5] = temp[3];
					}
					strncpy(temp18, blank18, 18);
					temp18[0] = (*objct).objcode[0];
					temp18[1] = (*objct).objcode[1];
					temp18[2] = (*objct).objcode[2];
					tempi = hextonum(temp18,0,&i,&converror);
					if(indexed)
						tempi += 58;
					else if(source.operand[0] == '@')
					{
						if(constant)
							tempi += 32;
						else
							tempi += 34;
					}
					else if(source.operand[0] == '#')
					{
						if(constant)
							tempi += 16;
						else
							tempi += 18;
					}
					else
						tempi += 50;
					numtohex(tempi, &temp4);
					(*objct).objcode[0] = temp4[1];
					(*objct).objcode[1] = temp4[2];
					(*objct).objcode[2] = temp4[3];
				}
				if(!success)
				{
					opaddress = tempaddress;
					(*objct).rectype = textrec;
					(*objct).objlength = 6;
					numtohex(opcode,&temp);
					(*objct).objcode[0] = temp[2];
					(*objct).objcode[1] = temp[3];
					opaddress -= base;
					if((opaddress >= 0) && (opaddress <= 4095))
						success = true;
					opad1 = opaddress / 256;
					opad2 = opaddress % 256;
					numtohex(opad1,&temp);
					(*objct).objcode[2] = temp[2];
					(*objct).objcode[3] = temp[3];
					numtohex(opad2,&temp);
					(*objct).objcode[4] = temp[2];
					(*objct).objcode[5] = temp[3];
					strncpy(temp18, blank18, 18);
					temp18[0] = (*objct).objcode[0];
					temp18[1] = (*objct).objcode[1];
					temp18[2] = (*objct).objcode[2];
					tempi = hextonum(temp18,0,&i,&converror);
					if(indexed)
						tempi += 60;
					else if(source.operand[0] == '@')
						tempi += 36;
					else if(source.operand[0] == '#')
						tempi += 20;
					else
						tempi += 52;
					numtohex(tempi, &temp4);
					(*objct).objcode[0] = temp4[1];
					(*objct).objcode[1] = temp4[2];
					(*objct).objcode[2] = temp4[3];
				}
				if(!success)
				{
					*errorsfound = true;
					(*errorflags)[25] = true;
					/* REQUIRED DISPLACEMENT OUT OF RANGE */
				}
			}
		}
	}
	if(firststmt && strncmp(source.operation, "START ", 6))
	/* THE FIRST SOURCE STATEMENT (EXCEPT FOR COMMENTS) MUST BE START */
	{
		*errorsfound = true;
		(*errorflags)[15] = true;
		/* MISSING OR MISPLACED START STATEMENT */
	}
	firststmt = false;
}

void p2_write_list(void)
{

/* THIS FUNCTION WRITES A LINE OF THE ASSEMBLY LISTING, WHICH CONTAINS
THE SOURCE STATEMENT AND (EXCEPT FOR COMMENT LINES) THE CURRENT
LOCATION COUNTER VALUE AND ANT OBJECT CODE THAT WAS GENERATED.
IF ANY ERRORS WERE DETECTED, THE ERROR MESSAGES ARE PRINTED FOLLOWING
THE SOURCE STATEMENT.

A MAXIMUM OF 6 HEX DIGITS OF OBJECT CODE ARE PRINTED PER LINE. IF
THE OBJECT CODE GENERATED FROM THE STATEMENT IS LONGER THAN THIS,
ADDITIONAL LINES ARE PRINTED. */

	int i,j;
	char4 temp;
	symrettype retcode;

	if((linenum == 0) || (linenum == 5))
		fprintf(lisfile, "  %d ", linenum);
	else if(linenum < 100)
		fprintf(lisfile, " %d ", linenum);
	else
		fprintf(lisfile, "%d ", linenum);
	linenum += 5;
	if(source.comline)
	{
		fprintf(lisfile, "     ");
		for(i = 0; i < 66; i++)
			fprintf(lisfile, "%c", source.line[i]);
	}
	else
	{
		if(strncmp(source.operation, "LTORG ", 6) && strncmp(source.operation, "END   ", 6) &&
			strncmp(source.operation, "BASE  ", 6) && strncmp(source.operation, "EXTDEF", 6) &&
			strncmp(source.operation, "EXTREF", 6) && strncmp(source.operation, "CSECT ", 6))
		{
			numtohex(locctr,&temp);
			for(i = 0; i < 4; i++)
				fprintf(lisfile, "%c", temp[i]);
		}
		else
			fprintf(lisfile, "    ");
		fprintf(lisfile, " ");
		for(i = 0; i < 66; i++)
			fprintf(lisfile, "%c", source.line[i]);
		i = 0;
		if(strncmp(source.operation, "END   ", 6))
			while((i < 8) && (i < objct.objlength))
			{
				fprintf(lisfile, "%c", objct.objcode[i]);
				i++;
			}
		for(j = i; j < 8; j ++)
			fprintf(lisfile, " ");
	}
	fprintf(lisfile, "\n");
	if(objct.objlength > 8)
	{
		for(i = 8; i < objct.objlength; i ++)
		{
			if((i % 8) == 1)
			{
				if(i != 9)
					fprintf(lisfile, "\n");
				fprintf(lisfile, "     ");
			}
			fprintf(lisfile, "%c", objct.objcode[i]);
		}
		fprintf(lisfile, "\n");
	}
	for(i = 0; i < MAXERRORS; i ++)
		if(errorflags[i])
		{
			fprintf(lisfile, " **** ");
			for(j = 0; j < 50; j++)
				fprintf(lisfile, "%c", errmsg[i][j]);
			fprintf(lisfile, "\n");
		}
	if(!strncmp(source.operation, "LTORG ", 6) || !strncmp(source.operation, "END   ", 6))
	{
		litpool = litpool1;
		access_littab(print_lis, &retcode, source.operand, &i);
		litpool1++;
	}
	for(i = 0; i < MAXERRORS; i++)
		errorflags[i] = false;
}

void p2_write_obj (objtype objct, int locctr, char6 progname[], int proglength[])
{

/* THIS FUNCTION PLACES THE GENERATED OBJECT CODE INTO THE OBJECT
PROGRAM. THERE ARE THREE TYPES OF OBJECT CODE TO BE HANDLED -
HEADREC (FROM START STATEMENT), ENDREC (FROM END STATEMENT), AND
TEXTREC (FROM INSTRUCTIONS AND WORD AND BYTE STATEMENTS).
TO KEEP TRACK OF THE TEXT RECORD CURRENTLY BEING CONSTRUCTED, THIS
FUNCTION USES THE GLOBAL VARIABLES TEXTSTART, TEXTADDR, TEXTLENGTH,
AND TEXTARRAY. */

	int i, j;
	char4 temp;
	int textbytes, address;
	symrettype retcode;
	char8 temp8;

	if(objct.rectype == headrec)
	/* HEADREC -- GENERATE HEADER RECORD IN OBJECT PROGRAM */
	{
		fprintf(objfile, "H");
		for(i = 0; i < 6; i++)
			fprintf(objfile, "%c", progname[cur_csect][i]);
		numtohex(locctr,&temp);
		fprintf(objfile, "00");
		for(i = 0; i < 4; i++)
			fprintf(objfile, "%c", temp[i]);
		numtohex(proglength[cur_csect], &temp);
		fprintf(objfile, "00");
		for(i = 0; i < 4; i++)
			fprintf(objfile, "%c", temp[i]);
		newhead = false;
		fprintf(objfile, "\n");
		if(def[cur_csect])
		{
			fprintf(objfile, "D");
			for(i = 0; i < 5; i++)
			{
				if(strncmp(extdef[cur_csect][i], blank6, 6))
				{
					for(j = 0; j < 6; j++)
						fprintf(objfile, "%c", extdef[cur_csect][i][j]);
					strncpy(temp8, extdef[cur_csect][i], 6);
					temp8[6] = ' ';
					temp8[7] = ' ';
					access_symtab(search, &retcode, temp8, &address);
					numtohex(address, &temp);
					fprintf(objfile, "00");
					for(j = 0; j < 4; j++)
						fprintf(objfile, "%c", temp[j]);
				}
			}
			fprintf(objfile, "\n");
		}
		if(ref[cur_csect])
		{
			fprintf(objfile, "R");
			for(i = 0; i < 5; i++)
			{
				if(strncmp(extref[cur_csect][i], blank6, 6))
					for(j = 0; j < 6; j++)
						fprintf(objfile, "%c", extref[cur_csect][i][j]);
			}
			fprintf(objfile, "\n");
		}
	}
	else if(objct.rectype == textrec)
	/* TEXTREC -- PUT OBJECT CODE INTO A TEXT RECORD. IF THE OBJECT
	CODE WILL NOT FIT INTO THE CURRENT TEXT RECORD, OR IF ADDRESSES
	ARE NOT CONTIGUOUS, A NEW TEXT RECORD MUST BE STARTED. */
	{
		if(textlength == 0)
		{
			textaddr = locctr;
			textstart = locctr;
		}
		if(((textlength + objct.objlength) > 60) || (locctr != textaddr))
		{
			fprintf(objfile, "T");
			numtohex(textstart,&temp);
			fprintf(objfile, "00");
			for(i = 0; i < 4; i++)
				fprintf(objfile, "%c", temp[i]);
			textbytes = textlength / 2;
			numtohex(textbytes,&temp);
			fprintf(objfile, "%c%c", temp[2], temp[3]);
			for(i = 0; i < textlength; i ++)
				fprintf(objfile, "%c", textarray[i]);
			fprintf(objfile, "\n");
			textlength = 0;
			textstart = locctr;
		}
		for(i = 0; i < objct.objlength; i ++)
			textarray[textlength+i] = objct.objcode[i];
		textlength = textlength + objct.objlength;
		textaddr = locctr + objct.objlength / 2;
	}
	else if(objct.rectype == endrec)
	/* ENDREC -- WRITE OUT THE LAST TEXT RECORD (IF THERE IS ANYTHING
	IN IT) AND THEN GENERATE THE END RECORD */
	{
		litpool = litpool2;
		if(!strncmp(source.operation, "END   ", 6))
			access_littab(print_obj, &retcode, source.operand, &i);
		if(textlength != 0)
		{
			fprintf(objfile, "T");
			numtohex(textstart,&temp);
			fprintf(objfile, "00");
			for(i = 0; i < 4; i++)
				fprintf(objfile, "%c", temp[i]);
			textbytes = textlength / 2;
			numtohex(textbytes,&temp);
			fprintf(objfile, "%c%c", temp[2], temp[3]);
			for(i = 0; i < textlength; i ++)
				fprintf(objfile, "%c", textarray[i]);
			fprintf(objfile, "\n");
		}
		if(relocatable)
		{
			i = 0;
			while(modrec[i].add_length != 0)
			{
				if(modrec[i].csect == cur_csect)
				{
					fprintf(objfile, "M");
					numtohex(modrec[i].start_loc, &temp);
					fprintf(objfile, "00");
					for(j = 0; j < 4; j++)
						fprintf(objfile, "%c", temp[j]);
					numtohex(modrec[i].add_length, &temp);
					for(j = 0; j < 2; j++)
						fprintf(objfile, "%c", temp[j + 2]);
					fprintf(objfile, "%c", modrec[i].plus_minus);
					for(j = 0; j < 6; j++)
						fprintf(objfile, "%c", modrec[i].symbol[j]);
					fprintf(objfile, "\n");
				}
				i++;
			}
		}
		fprintf(objfile, "E");
		for(i = 0; i < objct.objlength; i ++)
			fprintf(objfile, "%c", objct.objcode[i]);
		fprintf(objfile, "\n\n");
		if(strncmp(source.operation, "END   ", 6))
		{
			newhead = true;
			textlength = 0;
			cur_csect++;
		}
	}
	else if(!strncmp(source.operation, "LTORG ", 6))
	{
		litpool = litpool2;
		access_littab(print_obj, &retcode, source.operand, &i);
		litpool2++;
	}
}

void pass_1(void)
{

/* THIS IS THE MAIN FUNCTION FOR PASS 1. IT USES P1_READ_SOURCE TO
READ EACH INPUT STATEMENT (UNTIL ENDOFINPUT = TRUE). FOR
NON-COMMENT LINES, IT CALLS P1_ASSIGN_LOC AND P1_ASSIGN_SYM.
FOR ALL SOURCE LINES, IT USES ACCESS_INT_FILE TO WRITE THE
INTERMEDIATE FILE */

	boolean endofinput = false;
	int i;
	intrettype intreturn;
	int newlocctr;

	srcfile = fopen("input.dat", "r");
	intfile = fopen("output.tmp", "w");

	locctr = 0;

	p1_read_source (&source, &endofinput, &errorsfound, &errorflags);
	while(! endofinput)
	{
		if(source.comline)
			newlocctr = locctr;
		else
		{
			p1_assign_loc(source, locctr, &newlocctr, &errorsfound, &errorflags);
			if(!strncmp(source.operation, "START ", 6))
			{
				locctr = newlocctr;
				progstart = locctr;
				for(i = 0; i < 6; i++)
					progname[cur_csect][i] = source.labl[i];
			}
			if(!strncmp(source.operation, "CSECT ", 6))
			{
				proglength[cur_csect++] = locctr - progstart;
				locctr = newlocctr;
				progstart = locctr;
				for(i = 0; i < 6; i++)
					progname[cur_csect][i] = source.labl[i];
			}
			if(strncmp(source.labl, blank8, 8))
				p1_assign_sym(source, locctr, &errorsfound, &errorflags);
		}
		access_int_file(writeline, &intreturn, &source, &errorsfound, &errorflags);
		if(strncmp(source.operation, "LTORG ", 6))
			locctr = newlocctr;
		p1_read_source(&source, &endofinput, &errorsfound, &errorflags);
	}
	proglength[cur_csect] = locctr - progstart;
   cur_csect = 0;
	fclose(srcfile);
	fclose(intfile);
}

void pass_2(void)
{

/* THIS IS THE MAIN FUNCTION FOR PASS 2. IT READS EACH LINE FROM THE
INTERMEDIATE FILE, AND CALLS P2_ASSEMBLE_INST AND P2_WRITE_OBJ
FOR EACH NON-COMMENT LINE. HOWEVER, P2_WRITE_OBJ IS CALLED ONLY
IF GENOBJECT = TRUE. GENOBJECT IS SET TO FALSE (TO SUPPRESS THE
OBJECT PROGRAM) IF ANY ASSEMBLY ERRORS ARE DETECTED. P2_WRITE_LIST
IS CALLED FOR EVERY LINE PROCESSED. */

	boolean genobject = true;
	intrettype intreturn;

	firststmt = true;
	endfound = false;
	textlength = 0;
	objfile = fopen("output.obj", "w");
	lisfile = fopen("output.lis", "w");
	intfile = fopen("output.tmp", "r");
	litpool1 = 0;
	litpool2 = 0;
	access_int_file(readline, &intreturn, &source, &errorsfound, &errorflags);
	while(intreturn != endfile)
	{
		objct.rectype = none;
		objct.objlength = 0;
		strncpy(objct.objcode, blank30, 30);
		if(! source.comline)
		{
			p2_assemble_inst(source, locctr, &errorsfound, &errorflags, &objct);
			if(errorsfound)
				genobject = false;
			if(genobject)
				p2_write_obj(objct, locctr, progname, proglength);
			if(newhead)
			{
				objct.rectype = headrec;
				objct.objlength = 0;
				p2_write_obj(objct, locctr, progname, proglength);
			}
		}
		p2_write_list();
		access_int_file (readline, &intreturn, &source, &errorsfound, &errorflags);
	}
	fclose(intfile);
	fclose(lisfile);
	fclose(objfile);
}
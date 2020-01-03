#ifndef MEMORY_H
#define MEMORY_H

/*	Memory organization in RISC-V type mirco-controller
		Program memory size (ROM):					32KB = 32768B
		Available addresses for program memory:		32768B/4B = 8192 = 0x2000
		Available address space for program memory: 0x0000 - 0x8000

		Data memory size (RAM):						16KB = 16384B
		Available addresses space for data memory:	16384B/4B = 4096 = 0x1000
		Available address space for data memory:	0xA000 - 0xE000

		A note about "Address" type size
		Address type is 32 bits, since the align to the PC register.
*/

#include <stdint.h>
#include <stdbool.h>
#include "MErrors.h"
#include "Parser.h"
#include "Debug.h"

#define CODE_BASE		0x0000
#define CODE_TOP		0x8000
#define CODE_SIZE		((CODE_TOP-CODE_BASE)/4)

#define DATA_BASE		0xA000
#define DATA_TOP		0xE000
#define DATA_SIZE		((DATA_TOP-DATA_BASE)/4)

#define REGISTERS_NO	31

typedef uint8_t		Byte;
typedef uint16_t	Word;
typedef uint32_t	DWord;
typedef int8_t		SByte;
typedef int16_t		SWord;
typedef int32_t		SDWord;

typedef uint32_t	Address;

typedef struct registers_t {
	SDWord rX[REGISTERS_NO + 1];
	DWord  PC;
	DWord  flags;
}Registers;

extern DWord	g_codeSpace[CODE_SIZE];
extern SDWord	g_dataSpace[DATA_SIZE];

extern Registers reg;

DWord	loadCodeWord(Address);
SDWord	loadDataWord(Address);
void	storeDataWord(Address, SDWord);

Address		getPC();
void		setPC(Address);
void		incPC();
SDWord		getRegister(Byte);
void		setRegister(Byte, SDWord);
DWord		getFlag(DWord);
int			setFlag();
void		resetFlag();
Byte		getRS1();
Byte		getRS2();
Byte		getRD();

Byte		getOpCode(DWord);
Byte		getFunct3(DWord);
Byte		getFunct7(DWord);

#endif 

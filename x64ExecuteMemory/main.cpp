#include <windows.h>
#include <iostream>

extern "C" {
	int executeAs();
}

typedef long (*JittedFunc)();

int main (int argc, char** argv)
{
	// Execute the function in the assembly file test.asm directly
	int i = executeAs();

	/**
	 * The code below mimics the execution of the assembly defined function executeAs() by inserting
	 * the binary value of the assembly code into memory and executing this memory
	 */
	
	// test.asm in binary code
	const unsigned char source[11] = {0x55, 0x48, 0x89, 0xE5, 0xB8, 0x0F, 0x00, 0x00, 0x00, 0x5D, 0xC3};

	// Allocate memory for the binary code
	void* address;
	address = VirtualAlloc(NULL, sizeof(char) * 11, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	// Make sure allocation went fine
	if (address == NULL) {
		return 0;
	}

	// Copy the binary code into the allocated memory
	address = memcpy(address, source, sizeof(char) * 11);

	// Confirm copying went fine
	if (address == NULL) {
		return 0;
	}

	// Cast the pointer to a function type
	JittedFunc func = (JittedFunc) address;

	// Execute the address/memory/function
	int r = func();

	return 1;
}
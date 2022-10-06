#ifndef TEXT_TOOLS_H
#define TEXT_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <filesystem>
#include <string.h>
#include <assert.h>

struct Bufer {
	char* data; 				// Global data from file
	unsigned long len;		// Length of data in chars, with closing \0
};


// -----------------------------Main functions of library--------------------------------------------------------------
struct Bufer* init_bufer_for_file (const char* input_file_name);						// Read text form file to buffer
void clean_file (const char* file_name);
void clean_memory_of_bufer (struct Bufer *bufer);									// Clean ouput file

// -----------------------------Internal functions----------------------------------------------------------------------
void read_from_file (struct Bufer* bufer, const char* input_file_name);    	// Read test form file to bufer->data
void format_text(struct Bufer* bufer);								// Delete extra spaces and /0 strings. Replace /r, /n -> /0.
unsigned long len_of_file(FILE* file);
int is_final_character(char c);                                     // Return 1, if char is '/0', '/n', '/r'
int is_punctuation_mark (char a);                                     // Is it not letter
#endif
#include "../include/proc.h"
#include "../include/text_tools.h"

struct Bufer* init_bufer_for_file (const char* input_file_name) {
	struct Bufer* bufer = (struct Bufer* ) calloc (1, sizeof (struct Bufer));
	DEBUG_MESSAGE(debug_print(DEBUG_MAIN_STEPS, "Allocation for buffer result = %lu.\n", sizeof(*bufer));)
	assert(bufer);

	read_from_file(bufer, input_file_name);
	format_text (bufer);
	return bufer;
}

void read_from_file (struct Bufer* bufer, const char* input_file_name) {
	assert (bufer);

	FILE* input_file = NULL;
	if ((input_file = fopen (input_file_name, "rb"))) {
		unsigned long len = len_of_file (input_file);
		bufer->len = len;

		char* data = (char* ) calloc (len, sizeof(char));
		DEBUG_MESSAGE(debug_print(DEBUG_MAIN_STEPS, "Allocated %lld bytes for data\n", len * sizeof(char));)

		fread (data, sizeof (char), len, input_file);
		DEBUG_MESSAGE(debug_print(DEBUG_MAIN_STEPS, "Len of input = %lld, len of data = %ld\n", len, strlen(data));)
		fclose (input_file);
		bufer->data = data;
	}
	else {
		DEBUG_MESSAGE(debug_print(ERR_LOGGING, "Error in InitText!\n");)
	}
}

void format_text (struct Bufer* bufer) {				// Removing extra spacing
	assert (bufer);
	assert (bufer->data);
	char* data = bufer->data;

	unsigned long low = 0;
	unsigned long fast = 0;
	unsigned long end = bufer->len - 1;

	while ((fast < bufer->len) && (is_final_character(data[fast]) || data[fast] == ' '))	fast++;		// Removing starting extra elements
	while ((end > 0) && (is_final_character(data[end]) || data[end] == ' '))	end--;		// Removing ending extra elements (need to put \0 in the end)

	if (fast > end) {
		data[0] = '\0';
		return;
	}

	while (fast + 1 <= end) {
		bool flag_new_str = false;
		bool flag_extra_symbols = false;
		while ((is_final_character(data[fast]) || data[fast] == ' ') && (is_final_character(data[fast + 1]) || data[fast + 1] == ' ')) {
			flag_extra_symbols = true;
			if (is_final_character(data[fast]) || is_final_character(data[fast + 1])) {
				flag_new_str = true;
			}
			fast++;
			if (fast > end) break;
		}
		if (flag_extra_symbols && flag_new_str) {
			data[low] = '\0';
		}
		else if (flag_extra_symbols) {
			data[low] = ' ';
		}
		else {
			if (is_final_character(data[fast])) {
				data[low] = '\0';
			}
			else {
				data[low] = data[fast];
			}
		}
		low++;
		fast++;
	}
	data[low] = data[end];
	low++;
	data[low] = '\0';
	bufer->len = low + 1;
	DEBUG_MESSAGE(debug_print(DEBUG_MAIN_STEPS, "New len of data = %lld\n", bufer->len);)
}

unsigned long len_of_file (FILE* file) {
	assert (file != NULL);

	fseek (file, 0, SEEK_END);
	unsigned long len = (unsigned long) ftell (file) + 1; //including in len the closing \0
	rewind(file);

	return len;
}

// Return 1, if char is '/0', '/n', '/r'.
int is_final_character (char c) {
	if (c == '\n' || c == '\r' || c == '\0')
		return 1;
	return 0;
}

int is_punctuation_mark (char a) {
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')) {
		return 0;
	}
	return 1;
}

void clean_file (const char* file_name) {
	FILE* out_file = NULL;
	out_file = fopen (file_name, "w");
	fclose (out_file);
}

void clean_memory_of_bufer (struct Bufer *bufer) {
	free (bufer->data);
	free (bufer);
	DEBUG_MESSAGE(debug_print(DEBUG_MAIN_STEPS, "End of programm\n");)
}
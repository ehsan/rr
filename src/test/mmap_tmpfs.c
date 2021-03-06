/* -*- Mode: C; tab-width: 8; c-basic-offset: 8; indent-tabs-mode: t; -*- */

#include "rrutil.h"

#define TEST_FILENAME "foo.so"
#define TOKEN "hello kitty"

int main(int argc, char *argv[]) {
	int fd = open(TEST_FILENAME, O_CREAT | O_EXCL | O_RDWR, 0700);
	char* bytes;

	write(fd, TOKEN, sizeof(TOKEN));
	close(fd);

	fd = open(TEST_FILENAME, O_RDONLY);
	bytes = (char*)mmap(NULL, 4096, PROT_READ | PROT_EXEC, MAP_PRIVATE,
			    fd, 0);
	test_assert(bytes);
	test_assert(!strcmp(bytes, TOKEN));
	munmap(bytes, 4096);
	close(fd);

	unlink(TEST_FILENAME);

	atomic_puts("EXIT-SUCCESS");
	return 0;
}

/* -*- Mode: C; tab-width: 8; c-basic-offset: 2; indent-tabs-mode: nil; -*- */

#include "rrutil.h"

static void sighandler(int sig) {
  /* Must be a syscall we've already executed, otherwise patching gets in the
   * way */
  open("/dev/zero", O_RDONLY);

  atomic_puts("EXIT-SUCCESS");

  exit(0);
}

int main(int argc, char* argv[]) {
  char ch;
  int fd = open("/dev/zero", O_RDONLY);

  signal(SIGSEGV, sighandler);

  read(fd, &ch, 1);

  *(int*)0 = 0;

  return 0;
}

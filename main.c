#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

static void
error_message(DWORD err) {
  static char buf[256] = {0};
  char *p = buf + sizeof(buf);
  if (err == 0) return;
  FormatMessage(
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      err,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      buf,
      sizeof buf,
      NULL);
  while (--p > buf) {
    if (*p == '\r' || *p == '\n') {
      *p = 0;
      break;
    }
  }
  fprintf(stderr, "%s\n", buf);
}

int
main(int argc, char *argv[]) {
  DWORD pid = atoi(argv[1]);
  PROCESSENTRY32 pe;
  HANDLE h;
  char fname[MAX_PATH];

  h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  pe.dwSize = sizeof(PROCESSENTRY32);
  if (!Process32First(h, &pe)) {
    error_message(GetLastError());
    return 1;
  }

  fname[0] = 0;

  do {
    if (pe.th32ParentProcessID == pid) {
      strncpy(fname, pe.szExeFile, MAX_PATH - 1);
    }
  } while (Process32Next(h, &pe));

  printf("%s\n", fname);
}

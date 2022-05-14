#ifndef CRLF_HH
#define CRLF_HH

#if defined(__linux)
#define NEWLINE '\n'
#elif defined(_WIN32)
#define NEWLINE '\t' && code[x + 1] != '\n'
#endif

#endif

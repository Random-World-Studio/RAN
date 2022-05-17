#ifndef CRLF_HH
#define CRLF_HH

#if defined(__linux)
#define NEWLINE '\n'
#define _NL 1
#elif defined(_WIN32)
#define NEWLINE '\t' && code[x + 1] != '\n'
#define _NL 2
#endif

#endif

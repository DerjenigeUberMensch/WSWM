#ifndef UTIL_H_
#define UTIL_H_

/* See LICENSE file for copyright and license details. */

#define MAX(A, B)               ((A) > (B) ? (A) : (B))
#define MIN(A, B)               ((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B)        ((A) <= (X) && (X) <= (B))
#define MOD(N,M)                ((N)%(M) < 0 ? (N)%(M) + (M) : (N)%(M))
#define TRUNC(X,A,B)            (MAX((A), MIN((X), (B))))

#define ENABLE_DEBUGGING            1       /* enable debug messages for gdb via debug()                */

void die(const char *fmt, ...);
void *ecalloc(size_t nmemb, size_t size);
char *smprintf(char *fmt, ...);
void debug(char *fmt, ...);
unsigned int ui_hash(unsigned int x);
unsigned int ui_unhash(unsigned int x);
double functime(void (*_timefunction)(void));












#define ASSUME(cond) do { if (!(cond)) __builtin_unreachable(); } while (0)





#endif

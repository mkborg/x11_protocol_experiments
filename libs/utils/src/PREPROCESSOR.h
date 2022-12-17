/*

  MACROSes for preprocessor.

*/
#if !defined PREPROCESSOR_h
#define PREPROCESSOR_h

#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

#define _STRING(x) #x

#define _MIN(a, b) (((a) < (b)) ? (a) : (b))
#define _MAX(a, b) (((a) > (b)) ? (a) : (b))

#define CONSTSTRLEN(s) (sizeof(s)-1)

#define STRNCMP1(s1, s2) strncmp((s1), (s2), CONSTSTRLEN(s1))
#define STRNCMP2(s1, s2) strncmp((s1), (s2), CONSTSTRLEN(s2))

#endif // !defined PREPROCESSOR_h

#pragma once

#ifdef __cplusplus
extern "C" int sum(int, int); // C++ compiler sees this
#else
int sum(int, int);           // C compiler sees this
#endif

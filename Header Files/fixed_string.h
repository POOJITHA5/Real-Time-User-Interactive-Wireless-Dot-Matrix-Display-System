#ifndef DOTMATRIX_DRIVER_H
#define DOTMATRIX_DRIVER_H

#include "types.h"

void Init_SIPO(void);
void Init_dotmatrix(void);
void display_str(u8 *,u32);
void scroll_string(u8 *);

#endif

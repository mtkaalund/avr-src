#ifndef BITS_H_
#define BITS_H_

#define bit_get(p,m)	((p) & (m))
#define bit_set(p,m)	((p) |= (m))
#define bit_clear(p,m)	((p) &= ~(m))
#define bit_flip(p,m)	((p) ^= (m))
#define BIT(x)		(0x01 << (x))

#endif

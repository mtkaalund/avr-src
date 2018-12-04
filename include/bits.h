#ifndef BITS_H_
#define BITS_H_

// If _BV is not defined anywhere else
// it will be defined here.
#ifndef _BV
#define _BV(x)		(0x01 << (x))
#endif

#define bit_mask_get(p,m)	((p) & (m))
#define bit_mask_set(p,m)	((p) |= (m))
#define bit_mask_clear(p,m)	((p) &= ~(m))
#define bit_mask_flip(p,m)	((p) ^= (m))

#define bit_get(p,b)		((p) & (_BV(b)))
#define bit_set(p,b)		((p) |= (_BV(b)))
#define bit_clear(p,b)		((p) &= (_BV(b)))
#define bit_flip(p,b)		((p) ^= (_BV(b)))

#endif

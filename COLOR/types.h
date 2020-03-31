#ifndef TYPES_H
#define TYPES_H

#define flip_bits(a) ((a) = ~(a))
#define bit_set(a, b) ((a) |= (1 << (b)))
#define bit_clear(a, b) ((a) &= ~(1 << (b)))
#define bit_clear_no_shift(a, b) ((a) &= ~(b))
#define bit_set_no_shift(a, b) ((a) |= (b))
#define bit_test(a, b) ((a) & (1 << (b)))
#define bit_toggle(a, b) ((a) ^= (1 << (b)))
#define bit_toggle_special(a, b) ((a) ^= (b))
#define bit_copy(a, mask, b) ( (a) =  ( (a) & (mask) )|( (b) & (~(mask) ) )
#define bit_set_special(a, b, c) ((a) |= ((b) << (c)))
#define alignto(p, bits) (((p) >> (bits)) << (bits))
#define aligntonext(p, bits) alignto(((p) + (1 << (bits)) - 1), (bits))
#define addr_roundup(addr, padding) ((((uint32_t)(addr) + (1 << padding) - 1) >> padding) << padding)

typedef unsigned long uint32_t;
typedef unsigned int uint16_t;
typedef unsigned char uint8_t;

#endif /* TYPES_H */
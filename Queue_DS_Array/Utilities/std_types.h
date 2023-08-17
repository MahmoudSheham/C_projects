/*
 * std_types.h
 *
 * Created: 11/22/2022 2:44:53 PM
 *  Author: Mahmoud
 */


#ifndef STD_TYPES_H_
#define STD_TYPES_H_


#ifndef NULL
#define NULL 0
#endif // NULL

#define ZERO 0

typedef char				uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned long		uint32_t;
typedef unsigned long long	uint64_t;

typedef signed char			sint8_t;
typedef signed short		sint16_t;
typedef signed long			sint32_t;
typedef signed long long	sint64_t;

#define TRUE				1
#define FALSE				0

#define sei()  __asm__ __volatile__ ("sei" ::: "memory")

#define cli()  __asm__ __volatile__ ("cli" ::: "memory")


#define ISR(INT_VECT)void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)

#endif /* STD_TYPES_H_ */

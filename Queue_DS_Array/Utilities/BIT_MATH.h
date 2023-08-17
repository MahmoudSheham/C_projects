/*
 * BIT_MATH.h
 *
 * Created: 11/22/2022 7:01:45 PM
 *  Author: Mahmoud
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(VAR,BIT)						(VAR |= (1<<BIT))
#define CLR_BIT(VAR,BIT)						(VAR &= ~(1<<BIT))
#define TOG_BIT(VAR,BIT)						(VAR ^= (1<<BIT))
#define GET_BIT(VAR,BIT)						((VAR>>BIT) & 0x1)



#endif /* BIT_MATH_H_ */
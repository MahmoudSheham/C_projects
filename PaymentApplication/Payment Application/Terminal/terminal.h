																		/**terminal.h file**/

#ifndef TERMINAL_H
#define TERMINAL_H

#include "../Card/card.h"

typedef struct ST_terminalData_t
{

	uint8_t transactionData[11];
	float transAmount;
	float maxTransAmount;
}ST_terminalData_t;

typedef enum EN_trminalError_t
{
 
	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, 
	INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_trminalError_t;

EN_trminalError_t getTransactionDate(ST_terminalData_t *terminalData);	                        
EN_trminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *terminalData);		
EN_trminalError_t getTransactonAmount(ST_terminalData_t *terminalData);						    
EN_trminalError_t isBelowMaxAmount(ST_terminalData_t *terminalData);							
EN_trminalError_t setMaxAmount(ST_terminalData_t *terminalData, float maxAmount);				
EN_trminalError_t isValidCardPAN(ST_cardData_t *cardData); 

/**Terminal Test Functions**/
void getTransactionDataTest(void);
void isCardExpiredTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void SetMaxAmountTest(void);
void isValidCardPANTest(void);

#endif /**TERMINAL_H**/
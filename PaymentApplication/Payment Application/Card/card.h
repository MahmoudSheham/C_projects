																					 /**card.h file**/

#ifndef CARD_H
#define CARD_H

#include "../Utilities/STD_TYPES.h"

typedef struct ST_cardData_t 
{

	uint8_t cardHolderName[25];
	uint8_t primaryAcuntNumber[20];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	
	CARD_OK, WRONG_NAME, WRONG_EX_DATE, WRONG_PAN
}EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

/**Test functions**/
void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

#endif /**CARD_H**/
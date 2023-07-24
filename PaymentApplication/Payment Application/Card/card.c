																			#include "card.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	/**vrbile to store the error state to be trturned to the user**/
	EN_cardError_t cardErrorHandler;

	/**varible to store the length of the holder user name**/
	uint32_t cardHolderNameLength = 0;
	
	/**Aske the user to enter the holder name**/
	printf("Please Enter The Card Holder Name: "); 
	
	/**Read the name from the user**/
	gets(cardData->cardHolderName);

	/**Get the length of the card holder name**/
	cardHolderNameLength = strlen((const char*)cardData->cardHolderName);

	/**check if the crd holder name length is valid**/
	if (cardHolderNameLength <20 || cardHolderNameLength > 24)
	{
		
		/**if the name is not valid return wrong name to the user**/
		cardErrorHandler = WRONG_NAME;
		return cardErrorHandler;
	}
	else 
	{
	
		/**if the name is valid return card ok**/
		cardErrorHandler = CARD_OK;
		return cardErrorHandler;
	}

}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{

	/**a vrable to store the error state**/
	EN_cardError_t cardErrorHandler = WRONG_EX_DATE;
	
	/**vrable to store the length of the date**/
	uint32_t cardExpiryDateLength = 0;
	
	/**vrible to store the manth to check if the manth is between 1 and 12**/
	uint8_t month = 0;

	/**ask the user to enter the expiry date**/
	printf("Please Enter The Expiry Date: ");

	/**read the date from the user**/
	gets(cardData->cardExpirationDate);

	/**calclate the length of the date**/
	cardExpiryDateLength = strlen((const char*)cardData->cardExpirationDate);

	/**check if the date is valide or not**/
	if (cardExpiryDateLength != 5)
	{

		/**if the date is not valid return wrong ex date**/
		cardErrorHandler = WRONG_EX_DATE;
		return cardErrorHandler;
	}
	else 
	{
	
		/**if the date is valid retuen card ok**/
		cardErrorHandler = CARD_OK;

		/**chec the formate of the date**/
		while(--cardExpiryDateLength)
		{			 
		
			if ( (cardExpiryDateLength != 2) &&(cardData->cardExpirationDate[cardExpiryDateLength] > '9' || cardData->cardExpirationDate[cardExpiryDateLength] < '0'))
			{
				cardErrorHandler = WRONG_EX_DATE;
				return cardErrorHandler;
			}
			else if (cardExpiryDateLength == 2 && cardData->cardExpirationDate[cardExpiryDateLength] != '/')
			{

				cardErrorHandler = WRONG_EX_DATE;
				return cardErrorHandler;
			}
		}
							
		/**convert the manth to a dicemel form**/
		month =  (cardData->cardExpirationDate[0] - '0')*10 + (cardData->cardExpirationDate[1] -'0');
		
		/**check if the manth is between 1 and 12**/
		if (month < 1 || month > 12)
		{
		
			/**if the month is grater than 12 or smoller than 1 return wrong ex date**/
			cardErrorHandler = WRONG_EX_DATE;
			return cardErrorHandler;
		}
	}

	return cardErrorHandler;
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{

	EN_cardError_t cardErroHndlerr;
	uint32_t cardPANLength = 0;

	/**aske the user to enter the PAN**/
	printf("Please Enter The Primary Acount Number: ");

	/**read the PAN from the user**/
	gets(cardData->primaryAcuntNumber);

	/**get the length of the PAN**/
	cardPANLength = strlen(cardData->primaryAcuntNumber);

	/**check if the PAN length is valid or not**/
	if (cardPANLength > 19 || cardPANLength < 16)
	{
		
		/**if the PAN length is not valid return wrong PAN**/
		cardErroHndlerr = WRONG_PAN;
		return cardErroHndlerr;

	}
	else 
	{
		
		/**if the PAN length is valid check the fromat of the PAN**/
		cardErroHndlerr = CARD_OK;

		/**check all the digets of the PAN is a nomric or not**/
		while(--cardPANLength)
		{
			
			/**if one of the digets is not niomric**/
			if (cardData->primaryAcuntNumber[cardPANLength] > '9' || cardData->primaryAcuntNumber[cardPANLength] < '0')
			{
				
				/**return wrong PAN**/
				cardErroHndlerr = WRONG_PAN;
				return cardErroHndlerr;
			}
		}
	}

	return cardErroHndlerr;
}

/**Card Test Function**/
void getCardHolderNameTest(void)
{
	static uint8_t counter = 0;
	EN_cardError_t carderrorHandler;
	ST_cardData_t cardData;
	uint8_t name[20];

	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: getCardHolderName\n");

	printf("Test Case %d:\n", counter++);
		
	/**test the function the get the hoder name from the user**/
	carderrorHandler = getCardHolderName(&cardData);

	printf("Expected Result: ");
	gets(name);

	printf("Actual Result: ");

	switch (carderrorHandler)
	{
	case CARD_OK:
		printf("CARD_OK\n");
		break;
	case WRONG_NAME:
		printf("WRONG_NAME\n");
		break;
	case WRONG_EX_DATE:
		printf("WRONG_EX_DATE\n");
		break;
	case WRONG_PAN:
		printf("WRONG_PAN\n");
		break;
	default:
		printf("Error\n");
		break;
	}
}

void getCardExpiryDateTest(void)
{
	static uint8_t counter = 0;
	EN_cardError_t carderror;
	ST_cardData_t cardData;
	uint8_t date[20];

	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: getCardExpiryDate\n");

	printf("Test Case %d:\n", counter++);

	/**printf("Input Data: ");**/
	carderror = getCardExpiryDate(&cardData);

	printf("Expected Result: ");
	gets(date);

	printf("Actual Result: ");

	switch (carderror)
	{
	case CARD_OK:
		printf("CARD_OK\n");
		break;
	case WRONG_NAME:
		printf("WRONG_NAME\n");
		break;
	case WRONG_EX_DATE:
		printf("WRONG_EX_DATE\n");
		break;
	case WRONG_PAN:
		printf("WRONG_PAN\n");
		break;
	default:
		printf("Error\n");
		break;
	}
	return;
}

void getCardPANTest(void)
{
	static uint32_t testNumber = 0;
	EN_cardError_t carderror;
	ST_cardData_t cardData;
	uint8_t PAN[50];

	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: getCardPAN\n");


	printf("Test Case %d:\n", testNumber);

	/**printf("Input Data: ");**/
	carderror = getCardPAN(&cardData);

	printf("Expected Result: ");
	gets(PAN);

	printf("Actual Result: ");

	switch (carderror)
	{
	case CARD_OK:
		printf("CARD_OK\n");
		break;
	case WRONG_NAME:
		printf("WRONG_NAME\n");
		break;
	case WRONG_EX_DATE:
		printf("WRONG_EX_DATE\n");
		break;
	case WRONG_PAN:
		printf("WRONG_PAN\n");
		break;
	default:
		printf("Error\n");
		break;
	}
}

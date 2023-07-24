																							   #include "terminal.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

EN_trminalError_t getTransactionDate(ST_terminalData_t *terminalData)
{

	time_t transactionDate = time(NULL);
	EN_trminalError_t terminalError = TERMINAL_OK;
	uint32_t transactionDateLen = 0;
	uint8_t character;

	/**read the local time from the system**/
	struct tm transactinTime = *localtime(&transactionDate);

    transactinTime.tm_mon++;
	transactinTime.tm_year += 1900;


	/**convert the system date to a string**/

	/**convert the day to a steing**/
	terminalData->transactionData[0] = transactinTime.tm_mday / 10 + '0';
	terminalData->transactionData[1] = transactinTime.tm_mday % 10 + '0';

	/**sbrate the day an month by a '/'**/
	terminalData->transactionData[2] = '/';

	/**convert the manth to a string**/
	terminalData->transactionData[3] = transactinTime.tm_mon / 10 + '0';
	terminalData->transactionData[4] = transactinTime.tm_mon % 10 + '0';

	/**sabrate the month and the yeare by a '/'**/
	terminalData->transactionData[5] = '/';

	/**convert the yeare to a string**/
	terminalData->transactionData[6] = transactinTime.tm_year / 1000 + '0';
	terminalData->transactionData[7] = (transactinTime.tm_year % 1000) / 100 + '0';
	terminalData->transactionData[8] = (transactinTime.tm_year % 100)/ 10 + '0';
	terminalData->transactionData[9] = transactinTime.tm_year % 10 + '0';

	/**terminate the sting with '\0'**/
	terminalData->transactionData[10] = '\0';

	return terminalError;
}

EN_trminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *terminalData)
{

	/**variable to store rhe error state**/
	EN_trminalError_t terminalError = EXPIRED_CARD;

	/**compare the date of the card wiht the system date**/
	if (cardData->cardExpirationDate[3] > terminalData->transactionData[8])
		terminalError = TERMINAL_OK;
	else if (cardData->cardExpirationDate[3] == terminalData->transactionData[8])
		if (cardData->cardExpirationDate[4] > terminalData->transactionData[9])
			terminalError = TERMINAL_OK;
		else if (cardData->cardExpirationDate[4] == terminalData->transactionData[9])
			if (cardData->cardExpirationDate[0] > terminalData->transactionData[3])
				terminalError = TERMINAL_OK;
			else if (cardData->cardExpirationDate[0] == terminalData->transactionData[3])
				if (cardData->cardExpirationDate[1] > terminalData->transactionData[4])
					terminalError = TERMINAL_OK;
	
	return terminalError;
}

EN_trminalError_t getTransactonAmount(ST_terminalData_t *terminalData)
{

	EN_trminalError_t terminalError = TERMINAL_OK;

	/**aske the user to enter the transaction amount**/
	printf("Please Enter The Transaction Amount: ");

	/**read the transaction amount from the user**/
	scanf("%f", &terminalData->transAmount);

	/**check if the transaction amount is below 0**/
	if (terminalData->transAmount < 0)
	{
	
		/**if the transaction amount is smollaer than 0 return invalid amount**/
		terminalError = INVALID_AMOUNT;
		
		/**set the tranaction amount to zero and return**/
		terminalData->transAmount = 0;
		return terminalError;
	}

	return terminalError;
}

EN_trminalError_t isBelowMaxAmount(ST_terminalData_t *terminalData)
{

	EN_trminalError_t terminalError = EXCEED_MAX_AMOUNT;

	/**check if the transaction amount is below the max amount**/
	if (terminalData->transAmount < terminalData->maxTransAmount)
	{

		/**if the transaction amount is below the max amount return terminal ok**/
		terminalError = TERMINAL_OK;
		return terminalError;
	}

	return terminalError;
}

EN_trminalError_t setMaxAmount(ST_terminalData_t *terminalData, float maxAmount)
{

	EN_trminalError_t terminalError = TERMINAL_OK;
	
	/**check if the max amount is below zero**/
	if (maxAmount < 0)
	{
		/**if themax amount is smoler than zero return invalid max amount**/
		terminalError =  INVALID_MAX_AMOUNT;
		
		/**set the terminal max amount to zero**/
		terminalData->maxTransAmount = 0;
		
		/**return from function**/
		return terminalError;
	}

	/**if the max amount is grater than zero **/
	/**set the max amount**/
	terminalData->maxTransAmount = maxAmount;

	/**return from function**/
	return terminalError;
}

EN_trminalError_t isValidCardPAN(ST_cardData_t *cardData)
{


	EN_trminalError_t terminalError = TERMINAL_OK;
	uint8_t index = 0;
	/**temp to store a diget from the PAN temprary**sum to stor the sum of the digets**/ 
	uint32_t sum = 0, temp = 0;

	/**loop until het the '\0'**/
	while(cardData->primaryAcuntNumber[index] != '\0')
	{
	
		/**convert the diget to disemel number**/
		temp = cardData->primaryAcuntNumber[index] - '0';
		
		/**if the index is even**/
		if (!(index%2))
		{
		
			/**maltiplay the diget by 2**/
			temp *= 2;

			/**if it grater than 9**/
			if (temp > 9)
			{
			
				temp = temp % 10 + temp / 10;
			}
		}

		/**add the temp to the sum**/
		sum += temp;
		index++;
	}

	/**if the sum % 10 != 0**/
	if (sum % 10)
	{
	
		/**return invalid card PAN**/
		terminalError = INVALID_CARD;
		return terminalError;
	}

	return terminalError;
}

/**Terminal Test Functions**/
void getTransactionDataTest(void)
{

	ST_terminalData_t data;
	ST_terminalData_t *terminalData = &data;
	EN_trminalError_t terminaError;
	static uint8_t counter = 0;
	uint8_t character[50];

	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: getTransactionDate\n");

	printf("Test Case %d:\n", counter++);
	
		
	printf("Input Data: ");
	terminaError = getTransactionDate(terminalData);
	printf("Read The Date From The System ... %s\n", terminalData->transactionData);
	printf("Expected Result: ");
	gets(character);
	printf("Actual Result: ");

	switch (terminaError)
	{
	case TERMINAL_OK:
		printf("TERMINAL_OK\n");
		break;
	case WRONG_DATE:
		printf("WRONG_DATE\n");
		break;
	case EXPIRED_CARD:
		printf("EXPIRED_CARD\n");
		break;
	case INVALID_CARD:
		printf("INVALID_CARD\n");
		break;
	case INVALID_AMOUNT:
		printf("INVALID_AMOUNT\n");
		break;
	case EXCEED_MAX_AMOUNT:
		printf("EXCEED_MAX_AMOUNT\n");
		break;
	case INVALID_MAX_AMOUNT:
		printf("INVALID_MAX_AMOUNT\n");
		break;
	default:
		printf("Error\n");
		break;
	}

}

void isCardExpiredTest(void)
{

	ST_terminalData_t data;
	ST_terminalData_t *terminalData = &data;
	EN_trminalError_t terminaError;
	static uint8_t counter = 0;
	uint8_t character[50];
	ST_cardData_t cData, *cardData = &cData;

	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: isCardExpiired\n");
	
	printf("Test Case %d:\n", counter++);
	terminaError = getTransactionDate(terminalData);
	printf("Input Data: ");
	getCardExpiryDate(cardData);
	terminaError = isCardExpired(cardData, terminalData);
	printf("Expected Result: ");
	gets(character);
	printf("Actual Result: ");
	switch (terminaError)
	{
	case TERMINAL_OK:
		printf("TERMINAL_OK\n");
		break;
	case WRONG_DATE:
		printf("WRONG_DATE\n");
		break;
	case EXPIRED_CARD:
		printf("EXPIRED_CARD\n");
		break;
	case INVALID_CARD:
		printf("INVALID_CARD\n");
		break;
	case INVALID_AMOUNT:
		printf("INVALID_AMOUNT\n");
		break;
	case EXCEED_MAX_AMOUNT:
		printf("EXCEED_MAX_AMOUNT\n");
		break;
	case INVALID_MAX_AMOUNT:
		printf("INVALID_MAX_AMOUNT\n");
		break;
	default:
		printf("Error\n");
		break;
	}
}

void getTransactionAmountTest(void)
{
	ST_terminalData_t data;
	ST_terminalData_t *terminalData = &data;
	EN_trminalError_t terminaError;
	static uint8_t counter = 0;
	uint8_t character[50];

	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: getTransactionAmount\n");
	
	printf("Test Case %d:\n", counter++);
	printf("Input Data: ");
	terminaError = getTransactonAmount(terminalData);
	printf("Expected Result: ");
	gets(character);
	gets(character);
	printf("Actual Result: ");
	switch (terminaError)
	{
	case TERMINAL_OK:
		printf("TERMINAL_OK\n");
		break;
	case WRONG_DATE:
		printf("WRONG_DATE\n");
		break;
	case EXPIRED_CARD:
		printf("EXPIRED_CARD\n");
		break;
	case INVALID_CARD:
		printf("INVALID_CARD\n");
		break;
	case INVALID_AMOUNT:
		printf("INVALID_AMOUNT\n");
		break;
	case EXCEED_MAX_AMOUNT:
		printf("EXCEED_MAX_AMOUNT\n");
		break;
	case INVALID_MAX_AMOUNT:
		printf("INVALID_MAX_AMOUNT\n");
		break;
	default:
		printf("Error\n");
		break;
	}
}

void isBelowMaxAmountTest(void)
{

	ST_terminalData_t data;
	ST_terminalData_t *terminalData = &data;
	EN_trminalError_t terminaError;
	static uint8_t counter = 0;
	uint8_t character[50];
	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: isBelowMaxAmount\n");
	
	printf("Test Case %d:\n", counter++);
	printf("Input Data -\"Not That Tme Max Amount Is 10000.00\": ");
	getTransactonAmount(terminalData);
	setMaxAmount(terminalData, 10000);
		
	terminaError = isBelowMaxAmount(terminalData);

	printf("Expected Result: ");

	gets(character);
	gets(character);

	printf("Actual Result: ");

	switch (terminaError)
	{
	case TERMINAL_OK:
		printf("TERMINAL_OK\n");
		break;
	case WRONG_DATE:
		printf("WRONG_DATE\n");
		break;
	case EXPIRED_CARD:
		printf("EXPIRED_CARD\n");
		break;
	case INVALID_CARD:
		printf("INVALID_CARD\n");
		break;
	case INVALID_AMOUNT:
		printf("INVALID_AMOUNT\n");
		break;
	case EXCEED_MAX_AMOUNT:
		printf("EXCEED_MAX_AMOUNT\n");
		break;
	case INVALID_MAX_AMOUNT:
		printf("INVALID_MAX_AMOUNT\n");
		break;
	default:
		printf("Error\n");
		break;
	}
}

void SetMaxAmountTest(void)
{

	ST_terminalData_t data;
	ST_terminalData_t *terminalData = &data;
	EN_trminalError_t terminaError;
	static uint8_t counter = 0;
	uint8_t character[50];
	float maxAmount = 0;

	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: setMaxAmount\n");	

	printf("Test Case %d:\n", counter++);

	printf("Input Data: ");

	scanf("%f", &maxAmount);
	terminaError = setMaxAmount(terminalData, maxAmount);;
	printf("Expected Result: ");

	gets(character);
	gets(character);

	printf("Actual Result: ");

	switch (terminaError)
	{
	case TERMINAL_OK:
		printf("TERMINAL_OK\n");
		break;
	case WRONG_DATE:
		printf("WRONG_DATE\n");
		break;
	case EXPIRED_CARD:
		printf("EXPIRED_CARD\n");
		break;
	case INVALID_CARD:
		printf("INVALID_CARD\n");
		break;
	case INVALID_AMOUNT:
		printf("INVALID_AMOUNT\n");
		break;
	case EXCEED_MAX_AMOUNT:
		printf("EXCEED_MAX_AMOUNT\n");
		break;
	case INVALID_MAX_AMOUNT:
		printf("INVALID_MAX_AMOUNT\n");
		break;
	default:
		printf("Error\n");
		break;
	}

}

void isValidCardPANTest(void)
{

	ST_terminalData_t data;
	ST_terminalData_t *terminalData = &data;
	EN_trminalError_t terminaError;
	static uint8_t counter = 0;
	uint8_t character[50];
	ST_cardData_t cData, *cardData = &cData;

	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: isValidCardPAN\n");
	 
	printf("Test Case %d:\n", counter++);
	printf("Input Data: ");
	getCardPAN(cardData);
	terminaError = isValidCardPAN(cardData);
	printf("Expected Result: ");
	gets(character);
	printf("Actual Result: ");
	switch (terminaError)
	{
	case TERMINAL_OK:
		printf("TERMINAL_OK\n");
		break;
	case WRONG_DATE:
		printf("WRONG_DATE\n");
		break;
	case EXPIRED_CARD:
		printf("EXPIRED_CARD\n");
		break;
	case INVALID_CARD:
		printf("INVALID_CARD\n");
		break;
	case INVALID_AMOUNT:
		printf("INVALID_AMOUNT\n");
		break;
	case EXCEED_MAX_AMOUNT:
		printf("EXCEED_MAX_AMOUNT\n");
		break;
	case INVALID_MAX_AMOUNT:
		printf("INVALID_MAX_AMOUNT\n");
		break;
	default:
		printf("Error\n");
		break;
	}
}

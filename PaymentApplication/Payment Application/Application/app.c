#include <stdio.h>
#include <string.h>
#include "app.h"

float terminalMaxAmount = 10000;

void appStart(void)
{

	/**stor the card date**/
	ST_cardData_t cardData;

	/**stor the recevde the error returned from the card module**/
	EN_cardError_t cardError;
	
	/**stor the receved error the returned from the terminal moudule**/
	EN_trminalError_t terminalError;

	/**stor the terminal data**/
	ST_terminalData_t terminalData;
	
	/**to stor the transaction state**/
	EN_transState_t transState;

	/**to stor the transaction data**/
	ST_transaction_t transData;

	/**Ask the user to enter the card data**/
	cardError = getCardHolderName(&transData.CardHolderData);
	if(cardError == WRONG_NAME)
	{
	
		/**if the name is uncorrect print a masig to the user**/
		printf("The Card Holder Name Is Uncorrect\nPlease Tray Again\n");
		return;
	}

	/**get the expiration date from the user**/
	cardError = getCardExpiryDate(&transData.CardHolderData);
	if(cardError == WRONG_EX_DATE)
	{
	
		/**if the ex date is uncorrect print a masig to the user**/
		printf("Teh Exparation Date Is Uncorrect\nPlease Tray Again\n");
		return;
	}

	/**get the PAN from the user**/
	cardError = getCardPAN(&transData.CardHolderData);
	if(cardError == WRONG_PAN)
	{
	
		/**if the PAN is uncorrect print a masig to the user**/
		printf("The PAN Is Uncorrect\nPlease Tray Again\n");
		return;
	}

	/**The trminal prossceing**/
	/**read the system date**/
	terminalError = getTransactionDate(&transData.terminalData);
	if(terminalError == WRONG_DATE)
	{
	
		/**if ther a problem in the date prin masig in the screen**/
		printf("The Transaction Date Is Uncorrect\nPlease Tray Again\n");
		return;
	}

	/**check if the card expired or not**/
	terminalError = isCardExpired(&transData.CardHolderData, &transData.terminalData);
	if(terminalError == EXPIRED_CARD)
	{
	
		printf("The Card Expired\nPlease Tray With An Unexpired Card\n");
		return;
	}

	/**get the transaction amount from the user**/
	terminalError = getTransactonAmount(&transData.terminalData);
	if(terminalError == INVALID_AMOUNT)
	{
	
		printf("Ivalid Amount\nPlease Tray Again\n");
			return;
	}

	/**set the max amount of the terminal**/
	terminalError = setMaxAmount(&transData.terminalData, terminalMaxAmount);
	if(terminalError == INVALID_MAX_AMOUNT)
	{
	
		printf("Invalid Max Amount\nPlease Tray Again\n");
		return;
	}

	/**check if the transaction amount is below the max amount or not**/
	terminalError = isBelowMaxAmount(&transData.terminalData);
	if(terminalError == EXCEED_MAX_AMOUNT)
	{
	
		printf("Exeed The Max Amount\nPlease Tray Again\n");
		return;
	}

	/**check if the PAN is valid or not**/
	terminalError = isValidCardPAN(&transData.CardHolderData);
	if(terminalError == INVALID_CARD)
	{
	
		printf("Invald PAN\nPlease Tray Again\n");
		return;
	}

	/**The server prossceing**/
	/**receve the transaction data from the server**/
	transState = receieveTransactionData(&transData);
}

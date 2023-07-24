#include "server.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**accounts data base**/
ST_accountsDB_t accountsDB[255] = {{1000, BLOCKED, "8989374615436851"},		//blocked account
								   {30000.0, BLOCKED, "5807007076043875"}, 	//blocked account
								   {1000.0, RUNNING, "4003600000000014"},	//running account
								   {10000.0, BLOCKED, "0000000000000000"},		//blocked account
								   {600.0, RUNNING, "4200123000000208"}};	//running account
/**server side data base**/
ST_transaction_t serverSideTransactionData[255] ={0};

/**transaction sequnce number**/
uint8_t TSNumber = 0;

EN_transState_t receieveTransactionData(ST_transaction_t *transData)
{

	EN_transState_t transStateErrorHandler = APPROVED;
	EN_serverError_t serverErrorHandler;
	ST_accountsDB_t accountTemp;
	ST_accountsDB_t *accountRefrence = &accountTemp;
	uint8_t counter = 0;

	accountRefrence->balance = 0;
	for(counter = 0; counter < 20; counter++)
		accountRefrence->primaryAccountNumber[counter] = 0;
	accountRefrence->state = BLOCKED;

	serverErrorHandler = isValidAccount(&transData->CardHolderData, &accountRefrence);
	if (serverErrorHandler == ACCOUNT_NOT_FOUND)
	{
	
		transStateErrorHandler = FRAUD_CARD;
	}
	else 
	{
		serverErrorHandler = isAmountAvailable(&transData->terminalData, accountRefrence);
		if(serverErrorHandler == LOW_BALANCE)
		{
	
			transStateErrorHandler = DECLEINED_INSUFFECIENT_FUND;
		}
		else
		{
			serverErrorHandler = isBlockedAccount(accountRefrence);
			if(serverErrorHandler == BLOCKED_ACCOUNT)
			{
	
				transStateErrorHandler = DECLIND_STOLEN_CARD;
			}
		}
	}
	transData->transState = transStateErrorHandler;
	serverErrorHandler = saveTransaction(transData);
	if(serverErrorHandler != SERVER_OK)
	{
	
		transStateErrorHandler = INTERNAL_SERVER_ERROR;
		transData->transState = transStateErrorHandler;
		return transStateErrorHandler;
	}

	if(transStateErrorHandler == APPROVED)
		accountRefrence->balance = accountRefrence->balance - transData->terminalData.transAmount;
	
	return transStateErrorHandler;
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountRefrence)
{

	uint8_t validationFlag = TRUE;
	uint16_t counter = 0;
	uint8_t index = 0;
	EN_serverError_t serverError = ACCOUNT_NOT_FOUND;

	for(counter = 0; counter < 255; counter++)
	{
	
		if(strlen((const char*)cardData->primaryAcuntNumber) != strlen((const char*)accountsDB[counter].primaryAccountNumber))
			continue;
		while(cardData->primaryAcuntNumber[index] != '\0')
		{
		
			if(cardData->primaryAcuntNumber[index] != accountsDB[counter].primaryAccountNumber[index])
			{
			
				validationFlag = FALSE;
				break;
			}
			index++;
		}
		
		if(validationFlag)
		{

			serverError = SERVER_OK;
			*accountRefrence = &(accountsDB[counter]);
			return serverError;
		}
	
		validationFlag = TRUE;
	}

	accountRefrence = NULL;
	return serverError;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{

	EN_serverError_t serverErrorHandler = SERVER_OK;

	if (accountRefrence->state == BLOCKED)
	{
	
		serverErrorHandler = BLOCKED_ACCOUNT;
		return serverErrorHandler;
	}

	return serverErrorHandler;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *terminalData, ST_accountsDB_t *accountRefrence)
{

	/**varable to store the error state**/
	EN_serverError_t serverErrorHandler = LOW_BALANCE;

	/**chec if the balance is grater than the balance that the user will use**/
	if (accountRefrence->balance > terminalData->transAmount)
	{
	
		/**return server ok**/
		serverErrorHandler =  SERVER_OK;
		return serverErrorHandler;
	}

	return serverErrorHandler;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{

	EN_serverError_t serverError = SERVER_OK;
	uint8_t counter =0;

	serverSideTransactionData[TSNumber].transState = transData->transState;
	serverSideTransactionData[TSNumber].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
	serverSideTransactionData[TSNumber].terminalData.transAmount = transData->terminalData.transAmount;
	for (counter = 0; counter < 25; counter++)
	{
		

		serverSideTransactionData[TSNumber].CardHolderData.cardHolderName[counter] = transData->CardHolderData.cardHolderName[counter];

		if(counter < 6)
			serverSideTransactionData[TSNumber].CardHolderData.cardExpirationDate[counter] = transData->CardHolderData.cardExpirationDate[counter];
		
		if(counter < 20)
			serverSideTransactionData[TSNumber].CardHolderData.primaryAcuntNumber[counter] = transData->CardHolderData.primaryAcuntNumber[counter];

		if(counter < 11)
			serverSideTransactionData[TSNumber].terminalData.transactionData[counter] = transData->terminalData.transactionData[counter];
	}

	TSNumber++;

	listSavedTransactions();

	return serverError;
}

void listSavedTransactions(void)
{

	uint8_t counter = 0;

	for(counter = 0; counter < TSNumber; counter++)
	{

		printf("___________________________________________________________________________________________________________________\n");
		printf("Transaction Sequnce Number: %d\n", counter);
		printf("Transaction Date: %s\n", serverSideTransactionData[counter].terminalData.transactionData);
		printf("Transaction Amount: %f\n",serverSideTransactionData[counter].terminalData.transAmount);
		switch (serverSideTransactionData[counter].transState)
		{
		case APPROVED:
			printf("Transaction State: APPROVED\n");
			break;
		case DECLEINED_INSUFFECIENT_FUND:
			printf("Transaction State: DECLEINED_INSUFFECIENT_FUND\n");
			break;
		case DECLIND_STOLEN_CARD:
			printf("Transaction State: DECLIND_STOLEN_CARD\n");
			break;
		case FRAUD_CARD:
			printf("Transaction State: FRAUD_CARD\n");
			break;
		case INTERNAL_SERVER_ERROR:
			printf("Transaction State: INTERNAL_SERVER_ERROR\n");
			break;
		default:
			printf("Transaction State: ERROR STATE NOT FOUND\n");
			break;
		}
		printf("Transaction Max Amount: %f\n", serverSideTransactionData[counter].terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n", serverSideTransactionData[counter].CardHolderData.cardHolderName);
		printf("PAN: %s\n", serverSideTransactionData[counter].CardHolderData.primaryAcuntNumber);
		printf("Card Expiration Date: %s\n",serverSideTransactionData[counter].CardHolderData.cardExpirationDate);
		printf("___________________________________________________________________________________________________________________\n");
	}

	return;
}

/**Server Test Functons**/
void receieveTransactionDataTest(void)
{

	ST_transaction_t tData, *transData = &tData;
	EN_transState_t transState;
	static uint8_t counter = 0;
	uint8_t character[20];
	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: receieveTransactionData\n");

	printf("Test Case %d:\n", counter++);
	printf("Input Data: \n");

	getCardHolderName(&transData->CardHolderData);
	getCardExpiryDate(&transData->CardHolderData);
	getCardPAN(&transData->CardHolderData);
	getTransactionDate(&transData->terminalData);
	isCardExpired(&transData->CardHolderData, &transData->terminalData);
	getTransactonAmount(&transData->terminalData);
	setMaxAmount(&transData->terminalData, 10000);
	isBelowMaxAmount(&transData->terminalData);
	isValidCardPAN(&transData->CardHolderData);
	transState = receieveTransactionData(transData);	

	printf("Expected Result: ");
	gets(character);
	gets(character);
	printf("Actual Result: ");
	switch (transState)
	{
	case APPROVED:
		printf("APPROVED\n");
		break;
	case DECLEINED_INSUFFECIENT_FUND:
		printf("DECLEINED_INSUFFECIENT_FUND\n");
		break;
	case DECLIND_STOLEN_CARD:
		printf("DECLIND_STOLEN_CARD\n");
		break;
	case FRAUD_CARD:
		printf("FRAUD_CARD\n");
		break;
	case INTERNAL_SERVER_ERROR:
		printf("INTERNAL_SERVER_ERROR\n");
		break;
	default:
		printf("ERROR STATE NOT FOUND\n");
		break;
	}
}

void isValidAccountTest(void)
{

	ST_transaction_t transactionData, *transData = &transactionData;
	static uint8_t counter = 0;
	uint8_t character[20];
	ST_cardData_t cardDataTemp, *cardData = &cardDataTemp;
	ST_accountsDB_t accountRefranceTemp,
		*accountRefrancePointer = &accountRefranceTemp, 
		**accountRefrence = &accountRefrancePointer;
	EN_serverError_t serverError;

	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: isValidAccount\n");

	printf("Test Case %d:\n", counter++);
	printf("Input Data: \n");
	getCardHolderName(cardData);
	getCardExpiryDate(cardData);
	getCardPAN(cardData);;
	serverError = isValidAccount(cardData, accountRefrence);

	printf("\nExpected Result: ");
	gets(character);
	printf("Actual Result: ");

	switch (serverError)
	{
	case SERVER_OK:
		printf("SERVER_OK\n");
		break;
	case SAVING_FAILED:
		printf("SAVING_FAILED\n");
		break;
	case TRANSACTION_NOT_FOUND:
		printf("TRANSACTION_NOT_FOUND\n");
		break;
	case ACCOUNT_NOT_FOUND:
		printf("ACCOUNT_NOT_FOUND\n");
		break;
	case LOW_BALANCE:
		printf("LOW_BALANCE\n");
		break;
	case BLOCKED_ACCOUNT:
		printf("BLOCKED_ACCOUNT\n");
		break;
	default:
		printf("ERROR STATE NOT FOUND\n");
		break;
	}
}

void isBlockedAccountTest(void)
{

	ST_transaction_t tData, *transData = &tData;
	static uint8_t counter = 0;
	uint8_t character[20];
	ST_cardData_t cData, *cardData = &cData;
	ST_accountsDB_t AR, *aRef = &AR, **accountRefrence = &aRef;
	EN_serverError_t serverError;

	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: isBlockedAccount\n");

	printf("Test Case %d:\n", counter++);
	printf("Input Data: \n");
		
	getCardHolderName(cardData);
	getCardExpiryDate(cardData);
	getCardPAN(cardData);
	isValidAccount(cardData, accountRefrence);
	serverError = isBlockedAccount(aRef);

	printf("Expected Result: ");
	gets(character);
	printf("Actual Result: ");
	switch (serverError)
	{
	case SERVER_OK:
		printf("SERVER_OK\n");
		break;
	case SAVING_FAILED:
		printf("SAVING_FAILED\n");
		break;
	case TRANSACTION_NOT_FOUND:
		printf("TRANSACTION_NOT_FOUND\n");
		break;
	case ACCOUNT_NOT_FOUND:
		printf("ACCOUNT_NOT_FOUND\n");
		break;
	case LOW_BALANCE:
		printf("LOW_BALANCE\n");
		break;
	case BLOCKED_ACCOUNT:
		printf("BLOCKED_ACCOUNT\n");
		break;
	default:
		printf("ERROR STATE NOT FOUND\n");
		break;
	}
}

void isAmountAvailableTest(void)
{

	ST_transaction_t tData, *transData = &tData;
	static uint8_t counter = 0;
	uint8_t character[20];
	ST_cardData_t cData, *cardData = &cData;
	ST_accountsDB_t AR, *aRef = &AR, **accountRefrence = &aRef;
	EN_serverError_t serverError;

	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: isAmountAvailable\n");								   

	printf("Test Case %d:\n", counter++);
	printf("Input Data: \n");

	getCardHolderName(&transData->CardHolderData);
	getCardExpiryDate(&transData->CardHolderData);
	getCardPAN(&transData->CardHolderData);
	getTransactionDate(&transData->terminalData);
	isCardExpired(&transData->CardHolderData, &transData->terminalData);
	getTransactonAmount(&transData->terminalData);
	setMaxAmount(&transData->terminalData, 10000);
	isBelowMaxAmount(&transData->terminalData);
	isValidCardPAN(&transData->CardHolderData);
	isValidAccount(&transData->CardHolderData, accountRefrence);
	serverError = isAmountAvailable(&transData->terminalData, aRef);
	printf("Expected Result: ");
	gets(character);
	gets(character);

	printf("Actual Result: ");
	switch (serverError)
	{
	case SERVER_OK:
		printf("SERVER_OK\n");
		break;
	case SAVING_FAILED:
		printf("SAVING_FAILED\n");
		break;
	case TRANSACTION_NOT_FOUND:
		printf("TRANSACTION_NOT_FOUND\n");
		break;
	case ACCOUNT_NOT_FOUND:
		printf("ACCOUNT_NOT_FOUND\n");
		break;
	case LOW_BALANCE:
		printf("LOW_BALANCE\n");
		break;
	case BLOCKED_ACCOUNT:
		printf("BLOCKED_ACCOUNT\n");
		break;
	default:
		printf("ERROR STATE NOT FOUND\n");
		break;
	}
}

void saveTransactionTest(void)
{
   
	ST_transaction_t tData, *transData = &tData;
	static uint8_t counter = 0;
	uint8_t character[20];
	ST_cardData_t cData, *cardData = &cData;
	ST_accountsDB_t AR, *aRef = &AR, **accountRefrence = &aRef;
	EN_serverError_t serverError;

	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: saveTransaction\n");

	printf("Test Case %d:\n", counter++);
	printf("Input Data: \n");
	getCardHolderName(&transData->CardHolderData);
	getCardExpiryDate(&transData->CardHolderData);
	getCardPAN(&transData->CardHolderData);
	getTransactionDate(&transData->terminalData);
	isCardExpired(&transData->CardHolderData, &transData->terminalData);
	getTransactonAmount(&transData->terminalData);
	setMaxAmount(&transData->terminalData, 10000);
	isBelowMaxAmount(&transData->terminalData);
	isValidCardPAN(&transData->CardHolderData);
	isValidAccount(&transData->CardHolderData, accountRefrence);
	isAmountAvailable(&transData->terminalData, aRef);
	serverError = saveTransaction(transData);	

	printf("Expected Result: ");
	gets(character);
	gets(character);

	printf("Actual Result: ");
	switch (serverError)
	{
	case SERVER_OK:
		printf("SERVER_OK\n");
		break;
	case SAVING_FAILED:
		printf("SAVING_FAILED\n");
		break;
	case TRANSACTION_NOT_FOUND:
		printf("TRANSACTION_NOT_FOUND\n");
		break;
	case ACCOUNT_NOT_FOUND:
		printf("ACCOUNT_NOT_FOUND\n");
		break;
	case LOW_BALANCE:
		printf("LOW_BALANCE\n");
		break;
	case BLOCKED_ACCOUNT:
		printf("BLOCKED_ACCOUNT\n");
		break;
	default:
		printf("ERROR STATE NOT FOUND\n");
		break;
	}
}

void listSavedTransactionsTest(void)
{

	static uint8_t counter = 0;
	printf("Tester Name: Mahmoud Sheham\n");
	printf("Function Name: listSavedTransactions\n");

	printf("\nTest Case %d:\n", counter++);
	printf("Input Data: \n");

	//appStart();
	counter++;
}

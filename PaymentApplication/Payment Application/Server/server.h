																		/**server.h file**/

#ifndef SERVER_H
#define SERVER_H
			 
#include "../Terminal/terminal.h"

typedef enum EN_transState_t
{

	APPROVED, DECLEINED_INSUFFECIENT_FUND, DECLIND_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{

	ST_cardData_t CardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
}ST_transaction_t;

typedef enum EN_serverError_t
{

	SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND,ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

typedef enum EN_accountState_t
{

	RUNNING,
	BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{

	float balance;
	EN_accountState_t state;
	uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

EN_transState_t receieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t **accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *terminalData, ST_accountsDB_t *accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
void listSavedTransactions(void);

/**Server Test Functons**/
void receieveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);
void listSavedTransactionsTest(void);
#endif /**SERVER_H**/
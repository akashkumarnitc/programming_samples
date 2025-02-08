#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// structure to store account details.
 struct Account{
	int accountNumber;
	char name[50];
	float balance;
	

};

// function to creat a new account.

void createAccount(){
	struct Account acc;
	FILE *file = fopen("account.dat","ab+");
	
	if(file == NULL){
		printf("error opening file!\n");
		return;
	}
	printf("Enter account number: ");
	scanf("%d",&acc.accountNumber);
	printf("Enter account holder's name: ");
	scanf("%[^\n]",acc.name);
	printf("Enter initial balance: ");
	scanf("%f",&acc.balance);
	fwrite(&acc,sizeof(struct Account),1,file);
	fclose(file);
	printf("Account created successfully!\n");


}

//function to deposite money

void depositMoney(){
	int accountNumber;
	float amount;
	struct Account acc;
	FILE *file = fopen("accounts.dat","rb+");

	if(file == NULL){
		printf("error in getting your account!");
		return;
	}

	printf("Enter Account number: ");
	scanf("%d",&accountNumber);
	printf("Enter ammount to be deposited: ");
	scanf("%f",&amount);

	int found = 0;
	while(fread(&acc,sizeof(struct Account),1,file)){
		if(acc.accountNumber == accountNumber){
			found =1;
			acc.balance+=amount;
			fseek(file, -sizeof(struct Account),SEEK_CUR);
			fwrite(&acc,sizeof(struct Account),1,file);
			printf("Deposite successful! New balance: %.2f\n", acc.balance);
			break;
		}



	}

	if(!found){
		printf("Account not found!\n");
	}

	fclose(file);


}


//funtion to withdraw money

void withdrawMoney(){
	int accountNumber;
	float amount;
	struct Account acc;
	FILE *file = fopen("account.dat","rb+");
	
	if(file ==NULL){
		printf("Error opening file!");
		return;
	}
	
	printf("Enter Account Number: ");
	scanf("%d",&accountNumber);
	printf("Enter ammount to withdraw: ");
	scanf("%f",amount);

	int found =0;
	while(fread(&acc,sizeof(struct Account),1,file)){
		if(acc.accountNumber == accountNumber){
		found =1;
		if(acc.balance >= amount){
			acc.balance -= amount;
			fseek(file,-sizeof(struct Account), SEEK_CUR);
			fwrite(&acc, sizeof(struct Account),1,file);
			printf("Withdrawal succesful ! New balance: %.2f\n", acc.balance);

		}else{printf("Insufficient balance!\n");
			}
		break;
		}
	}
	if(!found){printf("Account not found!\n");
	}
	fclose(file);
}

//function to check balance

void checkBalance(){
	int accountNumber;
	struct Account acc;
	FILE *file = fopen("account.dat","rb");
	
	if(file == NULL){
	printf("Error in opening file!");
	return;
	}
	
	printf("Enter Account Number: ");
	scanf("%d",&accountNumber);

	int found = 0;
	while(fread(&acc,sizeof(struct Account),1,file)){
		if(acc.accountNumber == accountNumber){
			found =1;
			printf("Account Holder: %s\n",acc.name);
			printf("Current balance: %.2f\n",acc.balance);
			break;
		}
	}
	if(!found){
		printf("Account not found!");
	}
	fclose(file);
}


// main menu

int main(){
	int choice;
	while(1){
		printf("\n Bank Management System\n");
		printf("1. Create Account\n");
		printf("2. Deposit Money\n");
		printf("3. Withdraw Money\n");
		printf("4. Check Balance\n");
		printf("5. To Exit..\n");
		printf("Enter Your Choice: ");
		scanf("%d", &choice);
		
		switch(choice){
			case 1:
				createAccount();
				break;
			case 2:
				depositMoney();
				break;
			case 3:
				withdrawMoney();
				break;
			case 4:
				checkBalance();
				break;
			case 5:
				printf("Exiting...\n");
				exit(0);
			default:
				printf("Invalid choice please try again\n");
		}
	}

	return 0;
}

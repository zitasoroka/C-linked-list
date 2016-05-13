/*
From D14124330, Zita Soroka
This program captures transactions of a bank account.
A linked list is used to implement this which is a part of a bank account class.
The program contains:
-main function;
-function to create a linked list;
-function to add a node to the list;
-function to delete node from the list;
-function to traverse the list;
-function to search for a node;

I have included a few additional functions:
-function to deposit to the account;
-function to withdraw from the account;
*/

#include <iostream>
#include <string>

using namespace std;


class Account{

public:
    int accNo;
    static float balance;
    char accName[23];

    struct Transaction{
    int id;
    float amount;
    char description[50];
    Transaction *next;
    }*head, *cur; *prev; *ptr;

    struct Account::Transaction* initTransaction(float);
    struct Account::Transaction* searchNode(int);
    Account();
    void deposit();
    void withdraw();
    void deleteNode();
    void addTransaction(struct Transaction*);
    void displayTransactions();
    void actionrequest();
};

    float Account::balance=0;

    //Account constructor
    Account::Account(){

        head=0;
        cout<<"Enter account number : ";
        cin>>accNo;
        cout<<"Enter name of an account holder : ";
        cin.ignore();
        cin.getline(accName, 23);
    }

    //Function to deposit to the account
    //Which also calls a function to initialise a new transaction
    void Account::deposit(){
        float a;
        cout<<"Enter amount to deposit: ";
        cin>>a;
        Account::balance+=a;
        initTransaction(a);
    }

    //Function to withdraw from the account
    //Which also calls a function to initialise a new transaction
    void Account::withdraw(){
        float b;
        cout<<"Enter amount to withdraw: ";
        cin>>b;
        if(b>balance){
            cout<<"Not enough funds in the Account"<<endl;
        }
        else{
            Account::balance-=b;
            initTransaction(b);
        }
    }

    //Function to create a new node of type Transaction
    //Which also have another function that adds the newly created transaction to a transaction list
    struct Account::Transaction* Account::initTransaction(float i){
        Transaction *newT = new Transaction;
        newT->amount=i;
            cout<<"Enter Transaction id: ";
            cin>>newT->id;
            cout<<"Enter transaction description: ";
            cin.ignore();
            cin.getline(newT->description, 50);
        newT->next=NULL;
        addTransaction(newT);
        return newT;
    }

    //Function which when run first time initialises a Transactions list
    //After initial run it adds a Transaction passed in to a list
    void Account::addTransaction(struct Transaction *newNode){
        if(head==NULL){
            head=newNode;
            return;
        }
        Transaction *cur=head;
        while(cur){
            if(cur->next==NULL){
                cur->next=newNode;
                return;
            }
            cur=cur->next;
        }
    }

    //Returning a pointer to a node which data element 'id' is equal or less than input data
    struct Account::Transaction* Account::searchNode(int n){
        if(head == NULL) return head;
        Transaction *cur = head;
        Transaction *prev = head;
        while(cur){
            if(cur->id == n) return cur;
            if(cur->id > n) return prev;
            prev = cur;
            cur = cur->next;
        }
    }

    //Function to delete a node from a Transaction list
    void Account::deleteNode(){
        int transactionID;
        cout<<"Enter Transaction id: ";
        cin>>transactionID;
        Transaction *ptr = searchNode(transactionID);
        if(ptr == NULL)
            cout<<"No node with data= "<<transactionID<<endl;
        if(ptr == head){
            head = ptr->next;
            return;
        }
        Transaction *cur = head;
        Transaction *prev = head;

        while(cur){
            if(cur==ptr){
                prev->next = cur->next;
                return;
            }
            prev=cur;
            cur=cur->next;
        }
    }

    //Function to traverse the list of Transactions displaying the data element
    void Account::displayTransactions(){
        struct Transaction *list=head;
            cout <<"=========================================="<<endl;
            cout <<"The list of payments on the account are: "<<endl;
            while(list){
                    cout<<"Transaction id: "<<list->id<<endl;
                    cout<<"Transaction amount: "<<list->amount<<endl;
                    cout<<"Transaction description: "<<list->description<<endl;
                    list=list->next;
        }
        cout <<"==========================================="<<endl;
        cout <<'\n';
    }

    //Function to request an action from a user
    //Each choice is associated with an appropriate function
    void Account::actionrequest(){

    int i;

    cout<<"Would you like to do:"<<endl;
    cout<<" 1. Deposit"<<endl;
    cout<<" 2. Withdraw"<<endl;
    cout<<" 3. Remove a transaction"<<endl;
    cout<<" 4. Display all transactions"<<endl;
    cout<<" 5. I'm finished"<<endl;


    cin>>i;
    if(i==1){
        deposit();
        actionrequest();
        }
    else if(i==2){
        withdraw();
        actionrequest();
    }
    else if(i==3){
        deleteNode();
        actionrequest();
    }
    else if(i==4){
        displayTransactions();
        actionrequest();
    }
    else if(i==5){
        return;
    }
    else{
        while(cin.fail()) {
            cout << "Please enter a value as above: 1, 2, 3, 4 or 5"<< endl;
            cin.clear();
            cin.ignore('\n');
            cin>>i;
        }
        actionrequest();
        }
}

int main(){

    Account myAcc;
    myAcc.actionrequest();


    return 0;
}

/*
 * The Bank takes commands from stdin as well as from the ATM.  
 *
 * Commands from stdin be handled by bank_process_local_command.
 *
 * Remote commands from the ATM should be handled by
 * bank_process_remote_command.
 *
 * The Bank can read both .card files AND .pin files.
 *
 * Feel free to update the struct and the processing as you desire
 * (though you probably won't need/want to change send/recv).
 */

#ifndef __BANK_H__
#define __BANK_H__

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include "../util/hash_table.h"
#include "../util/list.h"

typedef struct _Bank
{
    // Networking state
    int sockfd;
    struct sockaddr_in rtr_addr;
    struct sockaddr_in bank_addr;

    // Protocol state
    // TODO add more, as needed

    // HashTable *pins; 
    // HashTable *card_nums;
    // HashTable *balances;

    List *pins; 
    List *card_nums;
    List *balances;

    unsigned char* key;
    unsigned char* iv;
} Bank;

Bank* bank_create(unsigned char key[32], unsigned char iv[16]);
void bank_free(Bank *bank);
ssize_t bank_send(Bank *bank, unsigned char *data, size_t data_len);
ssize_t bank_recv(Bank *bank, unsigned char *data, size_t max_data_len);
void bank_process_local_command(Bank *bank, char *command, size_t len);
void bank_process_remote_command(Bank *bank, unsigned char *ciphertext, size_t len);
void create_user(Bank *bank, char **args,int i);
void deposit(Bank *bank,char **args,int i);
void balance(Bank *bank, char **args,int i);
void atm_authenticate(Bank *bank, char **args, int num_args);
void atm_card(Bank *bank, char **args, int num_args);
void atm_pin(Bank *bank, char **args, int num_args);
void atm_balance(Bank *bank, char **args, int i);
void atm_withdraw(Bank *bank, char **args, int i);
int validate_user_card(Bank *bank, char * usr, char * filename);
void rand_str(unsigned char *dest, size_t length);
#endif


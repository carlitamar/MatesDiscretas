#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  
  char choice[50], redo = 'n';
  int length;
  
  char respuesta[50];
  
  do{
    do{
      printf("Do you want to encrypt (E) or decrypt (D) a message? ");
      scanf (" %[^\n]s", choice);
      
      length = strlen(choice);
      
      if(length > 1){
        redo = 'y';
        printf("\nThe character(s) you entered is an invalid choice. Please choose E or D.\n");
        goto endofdo;
      }
      else if(choice[0] != 'E' && choice[0] != 'D'){
        printf("\nThe character(s) you entered is an invalid choice. Please choose E or D.\n");
        redo = 'y';
      }
      else {
        redo = 'n';
      }
      endofdo: printf("\n");
    }while(redo == 'y');
    
    if(choice[0] == 'E'){
      int length, i, key;
      char chr, redo = 'n', strng[50], strngspaceless[50], keys[50], keyspaceless[50]; //character array of size 50

      do{
        printf("Enter a message to encrypt: ");
        scanf (" %[^\n]s", strng); 
        
        length = strlen(strng);
        
        for(i = 0; i < length; ++i){
          if(strng[i] == ' '){
            redo = 'n';
          }
          else if(strng[i] >= 'a' && strng[i] <= 'z') {
            redo = 'n';
          }
          else if(strng[i] >= 'A' && strng[i] <= 'Z') {
            redo = 'n';
          }
          else{
            printf("\nThe program can only encrypt a message that has characters with letters of the English alphabet and the blank. The offending character you used was %c and the position it occupies in the message is %i. Try a valid input statement\n\n", strng[i], i+1);
            redo = 'y';
            goto endoffor;
          }
        }
        endoffor: printf("\n");
      }while(redo == 'y');
    
      //choose a valid key
      char wrong = 'n';
      do{
        wrong = 'n';
        int x;
        
        for(x = 0; x < 50; ++x){
          keyspaceless[x] = 0;
        }

        printf("Enter key (between -26 and 26): ");
        scanf (" %[^\n]s", keys); 
        
        int len = strlen(keys);
        
        //deleting spaces
        int y = 0, neg = 0, pos = 0, malcharacter = 0, spaces = 0;
        for(x = 0; x < len; ++x){
          if(keys[x] == '+'){
            pos = 1;
          }
          else if(keys[x] == '-'){
            neg = -1;
          }
          else if(keys[x] >= '0' && keys[x] <= '9'){
            keyspaceless[y]=keys[x];
            y++;
          }
          else if(keys[x] == ' '){
            spaces++;
          }
          else{
            malcharacter = 1;
          }
        }
        //
        if(malcharacter == 1){
          printf("\nThe key input value writen incorrectly. You can only use the characters +/- and a number from -26 to 26. Please try again.\n\n");
        }
        else if(neg == -1 && pos == 1){
          printf("\nThe key input value writen incorrectly. You can't put + and - at the same time. Please try again.\n\n");
          wrong = 'y';
        }
        else if(neg == 0){
          key = atoi(keyspaceless);
          if(key <= -26 || key >=26){
          printf("\nThe key input value is out of range. Please try again.\n\n");
          }
          printf("key: %i\n", key);
        }
        else if(neg == -1){
          key = neg * (atoi(keyspaceless));
          if(key <= -26 || key >=26){
          printf("\nThe key input value is out of range. Please try again.\n\n");
          }
          printf("key: %i\n", key);
        }
        //
      }while(key <= -26 || key >=26 || wrong != 'n');
    
      printf("\n");
      printf("--------------------------\n");
      printf("The plain text message is: %s\n", strng);
      
      //deleting spaces
      char ch;
      int j, a, b = 0, resto;
      
      for(a = 0; strng[a] != '\0'; ++a){
        if(strng[a] != ' '){
          strngspaceless[b]=strng[a];
          b++;
        }
      }
      
      //encrypting
      for(i = 0; strngspaceless[i] != '\0'; ++i){
        ch = strngspaceless[i];
        if(ch >= 'a' && ch <= 'z'){
          ch = ch - 32;
          if((ch + key) > 'Z'){
            resto = (ch + key)%91;
            ch = 'A' + resto;
          }
          else if((ch + key) < 'A'){
            resto = ch%65;
            ch = 'Z' + (key+1) + resto;
          }
          else{
            ch = ch + key;
          }
          strngspaceless[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
          if((ch + key) > 'Z'){
            resto = (ch + key)%91;
            ch = ch + resto;
          }
          else if((ch + key) < 'A'){
            resto = ch%65;
            ch = 'Z' + (key+1) + resto;
          }
          else{
            ch = ch + key;
          }
          strngspaceless[i] = ch;
        }
      }
      printf("Encrypted message is: %s\n\n", strngspaceless);
    }
    else{ //choice[0] == 'D'
      int key, length, i;
      char chr, redo = 'n', strng[50], strngspaceless[50], keys[50], keyspaceless[50]; //character array of size 50
  
      //choose a valid message to decrypt (only capital letters)
      do{
        printf("Enter a message to decrypt: ");
        scanf(" %[^\n]s", strng);
      
        length = strlen(strng);
      
        for(i = 0; i < length; ++i){
          if(strng[i] == ' '){
            printf("\nThe program can only decrypt messages with characters with capital letters of the English alphabet. This message has a blank. The offending character you used was in the position %i of the message. Try a valid input statement.\n\n", i+1);
            redo = 'y';
            goto endoffor2;
          }
          else if(strng[i] > 'Z' || strng[i] < 'A') {
            printf("\nThe program can only decrypt messages with characters with capital letters of the English alphabet. The offending character you used was %c and the position it occupies in the message is %i. Try a valid input statement.\n\n", strng[i], i+1);
              redo = 'y';
            goto endoffor2;
          }
          else{
            redo = 'n';
          }
        }
        endoffor2: printf("\n");
      }while(redo == 'y');
      
      //choose a valid key
      char wrong = 'n';
      do{
        wrong = 'n';
        int x;
        
        for(x = 0; x < 50; ++x){
          keyspaceless[x] = 0;
        }

        printf("Enter key (between -26 and 26): ");
        scanf (" %[^\n]s", keys); 
        
        int len = strlen(keys);
        
        //deleting spaces
        int y = 0, neg = 0, pos = 0, malcharacter = 0, spaces = 0;
        for(x = 0; x < len; ++x){
          if(keys[x] == '+'){
            pos = 1;
          }
          else if(keys[x] == '-'){
            neg = -1;
          }
          else if(keys[x] >= '0' && keys[x] <= '9'){
            keyspaceless[y]=keys[x];
            y++;
          }
          else if(keys[x] == ' '){
            spaces++;
          }
          else{
            malcharacter = 1;
          }
        }
        //
        if(malcharacter == 1){
          printf("\nThe key input value writen incorrectly. You can only use the characters +/- and a number from -26 to 26. Please try again.\n\n");
        }
        else if(neg == -1 && pos == 1){
          printf("\nThe key input value writen incorrectly. You can't put + and - at the same time. Please try again.\n\n");
          wrong = 'y';
        }
        else if(neg == 0){
          key = atoi(keyspaceless);
          if(key <= -26 || key >=26){
          printf("\nThe key input value is out of range. Please try again.\n\n");
          }
          printf("key: %i\n", key);
        }
        else if(neg == -1){
          key = neg * (atoi(keyspaceless));
          if(key <= -26 || key >=26){
          printf("\nThe key input value is out of range. Please try again.\n\n");
          }
          printf("key: %i\n", key);
        }
        //
      }while(key <= -26 || key >=26 || wrong != 'n');
      
    
      printf("\n");
        
      //decripting
      char ch;
      int resto;
      
      for(i = 0; strng[i] != '\0'; ++i){
        ch = strng[i];
      
        if((ch - key) > 'Z'){
          resto = (ch - key)%91;
          ch = 'A' + resto;
        }
        else if((ch - key) < 'A'){
          resto = ch%65;
          ch = 'Z' - (key - resto) + 1;
        }
        else{
          ch = ch - key;
        }
        strng[i] = ch;
      }
      printf("Decrypted message is: %s\n\n", strng);
    }
    
    
    printf("Do you want to keep encrypting and decrypting? (Y/N)");
    scanf(" %s", respuesta);
    printf("\n");

  }while (respuesta[0] == 'Y');
}
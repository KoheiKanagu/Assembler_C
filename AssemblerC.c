//
//  AssemblerC.c
//
//  Created by Kohei on 2014/05/27.
//
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void convertBinaryC(char *string);
char *convertBinaryRegisterC(char *reg, int length);
int cmp(char *word, char *key, char *key2);

int main(void)
{
    char buf[256];
    char *array[256] = {'\0'};
    int i=0, f;
    
    printf("Input Code...\n");
    while(fgets(buf, 256, stdin) != NULL){
        if((buf[0] == '-') && (buf[1] == '1')){ //finish word
            break;
        }else if((buf[0] == '/') && (buf[1] == '/')){ //comments
            continue;
        }else if(buf[0] == '\n'){
            continue;
        }
        
        array[i] = (char *)malloc(strlen(buf));
        buf[strlen(buf)-1] = '\0';
        strcpy(array[i++], buf);
    }
    printf("%d Lines\n", i);
    printf("------------------------\n");
    
    for(f=0; f<i; f++){
        printf("%d : ", f);
        convertBinaryC(array[f]);
    }
    printf("[%d..255] : 0000000000000000\n", f);
    printf("------------------------\n");
    return 0;
}

int cmp(char *word, char *key, char *key2)
{
    if(strcmp(word, key) == 0 || strcmp(word, key2) == 0){
        return 1;
    }
    return 0;
}

void convertBinaryC(char *string)
{
    char *words[12] = {'\0'};
    int i=0;
    
    char *tp;
    tp = strtok(string, " ");
    words[i] = (char *)malloc(sizeof(strlen(tp)+1));
    strcpy(words[i++], tp);
    
    while(tp){
        tp = strtok(NULL, " ");
        if(tp){
            if((tp[0] == '/') && (tp[1] == '/')){ //comments
                continue;
            }
            words[i] = (char *)malloc(sizeof(strlen(tp)+1));
            strcpy(words[i++], tp);
        }
    }
    if(!i){
        return;
    }
    char *rs1, *rs2, *imm, *rd;
    
    if(cmp(words[0], "ST", "st")){
        rs1 = convertBinaryRegisterC(words[1], 3);
        rs2 = convertBinaryRegisterC(words[2], 3);
        printf("00000%s%s00000\n", rs1, rs2);
        
    }else if(cmp(words[0], "LD", "ld")){
        rs1 = convertBinaryRegisterC(words[1], 3);
        rs2 = convertBinaryRegisterC(words[2], 3);
        printf("00%s%s00000001\n", rs1, rs2);
        
    }else if(cmp(words[0], "ADD", "add")){
        rd = convertBinaryRegisterC(words[1], 3);
        rs1 = convertBinaryRegisterC(words[2], 3);
        rs2 = convertBinaryRegisterC(words[3], 3);
        printf("00%s%s%s00010\n", rd, rs1, rs2);
        
    }else if(cmp(words[0], "LI", "li")){
        rd = convertBinaryRegisterC(words[1], 3);
        imm = convertBinaryRegisterC(words[2], 8);
        printf("01%s000%s\n", rd, imm);
        
    }else if(cmp(words[0], "B", "b")){
        imm = convertBinaryRegisterC(words[1], 8);
        printf("10000000%s\n", imm);
        
    }else if(cmp(words[0], "BNZ", "bnz")){
        rs1 = convertBinaryRegisterC(words[1], 3);
        imm = convertBinaryRegisterC(words[2], 8);
        printf("10001%s%s\n", rs1, imm);
        
    }else if(cmp(words[0], "CMP", "cmp")){
        rd = convertBinaryRegisterC(words[1], 3);
        rs1 = convertBinaryRegisterC(words[2], 3);
        rs2 = convertBinaryRegisterC(words[3], 3);
        printf("00%s%s%s00100\n", rd, rs1, rs2);
        
    }else if(cmp(words[0], "MLT", "mlt")){
        rd = convertBinaryRegisterC(words[1], 3);
        rs1 = convertBinaryRegisterC(words[2], 3);
        rs2 = convertBinaryRegisterC(words[3], 3);
        printf("00%s%s%s00101\n", rd, rs1, rs2);
        
    }else if(cmp(words[0], "BZ", "bz")){
        rs1 = convertBinaryRegisterC(words[1], 3);
        imm = convertBinaryRegisterC(words[2], 8);
        printf("10010%s%s\n", rs1, imm);
        
    }else if(cmp(words[0], "NOP", "nop")){
        printf("0000000000000000\n");
    
    }else if(cmp(words[0], "ADDI", "addi")){
        rd = convertBinaryRegisterC(words[1], 3);
        imm = convertBinaryRegisterC(words[2], 8);
        printf("01%s001%s\n", rs1, imm);
        
    }else if(cmp(words[0], "ROOT", "root")){
        rd = convertBinaryRegisterC(words[1], 3);
        rs1 = convertBinaryRegisterC(words[2], 3);
        rs2 = convertBinaryRegisterC(words[3], 3);
        printf("00%s%s%s11111\n", rd, rs1, rs2);
    }else{
        printf("...Order Error...\n");
    }
}

char *convertBinaryRegisterC(char *reg, int length)
{
    int x = atoi(&reg[1]);
    
    if((length == 8) || (length == 16)){
        x = atoi(reg);
    }
    int bit = 1, i;
    int len = (int)length-1;
    char *c;
    c = (char *)malloc(64);
    
    for (i=0; i<(int)length; i++) {
        if (x & bit)
            c[len--] = '1';
        else
            c[len--] = '0';
        bit <<= 1;
    }
    return c;
}
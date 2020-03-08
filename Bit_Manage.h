#include <string.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int charToInt(char c)
{
   int arr[]={0,1,2,3,4,5,6,7,8,9};
   return arr[c-'0'];
}

char* char2Binary(char character)
{ 
     unsigned int I_char = 128;

     static char temp_lett[9];
     int contador = 0;

     for (I_char; I_char > 0 ; I_char >>=1)
     {
          if (I_char & character)
          {
               temp_lett[contador] = '1';
          }else
          {
               temp_lett[contador] = '0';
          }
          contador++;
     }
     
     temp_lett[8] ='\0';

     return temp_lett;
}

char Binary2Char(char* binary)
{

     int temp = 0;
     int suma = 0;
     for (int i = 0; i < strlen(binary); i++)
     {
          temp = charToInt(binary[i]);
          suma += pow(2,strlen(binary)-(i+1)) * temp;

     }
     char returned_character = (char)suma;

     return returned_character;


}

char* ReadMessage(int Bytes2Read,std::vector<int> &Colors_data)
{

     int bits2read = Bytes2Read *8;

     char *mensaje = new char[Bytes2Read];
     int read_count = 0;


     char binary_word[8];
     int word_count = 0;

     int mask  = 128;

     mask >>= 7;


     for (int i = 0; i < bits2read; i++)
     {

        if(Colors_data[i] & mask)
        {
           binary_word[word_count] = '1';
           word_count++;
        }else
        {
           binary_word[word_count] = '0';
           word_count++;
        }
        
     
        if (word_count == 8)
        {
             mensaje[read_count] =  Binary2Char(binary_word);
             read_count++;
             word_count = 0;
             binary_word[0] = 0;
             
        }
          

     }
     
     mensaje[Bytes2Read] = '\0';

     return mensaje;

}


void ApagarBit(int posicion, char &byte)
{
    unsigned int mask = 128;

    mask >>= 8-posicion;

    if (mask & byte)
    {
        byte ^= mask;
    }
    

    



}

void ApagarBit(int posicion, int &byte)
{
    unsigned int mask = 128;

    mask >>= 8-posicion;

    if (mask & byte)
    {
        byte ^= mask;
    }
    



}


void EncenderBit(int posicion, char &byte)
{
    unsigned int mask = 128;

    mask >>= 8-posicion;

    if (!(mask & byte))
    {
        byte ^= mask;
    }
    

    



}


void EncenderBit(int posicion, int &byte)
{
    unsigned int mask = 128;

    mask >>= 8-posicion;

    if (!(mask & byte))
    {
        byte ^= mask;
    }
    

    



}



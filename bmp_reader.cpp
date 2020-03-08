#include "bmp_reader.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>

void header::UnPackBuffer_Header()
{

    char * c = bufferheader;
    memcpy(&filetype,c,2);
    filetype[2] = '\0';
    memcpy(&csize,c+=2,4);    
    memcpy((char*)&message_size,c+=4,4);
    memcpy(&imageSataOffset,c+=4,4);




}
void header::ReadHeader_Header(ifstream &filename)
{
    
    filename.read((char *) &bufferheader,sizeof (bufferheader));
    UnPackBuffer_Header();



}


void Information_File::ReadHeader_Information(ifstream &filename)
{

    filename.read((char *) &bufferheader,sizeof (bufferheader));
    UnPackBuffer_Information();




}
void Information_File::UnPackBuffer_Information()
{

    char* c = bufferheader;

    memcpy(&biSize,c,4);
    memcpy(&width,c+=4,4);
    memcpy(&height,c+=4,4);
    memcpy(&planes,c+=4,2);
    memcpy(&bitPix,c+=2,2);
    memcpy(&biCompression,c+=2,4);
    memcpy(&biSizeImage,c+=4,4);
    memcpy(&biXPelsPerMeter,c+=4,4);
    memcpy(&biYPelsPerMeter,c+=4,4);
    memcpy(&biClrUsed,c+=4,4);
    memcpy(&biImportan,c+=4,4);




}



void BMP_INFORMATION::readColors(vector<int> &color_data,ifstream &fp)
{
            fp.seekg(header_bmp.imageSataOffset);




            int bytesxRow = (Info_bmp.width)*(Info_bmp.bitPix/8);
            int relleno=0;


            while (bytesxRow % 4 != 0) {

                bytesxRow++;
                relleno ++;

            }//CALCULATE HOW MANY BYTES TO FILL




            for (int y = Info_bmp.height; y >0;y--) {

                for (int x = 0; x < Info_bmp.width; x++) {
                    //fread(&colors_bmp.a,1,3,fp);
                    fp.read((char*)&colors_bmp.a,3);

                    colors_bmp.s = (colors_bmp.a/256)%256;
                    colors_bmp.d = colors_bmp.a%256;
                    colors_bmp.a = (colors_bmp.a/(256*256));

                    color_data.push_back(colors_bmp.d);
                    color_data.push_back(colors_bmp.s);
                    color_data.push_back(colors_bmp.a);




                }
                //fread(&colors_bmp.e,1,relleno,fp);
                fp.read((char*)&colors_bmp.e,relleno);

            }//SAVE THE COLORS IN TO COLOR_DATA


            // for (int var = 0; var < color_data.size(); var+=3) {
            //     std::cout << color_data[var] << "\n";
            // }



    fp.close();



}



void BMP_INFORMATION::OverWrite(vector<int> &color_data ,string filename,char* palabra)
{

            fstream fp;
            fp.open(filename, ios::in | ios::out | ios::binary);

            //write the size of the message
            fp.seekg(6);
            int size_message = strlen(palabra);

            // fp.seekg(50);
            // int size_message = strlen(palabra);

            fp.write((char*)&size_message,4);
           //cout << size_message;


            fp.seekg(header_bmp.imageSataOffset);




            int bytesxRow = (Info_bmp.width)*(Info_bmp.bitPix/8);
            int relleno=0;


            while (bytesxRow % 4 != 0) {

                bytesxRow++;
                relleno ++;

            }//CALCULATE HOW MANY BYTES TO FILL



            int contador = 0;
            int n;
            for (int y = Info_bmp.height; y >0;y--) {

                for (int x = 0; x < Info_bmp.width *3; x++) {
                    //fread(&colors_bmp.a,1,3,fp);
                    
      
                    fp.write((char*)&color_data[contador],1);
                   // cout << color_data[contador] << " -- ";
                    // fp.write((char*)&color_data[contador++],1);
                    // cout << color_data[contador] << " -- "; 
                    
                    // fp.write((char*)&color_data[contador++],1);
                    // cout << color_data[contador] << " \n "; 
                    
                    
                    
                    // n++;
                    // if (n == 3)
                    // {
                        
                    //     cout << "\n";
                    //     n=0;
                    // }
                    
            

                    contador++;

                }
                //fread(&colors_bmp.e,1,relleno,fp);
                fp.read((char*)&colors_bmp.e,relleno);
                
            }//SAVE THE COLORS IN TO COLOR_DATA

            fp.flush();
            fp.close();




}
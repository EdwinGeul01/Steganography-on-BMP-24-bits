#include <iostream>
#include <string.h>
#include "Bit_Manage.h"
#include "bmp_reader.h"
#include <vector>








void ReadBMP(BMP_INFORMATION &bmp, string filename, vector<int> color_data)
{
            
    ///READ BMP SECTION <------------------>\('-')/ 


    ifstream file;
    file.open(filename,ios::in);
    bmp.header_bmp.ReadHeader_Header(file);
    bmp.Info_bmp.ReadHeader_Information(file);
    bmp.readColors(color_data,file);
    file.close();


}

void WriteMessage(char* palabra , vector<int> &color_data)
{

    char binary[9];
    int colorData_count = 0;
    
    for (int i = 0; i < strlen(palabra); i++)
    {
        strcpy(binary,char2Binary(palabra[i]));


        for (size_t x = 0; x < strlen(binary); x++)
        {
            if (binary[x] == '0')
            {
               // cout << char2Binary(color_data[colorData_count]) << " - (" << color_data[colorData_count] << " ) --->";
                ApagarBit(1,color_data[colorData_count]);
               // cout << "(" << color_data[colorData_count] << ") - " <<  char2Binary(color_data[colorData_count]) << " APAGANDO \n";
                colorData_count++;
            }else if(binary[x] == '1')
            {
               // cout << char2Binary(color_data[colorData_count]) << " - (" << color_data[colorData_count] << " ) --->";
                EncenderBit(1,color_data[colorData_count]);
               // cout << "(" << color_data[colorData_count] << ") - " <<  char2Binary(color_data[colorData_count]) << " ENCENDIENDO \n";
                colorData_count++;
            }
            

        }
        


    }


}



int main(int argc, char **argv)
{


    std::vector<int> color_data;    //COLORS INFO CONTAINER
    char *palabra;
    string palabrastr;
        


    // Extraer el mensaje
    if(strcmp(argv[1],"-e") == 0)
    {
        ifstream fp;
        char *filename = argv[2]; 
        fp.open(filename,ios::in | ios::binary);

        if (fp.fail())
        {
            cout << "El archivo no ha sido encontrado !!!";
            return 0;
        }

    
        

        BMP_INFORMATION bmp;
        ReadBMP(bmp,filename,color_data);
        bmp.readColors(color_data,fp);

        //verificando Si el arhivo es apto para el uso del programa
        if (strcmp(bmp.header_bmp.filetype,"BM") != 0 || bmp.Info_bmp.bitPix != 24)
        {
            cout << "El archivo no es apto para el uso de este programa \n";
            return 0;
        }

        if (bmp.header_bmp.message_size == 0)
        {
            cout << "El arhivo no contiene un mensaje\n";
            return 0;
        }
        

        char* mensaje;
        mensaje = ReadMessage(bmp.header_bmp.message_size,color_data);


        if (argc == 5 && strcmp(argv[3],"-f")==0)
        {
        fstream save_fs;
        save_fs.open(argv[4], ios::app | ios::out );
        save_fs << mensaje <<"\n";
        save_fs.close();

        }else if(argc == 3)
        {
            cout << mensaje << "\n";
        }
        
        
        

        
    }

    //Escribe el Mensaje
    if (strcmp(argv[1],"-o") == 0)
    {
        ifstream fp;
        char *filename = argv[2]; 
        
        
        fp.open(filename,ios::in | ios::binary);

        if (fp.fail())
        {
            cout << "El archivo no ha sido encontrado !!!";
            return 0;
        }

        BMP_INFORMATION bmp;
        ReadBMP(bmp,filename,color_data);
        bmp.readColors(color_data,fp);
        

        //verificando Si el arhivo es apto para el uso del programa
        if (strcmp(bmp.header_bmp.filetype,"BM") != 0 || bmp.Info_bmp.bitPix != 24)
        {
            cout << "El archivo no es apto para guardar el mensaje \n";
            return 0;
        }

        if (strcmp(argv[3],"-m")==0)
        {
            palabrastr = argv[4];
            palabra  = new char[palabrastr.size()];
            strcpy(palabra,palabrastr.c_str());

        }else if(strcmp(argv[3],"-f")== 0)
        {
            ifstream readerFile;
            readerFile.open(argv[4],ios::in);
            
            readerFile.seekg(0,ios::end);

            int size = readerFile.tellg();
            palabra = new char[size];
            readerFile.seekg(0);
            
            if (size == 0)
            {
               cout << "no se encontro ningun mensaje en el archivo !!......\n";
               return 0;
            }
            else
            {
            readerFile.read((char*)palabra,size);
            palabra[size-1] = '\0';
            }
            

           

            
        }
        
        


    
        if (strlen(palabra) > (((bmp.Info_bmp.width * bmp.Info_bmp.height)*3)/8))
        {
            cout << "la informacion a guardar excede el limite permitido por el archivo \n";
            return 0;
        }
        

        WriteMessage(palabra,color_data);



        bmp.OverWrite(color_data,filename,palabra);
        cout << "Mensaje Escrito Correctamente!!.\n"

    }

    //muestra la cantidad de caracteres que puede guardar
    if (strcmp(argv[1],"-t") == 0)
    {

        ifstream fp;
        char *filename = argv[2]; 
        fp.open(filename,ios::in | ios::binary);

        if (fp.fail())
        {
            cout << "El archivo no ha sido encontrado !!!";
            return 0;
        }
        BMP_INFORMATION bmp;
        ReadBMP(bmp,filename,color_data);


        cout << "el tamaño maximo de caracteres a guardar es de  :  " << (int)(((bmp.Info_bmp.width * bmp.Info_bmp.height)*3)/8) << "\n"; 

        if (strcmp(bmp.header_bmp.filetype,"BM") != 0 || bmp.Info_bmp.bitPix != 24)
        {
            cout << "El archivo no es apto para guardar el mensaje \n";
            return 0;
        }

    }

    //muestra la validez de la imagen y si ya contiene un msj
    if (strcmp(argv[1],"-v") == 0)
    {

        ifstream fp;
        char *filename = argv[2]; 
        
        
        fp.open(filename,ios::in | ios::binary);

        if (fp.fail())
        {
            cout << "El archivo no ha sido encontrado !!!";
            return 0;
        }

        BMP_INFORMATION bmp;
        ReadBMP(bmp,filename,color_data);
        bmp.readColors(color_data,fp);
        

        //verificando Si el arhivo es apto para el uso del programa
        if (strcmp(bmp.header_bmp.filetype,"BM") != 0 || bmp.Info_bmp.bitPix != 24)
        {
            cout << "100: Imagen no valida para ocultar el mensaje. . \n";
            cout << "101: El archivo no contiene un mensaje. \n";

            return 0;
        }

        if (bmp.header_bmp.message_size != 0)
        {
            cout << "101: <ADVERTENCIA !!! > El arhivo ya contiene un mensaje de <" << bmp.header_bmp.message_size << "> Caracteres.\n";
        }

            cout << "100: Imagen no valida para ocultar el mensaje. \n";

    }

    //muestra las opciones del programa
    if (strcmp(argv[1],"-h") == 0)
    {
        cout << "************************************************************************************************" << endl
            << "******                         BMP SHOW AND HIDE INFORMATION PROGRAM                   *********" << endl
            << "************************************************************************************************" << endl;
        cout << "-o     if you want to write on the bmp file" << endl
            << "-e     if you want to read the file , the message is saved in the message text doc" << endl
            << "-t     shows the maximum size the message can have" << endl
            << "-v     Validate the image" << endl
            << "-h     show the different program options " << endl << endl;
    
    }


}


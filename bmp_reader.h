#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class header
{

    public:
    char bufferheader[14];

    char filetype[3];// 2 bytes
    uint32_t csize;// 4 bytes
    uint16_t message_size;// 4 bytes 
    uint32_t imageSataOffset; // 4 bytes
    ifstream file_bmp;

    void ReadHeader_Header(ifstream &filename);
    void UnPackBuffer_Header();


};

class Information_File
{

    public:
    char bufferheader[40];

    unsigned int biSize; // 4 bytes
    int width; // 4 bytes
    int height; // 4 bytes
    short planes,bitPix; // 4 bytes
    int biCompression,biSizeImage; // 4 bytes c/u
    int biXPelsPerMeter; // 4 bytes
    int biYPelsPerMeter; // 4 bytes
    int biClrUsed; // 4 bytes
    int biImportan; // 4 bytes

    ifstream file_bmp;


    void ReadHeader_Information(ifstream &filename);
    void UnPackBuffer_Information();


};

struct colors{

    public:

    //colors
     char  b;         /* Blue value */
     char  g;         /* Green value */
     char  r;         /* Red value */
    unsigned int a,s,d,e;



};

class BMP_INFORMATION
{

    public:
    
    header header_bmp;
    Information_File Info_bmp;
    colors colors_bmp;

    void readColors(std::vector<int> &color_data,ifstream &fp);
    void OverWrite(std::vector<int> &color_data,string filename,char* palabra);






};
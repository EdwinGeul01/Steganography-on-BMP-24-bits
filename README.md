# Steganography in 24 bit bmp images

## Concepts used
```
  bytes read & write
  structure of a 24 bit bmp
```


### How to Install
```
$ Git clone https://github.com/EdwinGeul01/Steganography-on-BMP-24-bits.git
$ cd Steganography-on-BMP-24-bits
$ g++ *.cpp -o run
```


#### Options 
```
-o     if you want to write on the bmp file
       
        $ ./run -o ./example_img.bmp -m 'here the message'
        $ ./run -o ./example_img.bmp -f 'here the directory of the file containing the message'
        
-e     if you want to read the file and save the message on a text doc
        $ ./run -e ./example_img.bmp 
        $ ./run -e ./example_img.bmp -f 'here the directory of the file save the message'
       
-t     shows the maximum size the message can have
        $ ./run -t ./example_img.bmp 
         
-v     Validate the image
        $ ./run -v ./example_img.bmp 
        
-h     show the different program options 
```

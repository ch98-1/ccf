# ccf
File compression app. -c (file) to compress. -d (file) to decompress  
  
Current version: 0
only opens project of matching version.
  
ccf format  
offset(byte), length(byte), description  
0, 1, run length encoding element size.
1, EOF, Compressed Data.  
  
//list of compression in order
1, Run length encoding. 1st data byte (byte 1) is the size of each chunks to be encoded  in bytes. Set to 0 for no run length encoding  
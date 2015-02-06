# ccf
File compression app. -c (file) to compress. -d (file) to decompress  
  
Current version: 0
  
ccf format  
offset(byte), length(byte), description  
0, 4, Format Description. "ccf\n" in ascii.  
4, 4, Current version. Allways backward compatable. 
8, 128, Compression format. Each nonzero byte is algolism used to compress the file in order.  
136, 128, File name.  
264, 4, Total file size in bytes.
268, Rest of file, Compressed Data.  
  
Compression formats  
format number, description
0, No compression. Skip this one.
1, Run length encoding. 1st data byte (byte 268) is the run length description in bytes, and 2nd data byte (byte 269) is the size of each chunk to be encoded  in bytes.  
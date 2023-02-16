In case of windows:
  Run the install.bat 
  OR
  Copy and paste the contents of .platformio into C:\Users\NAME\.platformio

in case of linux:
  Copy paste /furbadge_board/.platformio manually into the .platformio directory. 

Why?
  We need to add our board variant manually so the right pins are used. By default it uses the raspberry pico pinout.
  The furbadge is not officially supported, so this approach is the easiest.
  

#include <stdio.h>

int main(){
        int c;

        while((c = getchar()) != EOF){         
                  if(c == '\\'){
                  		  c = '\\';           
                          putchar(c);
                      }
                  if (c == '\t') {          
                            c = '\t';
                            putchar(c);  
                   }
                  if (c == '\n'){
                  		c= '\n';
                  		putchar(c);

                  } 
            
                    }
           return 0;       
          }
          
          

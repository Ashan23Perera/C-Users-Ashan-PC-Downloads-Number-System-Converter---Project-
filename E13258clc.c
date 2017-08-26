#include<stdio.h>
#include<limits.h>
#include<float.h>

char chararray[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};  
int intarray[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

int power(int base,int pow);              //function get the power of a number
int readInt(char array[]);                //function read a integer
int inputSize(char array[]);              //function read the input size
double readFraction(char array[]);        //function read the a float  
int binDec(char chr,int pos);             //function to  convert  
int readarg(char arg,char array[],int num); //function to check the input format errors  
float binFloat(char array[],int num,int nu);//convert binary in to float  

int main(int argc,char** argv){
int er_x=0;//if there is a error er_x=1,if not er_x=0;

//below error varible use if there is an error it's value >0 then it does'nt do any conversion

int error=0;//check if there is a error error!=0.if there is a no conversion
 
//Error 1              // The number of arguments is wrong
if(argc!=4){                                                        
   	fprintf(stderr,"ERROR: The number of arguments is wrong.\n");
	fprintf(stdout,"Usage: ./clc -<input format> -<output format> <input>.\n");
 error=error+1;
   er_x=1;
}	

//Error 2              //The input argument is wrong
if((argv[1][0]=='-')&&((argv[1][1]!='B')&&(argv[1][1]!='I')&&(argv[1][1]!='F')&&(argv[1][1]!='D')&&(argv[1][1]!='H'))){	
	fprintf(stderr,"ERROR: The input argument is wrong.\n");              
	fprintf(stdout,"Possible input arguments are -B, -H, -I, -F and -D.\n");
error=error+1;
 er_x=1;
}
	
//Error 3              //The output argument is wrong
if((argv[2][0]=='-')&&(argv[2][1]!='B')&&(argv[2][1]!='I')&&(argv[2][1]!='F')&&(argv[2][1]!='D')&&(argv[2][1]!='H')){	
	fprintf(stderr,"ERROR: The output argument is wrong.\n");               
	fprintf(stdout,"Possible output arguments are -B, -H, -I, -F and -D.\n");
error=error+1;
 er_x=1;
}

//Error 4              //Input format error at location x. 
int size=0;	
switch (argv[1][1]){       

	case 'B': size=2;
	case 'I': size=10;
	case 'F': size=10;
	case 'D' :size=10;
	default : size=16;
}
  
if(readarg(argv[1][1],argv[3],size)!=-1){                           
     fprintf(stderr,"ERROR: Input format error at location %d.\n",readarg(argv[1][1],argv[3],size));
  error=error+1;
   er_x=1;
}

//Error 5              //The input size is wrong
if(((argv[1][1]=='B')&&(inputSize(argv[3])!=32))&&((argv[1][1]=='B')&&(inputSize(argv[3])!=64))){	//Check Binary input Size
    fprintf(stderr,"ERROR:  The input size is wrong.\n");                   
   error=error+1;
    er_x=1;
}

if((argv[1][1]=='I')&& ((readInt(argv[3])>INT_MAX)&&(readInt(argv[3])<INT_MIN))){     //Check Integer Size
    fprintf(stderr,"ERROR:  The input size is wrong.\n");
  error=error+1;
   er_x=1;
}

if((argv[1][1]=='F') && ((readFraction(argv[3]) > FLT_MAX ) && (readFraction(argv[3]) < FLT_MIN))){    //Check Single precision floating point 32 bit number Size
		fprintf(stderr,"ERROR: The input size is wrong.\n");
  error=error+1;
   er_x=1;
}
if((argv[1][1]=='D') && ((readFraction(argv[3]) > DBL_MAX) && (readFraction(argv[3])<DBL_MIN)) ){   //Double precision 64 bit floating point number Size 
       fprintf(stderr,"ERROR: The input size is wrong.\n");
 error=error+1;
  er_x=1;
}
if(((argv[1][1]=='H')&&(inputSize(argv[3])!=8))&&((argv[1][1]=='H')&&(inputSize(argv[3])!=16))){ //Check Hexadecimal Size
      fprintf(stderr,"ERROR:  The input size is wrong.\n");
   error=error+1;
    er_x=1;
}

//if the above errors are not go for the conversion 

if(error==0){

//convert the same number systems 
if(argv[1][1]==argv[2][1])                               
	fprintf(stdout,"%s\n",argv[3]); 
    
 //convert binary in to decimal
if(argv[1][1]=='B' && argv[2][1]=='I'){                  
	  if(inputSize(argv[3])==32){
int i,num=0;
	    for(i=31;i>=0;i--)
          num=num+binDec(argv[3][i],(31-i));
            if(argv[3][0]=='1') 
	          fprintf(stdout,"-%d\n",num); //negative number
            else	 
              fprintf(stdout,"%d\n",num);  //positive number 
	  
	  }else{
		     fprintf(stderr,"ERROR:  This conversion is not possible.\n"); //Error:if binary number size is not 32 bit
         er_x=1;   		   
	   }		  
}
 
 //convert binary number in to Single precision floating point  number 	
if(argv[1][1]=='B' && argv[2][1]=='F'){              
    if(inputSize(argv[3])==32){
		if(argv[3][0]=='1')
        	fprintf(stdout,"-%0.2f\n",binFloat(argv[3],9,32)); //negative number
	    else
		    fprintf(stdout,"%0.2f\n",binFloat(argv[3],9,32));  //positive number
     
	}else{
		   fprintf(stderr,"ERROR:  This conversion is not possible.\n");  //Error: if binary number size is not 32 bit   
           er_x=1;		   
	   }
}

//convert binary number  in to Double precision floating point number	 
if(argv[1][1]=='B' && argv[2][1]=='D'){                 
	if(inputSize(argv[3])==64){
	     if(argv[3][0]=='1')
      	    fprintf(stdout,"-%0.6f\n",binFloat(argv[3],12,64));
	     else
		    fprintf(stdout,"%0.6f\n",binFloat(argv[3],12,64));
      
	  }else{
		   fprintf(stderr,"ERROR:  This conversion is not possible.\n"); //Error: if binary number size is not 32 bit   
		er_x=1;
		}
}

//convert binary number in to hexadecimal     	
if(argv[1][1]=='B' && argv[2][1]=='H'){                  
    char array[inputSize(argv[3])/4];
	int i;
   for(i=0;i<(inputSize(argv[3])/4);i++)
   {
      int num=binDec(argv[3][i*4],3)+binDec(argv[3][i*4+1],2)+binDec(argv[3][i*4+2],1)+binDec(argv[3][i*4+3],0); 
	   int j;                                          //convert each for bit integer in to             
		  for(j=0;j<16;j++)                             //hexadecimal number 
		    if(num==intarray[j])array[i]=chararray[j];  
	   
	}
     
       fprintf(stdout,"0x");
         for(i=0;i<(inputSize(argv[3])/4);i++)
              fprintf(stdout,"%c",array[i]);
}

//convert integer in to binary	
if(argv[1][1]=='I' && argv[2][1]=='B'){              
   int num=readInt(argv[3]);
   
   if(num<0)num=-1*num;  //if input is a negative number turn in to positive  
     
	 char array[32];
	   int i;
        for(i=0;i<31;i++){     //convert to binary format
			 if(num%2==1){
				 array[i]='1';
				 num=(num-1)>>1;
			 }else{
				 num=num>>1;
				 array[i]='0';
			 }
		 }
		 
	  if(argv[3][0]=='-')  //check it is a negative number
		     printf("1");
	  else                 //or positive number 
		   printf("0");
	
    	for(i=30;i>=0;i--)
			 fprintf(stdout,"%c",array[i]);
	
}

//convert Integer in  to Single precision floating point number
if(argv[1][1]=='I' && argv[2][1]=='F'){             
  	    fprintf(stdout,"%d.00\n",readInt(argv[3]));
}
//convert Integer in  to double precision 32 bit number 
if(argv[1][1]=='I' && argv[2][1]=='D'){             
		fprintf(stdout,"%d.000000\n",readInt(argv[3]));
} 

//convert integer in to 8 bit hexadecimal	
if(argv[1][1]=='I' && argv[2][1]=='H'){             
   	int num=readInt(argv[3]);
    
	if(num<0)num=-1*num; //if input is a negative number turn in to positive  
	
	int i;
	char array[8];                     
        for(i=0;i<8;i++)
		{
		int k; 
			for(k=0;k<16;k++)       //convert to hexdecimal 
			{ 
	            if(num%16==intarray[k])
				{
		    	    array[i]=chararray[k];
			        num=(num-(num%16))/16;
				}
			}
		}
	fprintf(stdout,"0x");
      for(i=7;i>=0;i--)
          fprintf(stdout,"%c",array[i]);			   
}

//convert Single precision floating point number in to binary	
if(argv[1][1]=='F' && argv[2][1]=='B'){          
	float num=readFraction(argv[3]);  //read the float number
	int *p;      
    p=(int *)&num;   //cast the float binary format in to integer
	int i;
          for(i=31;i>=0;i--)  //print it
			 fprintf(stdout,"%d",((*p)>>i)&1); 
}

//convert Single precision floating point number in to integer	
if(argv[1][1]=='F' && argv[2][1]=='I'){            
	if((readFraction(argv[3])>(INT_MAX/1.0))||(readFraction(argv[3])<(INT_MIN/1.0)))
	{
		 fprintf(stderr,"ERROR:  This conversion is not possible.\n"); //Error: if float value is in not range 
		    er_x=1;                                                    //float range 
	}
	else{
	   fprintf(stdout,"WARNING:  There is a possibility for a precision loss.\n%d\n",(int)readFraction(argv[3]));
	   er_x=1;
	}
}

 //convert Single precision floating point number in to double precision floating point number   	
if(argv[1][1]=='F' && argv[2][1]=='D'){           
	float num=readFraction(argv[3]);
		 fprintf(stdout,"%0.6f\n",num);
}

 //convert Single precision floating point number in to hexadecimal	
if(argv[1][1]=='F' && argv[2][1]=='H'){          
char array[32];
float num=readFraction(argv[3]);  //read the float number
int *p;
p=(int *)&num;      //cast the float binary format in to integer

int i;
     for(i=31;i>=0;i--)   //get the binary format in to array
	 {
	     if((*p)>>i&1)
		    array[31-i]='1'; 
          else
		    array[31-i]='0'; 
     }
char array1[8];                 //convert in to hexdecimal number
	   for(i=0;i<8;i++)         //using each 4 bit 
	   {
		  int num=binDec(array[i*4],3)+binDec(array[i*4+1],2)+binDec(array[i*4+2],1)+binDec(array[i*4+3],0); 
		  int j; 
		   for(j=0;j<16;j++) 
		     if(num==intarray[j])array1[i]=chararray[j];
	   }
 
 fprintf(stdout,"0x");
     for(i=0;i<8;i++)
           fprintf(stdout,"%c",array1[i]);
		   
}

//convert Single precision floating point number in to binary	
if(argv[1][1]=='D' && argv[2][1]=='B'){            
    float num=readFraction(argv[3]);  //read the float number
	int *p;
    p=(int *)&num;  //cast the float binary format in to integer
	   int i;
           for(i=63;i>=0;i--)
			fprintf(stdout,"%d",((*p)>>i)&1); 
}

//convert double precision floating point number in to unteger	
if(argv[1][1]=='D' && argv[2][1]=='I'){             
	 fprintf(stderr,"ERROR:  This conversion is not possible.\n"); //Error :this conversion is not possible
    er_x=1;      
}

//convert double precision floating point number in to Single precision floating point number	
if(argv[1][1]=='D' && argv[2][1]=='F'){           
	  fprintf(stderr,"ERROR:  This conversion is not possible.\n");	//Error :this conversion is not possible	
    er_x=1;  	
}

//convert double precision floating point number in to hexadecimal           	
if(argv[1][1]=='D' && argv[2][1]=='H'){           
char array[64];
    float num=readFraction(argv[3]);//read the float value
    int *p;
    p=(int *)&num; //cast in to binary fornmat integer
   
   int i;
      for(i=63;i>=0;i--)  //get the binary format in to array
	  {
	     if((*p)>>i&1)
		   array[63-i]='1'; 
         else
		   array[63-i]='0'; 
      }
 
      char array1[16];   //convert in to hexadecimal number
	   for(i=0;i<16;i++) //using each 4 bit
	   {
		  int num=binDec(array[i*4],3)+binDec(array[i*4+1],2)+binDec(array[i*4+2],1)+binDec(array[i*4+3],0); 
		  int j; 
		   for(j=0;j<16;j++) 
		     if(num==intarray[j])array1[i]=chararray[j];
	   }
	    
  fprintf(stdout,"0x");
     for(i=0;i<16;i++)
               fprintf(stdout,"%c",array1[i]);
}

//convert hexadecimal  number in to binary	
if(argv[1][1]=='H' && argv[2][1]=='B'){   
	int i,array[(inputSize(argv[3]))*4][4]; //array size=number of hexadecimal number *4 
	
	  for(i=0;i<((inputSize(argv[3]))*4);i++)
	  {                                        //convert each bit of hexadecimal number
		int j;                                 //to binary 
		for(j=0;j<16;j++)                      
		{
		  if(argv[3][i]==chararray[j])         //if hexadecimal number in 8 bit array[32] 
		  {                                    //if hexadecimal number in 16 bit array[64]
		   int k,num=intarray[j];  
		    for(k=0;k<4;k++)
			{  
			    array[i][k]=num%2;
			    num=(num-(num%2))/2;
			}
		  }
		}
	  }
	 	
		for(i=0;i<(inputSize(argv[3]));i++)
		{
		  int j;
		   for(j=3;j>=0;j--)
	         fprintf(stdout,"%d",array[i][j]); 
	    }
		
}

//convert hexdecimal number in to integer	
if(argv[1][1]=='H' && argv[2][1]=='I'){          
	if(inputSize(argv[3])==8) //this is possible for 8 bit hexadecimal number
	{	
	  long int i,num=0;
	     for(i=7;i>=0;i--){
		 int j;
		 for(j=0;j<16;j++)
		 {
		    if(argv[3][i]==chararray[j])          //convert in to integer 
			{                                     //consider the each bit position of the base 16 
		        if((i==0) && (j>7))
		            num=num+(power(16,7-i)*(intarray[j]%8)); 
		         else
			       num=num+(power(16,7-i)*intarray[j]); 
			 }
		   }
	   }
   int u=0;
	   for(i=7;i<16;i++)                      //check input is a negative number
		  if(argv[3][0]==chararray[i])u=1;    //for 1 st bit [8,9,,A,B,C,D,E,F] THERE is a negative number
		
	       if((u==1) && (num>=INT_MIN))//negative number   
		        fprintf(stdout,"-%ld\n",num);
	       else if((u==0) && (num<=INT_MAX))//positive number
	            fprintf(stdout,"%ld\n",num);
	      else{
	            fprintf(stderr,"ERROR:  This conversion is not possible.\n"); //if num is not in integer range  
	      er_x=1;                            //this conversion is not possible
	     }
    }else{
		  fprintf(stderr,"ERROR:  This conversion is not possible.\n");
		  er_x=1;
	}	 
}

//convert hexdecimal number in to Single precision floating point number  
if(argv[1][1]=='H' && argv[2][1]=='F'){         
	if(inputSize(argv[3])==8) //this conversion is possible only 8 bit hexdecimal number
	{
	 int i;
	 char array[32];
	for(i=0;i<inputSize(argv[3]);i++)  //convert hexadecimal number in to binary
	{
	    int j;
	     for(j=0;j<16;j++)                        
	    {
		  if(argv[3][i]==chararray[j]) 
		  {
		  int k,num=intarray[j];  
		    for(k=3;k>=0;k--)
			{
			 if(num%2==1)
			 {
				 array[4*i+k]='1';
				  num=(num-1)/2;
			 }else{
				 array[4*i+k]='0';
			      num=num/2;
			 } 
			}  			  
		  }
	    }
	}
//pass the binary array to binFloat function to convert Single precision floating point number	
	  	   if(array[0]=='1') //negeative number
        	     fprintf(stdout,"-%0.2f\n",binFloat(array,9,32));
    	    else             //positive number  
        	     fprintf(stdout,"%0.2f\n",binFloat(array,9,32));
    }else{
	      fprintf(stderr,"ERROR:  This conversion is not possible.\n");
		 er_x=1;
   }
}

//convert hexdecimal number in to double precision floating point number	
if(argv[1][1]=='H' && argv[2][1]=='D'){                
int i;
char array[64];
 for(i=0;i<inputSize(argv[3]);i++)
 {
	int j;
	for(j=0;j<16;j++)
	{
	  if(argv[3][i]==chararray[j])  // convert each hexadecimal bit in to binary
	  {
	    int k,num=intarray[j];  
		    for(k=3;k>=0;k--)
		    {
				  if(num%2==1)
				  {
				       array[4*i+k]='1';
				       num=(num-1)/2;
				  }else{
					  array[4*i+k]='0';
			          num=num/2;
				  }
			}              			  
	  }
	}
  }
  //pass the binary array to binFloat function to convert binary in to Double precision floating point number 
	 	 if(array[0]=='1')     //negative number
      	      fprintf(stdout,"-%0.2f\n",binFloat(array,12,64)); //
	     else                  //positive number 
		      fprintf(stdout,"%0.2f\n",binFloat(array,12,64));	
}
 
}//End main if

	return er_x;
}//End of main function

 //power function 
int power(int base,int pow){    
  int i,sum=1;	
	for(i=1;i<=pow;i++)  //use only for give a positive number
		sum=sum*base;    //Here should be pow>=0
	return sum;
}
 //readInt function 
int readInt(char array[]){       
int arglength=inputSize(array);	
int sum=0,i;
	for(i=0;i<arglength;i++)   
	{
	  int j;
      for(j=0;j<10;j++)
	  {	  
		if(array[i]==chararray[j])
		   sum=sum+(power(10,(arglength-1-i)))*intarray[j];	//convert in to integer
	  }	
	}
if(array[0]=='-')	 //if negative number    
	return  -1*sum;
else                 //if positive number
	return sum;
}

 //readFraction function
double readFraction(char array[]){ 
int arglength=inputSize(array);	
int i,k=0;
  for(i=0;array[i]!='.';i++)  //read the array up to decimal point
          k=k+1;   //k use here to get the decimal point
	  
double sum=0.0;
	for(i=0;i<arglength;i++){
	  int j;
       for(j=0;j<10;j++)
 	   {	  
	     	if((array[i]==chararray[j])&&(i<k))  //get the  full part of the number   
	             sum=sum+(power(10,(k-1-i)))*intarray[j];	
	        else if((array[i]==chararray[j])&&(i>k)) //get the fraction part
		       sum=sum+((double)intarray[j])/(power(10,(i-k)));	
       }	
}

if(array[0]=='-')	//negative number
	return  -1*sum;
else         //positive number
	return sum;
}

//binFloat function 
float binFloat(char array[],int num,int nu){  //convert binary number in to floating point 32 bit number
int i,sum=0;	
	for(i=1;i<num;i++)
	{
		if(array[i]=='1')	
		   sum=sum+(power(2,(num-1-i))); 
	}
sum=sum-(power(2,(num-2))-1);	  //get the exponent
	  
float number=0.0;
	for(i=num;i<nu;i++)
	{
        if(array[i]=='1')           
           number=number+(1.0/power(2,i-(num-1)));		   
	} 
number=number+1;               //get the significaned
	
     if(sum<-7)   //if exponent <-7
		 return 0.00; 
   else  if(sum>0 )    //if exponenet>0
	   return (number*power(2,sum));
   else              //if exponenet<0 and exponenet>-7
	  return (number/power(2,(-1*sum)));
}

//inputSize function
int inputSize(char array[]){  //get the inputsize of a given format
 int i,arglength=0;                   
    for(i=0;array[i]!='\0';i++) arglength=arglength+1; 	
   
 return arglength;   
}

//binDec function
int binDec(char chr,int pos){  //convert a binary number in to it's position to 2 nd base
 int number=0;
	if(chr=='1')                 
		number=number+(1<<pos);

	return number;
}

//read arg function
int readarg(char arg,char array[],int num){  //this function cheack the input unnessary characters
int i,x=-1,m=0; 
  for(i=0;i<inputSize(array);i++)  
  {
	
	if(array[i]=='.')  //check how many '.' in the input
		m=m+1;
 	
	int k,u=0;                         
	  for(k=0;k<num;k++)
	  { 
	     if(array[i]==chararray[k]) //check for the valid characters 
		                  u=1;
	      else if((arg=='I' && array[0]=='-')||(arg=='F' && array[0]=='-')||(arg=='D' && array[0]=='-'))
                          u=1;        //cheack more than '-' in the input
      }

	 if(u!=1 && array[i]!='.') 
    	 x=i;
	 
	 if((m>1) && ((arg=='F')||(arg=='D'))) //check whether it has more than '.' in the input
	 {
     	 x=i;
         m=1;		 
	 }
	 
   }
 return x;//return the wrong characters position
}







#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
bool recursive_=false;
struct text{
char line[100];
};
struct text input[50],input2[50],input3[50];
struct text loops[10];
int dongu_sayisi=0;
int counter=0;// bu degeri main fonksiyonundan buraya Ã§ektim


struct loop{
int start;
int stop;
int adet;
};

struct loop publc[15];
int public_counter=0;//generating a public struct to keeps loop's infos
int sbt = 0;
void recursive()
{
  int i=0;
  char *fonk_isim;
  struct loop fonk_;


  for(;i<=counter;i++)
    {
      if(strstr(input2[i].line,"void")!=NULL || strstr(input2[i].line,"int")!=NULL || strstr(input2[i].line,"float")!=NULL || strstr(input2[i].line,"char")!=NULL)
      {
        fonk_isim=strtok(input2[i].line," ");
        fonk_isim=strtok(NULL," ");
        fonk_.start=i;
        break;
      }
    }
int j=1;
    for(;j<counter;j++)
    {
        if(strcmp(input2[j].line,"}")==1)
      {
        fonk_.stop=j;
        break;
      }
    }

    int index=fonk_.start;
    for (; index < fonk_.stop; index++)
    {
        if(strstr(input2[index].line,fonk_isim)!=NULL)
       {
         sbt++;
         recursive_=true;
       }
    }


}


//this function find a finish index of the spesific loop and save it to the public loop array of struct
void finding_info(struct text input[],int start_index)
{
int balance=0;
int current_index=start_index+1;
while(1)
{
if(strstr(input[current_index].line,"{")!=NULL)
        balance+=1;
if(strstr(input[current_index].line,"}")!=NULL)
        balance-=1;
if(balance==0)
{
    publc[public_counter].start=start_index;
    publc[public_counter].stop=current_index;
    public_counter++;
    break;
}
current_index++;
}

}


void degisken_kontrolu(struct text input[])
{
  int i=0,degisken=0;
	for(;i<=dongu_sayisi;i++)
	{
		if(strstr(loops[i].line,"for")!=NULL)
		 {
		 	if(strstr(loops[i].line,"++")!=NULL || strstr(loops[i].line,"--")!=NULL)
				sbt++;
			else if(strstr(loops[i].line,"*")!=NULL || strstr(loops[i].line,"/")!=NULL )
				degisken++;

		 }

		if(strstr(loops[i].line,"while")!=NULL)
		{
      		int son=publc[i].stop;
			if(strstr(input[son-1].line,"++")!=NULL || strstr(input[son-1].line,"--")!=NULL)
				sbt++;

			else if(strstr(input[son-1].line,"*")!=NULL || strstr(input[son-1].line,"/")!=NULL)
				degisken++;

		}

    if(strstr(loops[i].line,"do")!=NULL)
		{
     		 int son=publc[i].stop;
			if(strstr(input[son-1].line,"++")!=NULL || strstr(input[son-1].line,"--")!=NULL)
				sbt++;

			else if(strstr(input[son-1].line,"*")!=NULL || strstr(input[son-1].line,"/")!=NULL)
				degisken++;

		}


	}


	recursive();
  if(sbt==0 && degisken==0)
    printf("zaman karmasikligi: O(1)");
  else if(sbt==1 && degisken ==1)
    printf("zaman karmasikligi: O(nlogn)");
  else if(sbt==1 && degisken!=1 && degisken!=0)
    printf("zaman karmasikligi: O(nlogn%d)",degisken);
  else if(sbt!=1 && degisken==1 && sbt!=0)
    printf("zaman karmasikligi: O(n%dlogn)",sbt);
  else if(sbt==1 &&degisken==0)
    printf("zaman karmasikligi: O(n)");
  else if(sbt==0 &&degisken==1)
    printf("zaman karmasikligi: O(logn)");
  else if(sbt!=1 && sbt!=0 && degisken==0)
    printf("zaman karmasikligi: O(n%d)",sbt);
  else
    printf("zaman karmasikligi: O(n%dlogn%d)",sbt,degisken);
}



int compute_commas(char *words){
        int i=0;
        int number_of_commas=0;
        while(1)
        {
            //printf("%c",words[i]);
            if(words[i]==',')
                number_of_commas++;
            i++;
            if(i==20)
            break;
        }
    return number_of_commas;
}

int compute_square_brackets(char *words){
int i=0;
        int number_of_square_brackets=0;
        while(1)
        {
            //printf("%c",words[i]);
            if(words[i]=='[')
                number_of_square_brackets++;
            i++;
            if(i==20)
            break;
        }
    return number_of_square_brackets;
}




//this function checks about statements in the input and send them to justify the finish indexes
void process_code(struct text input[],int length){
    int i=0; //sizeof(input[])/sizeof(input[1]);
    for(;i<=length;i++){
    if(strstr(input[i].line,"for")!=NULL || strstr(input[i].line,"while")!=NULL || strstr(input[i].line,"do")!=NULL)
    {
        strcpy(loops[dongu_sayisi].line,input[i].line);
        finding_info(input,i);
        dongu_sayisi++;

    }

    if(strstr(input[i].line,"}while")!=NULL)
    	{
    		dongu_sayisi--;
    		break;
		}
    }

}


//get function's name's index
int other_function_index;

//global variables of time complexity helper
bool if_it_is_a_function_control = false;
bool main_starts_control = false;
char other_functions_names[5][50];
int other_function_names_counter = 0;
int return_control_value = 0;
int n_counterarrays_counter = 0;
int n_counter[10]={0,0,0,0,0,0,0,0,0,0};
int g_counter=0;
int n_square_counter[10]={0,0,0,0,0,0,0,0,0,0};
int n_squarecounterarrays_counter = 0;
int validity=1;
int current_function_index=0;

 // function index that exists before main it controls a error in case of a function input consider as a function.

//this function anlyise each pair and save the values to the global variables
int mainrowsvalue;
void time_complexity_helper(char *words,char *after,int rows_value){
int number_of_commas;
if(rows_value == mainrowsvalue)
number_of_commas = 0;
else
number_of_commas = compute_commas(after);
int number_of_square_brackets = compute_square_brackets(after);

if(strstr(words,"printf")!=NULL)
validity=0;

//this part computes the return value and saved it
if(strstr(after,"main")!=NULL)
{
    mainrowsvalue=rows_value;
    main_starts_control = true;
    if(strstr(words,"int")!=NULL)
        {return_control_value=4;}
    else if(strstr(words,"float")!=NULL)
        {return_control_value=4;}
    else if(strstr(words,"double")!=NULL)
        {return_control_value=8;}
    else if(strstr(words,"char")!=NULL)
        {return_control_value=1;}
       return;
}
//return value saving part is over

// checking the other functions names and saved it then controls if it exists in the function cause that means it s a recursive function
if(main_starts_control == false && (strstr(words,"int")!=NULL || strstr(words,"void")!=NULL  || strstr(words,"float")!=NULL  || strstr(words,"double")!=NULL) && if_it_is_a_function_control == true && other_function_index != rows_value ){
    strcpy(other_functions_names[other_function_names_counter],after);
    other_function_names_counter++;
    other_function_index = rows_value;
}
int k = 0 ;
for (; k < other_function_names_counter ; k++)
    {
        if(main_starts_control == true && (strstr(words,other_functions_names[k])!=NULL || strstr(after,other_functions_names[k])!=NULL))
        {
            n_counter[n_counterarrays_counter] +=1;
            n_counterarrays_counter++;
            n_square_counter[n_squarecounterarrays_counter]=1;
            n_squarecounterarrays_counter++;
        }
    }



if(strstr(words,"int")!=NULL && validity==1 && main_starts_control == true)
{
    if(number_of_square_brackets>0)
    {
        n_counter[n_counterarrays_counter] +=4;
        n_counterarrays_counter++;
        n_square_counter[n_squarecounterarrays_counter]=number_of_square_brackets;
        n_squarecounterarrays_counter++;
    }

    else
    {
        g_counter+=(4+(4*number_of_commas));
    }
}
if(strstr(words,"double")!=NULL && validity==1 && main_starts_control == true)
{
    if(number_of_square_brackets)
    {
        n_counter[n_counterarrays_counter] +=8;
        n_counterarrays_counter++;
        n_square_counter[n_squarecounterarrays_counter]=number_of_square_brackets;
        n_squarecounterarrays_counter++;
    }

    else
    {
        g_counter+=(8+(8*number_of_commas));
    }
}
if(strstr(words,"float")!=NULL && validity==1 && main_starts_control == true)
{
    if(number_of_square_brackets)
    {

        n_counter[n_counterarrays_counter] +=4;
        n_counterarrays_counter++;
        n_square_counter[n_squarecounterarrays_counter]=number_of_square_brackets;
        n_squarecounterarrays_counter++;
    }

    else
    {
        g_counter+=(4+(4*number_of_commas));
    }

}
if(strstr(words,"char")!=NULL && validity==1 && main_starts_control == true)
{
    if(number_of_square_brackets)
    {
        n_counter[n_counterarrays_counter] +=1;
        n_counterarrays_counter++;
        n_square_counter[n_squarecounterarrays_counter]=number_of_square_brackets;
        n_squarecounterarrays_counter++;
    }

    else
    {
        g_counter+=(1+(1*number_of_commas));
    }
}

if(strstr(words,"return")!=NULL && main_starts_control == true)
{
    if(atoi(after)>0 || atoi(after)<0 || strstr(after,"0")!=NULL)
    {
        return_control_value = 0;
    }

    else
    {
         g_counter+=return_control_value;
    }
}

}


//first function to call to find place complexity
//it divides the line for a special caracter and send each pair to the time complexity helper function
void find_time_complexity(struct text input[],int length){
 char *words[20];
 const char seperator[2] = " ";
int i=0;
    for(;i<=length;i++){
        if(strstr(input[i].line , "{") != NULL)
        if_it_is_a_function_control = true;

        words[0] = strtok(input[i].line, seperator);



        int k=0;
        while( words[k] != NULL )
            {
                //printf( " %s\n", words[k] );
                k++;
                words[k] = strtok(NULL, seperator);

            }
            //first sentence ended   counter = k-1
      int u=0;      for(;u<k;u++)
            {
                if(u==k-1)
                {
                time_complexity_helper(words[u],words[0],i);
                }
                else
                {
                time_complexity_helper(words[u],words[u+1],i);
                }

            }
            validity=1;
            if_it_is_a_function_control = false;


    }
}

void zaman_hesapla(struct text input[],int length)
{
  int i=0,sabit=0,j=0,k=0;
   int fark;
  for(;i<=length;i++)
    {
      if(strstr(input[i].line,"int main")!=NULL)
        j=k=i+2;
    }
  		i=0;

      for(;j<length-1;j++)
      {
        if(strstr(input[j].line,"for")==NULL ||strstr(input[j].line,"while")==NULL ||strstr(input[j].line,"do")==NULL)
        {
          if(j<publc[i].start || j>publc[i].stop)
          {
            sabit++;
          }

        }
      }
   k=dongu_sayisi-1;
  for(;k>=0;k--)
  { publc[k].adet=1;
    for(i=k-1;i>=0;i--)
    {
      if(publc[k].start>publc[i].start && publc[k].stop< publc[i].stop)
      publc[k].adet++;
    }
  }
  int n=0,m=0;
  k=0;
  for(i=0;i<dongu_sayisi;i++)
  {
    if(publc[i].adet==1)
      n++;
    else if(publc[i].adet==2)
      m++;
    else if(publc[i].adet==3)
      k++;
  }

  //printf("\n\nA:dongu icerisindeki islemi temsil eden sabit.");
  printf("\n");
  switch (recursive_)
  {
  	case 0:
  		{
  			if(n==0 && m==0 & k==0)
			  printf("T(n)=%d",sabit);
			else if(n==1 & m==1 & k==1)
			  printf("T(n)=nm(2k+2)+n(2m+2)+2n+%d+A",sabit+2);
			else if(n==1 && m==0&& k==0)
  			  printf("T(n)=A+2n+%d",sabit+2);
  			else if(n==1 && m==2 && k==1)
  			  printf("T(n)=A+2n+2n(2m+2)+nm(2k+2)+%d",sabit+2);
  			else if(n==1 && m==1 && k==0)
  			  printf("T(n)=A+2nm+4n+%d",sabit+2);
  			else if(n==1 && m==2 && k==0)
 			 printf("T(n)=A+4nm+8n+%d",sabit+4);
 			else if(n==2 && m==1 && k==0)
  			 printf("zaman denklemi: T(n)=A+2nm+6n+%d",sabit+4);
  		    else if(n==2 && m==2 && k==0)
  			 printf("zaman denklemi: T(n)=A+4nm+8n+%d",sabit+4);
  			else if(n==2 && m==0 && k==0)
  			 printf("zaman denklemi: T(n)=A+4n+%d",sabit+4);

		}
		break;
	case 1:
		{
		    if(n==0 && m==0 && k==0 )
  				printf("zaman denklemi: T(n)=n+%d",sabit);
			else if(n==1 & m==1 & k==1)
			  printf("T(n)=nm(2k+2)+n(2m+2)+3n+%d",sabit+2);
			else if(n==1 && m==0&& k==0)
  			  printf("T(n)=3n+%d",sabit+2);
  			else if(n==1 && m==2 && k==1)
  			  printf("T(n)=3n+2n(2m+2)+nm(2k+2)+%d",sabit+2);
  			else if(n==1 && m==1 && k==0)
  			  printf("T(n)=2nm+5n+%d",sabit+2);
  			else if(n==1 && m==2 && k==0)
 			 printf("T(n)=4nm+9n+%d",sabit+4);
 			else if(n==2 && m==1 && k==0)
  			 printf("zaman denklemi: T(n)=2nm+7n+%d",sabit+4);
  		    else if(n==2 && m==2 && k==0)
  			 printf("zaman denklemi: T(n)=4nm+9n+%d",sabit+4);
  			else if(n==2 && m==0 && k==0)
  			 printf("zaman denklemi: T(n)=5n+%d",sabit+4);
		}
  }

}



int main(){

FILE *fp;
int ilkDeger;
 if ((fp = fopen("input.txt", "r")) == NULL) {
      printf("dosya acma hatasi\n");
  }

  if(fscanf(fp,"%d",&ilkDeger) == EOF )
  {
      printf("dosyada veri olmamasi sebebi ile veri okunamiyor ... \n\n");
  }
  else
  {
    while(!feof(fp))
    {
        fgets(input[counter].line,sizeof(input[counter].line),fp);
        input2[counter]=input[counter];
        input3[counter]=input[counter];
        counter++;
    }


fclose(fp);
int i=0;
    for(;i<counter;i++)
    {
        printf("%s",input[i].line);
    }
    printf("\n");
    process_code(input,counter);
    find_time_complexity(input,counter);
    degisken_kontrolu(input);


    //this part writes n values
    printf("\n\nYer karmasikligi = ");int j = 0 ;
    for( ;j< n_counterarrays_counter ; j++)
    {
        if(j>0)
        printf(" + ");
        printf("%d n^%d",n_counter[j],n_square_counter[j]);

    }
    printf(" + %d",g_counter);

     int t=0,big_o_value = n_square_counter[t];
     for( t=1;t< n_counterarrays_counter ; t++)
    {
        if(n_square_counter[t]>big_o_value)
        big_o_value = n_square_counter[t];
    }
    if(big_o_value == 0)
        printf("\tO(1)");
    else
    printf("\tO(n^%d)\n\n",big_o_value);


  zaman_hesapla(input3,counter);
  }
  }



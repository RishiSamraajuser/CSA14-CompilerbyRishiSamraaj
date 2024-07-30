#include<stdio.h>
#include<ctype.h>
#include<string.h>
int main()
{
	int i,j,m;
	int ic=0,cc=0,oc=0;
	char s[30],id[30],op[30],c[30];
	printf("Enter the string\n");
	scanf("%[^\n]s",&s);
	for(i=0;i<strlen(s);i++)
	{
		if(isspace(s[i]))
		{
			continue;
		}
		else if(isalpha(s[i]))
		{
			id[ic]=s[i];
			ic++;
		}
		else if(isdigit(s[i]))
		{
			m=(s[i]-'0');
			i=i+1;
		    while(isdigit(s[i]))
	    	{
		    	m=m*10+(s[i]-'0');
		    	i++;
	    	}
	    	i=i-1;
	    	c[cc]=m;
	    	cc++;
	   }
	   else
	   {
	   	    if(s[i]=='*')
	   			{
	   	        	op[oc]='*';
	   	    		oc++;
		   		}
		   	else if(s[i]=='-')
		   	    {
		   	    	op[oc]='-';
	   	    		oc++;
				}
			else if(s[i]=='+')
		   	    {
		   	    	op[oc]='+';
	   	    		oc++;
				}
			else if(s[i]=='=')
		   	    {
		   	    	op[oc]='=';
	   	    		oc++;
				}
	   }
    }
    printf("Id :");
    for(j=0;j<ic;j++)
    {
    	printf("%c",id[j]);
	}
	printf("\nConstants :");
    for(j=0;j<cc;j++)
    {
    	printf("%d",c[j]);
	}
	printf("\nOperator :");
    for(j=0;j<oc;j++)
    {
    	printf("%c",op[j]);
	}
return 0;
}

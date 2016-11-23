#include <stdio.h>



#define Max_Resource_no 4
#define Max_process_no 5


void Print_Resource(int resource[Max_Resource_no])
{
    int i;
    for (i=0 ; i<Max_Resource_no ;i++ )
           printf ("\tR%d\t", i);
           printf ("\n");
    for (i=0 ; i<Max_Resource_no ;i++ )      
           printf ("\t%d \t",resource[i]);
}

/*To print matrices*/
void Print_Matrices(int a[Max_process_no][Max_Resource_no])
{
    int i, j;
    for (i=0 ; i<Max_Resource_no ;i++ )      
           printf ("\tR%d\t",i);
    for (i=0 ; i<Max_process_no ;i++ )
    {
        printf ("\n P%d \t",i);
        for (j=0 ; j<Max_Resource_no ;j++ )
        {
            printf("%d \t\t",a[i][j]);
        }
    }
}

void GetAvailResource(int current_loan[Max_process_no][Max_Resource_no], int available_resource[Max_Resource_no],int total_resource[Max_Resource_no])
{
    int i , j , sum =0;
    
    for (i=0 ; i < Max_Resource_no ;i++ )
    {
		sum=0;
       for (j=0 ; j< Max_process_no ;j++ )
        {
            sum+= current_loan[j][i];
        }
        
        available_resource[i] =  total_resource[i] - sum;
    }
}

void BankingResource(int available_resource[Max_Resource_no],int current_loan[Max_process_no][Max_Resource_no],int max_loan[Max_process_no][Max_Resource_no])
{

    int i , j ,  exec_flag ,safe_flag; 
	int count = Max_process_no +1;
	
	
    int pexec_order[Max_process_no]; int k =0 ;
	int run_process[Max_process_no] ={1,1,1,1,1};
    
	while(count != 0)

    { 
		safe_flag =0;

		  for(i=0; i < Max_process_no ; i++)

		  { 
			  if (run_process[i] ==1)
			  {
				 exec_flag =1;
						 for(j=0 ; j< Max_Resource_no ; j++)
							{
								 if (available_resource[j] < (max_loan[i][j] - current_loan[i][j]))
								 {
									 printf("\n Executing process P%d is UNSAFE. Delay execution of P%d.\n",i,i);
									 exec_flag =0;
									 safe_flag =0;
									 break;
								 }
							}
			 
					if (exec_flag == 1)
					{
					   run_process[i] =0;
					   printf("\n Executing process P%d is SAFE. Completing execution of P%d\n",i,i);
                        
						  pexec_order[k++]=i;
						
					   for (j=0 ; j< Max_Resource_no ; j++)
					   {
						 available_resource[j] = available_resource[j]+ current_loan [i][j];
					   }
					   printf("\n The total available resource in system are after P%d completed: \n",i);
					   Print_Resource(available_resource);
					   safe_flag =1;
					   count--;
     
					   //printf("\n%d",count);
					   break;

					}
			  }
		  }
        if(count == 1) break;
	}
   printf("\n The order of execution for all the processes using Banker's Algorithm is :\t");
   for(i=0; i< Max_process_no; i++)
		printf (" P%d\t",pexec_order[i]);	
   printf("\n");
}

int main()
{      
    int total_resource[Max_Resource_no] = {8, 5, 9, 7}; //Effective resource vector 
    int available_resource[Max_Resource_no]; // Available resource vector
    
    /*Number of resources held by process*/
    int current_loan[Max_process_no][Max_Resource_no] = {
															{2, 0, 1, 1},{0, 1, 2, 1},{4, 0, 0, 3},{0, 2, 1, 0},{1, 0, 3, 0}
                                                        }; 
                                                        
    /*Maximum resouces need by the processes to complete */                                                    
    int max_loan[Max_process_no][Max_Resource_no]= {
														{3, 2, 1, 4},{ 0, 2, 5, 2},{ 5, 1, 0, 5},{1, 5, 3, 0},{3, 0, 3, 3}                                                         
                                                    };
    
    int i;    // index for loops and counter for running process
    
   // int p_exec_order[Max_process_no];
    
    printf("\n The process to be run are : \n");
    for (i=0 ; i<Max_process_no ;i++ )
           printf ("\tP%d \t", i);

    printf("\n The resources to be given are : \n");
    for (i=0 ; i<Max_Resource_no ;i++ )
           printf ("\tR%d \t", i);
    
    
    printf("\n The maximum resources in the system are : \n");
    Print_Resource(total_resource);
          
    
    printf("\n The Maximum resources that can be allocated to the processes in the system are : \n");
    Print_Matrices(max_loan);
       
    printf("\n The allocated resources for each of the processes in the system are : \n");
    Print_Matrices(current_loan); 
    

    printf("\n The total available resource in system are : \n");
	GetAvailResource(current_loan,available_resource,total_resource);
    Print_Resource(available_resource);

    BankingResource(available_resource,current_loan,max_loan);

	
    
    return 0;
}














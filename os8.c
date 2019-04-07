#include<stdio.h>
#include<windows.h>
struct process
{                                    //tt->turn-around time
	char name;		     //at->arrival time
	int at,bt,wt,tt,rt;	     //bt->burst time
	int completed;		     //wt->waiting time									
				     //rt->remaining time
}p[10],temp;			     //n->no of processes
									
int n;
int q[10];  //queue
int front=-1,rear=-1;
void enqueue(int i)
{
    if(rear==10)
        printf("overflow");
    rear++;
    q[rear]=i;
    if(front==-1)
        front=0;

}

int dequeue()
{
    if(front==-1)
        printf("underflow");
    int temp=q[front];
    if(front==rear)
        front=rear=-1;
    else
        front++;
    return temp;
}
int isInQueue(int i)
{
    int k;
    for(k=front;k<=rear;k++)
    {
        if(q[k]==i)
        return 1;
    }
    return 0;
}



int main()
{
    int i,j,time=0,sum_bt=0,tq;
    char c;
    float avgwt=0;
    float avgtat=0;
     
     printf("\nEnter Number of Processes:\n");
     scanf("%d",&n);
     printf("Arrival time for all process must be same:\n");
     for(i=0,c='A';i<n;i++,c++)
     {
         p[i].name=c;
         printf("\n Process %c\n",c);
         printf("\n Arrival Time :");
         scanf("%d",&p[i].at);
         printf(" Burst Time :");
         scanf("%d",&p[i].bt);
         p[i].completed=0;
         sum_bt+=p[i].bt;
    }
    
    	for(i=0;i<n;i++)
	{
		for(j=i;j>=1;j--)
		{
		
			 if(p[j].at==p[j-1].at)
			{				//sorting according to burst time so first sorted job will execute
				if(p[j].bt<p[j-1].bt)                  
				{
					temp=p[j-1];
					p[j-1]=p[j];
					p[j]=temp;
				}
			}
		}
	}
	for(i=0;i<n;i++)
	{
		p[i].rt=p[i].bt;
	}
    printf("\nEnter the time unit after which CPU preemt:");
    scanf("%d",&tq);
    enqueue(0);          // enqueue the first process
    printf("Process execution order: ");
    for(time=p[0].at;time<sum_bt;)       // run until the total burst time reached
    {   
        i=dequeue();
        if(p[i].rt<=tq)
        {                          /* for processes having remaining time with less than or  equal  to time quantum  */
            Sleep(1000*tq);                 
            time+=p[i].rt;
            p[i].rt=0;
            p[i].completed=1;         
            printf(" %c ",p[i].name);
            p[i].wt=time-p[i].at-p[i].bt;
            p[i].tt=time-p[i].at;      
            for(j=0;j<n;j++)     /*enqueue the processes which have come while scheduling */
            {
                if(p[j].at<=time && p[j].completed!=1&& isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
        }
        else               // more than time quantum
        {
            time+=tq;
            p[i].rt-=tq;
            printf(" %c ",p[i].name);
            for(j=0;j<n;j++)    /*first enqueue the processes which have come while scheduling */
            {
                if(p[j].at<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
            enqueue(i);   // then enqueue the uncompleted process
        }
    }

    printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time");
    for(i=0;i<n;i++)
    {
        avgwt+=p[i].wt;
        avgtat+=p[i].tt;
        printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d",p[i].name,p[i].at,p[i].bt,p[i].wt+3,p[i].tt);
    }
    printf("\nAverage waiting time:%f\n",avgwt/n);
    printf("\nAverage turnarround time:%f\n", avgtat/n);
}






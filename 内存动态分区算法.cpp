/*
【内存管理】动态分区分配算法
1、首次适应算法
2、循环首次适应算法
3、最佳适应算法
4、最坏适应算法 
*/

#include<iostream>
#include<algorithm>
#include<fstream>
using namespace std;
#define MAXNUM 100
static int PartitionNum;//分区个数
static int Size[MAXNUM];//空闲分区内存大小
static int ProcessNum;//进程个数
static char ProcessName[MAXNUM];//进程名字
static int ProcessSize[MAXNUM];//进程大小
 char ProcessToPartition[MAXNUM][MAXNUM];//用二维数组记录进程在分区的位置
static int leftSize[MAXNUM];//剩余空闲内存
static int leftProcess[MAXNUM];//剩余进程,被存放则为0


typedef struct {//分区
	int Size; // 容量
	int id; // 地址 
}Partition;

void inPut();//输入数据
void Initialize();//初始化
void showPartition();//展示分区
void showMenu(); // 实现菜单功能
void FF(); // 首次适应算法 
void NF(); // 循环首次适应算法 
void BF(); // 最佳适应算法 
void WF(); // 最坏适应算法 



void showMenu(){
	cout<<"\t*********************************\t"<<endl;
	cout<<"\t********** 动态分区模拟 *********\t"<<endl;
	cout<<"\t******** 0、退出分区模拟 ********\t"<<endl;
	cout<<"\t********** 1、添加分区 **********\t"<<endl;
	cout<<"\t******** 2、首次适应算法 ********\t" <<endl;
	cout<<"\t****** 3、循环首次适应算法 ******\t"<<endl;
	cout<<"\t******** 4、最佳适应算法 ********\t"<<endl;
	cout<<"\t******** 5、最坏适应算法 ********\t"<<endl;
}

void Initialize(){
	for(int i=0;i<ProcessNum;i++){
		for(int j=0;j<PartitionNum;j++){
			ProcessToPartition[i][j] =NULL;
			leftSize[j] = Size[j];
		}
	}
}

void inPut(){
	int i;
	cout<<"输入分区数："<<endl;
	cin>>PartitionNum;
	cout<<"输入各个分区的大小："<<endl;
	for(i=0;i<PartitionNum;i++){
		cin>>Size[i];
	}
	cout<<"输入进程数："<<endl;
	cin>>ProcessNum;
	cout<<"输入各个进程的大小："<<endl;
	for(i=0;i<ProcessNum;i++){
			ProcessName[i]+=65;//自动帮进程生成名字
		}
	for(i=0;i<PartitionNum;i++){
			cin>>ProcessSize[i];//输入进程大小
		}
		
 	cout<<"分区名称: "<<"\t\t";
    for (i=0;i<PartitionNum;i++){
        cout<<"P"<<i+1<<"\t";
    }
    cout<<endl<<"内存大小: "<<"\t\t";
    for (i=0;i<PartitionNum;i++){
        cout<<Size[i]<<"\t";
	    }	
	cout<<endl<<"进程名称: "<<"\t\t";
    for (i=0;i<ProcessNum;i++){
        cout<<ProcessName[i]<<"\t";
    }
    cout<<endl<<"进程大小： "<<"\t\t";
    for (i=0;i<ProcessNum;i++){
        cout<<ProcessSize[i]<<"\t";
    }
    cout<<endl<<"--------------------------------"<<endl;
}

void display(){
     int i;
      cout<<"进程名称: "<<"\t\t";
      for (i=0;i<ProcessNum;i++){
          cout<<ProcessName[i]<<"\t";
      }
      cout<<endl;
      cout<<"进程大小： "<<"\t\t";
      for (i=0;i<ProcessNum;i++){
          cout<<ProcessSize[i]<<"\t";
      }
      cout<<endl;
   
      cout<<"分区名称: "<<"\t\t";
      for (i=0;i<PartitionNum;i++){
          cout<<"P"<<i+1<<"\t";
      }
      cout<<endl<<"内存大小: "<<"\t\t";
      for (i=0;i<PartitionNum;i++){
          cout<<Size[i]<<"\t";
      }
      cout<<endl<<"分区剩余内存大小: "<<"\t";
      for (i=0;i<PartitionNum;i++){
          cout<<leftSize[i]<<"\t";
      }
      cout<<endl<<"分区结果:"<<endl;
      for (i=0;i<PartitionNum;i++){
          for (int j = 0;j<ProcessNum;j++){
              if (ProcessToPartition[j][i]!=NULL){
                  cout<<ProcessToPartition[j][i]<<": P"<<i+1<<endl;
              }
          }
      }
  
}

//首次适应算法
void FF(){
	cout<<"首次适应算法"<<endl;
	Initialize();
	for(int i=0;i<ProcessNum;i++){//遍历
		for(int j=0;j<PartitionNum;j++){//每次从分区的首地址开始照
		//当剩余分区空间不为0且够放的下进程时
			if(leftProcess[i] <= leftSize[j]&&leftSize!=0){
			leftSize[j]-=leftProcess[i];
			leftProcess[j]=0;
			ProcessToPartition[i][j] = ProcessName[i];//存放进程名称
			break;
			}
		}
	}
	display();
}	


//循环首次适应算法
void NF(){
	cout<<"首次适应算法"<<endl;
	Initialize();
	int j,nextPartiton=0;//存放下一个空分区的数字
	bool FitSuccess=false;
	for(int i=0;i<ProcessNum;i++){
		FitSuccess=true;
		while(FitSuccess){
			if(leftSize[nextPartiton] >= leftProcess[i]){
				leftSize[nextPartiton] -=leftProcess[i];
				leftProcess[i]=0;
				ProcessToPartition[i][nextPartiton] = ProcessName[i];
				nextPartiton++;
				if(nextPartiton > PartitionNum-1){
					nextPartiton = 0;//当nextPartition遍历到分区末尾的时候，返回首位置
				}
				 FitSuccess = false;
			}else{
				nextPartiton++;
				if(nextPartiton > PartitionNum-1){
					nextPartiton =0;//当nextPartition遍历到分区末尾的时候，返回首位置
				}  
				j++;
                if(j>=PartitionNum){//避免死循环
                	FitSuccess=false;
                    j=0;
                }	
			}
		}	
	}
	display();
}

//最佳适应算法
void BF(){
  //对分区大小进行排序,每次分配完一个进程的内存大小后，重新排序
    cout<<"BF"<<endl;
    Initialize();
    int i,j,s,t;
    Partition best[MAXNUM];
    Partition temp;
    for (i=0;i<PartitionNum;i++){
        best[i].Size = Size[i];
        best[i].id = i;
    }
 
    for (i=0;i<ProcessNum;i++){
        //冒泡排序(每次分配完一个进程后，都需要重新排序)
        for (s=0;s < PartitionNum - 1;s++){
            for (t = s;t < PartitionNum - 1;t++){
                if (best[s].Size > best[t].Size){
                    temp = best[s];
                    best[s] = best[t];
                    best[t] = temp;
                }
            }
        }
 
        for (j=0;j<PartitionNum;j++){
            if (leftProcess[i] <= best[j].Size){
                best[j].Size -= leftProcess[i];
                leftProcess[i] = 0;
 
                ProcessToPartition[i][best[j].id] = ProcessName[i];
                break;
            }
        }
        leftSize[best[j].id] = best[j].Size;
    }
    display();

}

//最坏适应算法 
void WF(){
	   cout<<"WF"<<endl;
	     Initialize();
	     int i,j,s,t;
	     Partition Worst[MAXNUM];
	     Partition temp;
	     for (i = 0;i<PartitionNum;i++){
	         Worst[i].Size = Size[i];
	         Worst[i].id = i;
	     }
	  
	     for (i = 0;i<ProcessNum;i++){
	         for (s=0;s<PartitionNum - 1;s++){
	             for (t=s;t<PartitionNum - 1;t++){
	                 if (Worst[s].Size < Worst[t].Size){
	                     temp = Worst[s];
	                     Worst[s] = Worst[t];
	                     Worst[t] = temp;
	                 }
	             }
	         }
	  
	         for (j=0;j<PartitionNum;j++){
	             if (leftProcess[i] <= Worst[j].Size){
	                 Worst[j].Size -= leftProcess[i];
	                 leftProcess[j] = 0;
	  
	                 ProcessToPartition[i][Worst[j].id] = ProcessName[i];
	                 break;
	             }
	             else{
	                 cout<<"Fail to Partition "<<ProcessName[i]<<endl;
	                 break;
	             }
	         }
	         leftSize[Worst[j].id] = Worst[j].Size;
	     }
	     display();
	 
}


void choose_Algorithm(){
		showMenu();
		int choose;
		cin>>choose;
		cout<<endl;
		if (choose==1)
		{
			inPut();
			choose_Algorithm();
		}
			else if(choose==2)
			{
				FF();
				choose_Algorithm();
			}
			else if(choose==3){
	            NF();
	            choose_Algorithm();
			}
			else if(choose==4){
	            BF();
	            choose_Algorithm();
			}
			else if(choose==5){
	            WF();
	            choose_Algorithm();
			}
			else if(choose==0){
	          exit(0);
			}
		else
		{
			cout<<"请输入正确的选择"<<endl;
			cout<<"------------------------------------------------------"<<endl;
			choose_Algorithm();  //递归
		}
}
int main(){
	choose_Algorithm();
}




 

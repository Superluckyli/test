/*
���ڴ������̬���������㷨
1���״���Ӧ�㷨
2��ѭ���״���Ӧ�㷨
3�������Ӧ�㷨
4�����Ӧ�㷨 
*/

#include<iostream>
#include<algorithm>
#include<fstream>
using namespace std;
#define MAXNUM 100
static int PartitionNum;//��������
static int Size[MAXNUM];//���з����ڴ��С
static int ProcessNum;//���̸���
static char ProcessName[MAXNUM];//��������
static int ProcessSize[MAXNUM];//���̴�С
 char ProcessToPartition[MAXNUM][MAXNUM];//�ö�ά�����¼�����ڷ�����λ��
static int leftSize[MAXNUM];//ʣ������ڴ�
static int leftProcess[MAXNUM];//ʣ�����,�������Ϊ0


typedef struct {//����
	int Size; // ����
	int id; // ��ַ 
}Partition;

void inPut();//��������
void Initialize();//��ʼ��
void showPartition();//չʾ����
void showMenu(); // ʵ�ֲ˵�����
void FF(); // �״���Ӧ�㷨 
void NF(); // ѭ���״���Ӧ�㷨 
void BF(); // �����Ӧ�㷨 
void WF(); // ���Ӧ�㷨 



void showMenu(){
	cout<<"\t*********************************\t"<<endl;
	cout<<"\t********** ��̬����ģ�� *********\t"<<endl;
	cout<<"\t******** 0���˳�����ģ�� ********\t"<<endl;
	cout<<"\t********** 1����ӷ��� **********\t"<<endl;
	cout<<"\t******** 2���״���Ӧ�㷨 ********\t" <<endl;
	cout<<"\t****** 3��ѭ���״���Ӧ�㷨 ******\t"<<endl;
	cout<<"\t******** 4�������Ӧ�㷨 ********\t"<<endl;
	cout<<"\t******** 5�����Ӧ�㷨 ********\t"<<endl;
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
	cout<<"�����������"<<endl;
	cin>>PartitionNum;
	cout<<"������������Ĵ�С��"<<endl;
	for(i=0;i<PartitionNum;i++){
		cin>>Size[i];
	}
	cout<<"�����������"<<endl;
	cin>>ProcessNum;
	cout<<"����������̵Ĵ�С��"<<endl;
	for(i=0;i<ProcessNum;i++){
			ProcessName[i]+=65;//�Զ��������������
		}
	for(i=0;i<PartitionNum;i++){
			cin>>ProcessSize[i];//������̴�С
		}
		
 	cout<<"��������: "<<"\t\t";
    for (i=0;i<PartitionNum;i++){
        cout<<"P"<<i+1<<"\t";
    }
    cout<<endl<<"�ڴ��С: "<<"\t\t";
    for (i=0;i<PartitionNum;i++){
        cout<<Size[i]<<"\t";
	    }	
	cout<<endl<<"��������: "<<"\t\t";
    for (i=0;i<ProcessNum;i++){
        cout<<ProcessName[i]<<"\t";
    }
    cout<<endl<<"���̴�С�� "<<"\t\t";
    for (i=0;i<ProcessNum;i++){
        cout<<ProcessSize[i]<<"\t";
    }
    cout<<endl<<"--------------------------------"<<endl;
}

void display(){
     int i;
      cout<<"��������: "<<"\t\t";
      for (i=0;i<ProcessNum;i++){
          cout<<ProcessName[i]<<"\t";
      }
      cout<<endl;
      cout<<"���̴�С�� "<<"\t\t";
      for (i=0;i<ProcessNum;i++){
          cout<<ProcessSize[i]<<"\t";
      }
      cout<<endl;
   
      cout<<"��������: "<<"\t\t";
      for (i=0;i<PartitionNum;i++){
          cout<<"P"<<i+1<<"\t";
      }
      cout<<endl<<"�ڴ��С: "<<"\t\t";
      for (i=0;i<PartitionNum;i++){
          cout<<Size[i]<<"\t";
      }
      cout<<endl<<"����ʣ���ڴ��С: "<<"\t";
      for (i=0;i<PartitionNum;i++){
          cout<<leftSize[i]<<"\t";
      }
      cout<<endl<<"�������:"<<endl;
      for (i=0;i<PartitionNum;i++){
          for (int j = 0;j<ProcessNum;j++){
              if (ProcessToPartition[j][i]!=NULL){
                  cout<<ProcessToPartition[j][i]<<": P"<<i+1<<endl;
              }
          }
      }
  
}

//�״���Ӧ�㷨
void FF(){
	cout<<"�״���Ӧ�㷨"<<endl;
	Initialize();
	for(int i=0;i<ProcessNum;i++){//����
		for(int j=0;j<PartitionNum;j++){//ÿ�δӷ������׵�ַ��ʼ��
		//��ʣ������ռ䲻Ϊ0�ҹ��ŵ��½���ʱ
			if(leftProcess[i] <= leftSize[j]&&leftSize!=0){
			leftSize[j]-=leftProcess[i];
			leftProcess[j]=0;
			ProcessToPartition[i][j] = ProcessName[i];//��Ž�������
			break;
			}
		}
	}
	display();
}	


//ѭ���״���Ӧ�㷨
void NF(){
	cout<<"�״���Ӧ�㷨"<<endl;
	Initialize();
	int j,nextPartiton=0;//�����һ���շ���������
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
					nextPartiton = 0;//��nextPartition����������ĩβ��ʱ�򣬷�����λ��
				}
				 FitSuccess = false;
			}else{
				nextPartiton++;
				if(nextPartiton > PartitionNum-1){
					nextPartiton =0;//��nextPartition����������ĩβ��ʱ�򣬷�����λ��
				}  
				j++;
                if(j>=PartitionNum){//������ѭ��
                	FitSuccess=false;
                    j=0;
                }	
			}
		}	
	}
	display();
}

//�����Ӧ�㷨
void BF(){
  //�Է�����С��������,ÿ�η�����һ�����̵��ڴ��С����������
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
        //ð������(ÿ�η�����һ�����̺󣬶���Ҫ��������)
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

//���Ӧ�㷨 
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
			cout<<"��������ȷ��ѡ��"<<endl;
			cout<<"------------------------------------------------------"<<endl;
			choose_Algorithm();  //�ݹ�
		}
}
int main(){
	choose_Algorithm();
}




 

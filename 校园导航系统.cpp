#include"malloc.h"
#include"stdio.h"
#include"string.h"
#define MAXVEX 50             /*��󶥵����*/ 
#define MAXWEIGHT 50000       /*���Ȩֵ*/
typedef int weight;          /*Ȩֵ*/ 
typedef struct{              /*��������*/ 
	int no;                   /*������*/ 
	char name[20];            /*��������*/ 
	char desc[100];           /*������*/ 
}DataType;
typedef	 struct{
	weight arcs[MAXVEX][MAXVEX];   /*�ڽӾ���*/
	DataType data[MAXVEX];         /*������Ϣ*/
	int vexs;                     /*������*/ 
}MGraph,*AdjMetrix;

	/*��������*/
void CreateGraph(AdjMetrix g,int m[][MAXVEX],DataType d[],int n)
{
	int i,j;
	g->vexs=n;
	for(i=0;i<n;i++)
	{
		g->data[i]=d[i];
 		for(j=0;j<n;j++)   
			g->arcs[i][j]=m[i][j];
	}
} 

//��ʾ�ڽӾ��� 
void DispGraph(AdjMetrix g)
{
	int i,j;
	printf("���㣺\n\t");
	for(i=0;i<g->vexs;i++)
	  printf("%s\t",g->data[i].name);
	printf("\n\n�ڽӾ���");
	for(i=0;i<g->vexs;i++)
	{
		printf("\n%s:\n",g->data[i].name);
		for(j=0;j<g->vexs;j++)
		   printf("%d\t",g->arcs[i][j]);
	}
	printf("\n\n");
}

/*���ݾ������Ʋ�ѯ������Ϣ*/
void QueryVex(AdjMetrix g,char name[])
{
	int i;
	for(i=0;i<g->vexs;i++)
		if(!strcmp(name,g->data[i].name))
 			printf("�����ţ�[%d],��������:%s\n ���:\n-----------\n%s\n",g->data[i].no,g->data[i].name,g->data[i].desc);
	return;
 	
} 

/*���ݾ������Ʋ��Ҿ������*/
int Locate(AdjMetrix g,char name[])
{
	for(int i=0;i<g->vexs;i++)
		if(!strcmp(name,g->data[i].name))
			return i;
	return -1;
} 

/*��ʾ���·��*/
void DispPath(AdjMetrix g,int path[],int dis[],int start,int end)
{
	int top=-1,pos;
	DataType base[MAXVEX];
	DataType x;
	pos=path[end];
	while(pos!=start){base[++top]=g->data[pos];  pos=path[pos];}
	base[++top]=g->data[start];
	printf("��[%s]��[%s]�����·��Ϊ��",g->data[start].name,g->data[end].name);
	while(top!=-1){
		x=base[top--];printf("%s->",x.name);}
		printf("%s",g->data[end].name);
		printf("\n��·����%d�ף���Լ��Ҫ��%d����\n\n",dis[end],dis[end]/60);
} 

/*�����·��*/
void Dijstra(AdjMetrix g,int v,int dis[],int path[])
{
	int vset[MAXVEX];
	int MinDis,i,j,w;
	for(i=0;i<g->vexs;i++)//��ʼ�� 
	{
		vset[i]=1;
		dis[i]=g->arcs[v][i];
		printf("%d\t",dis[i]);	
	} 
	vset[v]=0;//����v���뼯��V�� 
	for(i=1;i<g->vexs;i++)
	{
		MinDis=MAXWEIGHT;
		for(j=0;j<g->vexs;j++)//���v��w�����·�� 
		  if(vset[j]&&dis[j]<MinDis)
		  {
  			w=j;
  			MinDis=dis[j];
  		} 
  		printf("\n����%s������%s�����·��ֵΪ��%d\n",g->data[v].name,g->data[w].name,MinDis);//������·�� 
		  //����Ƿ���ͨͼ������·��ʱ�˳��㷨 
		  if(MinDis==MAXWEIGHT)return;
		  
		  
		  path[w]=v;
		  v=w;
		  
		  
		  vset[w]=0;//����w���뼯��V
		  //���ڼ���w����Ҫ�޸�v������W�ж�������·��ֵ 
		  for(j=0;j<g->vexs;j++)
		  {
  			if(vset[j]&&g->arcs[w][j]<MAXWEIGHT&&dis[w]+g->arcs[w][j]<dis[j])
  			dis[j]=dis[w]+g->arcs[w][j];
  		} 
	} 	
} 

int main(int argc,char* argv[])
{
	MGraph gg;
	AdjMetrix g=&gg;
	DataType d[]={{1,"����","�����ǹ�����ѧ������,λ�ڹ�����ѧ����������������ѧ��·100��"},{2,"�ۺ�¥","�ǹ�����ѧ�����ۺϽ�ѧ¥��Ρ����ΰ���Ҹ����ִ�������2000�꽨��"},{3,"������","������"},
	{4,"��������","��������"},{5,"������","�������ǹ�����ѧ������ѧ���������ѧ��ͨ"},{6,"�����ѧԺ","�����ѧԺ"},{7,"����¥","����¥�Ǿ�����������"
	},{8,"����¥","����¥�ǹ�����ѧ�������������"},{9,"��Է","��Էλ��ѧ���������ڣ���ͨ����"},{10,"ͼ���","������ѧͼ����ǹ��������󡢲�������ͼ��ݣ�������ΰ׳�ۣ�����³�ཱ"}};
	int
	m[][MAXVEX]={
	{MAXWEIGHT,1500,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT},
	{1500,MAXWEIGHT,1000,MAXWEIGHT,MAXWEIGHT,800,MAXWEIGHT,MAXWEIGHT,1500,MAXWEIGHT},
	{MAXWEIGHT,1000,MAXWEIGHT,400,MAXWEIGHT,300,200,200,MAXWEIGHT,MAXWEIGHT},
	{MAXWEIGHT,MAXWEIGHT,400,MAXWEIGHT,200,MAXWEIGHT,100,100,MAXWEIGHT,800},
	{MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,200,MAXWEIGHT,MAXWEIGHT,250,260,MAXWEIGHT,1500},
	{MAXWEIGHT,800,300,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,50,400,MAXWEIGHT,MAXWEIGHT},
	{MAXWEIGHT,MAXWEIGHT,200,100,250,50,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT},
	{MAXWEIGHT,MAXWEIGHT,200,100,260,400,MAXWEIGHT,MAXWEIGHT,600,MAXWEIGHT},
	{MAXWEIGHT,1500,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,600,MAXWEIGHT,900},
	{MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,800,1500,MAXWEIGHT,MAXWEIGHT,MAXWEIGHT,900,MAXWEIGHT}
	};
	int dis[5],path[MAXVEX];
	int choice=0,start,end;
	char vname[20];
	DataType x;
	CreateGraph(g,m,d,10);
	DispGraph(g);
	do{
		printf("******************************************* \n");
	    printf("* 	       У԰����ϵͳ               * \n");
	    printf("*-----------------------------------------* \n");
	    printf("*          1.��ѯ������Ϣ                 * \n");
	    printf("*          2.������ĳ����������·��     * \n");
	    printf("*          0.�˳�                         * \n");
	    printf("******************************************* \n");
	    printf("\n please select(1,2,0):");
	    scanf("%d",&choice);
	    if(choice<0 ||choice>10)  continue;
	    switch(choice)
	    {
   		case 1:
    		printf("\n�����뾰�����֣�");
			scanf("%s",vname);
			QueryVex(g,vname);break;
		case 2:
			printf("\n���������������ڵľ������ƣ�");
			scanf("%s",vname); 
			start=Locate(g,vname);
			printf("\n��������Ҫȥ�ľ������ƣ�");
			scanf("%s",vname);
			end=Locate(g,vname);
			if(start!=-1 ||end!=-1)
			{
				Dijstra(g,start,dis,path);
				DispPath(g,path,dis,start,end);
			} 
			break;
		
		case 0:exit(0);
    	}
	}while(1);
	return 0;
}

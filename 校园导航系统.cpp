#include"malloc.h"
#include"stdio.h"
#include"string.h"
#define MAXVEX 50             /*最大顶点个数*/ 
#define MAXWEIGHT 50000       /*最大权值*/
typedef int weight;          /*权值*/ 
typedef struct{              /*景点类型*/ 
	int no;                   /*景点编号*/ 
	char name[20];            /*景点名称*/ 
	char desc[100];           /*景点简介*/ 
}DataType;
typedef	 struct{
	weight arcs[MAXVEX][MAXVEX];   /*邻接矩阵*/
	DataType data[MAXVEX];         /*顶点信息*/
	int vexs;                     /*顶点数*/ 
}MGraph,*AdjMetrix;

	/*创建矩阵*/
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

//显示邻接矩阵 
void DispGraph(AdjMetrix g)
{
	int i,j;
	printf("顶点：\n\t");
	for(i=0;i<g->vexs;i++)
	  printf("%s\t",g->data[i].name);
	printf("\n\n邻接矩阵：");
	for(i=0;i<g->vexs;i++)
	{
		printf("\n%s:\n",g->data[i].name);
		for(j=0;j<g->vexs;j++)
		   printf("%d\t",g->arcs[i][j]);
	}
	printf("\n\n");
}

/*根据景点名称查询景点信息*/
void QueryVex(AdjMetrix g,char name[])
{
	int i;
	for(i=0;i<g->vexs;i++)
		if(!strcmp(name,g->data[i].name))
 			printf("景点编号：[%d],景点名称:%s\n 简介:\n-----------\n%s\n",g->data[i].no,g->data[i].name,g->data[i].desc);
	return;
 	
} 

/*根据景点名称查找景点序号*/
int Locate(AdjMetrix g,char name[])
{
	for(int i=0;i<g->vexs;i++)
		if(!strcmp(name,g->data[i].name))
			return i;
	return -1;
} 

/*显示最短路径*/
void DispPath(AdjMetrix g,int path[],int dis[],int start,int end)
{
	int top=-1,pos;
	DataType base[MAXVEX];
	DataType x;
	pos=path[end];
	while(pos!=start){base[++top]=g->data[pos];  pos=path[pos];}
	base[++top]=g->data[start];
	printf("从[%s]到[%s]的最佳路径为；",g->data[start].name,g->data[end].name);
	while(top!=-1){
		x=base[top--];printf("%s->",x.name);}
		printf("%s",g->data[end].name);
		printf("\n此路径长%d米，大约需要走%d分钟\n\n",dis[end],dis[end]/60);
} 

/*求最短路径*/
void Dijstra(AdjMetrix g,int v,int dis[],int path[])
{
	int vset[MAXVEX];
	int MinDis,i,j,w;
	for(i=0;i<g->vexs;i++)//初始化 
	{
		vset[i]=1;
		dis[i]=g->arcs[v][i];
		printf("%d\t",dis[i]);	
	} 
	vset[v]=0;//顶点v加入集合V中 
	for(i=1;i<g->vexs;i++)
	{
		MinDis=MAXWEIGHT;
		for(j=0;j<g->vexs;j++)//求出v到w的最短路径 
		  if(vset[j]&&dis[j]<MinDis)
		  {
  			w=j;
  			MinDis=dis[j];
  		} 
  		printf("\n顶点%s到顶点%s的最短路径值为：%d\n",g->data[v].name,g->data[w].name,MinDis);//输出最短路径 
		  //如果是非连通图，则无路径时退出算法 
		  if(MinDis==MAXWEIGHT)return;
		  
		  
		  path[w]=v;
		  v=w;
		  
		  
		  vset[w]=0;//顶点w加入集合V
		  //由于加入w，需要修改v到集合W中顶点的最短路径值 
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
	DataType d[]={{1,"南门","南门是广西大学的正门,位于广西大学南宁市西乡塘区大学东路100号"},{2,"综合楼","是广西大学最大的综合教学楼，巍峨雄伟并且富有现代化，于2000年建成"},{3,"大礼堂","大礼堂"},
	{4,"西体育馆","西体育馆"},{5,"西大附中","西大附中是广西大学附属中学，与广西大学相通"},{6,"外国语学院","外国语学院"},{7,"君武楼","君武楼是君武先生命名"
	},{8,"网络楼","网络楼是广西大学的网络控制中心"},{9,"南苑","南苑位于学生宿舍区内，交通便利"},{10,"图书馆","广西大学图书馆是广西面积最大、藏书最多的图书馆，建筑宏伟壮观，曾获鲁班奖"}};
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
	    printf("* 	       校园导游系统               * \n");
	    printf("*-----------------------------------------* \n");
	    printf("*          1.查询景点信息                 * \n");
	    printf("*          2.给出到某个景点的最佳路线     * \n");
	    printf("*          0.退出                         * \n");
	    printf("******************************************* \n");
	    printf("\n please select(1,2,0):");
	    scanf("%d",&choice);
	    if(choice<0 ||choice>10)  continue;
	    switch(choice)
	    {
   		case 1:
    		printf("\n请输入景点名字：");
			scanf("%s",vname);
			QueryVex(g,vname);break;
		case 2:
			printf("\n请输入你现在所在的景点名称：");
			scanf("%s",vname); 
			start=Locate(g,vname);
			printf("\n请输入你要去的景点名称：");
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

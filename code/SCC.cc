#include<memory.h>
struct edge{int e, nxt;};
int V, E;
edge e[MAXE], er[MAXE];
int sp[MAXV], spr[MAXV];
int group_cnt, group_num[MAXV];
bool v[MAXV];
int stk[MAXV];
void fill_forward(int x)
{
  int i;
  v[x]=true;
  for(i=sp[x];i;i=e[i].nxt) if(!v[e[i].e]) fill_forward(e[i].e);
  stk[++stk[0]]=x;
}
void fill_backward(int x)
{
  int i;
  v[x]=false;
  group_num[x]=group_cnt;
  for(i=spr[x];i;i=er[i].nxt) if(v[er[i].e]) fill_backward(er[i].e);
}
void add_edge(int v1, int v2) //add edge v1->v2
{
  e [++E].e=v2; e [E].nxt=sp [v1]; sp [v1]=E;
  er[  E].e=v1; er[E].nxt=spr[v2]; spr[v2]=E;
}
void SCC()
{
  int i;
  stk[0]=0;
  memset(v, false, sizeof(v));
  for(i=1;i<=V;i++) if(!v[i]) fill_forward(i);
  group_cnt=0;
  for(i=stk[0];i>=1;i--) if(v[stk[i]]){group_cnt++; fill_backward(stk[i]);}
}

// Tarjan's SCC Algorithm
int n, m;
struct Node{vector<int> adj;};
Node graph[MAX_N];
stack<int> Stack;
bool onStack[MAX_N];
int Indices;
int Index[MAX_N];
int LowLink[MAX_N];
int component[MAX_N];
int numComponents;

void tarjanDFS(int i)
{
    Index[i] = ++Indices;
    LowLink[i] = Indices;
    Stack.push(i); onStack[i] = true;
    for (int j=0;j<graph[i].adj.size();j++){
        int w = graph[i].adj[j];
        if (Index[w] == 0){
            tarjanDFS(w);
            LowLink[i] = min(LowLink[i], LowLink[w]);
        }else if (onStack[w]){
            LowLink[i] = min(LowLink[i], Index[w]);
        }
    }
    if (LowLink[i] == Index[i]){
        int w = 0;
        do{
            w = Stack.top(); Stack.pop();
            component[w] = numComponents;
            onStack[w]=false;
        } while (i != w && !Stack.empty());
        numComponents++;
    }
}

void Tarjan()
{
    Indices = 0;
    while (!Stack.empty()) Stack.pop();
    for (int i=n;i>0;i--) onStack[i] = LowLink[i] = Index[i] = 0;
    numComponents = 0;
    for (int i=n;i>0;i--) if (Index[i] == 0) tarjanDFS(i);
}

// add edge i to j
// graph[i].adj.push_back(j);
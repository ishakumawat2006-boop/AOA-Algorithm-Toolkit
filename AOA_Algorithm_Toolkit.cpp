#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;

const int INF = 9999;

/* 1. QUICK SORT */
int partitionQS(vector<int>& a, int low, int high) {
    int pivot = a[high], i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}
void quickSort(vector<int>& a, int low, int high) {
    if (low < high) {
        int p = partitionQS(a, low, high);
        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}
void runQuickSort() {
    int n; cout << "\nEnter number of elements: "; cin >> n;
    vector<int> a(n); cout << "Enter elements:\n";
    for (int &x : a) cin >> x;
    quickSort(a, 0, n - 1);
    cout << "Sorted Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n";
}

/* 2. MERGE SORT */
void mergeParts(vector<int>& a, int l, int m, int r) {
    vector<int> temp;
    int i = l, j = m + 1;
    while (i <= m && j <= r) {
        if (a[i] < a[j]) temp.push_back(a[i++]);
        else temp.push_back(a[j++]);
    }
    while (i <= m) temp.push_back(a[i++]);
    while (j <= r) temp.push_back(a[j++]);
    for (int k = 0; k < (int)temp.size(); k++) a[l + k] = temp[k];
}
void mergeSort(vector<int>& a, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        mergeParts(a, l, m, r);
    }
}
void runMergeSort() {
    int n; cout << "\nEnter number of elements: "; cin >> n;
    vector<int> a(n); cout << "Enter elements:\n";
    for (int &x : a) cin >> x;
    mergeSort(a, 0, n - 1);
    cout << "Sorted Array: ";
    for (int x : a) cout << x << " ";
    cout << "\n";
}

/* 3(a). TOPOLOGICAL SORT */
void runTopologicalSort() {
    int n; cout << "\nEnter number of vertices: "; cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    vector<int> indeg(n, 0), q(n), result;
    cout << "Enter adjacency matrix:\n";
    for (int i=0;i<n;i++) for(int j=0;j<n;j++) {
        cin >> g[i][j];
        if (g[i][j] == 1) indeg[j]++;
    }
    int front=0,rear=0;
    for(int i=0;i<n;i++) if(indeg[i]==0) q[rear++]=i;
    while(front<rear) {
        int v=q[front++]; result.push_back(v);
        for(int i=0;i<n;i++) if(g[v][i]) {
            indeg[i]--;
            if(indeg[i]==0) q[rear++]=i;
        }
    }
    if((int)result.size()!=n) cout << "Topological Ordering is not possible. Graph contains a cycle.\n";
    else {
        cout << "Topological Ordering: ";
        for(int x:result) cout << x << " ";
        cout << "\n";
    }
}

/* 3(b). WARSHALL */
void runWarshall() {
    int n; cout << "\nEnter number of vertices: "; cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    cout << "Enter adjacency matrix:\n";
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin >> g[i][j];
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(g[i][k] && g[k][j]) g[i][j]=1;
    cout << "Transitive Closure Matrix:\n";
    for(auto &row:g){ for(int x:row) cout << x << " "; cout << "\n"; }
}

/* 4. 0/1 KNAPSACK */
void runKnapsack() {
    int n,W; cout << "\nEnter number of items: "; cin >> n;
    vector<int> wt(n+1), p(n+1);
    cout << "Enter weights:\n"; for(int i=1;i<=n;i++) cin>>wt[i];
    cout << "Enter profits:\n"; for(int i=1;i<=n;i++) cin>>p[i];
    cout << "Enter knapsack capacity: "; cin>>W;
    vector<vector<int>> K(n+1, vector<int>(W+1,0));
    for(int i=1;i<=n;i++) for(int w=1;w<=W;w++)
        if(wt[i]<=w) K[i][w]=max(p[i]+K[i-1][w-wt[i]],K[i-1][w]);
        else K[i][w]=K[i-1][w];
    cout << "Maximum Profit = " << K[n][W] << "\n";
}

/* 5. DIJKSTRA */
void runDijkstra() {
    int n,src; cout << "\nEnter number of vertices: "; cin>>n;
    vector<vector<int>> g(n, vector<int>(n));
    cout << "Enter adjacency matrix (0 means no edge):\n";
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){ cin>>g[i][j]; if(g[i][j]==0 && i!=j) g[i][j]=INF; }
    cout << "Enter source vertex: "; cin>>src;
    vector<int> dist(n,INF), vis(n,0); dist[src]=0;
    for(int c=0;c<n;c++){
        int u=-1;
        for(int i=0;i<n;i++) if(!vis[i] && (u==-1 || dist[i]<dist[u])) u=i;
        if(u==-1 || dist[u]>=INF) break;
        vis[u]=1;
        for(int v=0;v<n;v++) if(!vis[v] && g[u][v]<INF && dist[u]+g[u][v]<dist[v])
            dist[v]=dist[u]+g[u][v];
    }
    cout << "Shortest distances from vertex " << src << ":\n";
    for(int i=0;i<n;i++) cout<<"Vertex "<<i<<" -> Distance = "<<(dist[i]>=INF?INF:dist[i])<<"\n";
}

/* 6. FLOYD */
void runFloyd() {
    int n; cout << "\nEnter number of vertices: "; cin>>n;
    vector<vector<int>> g(n, vector<int>(n));
    cout << "Enter weighted adjacency matrix (0 means no edge):\n";
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){ cin>>g[i][j]; if(g[i][j]==0 && i!=j) g[i][j]=INF; }
    for(int k=0;k<n;k++) for(int i=0;i<n;i++) for(int j=0;j<n;j++)
        if(g[i][k]+g[k][j]<g[i][j]) g[i][j]=g[i][k]+g[k][j];
    cout<<"Shortest Distance Matrix:\n";
    for(auto &row:g){ for(int x:row) cout<<(x>=INF?"INF":to_string(x))<<" "; cout<<"\n"; }
}

/* 7. PRIM */
void runPrim() {
    int n; cout << "\nEnter number of vertices: "; cin>>n;
    vector<vector<int>> c(n, vector<int>(n));
    cout<<"Enter cost adjacency matrix:\n";
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){cin>>c[i][j]; if(c[i][j]==0)c[i][j]=INF;}
    vector<int> vis(n,0); vis[0]=1; int edges=0,total=0;
    cout<<"Edges in Minimum Spanning Tree:\n";
    while(edges<n-1){
        int mn=INF,a=-1,b=-1;
        for(int i=0;i<n;i++) if(vis[i]) for(int j=0;j<n;j++)
            if(!vis[j] && c[i][j]<mn){mn=c[i][j];a=i;b=j;}
        if(b==-1){cout<<"MST cannot be formed (graph may be disconnected).\n";return;}
        cout<<a<<" --> "<<b<<" = "<<mn<<"\n"; total+=mn; vis[b]=1; edges++;
    }
    cout<<"Minimum Cost = "<<total<<"\n";
}

/* 8. KRUSKAL */
struct Edge{int u,v,w;};
int findSet(vector<int>& parent,int x){ return parent[x]==x?x:parent[x]=findSet(parent,parent[x]); }
bool unionSet(vector<int>& parent, vector<int>& rankv,int a,int b){
    a=findSet(parent,a); b=findSet(parent,b); if(a==b)return false;
    if(rankv[a]<rankv[b]) swap(a,b);
    parent[b]=a; if(rankv[a]==rankv[b])rankv[a]++; return true;
}
void runKruskal(){
    int n; cout<<"\nEnter number of vertices: ";cin>>n;
    vector<vector<int>> c(n,vector<int>(n)); vector<Edge> edges;
    cout<<"Enter cost adjacency matrix:\n";
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>c[i][j];
    for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) if(c[i][j]!=0) edges.push_back({i,j,c[i][j]});
    sort(edges.begin(),edges.end(),[](Edge a,Edge b){return a.w<b.w;});
    vector<int> parent(n),rankv(n,0); for(int i=0;i<n;i++)parent[i]=i;
    int total=0,count=0; cout<<"Edges in Minimum Spanning Tree:\n";
    for(auto e:edges) if(unionSet(parent,rankv,e.u,e.v)){cout<<e.u<<" --> "<<e.v<<" = "<<e.w<<"\n";total+=e.w;if(++count==n-1)break;}
    if(count!=n-1) cout<<"MST cannot be formed (graph may be disconnected).\n";
    else cout<<"Minimum Cost = "<<total<<"\n";
}

/* 9. TSP - follows the supplied lab's recursive approach */
int tspN; int tspCost[10][10]; bool tspVisited[10]; int bestTSP;
void tsp(int city,int count,int cur){
    if(count==tspN){ if(tspCost[city][0]!=0) bestTSP=min(bestTSP,cur+tspCost[city][0]); return; }
    for(int i=0;i<tspN;i++) if(!tspVisited[i] && tspCost[city][i]!=0){
        tspVisited[i]=true; tsp(i,count+1,cur+tspCost[city][i]); tspVisited[i]=false;
    }
}
void runTSP(){
    cout<<"\nEnter number of cities: ";cin>>tspN;
    cout<<"Enter cost matrix:\n"; for(int i=0;i<tspN;i++)for(int j=0;j<tspN;j++)cin>>tspCost[i][j];
    fill(tspVisited,tspVisited+10,false); tspVisited[0]=true; bestTSP=INF; tsp(0,1,0);
    if(bestTSP==INF) cout<<"No complete tour exists.\n"; else cout<<"Minimum Travelling Cost = "<<bestTSP<<"\n";
}

/* 10. N-QUEENS */
int qx[20], qcount;
bool placeQueen(int k,int col){
    for(int j=1;j<k;j++) if(qx[j]==col || abs(qx[j]-col)==abs(j-k)) return false;
    return true;
}
void nQueens(int k,int n){
    for(int col=1;col<=n;col++) if(placeQueen(k,col)){
        qx[k]=col;
        if(k==n){
            qcount++; cout<<"\nSolution "<<qcount<<":\n";
            for(int i=1;i<=n;i++){for(int j=1;j<=n;j++)cout<<(qx[i]==j?"Q ":". ");cout<<"\n";}
        } else nQueens(k+1,n);
    }
}
void runNQueens(){
    int n; cout<<"\nEnter number of Queens: ";cin>>n; qcount=0; nQueens(1,n);
    if(qcount==0) cout<<"\nNo solution exists.\n";
}

int main(){
    int choice;
    do{
        cout<<"\n========== AOA ALGORITHM TOOLKIT ==========\n";
        cout<<"1. Quick Sort\n2. Merge Sort\n3. Topological Ordering\n";
        cout<<"4. Transitive Closure (Warshall)\n5. 0/1 Knapsack\n6. Dijkstra\n";
        cout<<"7. Floyd\n8. Prim\n9. Kruskal\n10. Travelling Salesman Problem\n";
        cout<<"11. N-Queens\n12. Exit\nEnter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:runQuickSort();break; case 2:runMergeSort();break;
            case 3:runTopologicalSort();break; case 4:runWarshall();break;
            case 5:runKnapsack();break; case 6:runDijkstra();break;
            case 7:runFloyd();break; case 8:runPrim();break;
            case 9:runKruskal();break; case 10:runTSP();break;
            case 11:runNQueens();break; case 12:cout<<"Exiting...\n";break;
            default:cout<<"Invalid choice.\n";
        }
    }while(choice!=12);
    return 0;
}

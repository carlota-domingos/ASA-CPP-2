#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

class GraphMatrix {
public:
    int nodes;
    std::vector<std::vector<int>> graph;
    GraphMatrix(int mnodes) : nodes(mnodes), graph(nodes + 1, std::vector<int>(nodes + 1, 0)) {}


    void addEdge(int i, int f){
        if(graph[i][f]==0)
            graph[i][f]=1; 
    }

    void itdfs(int node, std::vector<int>& color, std::list<int>& order) {
        std::stack<int> queue;
        queue.push(node);

        while(!queue.empty()){
            int current = queue.top();
            queue.pop();

            if(color[current]==1){
                visited[current] = true;
                order.push_front(current);
               
                for (int neighbour = 1; neighbour <= nodes; ++neighbour) {
                    
                    if (graph[current][neighbour]!=0 && !visited[neighbour]) {
                        queue.push(neighbour);
    
                    }
                }
            }
        }
    }

    void dfs(std::list<int>& order){
        std::vector<bool> visited(nodes+1,false);
        for(int i=1;i<=nodes;i++){
            if(!visited[i]){
                itdfs(i,visited,order);
            }
        }
        for(int i:order){
            printf("%d ",i);
        }
        
    }

    void transpose() {
        std::vector<int> nodeline (nodes+1,0);
        std::vector<std::vector<int>> transposed(nodes+1,nodeline);
        for (int i = 1; i <= nodes; i++) {
            for (int j = 1; j <= nodes; j++) {
                transposed[i][j] = graph[j][i];
            }
        }
        graph = transposed;
    }



    GraphMatrix getSCCGraph(){
        std::vector<std::list<int>> components;
        int ncomponents=0;

        std::vector<bool> visited(nodes+1,false);
        std::list<int> order;

        dfs(order);
        for(int i :order){
            printf("%d",i);
        }
        transpose();

        while(!order.empty()){
            int node = *order.begin();
            order.pop_front();

            if(!visited[node]){
                std::list<int> currSCC;
                ncomponents++;
                itdfs(node,visited,currSCC);
                components.push_back(currSCC);
            }
        }

        GraphMatrix SCCgraph(ncomponents);
        
        for(int i=0; i< ncomponents; i++){
            std::list<int> curSCC= components[i];
            for(std::list<int>::iterator it= curSCC.begin();it!=curSCC.end();it++){
                for(int child: graph[*it]){
                    for (int j = 0; j < ncomponents; ++j) {
                        std::list<int> visitingSCC = components[j];
                        if (std::find(visitingSCC.begin(), visitingSCC.end(), child) != visitingSCC.end()) { 
                            SCCgraph.addEdge(j,i); 
                            break;
                        
                        }
                    }
                }
                
            }
        }
        return SCCgraph;
    }
};

int main(){
    int numusers,nrelations;
    int user1, user2;
    scanf("%d %d", &numusers, &nrelations);
    GraphMatrix tugaNet(numusers);
    while(nrelations!=0){
        scanf("%d %d", &user1, &user2);
        tugaNet.addEdge(user1,user2);
        nrelations--;
    }
   
    
    tugaNet=tugaNet.getSCCGraph();
    for (int i = 1; i <= tugaNet.nodes; i++) {
            for (int j = 1; j <= tugaNet.nodes; j++) {
                printf("%d ", tugaNet.graph[i][j]);
            }
            printf("\n");
        }
    return 0;
    
}

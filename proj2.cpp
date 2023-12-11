#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

class GraphMatrix {
public:
    int nodes;
    std::vector<std::vector<int>> graph;
    void Graph(int mnodes){
        nodes=mnodes;
        graph.resize(nodes+1);
        for(int i=0;i<=nodes;i++)
            graph[i].resize(nodes+1);
    }

    void addEdge(int i, int f){
        if(graph[i][f]==0)
            graph[i][f]=1; 
    }

    void itdfs(int node, std::vector<bool> visited, std::vector<int> order) {
        std::stack<int> queue;
        visited[node] = true;

        queue.push(node);
        while(!queue.empty()){
            int current = queue.top();
            queue.pop();

            if(!visited[current]){
                visited[current] = true;
                order.insert(order.begin(),current);
                for (int neighbour = 1; neighbour <= nodes; ++neighbour) {
                    if (graph[current][neighbour] && !visited[neighbour]) {
                        queue.push(neighbour);
                    }
                }
            }
        }
    }

    void dfs(std::vector<int> order){
        std::vector<bool> visited(nodes+1,false);
        for(int i=1;i<=nodes;i++){
            if(!visited[i]){
                itdfs(i,visited,order);
            }
        }
    }

    void transpose() {
        std::vector<int> nodeline (nodes+1);
        std::vector<std::vector<int>> transposed(nodes+1,nodeline);
        for (int i = 1; i <= nodes; i++) {
            for (int j = i+1; j <= nodes; j++) {
                transposed[i][j] = graph[j][i];
                transposed[j][i] = graph[i][j];
            }
        }
        graph = transposed;
    }



    GraphMatrix getSCCGraph(){
        std::vector<std::vector<int>> components;
        int ncomponents=0;
        std::vector<bool> visited;
        std::vector<int> order;
        dfs(order);
        transpose();
        while(!order.empty()){
            
            int node = *order.begin();
            order.erase(order.begin());

            if(!visited[node]){
                std::vector<int> currSCC;
                std::vector<int> comp;
                ncomponents++;
                itdfs(node,visited,currSCC);
                components.push_back(currSCC);
            }
        }

        GraphMatrix SCCgraph;
        SCCgraph.Graph(ncomponents+1);
        for(int i=0; i< ncomponents; i++){
            while(!components[i].empty()){
                int current = *components[i].begin();
                components[i].erase(components[i].begin());
                for(int child: graph[current]){
                    for (int j = 0; j < ncomponents; ++j) {
                        std::vector<int> visitingSCC = components[j];
                        while(!visitingSCC.empty()){
                            if (std::find(visitingSCC.begin(), visitingSCC.end(), child) != visitingSCC.end()) { 
                                SCCgraph.addEdge(j,i); 
                                break;
                            }
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
    GraphMatrix tugaNet;
    tugaNet.Graph(numusers);
    while(nrelations!=0){
        scanf("%d %d", &user1, &user2);
        tugaNet.addEdge(user1,user2);
        nrelations--;
    }
    tugaNet=tugaNet.getSCCGraph();
    return 0;
}

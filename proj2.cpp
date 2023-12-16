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

    void itdfs(int node, std::vector<int>& colour, std::list<int>& order) {
        std::stack<int> queue;

        queue.push(node);

        while(!queue.empty()){
            int current = queue.top();

            if(colour[current]==0){
                colour[current] = 1;
            
                for (int neighbour = nodes; neighbour >= 1; neighbour--) {
                    if (graph[current][neighbour]==1 && colour[neighbour]!=2) {
                        queue.push(neighbour);
                        break;
                    }
                }
            } else if(colour[current]==1) {
                colour[current]=2;
                order.push_front(current);
                queue.pop();
            } else {
                queue.pop();
            }
        }
    }

    void dfs(std::list<int>& order){
        std::vector<int> colour(nodes+1,0);
        for(int i=1;i<=nodes;i++){
            if(colour[i]==0){
                itdfs(i,colour,order);
            }
        }
        for(int i:order){
            printf("%d ",i);
        }
        
    }




    int getMaxJumps(){
        std::vector<int> colour(nodes+1,false);
        std::list<int> order;

        dfs(order);

        
        return 0;
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
    for (int i = 1; i <= tugaNet.nodes; i++) {
        for (int j = 1; j <= tugaNet.nodes; j++) {
            printf("%d ", tugaNet.graph[i][j]);
        }
        printf("\n");
    }
    std::list<int> order;
    tugaNet.dfs(order);
    return 0;
    
}

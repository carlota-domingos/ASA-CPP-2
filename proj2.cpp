#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <algorithm>

class GraphList {
public:
    int nodes;
    std::vector<std::list<int>> graph;
    std::vector<std::list<int>> transposedGraph;
    GraphList(int mnodes) : nodes(mnodes), graph(nodes + 1), transposedGraph(nodes+1) {}


    void addEdge(int i, int f){
        graph[i].push_front(f);
        transposedGraph[f].push_front(i);
    }

    void itdfs(int node, std::vector<int>& colour, std::list<int>& order) {
        std::stack<int> queue;

        queue.push(node);

        while(!queue.empty()){
            int current = queue.top();

            if(colour[current]==0){
                colour[current] = 1;
                for (std::list<int>::iterator neighbour=graph[current].begin();neighbour!=graph[current].end();neighbour++) {
                    if (colour[*neighbour]!=2) {
                        queue.push(*neighbour);
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
        std::vector<int> parent(nodes+1,0);
        std::vector<int> max_jump_node(nodes+1,0);
        std::list<int> order;
        int max_jump=0;
        dfs(order);
        
        return max_jump;
    }
};

int main(){
    int numusers,nrelations;
    int user1, user2;
    scanf("%d %d", &numusers, &nrelations);
    GraphList tugaNet(numusers);
    while(nrelations!=0){
        scanf("%d %d", &user1, &user2);
        tugaNet.addEdge(user1,user2);
        nrelations--;
    }

    printf("%d\n", tugaNet.getMaxJumps());
    return 0;
    
}

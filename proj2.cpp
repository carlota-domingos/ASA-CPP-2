#include <cstdio>
#include <vector>
#include <list>
#include <stack>

class GraphList {
public:
    int nodes;
    std::vector<std::vector<int>> graph;
    std::vector<std::vector<int>> transposedGraph;
    std::vector<int> colour;
    std::vector<int> parents;
    std::vector<int> max_jump_node;
    GraphList(int mnodes) : nodes(mnodes), graph(nodes + 1), transposedGraph(nodes+1) ,
                           colour(nodes + 1, 0), parents(nodes + 1, 0), max_jump_node(nodes+1,0) {}
    

    //adiciona a adjacencia noo grafo normal e no transposto
    void addEdge(int i, int f){
        graph[i].push_back(f);
        transposedGraph[f].push_back(i);
    }

    void dfs(std::stack<int>& order,std::stack<int>& queue){
        for(int node=1 ; node<=nodes ; node++){
            if(colour[node]==0){ //se nó n for visitado 
                                //fzr dfs iterativa
                queue.push(node);
                int current;
                while(!queue.empty()){
                    current = queue.top();

                    if(colour[current]==0){//if not visited
                        colour[current] = 1; //marks node as visited
                        for (int neighbour: graph[current]) { //visitar vizinho
                            if (colour[neighbour]==0) {
                                queue.push(neighbour);//
                            }
                        }
                    } else if(colour[current]==1) {
                        colour[current]=2; //marks node as closed
                        order.push(current);
                        queue.pop();
                    } else {
                        queue.pop();
                    }
                }
            }
        }        
    }

    int second_dfs(std::stack<int>& order,std::stack<int>& queue){
        int parent;
        int value;
        int max_jump=0;
        int node;
        while(!order.empty()){
            node=order.top();
            order.pop();
            if(parents[node]==0){//ainda nao visistado
                queue.push(node);
                parent= node;
                value =0;
              
                while(!queue.empty()){//while da scc
                    node = queue.top();
                    queue.pop();
                    parents[node]=parent;
                    for (int neighbour: transposedGraph[node]) {
                        if(parents[neighbour]!=parent){
                            if(parents[neighbour]!=0){
                                if (max_jump_node[parents[neighbour]]>=value)
                                    value = max_jump_node[parents[neighbour]]+1;
                            } else {
                                queue.push(neighbour);
                            }
                        }
                    }
                }
                max_jump_node[parent]=value;
                if(max_jump_node[parent]>max_jump)
                    max_jump= max_jump_node[parent];
            }
        }
        return max_jump;
    }

    int getMaxJumps(){
        std::stack<int> order;
        std::stack<int> queue;
        dfs(order,queue);
        return second_dfs(order,queue);
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

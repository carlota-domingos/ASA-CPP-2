#include <iostream>
#include <vector>
#include <list>
#include <stack>

class GraphList {
public:
    int nodes;
    std::vector<std::list<int>> graph;
    std::vector<std::list<int>> transposedGraph;
    GraphList(int mnodes) : nodes(mnodes), graph(nodes + 1), transposedGraph(nodes+1) {}

    //adiciona a adjacencia noo grafo normal e no transposto
    void addEdge(int i, int f){
        graph[i].push_front(f);
        transposedGraph[f].push_front(i);
    }

    void dfsVisit(int node, std::vector<int>& colour, std::list<int>& order) {
        std::stack<int> queue;
        std::list<int>::iterator neighbour;
        queue.push(node);
        int current;
        while(!queue.empty()){
            current = queue.top();

            if(colour[current]==0){
                colour[current] = 1;
                for (neighbour=graph[current].begin();neighbour!=graph[current].end();neighbour++) {
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
                dfsVisit(i,colour,order);
            }
        }        
    }

    int second_dfs(int node, std::vector<int>& parents, std::vector<int>& max_jump_node){
        std::stack<int> queue;
        queue.push(node);
        int parent= node;
        int value =0;
        std::list<int>::iterator neighbour;
        while(!queue.empty()){
            node = queue.top();
            queue.pop();
            parents[node]=parent;
            for (neighbour=transposedGraph[node].begin();neighbour!=transposedGraph[node].end();neighbour++) {
                if(parents[*neighbour]!=parent){
                    if(parents[*neighbour]!=0){
                        if (max_jump_node[parents[*neighbour]]>=value)
                            value = max_jump_node[parents[*neighbour]]+1;
                    } else {
                        queue.push(*neighbour);
                    }
                }
                
            }
        }
        max_jump_node[parent]=value;
        return value;
    }

    int getMaxJumps(){
        std::vector<int> parents(nodes+1,0);
        std::vector<int> max_jump_node(nodes+1,0);
        std::list<int> order;
        int max_jump=0;
        int node,i;
        int max_current_SCC;
        dfs(order);
        while((node= *order.begin())!=0){
            order.pop_front();
            if(parents[node]!=0){
                continue;
            }else if((max_current_SCC=second_dfs(node,parents,max_jump_node))>max_jump){
                max_jump= max_current_SCC;
            }
        }
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

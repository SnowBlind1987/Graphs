#include <iostream>
#include <vector>

using std::vector;
using std::pair;

struct vertex{
    vertex (): id(-1),isVisited(false),con(-1){}
    int id;
    bool isVisited;
    int con; 
};
class graph{
    private:
        vector<vector<vertex> > adj;
        int n_vert;
    public:
        void readGraph(){
            size_t n,m;
            std::cin>>n>>m;
            adj.resize(n,vector<vertex>());
            for (int i=0;i<m;i++){
                int x,y;
                std::cin>>x>>y;
                adj[x-1].push_back(vertex());
                adj[x-1].back().id=y;
                adj[y-1].push_back(vertex());
                adj[y-1].back().id=x;
            }
        }
};
int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  return 0;
}

int main() {
    graph test;
    test.readGraph();
  /*size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);*/
}

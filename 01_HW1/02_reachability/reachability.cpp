#include <iostream>
#include <vector>
#include <map>
using std::vector;
using std::pair;
using std::map;

struct vertex{
    vertex (): id(-1),isVisited(false),con(-1),nAdj(0){}
    int id;
    bool isVisited;
    int con;
    int nAdj;
	vector<vertex*> adj;
};
class graph{
    private:
        typedef map<int,vertex*> vmap;
		vmap vertices;
        int n_vert;
		int n_edges;
        
    public:
		void readGraph(){
			vmap::iterator it;
			vertex* tmp1;
			vertex* tmp2;
			std::cin>>this->n_vert>>this->n_edges;
			for (int i=0;i<n_edges;i++){
				int x,y;
				std::cin>>x>>y;
				it=vertices.find(x);
				if (it==vertices.end()){
					tmp1=new vertex;
					vertices[x]=tmp1;
					tmp1->id=x;
					it=vertices.find(y);
					if (it==vertices.end()){
						tmp2=new vertex;
						tmp2->id=y;
						vertices[y]=tmp2;;
						tmp1->adj.push_back(tmp2);
							
					}else{
						tmp1->adj.push_back(it->second);
					}
					
				}else{
					tmp1=it->second;
					it=vertices.find(y);
					if (it==vertices.end()){
						tmp2=new vertex;
						tmp2->id=y;
						vertices[y]=tmp2;
						tmp1->adj.push_back(tmp2);
					}else{
						tmp2=it->second;
						tmp1->adj.push_back(tmp2);
					}
				}
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

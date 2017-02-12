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
		void readUndirectedGraph(){
			vmap::iterator it1;
            vmap::iterator it2;
			vertex* tmp1;
			vertex* tmp2;
			std::cin>>this->n_vert>>this->n_edges;

            for (int i=0;i<n_vert;i++){
                tmp1=new vertex;
                tmp1->id=i+1;
                vertices[i+1]=tmp1;
            }
			for (int i=0;i<n_edges;i++){
				int x,y;
				std::cin>>x>>y;
                it1=vertices.find(x);
                it2=vertices.find(y);

                it1->second->adj.push_back(it2->second);
                it1->second->nAdj++;
                it2->second->adj.push_back(it1->second);
                it2->second->nAdj++;
			}
        }

    void showAll(){
        vmap::iterator it=vertices.begin();
        for (it;it!=vertices.end();it++){
            std::cout<<it->first<<" "<<it->second->con<<std::endl;
        }
    }

    void explore(vertex* vtx,int conVal){
        vtx->isVisited=true;
        vtx->con=conVal;
        for (int i=0;i<vtx->nAdj;i++){
            if (not vtx->adj[i]->isVisited){
                explore(vtx->adj[i],conVal);
            }
        }
    }

    void DFS(){
        //run explore on all vertices and assign connectivity values
        vmap::iterator it=vertices.begin();
        int cc=1;
        for (it;it!=vertices.end();it++){
            if (not it->second->isVisited){
                explore(it->second,cc);
                cc++;
            }
        }
    }
    
    bool checkCon(int a, int b){
        vmap::iterator it1=vertices.find(a);
        vmap::iterator it2=vertices.find(b);

        return (it1->second->con==it2->second->con);
    }

};
int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  return 0;
}

int main() {
    graph test;
    test.readUndirectedGraph();
    test.DFS();
    int a,b;
    std::cin>>a>>b;
    std::cout<<test.checkCon(a,b)<<std::endl;

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

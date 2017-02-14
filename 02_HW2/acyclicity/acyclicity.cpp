#include <iostream>
#include <vector>
#include <map>
using std::vector;
using std::pair;
using std::map;
using std::endl;
struct vertex{
    vertex (): id(-1),isVisited(false),isSink(false),isSource(false),
	con(-1),nAdj(0){}
    int id;
    bool isVisited;
	bool isSink;
	bool isSource;
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
        int n_connected_comp; 

		void explore(vertex* vtx,int conVal){
        	vtx->isVisited=true;
        	vtx->con=conVal;
			if (vtx->nAdj==0) {vtx->isSink=true;}

        	for (int i=0;i<vtx->nAdj;i++){
        	    if (not vtx->adj[i]->isVisited){
        	        explore(vtx->adj[i],conVal);
        	    }
        	}
   		}

		bool isCyclic(vertex* vtx){
			vtx->isVisited=true;
			bool result;
			if (vtx->nAjd==0) {result=false;}
			for (int i=0;i<vtx->nAdj;i++){
				if(vtx->isVisited){
					result=true;
				}else{
					result=vtx->nAdj[i]
				}
			}
			return false;
		}

		void resetAll(){
			vmap::iterator it=vertices.begin();
			for(it;it!=vertices.end();it++){
				it->second->isVisited=false;
				it->second->con=-1;
			}
		}

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
		void readDirectedGraph(){
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
			}
        }

    void showAll(){
        vmap::iterator it=vertices.begin();
        for (it;it!=vertices.end();it++){
            std::cout<<it->first<<" "<<it->second->con<<endl;
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
        this->n_connected_comp=cc-1;
    }
   	 
    bool checkCon(int a, int b){
        vmap::iterator it1=vertices.find(a);
        vmap::iterator it2=vertices.find(b);

        return (it1->second->con==it2->second->con);
    }
    int getNComponents(){return this->n_connected_comp;};
};
int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  return 0;
}

int main() {
    graph DAG;
    DAG.readDirectedGraph();
}

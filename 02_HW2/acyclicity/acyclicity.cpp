#include <iostream>
#include <vector>
#include <map>
using std::vector;
using std::pair;
using std::map;
using std::cout;
using std::endl;
struct vertex{
    vertex (): id(-1),isVisited(false),isSink(false),isSource(false),
	con(-1),nAdj(0), nRev(0){}
    int id;
    bool isVisited;
	bool isSink;
	bool isSource;
    int con;
	int pre;
	int post;
    int nAdj;
	int nRev;
	vector<int> adj;
	vector<int> reverse;//only needed for directed graphs
};
class graph{
    private:
        typedef map<int,vertex*> vmap;
		vmap vertices;
		int clock;
        int n_vert;
		int n_edges;
        int n_connected_comp; 
		bool isDirected;


		void explore(vertex* vtx,int conVal){
			this->clock++;
			vtx->pre=this->clock;	
        	vtx->isVisited=true;
        	vtx->con=conVal;
			if (vtx->nAdj==0) {vtx->isSink=true;}
        	for (int i=0;i<vtx->nAdj;i++){
				auto adj_it=this->vertices.find(vtx->adj[i]);
        	    if (not adj_it->second->isVisited){
        	        explore(adj_it->second,conVal);
        	    }
        	}
			this->clock++;
			vtx->post=clock;
   		}
		/*void linearOrder(vertex* vtx){
            vmap::iterator=it;
			if(vtx->nAdj==0) {
				for (int i=0;i<vtx->reverse.size();i++){
					int id=vtx->reverse[i]->id;
                    it=vertices.find(id);
                    vertex* tmp=it->second;
                    
				}
			}	
		}*/
		

    public:

		graph(){
			this->clock=0;
			this->n_vert=0;
			this->n_edges=0;
			this->n_connected_comp=0;	
		}
		//copy constructor
		graph(const graph& copy){
			this->clock=copy.clock;
			this->n_vert=copy.n_vert;
			this->n_edges=copy.n_edges;
			this->n_connected_comp=copy.n_connected_comp;
			this->isDirected=copy.isDirected;
			auto it=copy.vertices.begin();
			int node_id;
			for (it;it!=copy.vertices.end();it++){
				node_id=it->first;
            	vertex* vtx=new vertex;
				vtx->id=node_id;
				vtx->isVisited=it->second->isVisited;
				vtx->isSink=it->second->isSink;
				vtx->isSource=it->second->isSource;
    			vtx->con=it->second->con;
				vtx->pre=it->second->pre;
				vtx->post=it->second->post;
				vtx->nAdj=it->second->nAdj;
				vtx->adj.resize(vtx->nAdj);
				vtx->adj=it->second->adj;
				vtx->nRev=it->second->nRev;
				vtx->reverse.resize(vtx->nRev);
				vtx->reverse=it->second->reverse;
				this->vertices[node_id]=vtx;
				vtx=NULL;
        	}

		}

		~graph(){
			vmap::iterator it=this->vertices.begin();
			for(it;it!=this->vertices.end();it++){
				delete it->second;
				it->second=NULL;
			}
		}
		void resetAll(){
			vmap::iterator it=this->vertices.begin();
			this->clock=0;
			for(it;it!=this->vertices.end();it++){
				it->second->isVisited=false;
				it->second->con=-1;
				it->second->pre=0;
				it->second->post=0;
			}
		}	
		void readUndirectedGraph(){
			vmap::iterator it1;
            vmap::iterator it2;
			vertex* tmp1;
			vertex* tmp2;
			this->isDirected=false;
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

                it1->second->adj.push_back(y);
                it1->second->nAdj++;
                it2->second->adj.push_back(x);
                it2->second->nAdj++;
			}
        }
		void readDirectedGraph(){
			vmap::iterator it1;
            vmap::iterator it2;
			vertex* tmp1;
			vertex* tmp2;
			this->isDirected=true;
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

                it1->second->adj.push_back(y);
                it1->second->nAdj++;
				it2->second->reverse.push_back(x);
				it2->second->nRev++;
			}
        }

    void showAll(){
        vmap::iterator it=vertices.begin();
        for (it;it!=vertices.end();it++){
            std::cout<<it->first<<" "<<it->second->pre<<" "<<it->second->post<<endl;
        }
    }

    
    void DFS(){
        //run explore on all vertices and assign connectivity values
        vmap::iterator it=vertices.begin();
		this->resetAll();
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
	//reverse the adjacency list for directed graphs only
	//doesn't make sense for undirected graphs
	void reverseGraph(){
		if (not isDirected){return;}
		vector<int> tmp;
		vmap::iterator it=this->vertices.begin();
		for (it;it!=this->vertices.end();it++){
			tmp.resize(it->second->nAdj);
			tmp=it->second->adj;
			it->second->adj.clear();
			it->second->adj.resize(it->second->nRev);
			it->second->adj=it->second->reverse;
			it->second->reverse.clear();
			it->second->reverse.resize(it->second->nAdj);
			it->second->reverse=tmp;
			tmp.clear();
			int swp=it->second->nAdj;
			it->second->nAdj=it->second->nRev;
			it->second->nRev=swp;
		}

		
	}

	void showAdj(int id){
		auto it=this->vertices.find(id);
		cout<<"Number of of adjacents: "<<it->second->nAdj<<endl;
		for (int i=0;i<it->second->nAdj;i++){
			cout<<it->second->adj[i]<<" ";
		}
		cout<<endl;
	}	
};

int main() {
    graph DAG;
    DAG.readDirectedGraph();
	DAG.DFS();
	DAG.showAll();
	graph cDAG= graph(DAG);
	cDAG.reverseGraph();
	cDAG.DFS();
	cDAG.showAll();
}

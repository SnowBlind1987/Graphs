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
	con(-1),nAdj(0), nRev(0),isInComp(false){}
    int id;
    bool isVisited;
	bool isSink;
	bool isSource;
	bool isInComp;
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
		vmap post_order;
		map<int,int> connected_comp;
		int clock;
        int n_vert;
		int n_edges;
        int n_connected_comp; 
		bool isDirected;
		int nccs; //number of connected components

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
		void exploreReverse(vertex* vtx){
            vtx->isVisited=true;
			this->clock++;
			vtx->pre=this->clock;
			for (int i=0;i<vtx->nRev;i++){
				auto rev_it=this->vertices.find(vtx->reverse[i]);
				if (not rev_it->second->isVisited){
					exploreReverse(rev_it->second);
				}
			}
			this->clock++;
			vtx->post=this->clock;
		}
		
		void exploreSort(vertex* vtx, int con_number){
			vtx->isVisited=true;
			vtx->isInComp=true;
			connected_comp[vtx->id]=con_number;
			for (int i=0;i<vtx->nAdj;i++){
				auto adj_it=this->vertices.find(vtx->adj[i]);
				if (not adj_it->second->isVisited){
					exploreSort(adj_it->second,con_number);
				}	
			}
			
		}

		void setPostOrder(){
			vmap::iterator it=vertices.begin();
			for (it;it!=vertices.end();it++){
				int tmp_post=it->second->post;
				this->post_order[tmp_post]=it->second;
			}

		}

		void resetVisited(){
			vmap::iterator it=vertices.begin();
			for(it;it!=vertices.end();it++){
				it->second->isVisited=false;
			}
		}
    public:

		graph(){
			this->clock=0;
			this->n_vert=0;
			this->n_edges=0;
			this->n_connected_comp=0;	
			this->nccs=0;
		}
		//copy constructor
		graph(const graph& copy){
			this->clock=copy.clock;
			this->n_vert=copy.n_vert;
			this->n_edges=copy.n_edges;
			this->n_connected_comp=copy.n_connected_comp;
			this->isDirected=copy.isDirected;
			auto it=copy.vertices.begin();
			this->nccs=copy.nccs;

			for (it;it!=copy.vertices.end();it++){
				int node_id=it->first;
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
	void dfsReverse(){
		vmap::iterator it=vertices.begin();
		this->resetAll();
        for (it;it!=vertices.end();it++){
            if (not it->second->isVisited){
                exploreReverse(it->second);
            }
        }
		this->setPostOrder();
	}
   	
	void calcConnectedComponents(){
		this->dfsReverse();
		vmap::reverse_iterator it=post_order.rbegin();
		this->resetVisited();
        int comp_n=1;
		for (it;it!=post_order.rend();it++){
            if (not it->second->isInComp){
			    exploreSort(it->second,comp_n);
                comp_n++;
            }
		}
        this->nccs=comp_n-1;
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

    bool hasCycle(){
        if (this->n_vert==this->nccs){
            return false;
        }else{
            return true;
        }
    }

    int getNComp(){
        return this->nccs;
    }
};


int main() {
    graph DAG;
    DAG.readDirectedGraph();
    //DAG.dfsReverse();
    DAG.calcConnectedComponents();
    cout<<DAG.getNComp()<<endl;
}

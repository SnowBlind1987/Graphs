#include <iostream>
#include <vector>
#include <map>
#include <queue> 
using std::vector;
using std::pair;
using std::map;
using std::cout;
using std::endl;
using std::queue;
struct vertex{
    vertex (): id(-1),isVisited(false),isSink(false),isSource(false),
	con(-1),nAdj(0), nRev(0),isInComp(false),prev(NULL),dist(0),color(-1){}
    int id;
    bool isVisited;//bool for visited
	bool isSink;//bool for sink
	bool isSource;//bool for source
	bool isInComp;//bool to flag if vertex is in comp
    int con;//connected component number
	int pre;//pre number for DFS
	int post;//post number for DFS
    int nAdj;//number of adjacent nodes
	int nRev;//number or nodes in reverse, only used for directed graphs
	int dist;//distance from node
	int color;
	vertex* prev;//pointer for a previous vertex for BFS
	vector<int> adj;//vector for all adjacent vertices
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
		int inf;
		bool isBipartite;

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
			this->isBipartite=true;
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
			this->inf=n_vert+1;
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
			this->inf=this->n_vert+1;
        }

    void showAll(){
        vmap::iterator it=vertices.begin();
        for (it;it!=vertices.end();it++){
            std::cout<<it->first<<" "<<it->second->color<<std::endl;
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
        this->setPostOrder();
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

   	void BFS(vertex* S){
		queue<vertex* > vQ;
		vmap::iterator it=vertices.begin();
		for (it;it!=vertices.end();it++){
			it->second->dist=this->inf;
			it->second->prev=NULL;
		}	
		S->color=0;
		S->dist=0;
		S->prev=NULL;
		S->isVisited=true;
		vQ.push(S);
		int counter=0;

		while( not vQ.empty()){
			vertex* cur=vQ.front();
			vQ.pop();
			counter++;
			for (int i=0;i<cur->nAdj;i++){
				
				int adjId=cur->adj[i];
				auto adj_it=vertices.find(adjId);
				adj_it->second->isVisited=true;
				if (adj_it->second->isVisited and cur->color==adj_it->second->color){
					this->isBipartite=false;;
				}
				if (adj_it->second->dist==this->inf){
					adj_it->second->color=counter%2;//either odd or even
					vQ.push(adj_it->second);
					adj_it->second->dist=cur->dist+1;
					adj_it->second->prev=cur;
				}
			}
		}
	}

	bool biparteCheck(){
		bool result;
		auto it=vertices.begin();
		for (it;it!=vertices.end();it++){
			if (not it->second->isVisited){
				this->BFS(it->second);
			}
		}
		
		return this->isBipartite;
	}

	int getDist(int source, int dest){
		vmap::iterator it=vertices.find(source);
		this->BFS(it->second);
		it=vertices.find(dest);
		if (it->second->dist!=this->inf){
			return it->second->dist;
		}else{
			return -1;
		}
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

    void showPostInReverse(){
        vmap::reverse_iterator it=post_order.rbegin();
        for(it;it!=post_order.rend();it++){
            cout<<it->second->id<<" ";
        }
        cout<<endl;
    }
};


int main() {
    graph myGraph;
    myGraph.readUndirectedGraph();
	std::cout<<myGraph.biparteCheck()<<std::endl;
//	myGraph.showAll();

}

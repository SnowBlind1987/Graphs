#include <iostream>
#include <vector>
#include <map>
#include <queue> 
#include <algorithm>
#include <unordered_map>
using std::vector;
using std::pair;
using std::map;
using std::cout;
using std::endl;
using std::queue;
using std::unordered_map;
using std::swap;
struct vertex{
    vertex (): id(-1),isVisited(false),isSink(false),isSource(false),
	con(-1),nAdj(0), nRev(0),isInComp(false),prev(NULL),dist(0){}
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
	vertex* prev;//pointer for a previous vertex for BFS
	vector<int> adj;//vector for all adjacent vertices
	vector<int> weight;//if a weighted graph need weights for each adj
	vector<int> reverse;//only needed for directed graphs
};

class PriorityQueue{
	private:
	int size;
    int max_size;
	vector<vertex* > Hvect;
	unordered_map<vertex*,int> vert2ind;//map of vertices to their location in H

	int Paren(int i){
		int div=(i-1)/2;
		if (i==0) {
			return -1;
		}else{
			return div;
		}
	}
	int LC(int i){
		return 2*i+1;
	}
	int RC(int i){
		return 2*i+2;
	}

	void siftUp(int i){
		if (this->size==0)return;
		auto it=vert2ind.begin();
		while (i>0 and Hvect[Paren(i)]->dist > Hvect[i]->dist) {
			if ( Hvect[Paren(i)]->dist > Hvect[i]->dist){
				it=vert2ind.find(Hvect[i]);
				it->second=Paren(i);
				it=vert2ind.find(Hvect[Paren(i)]);
				it->second=i;
				swap(Hvect[Paren(i)],Hvect[i]);
				i=Paren(i);
			}
		}
	}
	void siftDown(int i){
		int minInd=i;
		int l=LC(i);
		//*****Left Child*****************
		if(l<this->size and Hvect[l]->dist<Hvect[minInd]->dist){
			minInd=l;
		}
		//******Right Child*****************
		int r=RC(i);
		if(r<this->size and Hvect[r]->dist<Hvect[minInd]->dist){
			minInd=r;
		}
		
		//******End Right Child*************
		auto it=vert2ind.begin();
		if (i!=minInd){
			it=vert2ind.find(Hvect[i]);
			it->second=minInd;
			it=vert2ind.find(Hvect[minInd]);
			it->second=i;

			swap(Hvect[i],Hvect[minInd]);
			siftDown(minInd);
		}
	}
	public:
    PriorityQueue(){this->size=0;}
    PriorityQueue(int max){
        this->max_size=max;
		this->size=0;
        this->Hvect.resize(max);
		for (int i=0;i<max;i++){
			Hvect[i]=NULL;
		}
    }
	void setMaxSize(int n){
		this->max_size=n;
		this->size=0;
		Hvect.resize(n);
	}
	int getSize(){
		return this->size;
	}

    void insert(vertex* vtx){
        if (this->size==this->max_size){
            return;
        }else{
            this->Hvect[size]=vtx;
			vert2ind[vtx]=size;	
            this->siftUp(size);
            this->size++;
        }

    }

    vertex* extractMin(){
		auto it=vert2ind.begin();
		vertex* max=Hvect[0];
		it=vert2ind.find(Hvect[size-1]);
		it->second=0;
        swap(Hvect[0],Hvect[size-1]);
		it=vert2ind.find(max);
		it->second=size-1;
		
        this-size--;
        this->siftDown(0);
        return max;
    }

	vertex* getMin(){
		return Hvect[0];
	}
    
    
    void changePriority(int prior,vertex* vtx){
		auto it=vert2ind.find(vtx);
		int i=it->second;
        int old_prior=Hvect[i]->dist;
		//if (old_prior==prior) return;
        Hvect[i]->dist=prior;
        if (prior>old_prior){
            this->siftDown(i);
        }else{
            this->siftUp(i);
        }
    }
	void showAll(){
		for (int i=0;i<this->size;i++){
			cout<<Hvect[i]->id<<" "<<Hvect[i]->dist<<endl;
		}
	}
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


	void Dijkstra(vertex* vtx){
		PriorityQueue dq(this->n_vert);
		vmap::iterator it=vertices.begin();
		for (it;it!=vertices.end();it++){
			it->second->dist=this->inf;
			it->second->prev=NULL;;
		}
		vtx->dist=0;
		it=vertices.begin();
		for (it;it!=vertices.end();it++){
			dq.insert(it->second);
		}
		while(dq.getSize()!=0){
			vertex* cur=dq.extractMin();
			int newDist;
			for (int i=0;i<cur->nAdj;i++){
				int adjId=cur->adj[i];
				int adjW=cur->weight[i];
				auto adj_it=vertices.find(adjId);
				if (adj_it->second->dist>cur->dist+adjW){
					newDist=cur->dist+adjW;
					adj_it->second->dist=newDist;
					adj_it->second->prev=cur;
					dq.changePriority(newDist,adj_it->second);
				}
			}
		}
	}

	void Relax(vertex* vtx){
        static bool isFirst=true;
        if (isFirst){
		    vmap::iterator it=vertices.begin();
		    for (it;it!=vertices.end();it++){
		    	it->second->dist=this->inf;
		    	it->second->prev=NULL;
		    }
		    vtx->dist=0;
        }
        isFirst=false;
		if (vtx->nAdj==0) {return;}
		int adjId=vtx->adj[0];
		bool isLarger;
	    for (int i=0;i<vtx->nAdj;i++){
	    	int adjId=vtx->adj[i];
	    	vmap::iterator adj_it=vertices.find(adjId);
	    	vertex* adjV=adj_it->second;
	    	int sub_dist=vtx->dist+vtx->weight[i];
	    	isLarger=adjV->dist > sub_dist;
	    	if (isLarger){
	    		adjV->dist=sub_dist;
                adjV->prev=vtx;
                Relax(adjV);
	    	}
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
	
	void readWeightedGraph(){
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
				int x,y,w;
				std::cin>>x>>y>>w;
                it1=vertices.find(x);
                it2=vertices.find(y);

                it1->second->adj.push_back(y);
				it1->second->weight.push_back(w);
                it1->second->nAdj++;
				it2->second->reverse.push_back(x);
				it2->second->nRev++;
			}
			this->inf=1000000;
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
		S->dist=0;
		S->prev=NULL;
		vQ.push(S);
		while( not vQ.empty()){
			vertex* cur=vQ.front();
			vQ.pop();
			for (int i=0;i<cur->nAdj;i++){
				int adjId=cur->adj[i];
				auto adj_it=vertices.find(adjId);
				if (adj_it->second->dist==this->inf){
					vQ.push(adj_it->second);
					adj_it->second->dist=cur->dist+1;
					adj_it->second->prev=cur;
				}
			}
		}
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
	int getWeightedDist(int start, int end){
		vmap::iterator it=vertices.find(start);
		this->Dijkstra(it->second);
		it=vertices.find(end);
		if (it->second->dist==this->inf){
			return -1;
		}else{
			return it->second->dist;
		}
	}

	int getWeightedDist_naive(int start, int end){
		vmap::iterator it=vertices.find(start);
		this->Relax(it->second);
		it=vertices.find(end);
		if (it->second->dist==this->inf){
			return -1;
		}else{
			return it->second->dist;
		}
	}
	
};


int main() {
    graph myGraph;
	myGraph.readWeightedGraph();
	int a,b;
	std::cin>>a>>b;
	cout<<myGraph.getWeightedDist(a,b)<<endl;
	cout<<myGraph.getWeightedDist_naive(a,b)<<endl;

}

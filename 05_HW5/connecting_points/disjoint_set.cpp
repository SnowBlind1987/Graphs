#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include<math.h>
using std::vector;
using std::pair;
using std::unordered_map;
using std::cout;
using std::endl;
using std::queue;
class tree{
	private: 
	tree* parent;
	int id;int rank;
	double x;double y;
	public:
	tree(int vid){
		this->id=vid;
		this->rank=0;
		this->parent=NULL;
	}	
	tree (int vid, double xx, double yy){
		this->id=vid;
		this->x=xx;
		this->y=yy;
		this->rank=0;
		this->parent=NULL;
	}

	tree* getPointer(){return this;}
	tree* getParent() {return this->parent;}
	int getId(){return this->id;}
	int getRank(){return this->rank;}
	void setRank(int r){this->rank=r;}
	void setParent(tree* cur){
		this->parent=cur;}
	void setX(double xx){
		this->x=xx;
	}
	void setY(double yy){
		this->y=yy;
	}

	double getX(){
		return this->x;
	}
	double getY(){
		return this->y;
	}
};
class disjointSet{
	private:
	unordered_map<int,tree*> id2p;
	int n_sets=0;	
	public:
	int getNsets(){return this->n_sets;}
	void insert(int id,double xx,double yy){
		auto it=id2p.find(id);
		if (it!=id2p.end()){
			cout<<"Error inserting a non-unique id\n";
			return;
		}
		id2p[id]=new tree(id);
		this->n_sets++;
	}
	//returns the pointer to the root tree
	tree* find(int id){
		auto it=id2p.find(id);
		tree* wrk=NULL;	
		if (it==id2p.end()){
			cout<<"Error: couldn't find the node\n";
			return wrk;
		}	
		queue<tree*> inPath;
		if (it->second->getParent()!=NULL){

			inPath.push(it->second);
			return find(it->second->getParent()->getId());
			//it->second->setParent(wrk);
		}else{
			while(not inPath.empty()){
				wrk=inPath.front();
				inPath.pop();
				wrk->setParent(it->second);
			}
			return it->second;
		}
	}

	bool join(int a,int b){
		auto it_a=id2p.find(a);
		auto it_b=id2p.find(b);
		if (it_a->first==it_b->first){
			return false;
		}else{
			int rank_a=it_a->second->getRank();
			int rank_b=it_b->second->getRank();	
			if (rank_b<rank_a){
				it_b->second->setParent(it_a->second);
			}else{
				it_a->second->setParent(it_b->second);
				if (rank_a==rank_b){
					it_b->second->setRank(rank_b+1);
				}
			}
			this->n_sets--;
			return true;
		}
	}
	
	
};


int nEdges(int m){
	int sum=0;
	for (int i=1;i<m;i++){
		sum=sum+i;
	}
	return sum;
}
int main(){
	disjointSet ds;
	size_t n;
	n=6;
	//std::cin >> n;
	int nE=nEdges(n);
	vector<double> eLength(nE);
	vector<pair<int,int>> eVerts(nE);
	vector<pair<double,double> > pos(n);
	vector<int>id(n);
	int x,y;
	/*
	for (int i=1;i<=n;i++){
		std::cin>>x>>y;
		ds.insert(i,x,y);	
		pos[i-i]=std::make_pair(x,y);
		id[i-1]=i;
	}	
	*/
	int iter=0;
	for (int i=1;i<n;i++){
		for (int j=i+1;j<=n;j++){
			/*eVerts[iter]=std::make_pair(i,j);
			eLength[iter]=sqrt((pos[i-1].first-pos[j-1].first)*(pos[i-1].first-pos[j-1].first)+
						(pos[i-1].second*pos[i-1].second-pos[j-1].second+pos[j-1].second*pos[j-1].second));
		*/
		iter++;
		}
	}
	cout<<iter<<endl;
}

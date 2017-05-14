#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include<math.h>
#include <algorithm>
#include <iomanip>

using std::vector;
using std::pair;
using std::unordered_map;
using std::cout;
using std::endl;
using std::queue;

struct sort_data{
	double eLength;
	pair<int,int> eVert;
};
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
		this->x=0.;
		this->y=0.;
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

bool compareEdges(const sort_data &a,const sort_data& b){
	return a.eLength<b.eLength;
}
int main(){
	disjointSet ds;
	size_t n;
	std::cin >> n;
	int nE=nEdges(n);
	vector<std::pair<double,double> > pos(n);
	vector<int>id(n);
	double x,y;
	vector<sort_data> sortd(nE);
	for (int i=1;i<=n;i++){
		std::cin>>x>>y;
		ds.insert(i,x,y);	
		pos[i-1]=std::make_pair(x,y);
		id[i-1]=i;
	}	
	int iter=0;
	for (int i=1;i<n;i++){
		for (int j=i+1;j<=n;j++){
			double x1=pos[i-1].first;
			double y1=pos[i-1].second;
			double x2=pos[j-1].first;
			double y2=pos[j-1].second;
			sortd[iter].eVert=std::make_pair(i,j);
			sortd[iter].eLength=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
			iter++;
		}
	}
	
	std::sort(sortd.begin(),sortd.end(),compareEdges);
	double dist=0.;
	for (int i=1;i<=nE;i++){
		int v1=sortd[i-1].eVert.first;
		int v2=sortd[i-1].eVert.second;
		if (ds.find(v1)!=ds.find(v2)){
			ds.join(v1,v2);
			dist+=sortd[i-1].eLength;
			if (ds.getNsets()==1) {
				break;
			}
		}		
		
	}
	std::cout << std::setprecision(10) << dist << std::endl;
}

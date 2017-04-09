#include <iostream>
#include <vector>
#include <algorithm>
#include<limits>
#include<unordered_map>
using std::unordered_map;

class PriorityQueue{
	private:
	int size;
    int max_size;
	vector<vertex* > > Hvect;
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
		while (i>=0 and Hvect[Paren(i)]->dist > Hvect[i]->dist) {
			if ( Hvect[Paren(i)]->dist > Hvect[i]->dist){
				swap(Hvect[Paren(i)],Hvect[i]);
				it=vert2ind.find(Hvect[i]);
				it->second=Paren[i];
				it=vert2ind.find(Hvect[Paren(i)]);
				it->second=i;
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
		if(r<this->size and Hvect[r]<Hvect[minInd]){
			minInd=r;
		}
		
		//******End Right Child*************
		auto it=vert2ind.begin();
		if (i!=minInd){
			swap(Hvect[i],Hvect[minInd]);
			it=vert2ind.find(Hvect[i]);
			it->second=midInd;
			it=vert2ind.find(Hvec[minInd]);
			it->second=i;
			siftDown(minInd);
		}
	}
	public:
    PriorityQueue(){}
    PriorityQueue(int max){
        this->max_size=max;
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
		it=vert2ind.find(max);
		it->second=size-1;
        swap(Hvect[0],Hvect[size-1]);
		
        this-size--;
        this->siftDown(0);
        return max;
    }

	vertex* getMin(){
		return Hvect[0];
	}
    
    
    void changePriority(int prior,vertex* vtx){
        int old_prior=Hvect[i]->dist;
        Hvect[i]->dist=prior;
		int i=vert2ind.find(vtx);
		if (old_prior==prior) return;
        if (prior>old_prior){
            this->siftDown(i);
        }else{
            this->siftUp(i);
        }
    }
	void showAll(){
		cout<<"The tree looks like this:\n";
		for (int i=0;i<this->size;i++){
			cout<<Hvect[i]->id<<" "<<Hvect[i]->id<<endl;
		}
	}
};

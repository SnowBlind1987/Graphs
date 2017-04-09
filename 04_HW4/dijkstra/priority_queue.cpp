#include <iostream>
#include <vector>
#include <algorithm>
#include<limits>
#include<unordered_map>
using std::unordered_map;

class PriorityQueue{
	private:
	int size;//pair<time, id>
    int max_size;
	vector<vertex* > > Hvect; //pair<dist, id>
	unordered_map<int,vertex*> ind2vert;	

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
		while (i>=0 and Hvect[Paren(i)].first>=Hvect[i].first) {
			if ( Hvect[Paren(i)].first>Hvect[i].first){
				swap(Hvect[Paren(i)],Hvect[i]);
				i=Paren(i);
			}
		}
	}
	void siftDown(int i){
		int minInd=i;
		int l=LC(i);
		//*****Left Child*****************
		if(l<this->size and Hvect[l].first<Hvect[minInd].first){
			minInd=l;
		}
		//******Right Child*****************
		int r=RC(i);
		if(r<this->size and Hvect[r]<Hvect[minInd]){
			minInd=r;
		}
		
		//******End Right Child*************
		if (i!=minInd){
			swap(Hvect[i],Hvect[minInd]);
			siftDown(minInd);
		}
	}
	public:
    PriorityQueue(){}
    PriorityQueue(int max){
        this->max_size=max;
        this->Hvect.resize(max);
		for (int i=0;i<max;i++){
			Hvect[i]=make_pair(0,-1);
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

    void insert(long priority,int id){
        if (this->size==this->max_size){
            return;
        }else{
            this->Hvect[size]=make_pair(priority,id);
            this->siftUp(size);
            this->size++;
        }

    }

    pair<long,int> extractMin(){
		pair<long,int> max=Hvect[0];
        swap(Hvect[0],Hvect[size-1]);
        this-size--;
        this->siftDown(0);
        return max;
    }

	pair<long,int> getMin(){
		return Hvect[0];
	}
    
    void remove(int i){
        Hvect[i].first=std::numeric_limits<long >::max();
        this->siftUp(i);
        pair<long,int> trash;
		trash=this->extractMin();
    }
    
    void changePriority(long prior,int i){
        long old_prior=Hvect[i].first;
        Hvect[i].first=prior;
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
			cout<<Hvect[i].first<<" "<<Hvect[i].second<<endl;
		}
	}
};

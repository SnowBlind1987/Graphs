#include <iostream>
#include <vector>

using std::vector;
using std::pair;

class adjList{
	private:
	vector<vector<int> > mat;

	public:
	adjList(int nvert){
		mat.resize(nvert,vector<int>());
	}
	read_edges(int nedges){
		for (int i=0, i<nedges, i++){
			int x,y;
			std::cin>>x>>y;
			mat[x-1].push_back(y-1);
			mat[y-1].push_back(x-1);
		}
	}
	
	vector <int> & operator()(int vert){
		//this may be wront but good idea
	}

};
int reach(vector<vector<int> > &adj, int x, int y) {
  //write your code here
  return 0;
}

int main() {
  size_t n, m;
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
  std::cout << reach(adj, x - 1, y - 1);
}

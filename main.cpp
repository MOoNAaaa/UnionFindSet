#include <iostream>
#include <vector>

using namespace std;

// 优化并查集
// father初始化为 -1 ， 绝对值代表该集合中元素的个数
class UnionFindSet{
private:
    vector<int> father;
    vector<int> rank;
public:
    UnionFindSet(unsigned int n):father(n, -1), rank(n, 0){
    }
    int findFather(int son){
        if(father[son] < 0)
            return son;
        // 优化1：路径压缩（be plant）
        father[son] = findFather(father[son]);
        return father[son];
    }
    void unionTwoSet(int a, int b){
        int fa = findFather(a);
        int fb = findFather(b);
        if(fa != fb){
            // 优化2：按秩合并
            if(rank[fa] > rank[fb]){    // fa 的秩大， fb 并入 fa
                father[fa] += father[fb];
                father[fb] = fa;
            } else{  // fb 的秩大， fa 并入 fb
                father[fb] += father[fa];
                father[fa] = fb;
                if(rank[fa] == rank[fb])
                    ++rank[fb];
            }
        }
    }
    int numOfSet(){
        int count = 0;
        for (int i = 0; i < father.size(); ++i) {
            if(father[i] < 0)
                count++;
        }
        return count;
    }

};
class Solution{
public:
    int findCircleNum(vector<vector<int>>& matrix){
        int res = 0;
        UnionFindSet unionFindSet(matrix.size());
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = i + 1; j < matrix[0].size(); ++j) {
                if(matrix[i][j] == 1){
                    unionFindSet.unionTwoSet(i, j);
                }
            }
        }
        res = unionFindSet.numOfSet();
        return res;
    }
};
int main() {
    Solution solution;
    int n;
    while (cin>>n){
        vector<vector<int>> matrix(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin>>matrix[i][j];
            }
        }
        cout<<solution.findCircleNum(matrix)<<endl;
    }
    return 0;
}
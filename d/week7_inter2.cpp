    #include <iostream>
    #include <vector>
    #include <map>
    #include <algorithm>
    using namespace std;

    int main(){
        int i, n, m, l, t;
        scanf("%d",&n);
        map<int, int> favo;
        scanf("%d",&m);
        for(i=0; i<m; i++){
            scanf("%d",&t);
            favo.insert(make_pair(t,i));
        }
        vector<int> v;
        scanf("%d",&l);
        for(i=0; i<l; i++){
            scanf("%d",&t);
            map<int,int>::iterator it = favo.find(t);
            if(it!=favo.end()){
                v.push_back(it->second);
            }
        }
        int len = v.size();
        if(len==0){
            printf("0\n");
            return 0;
        }
        vector<int> d(len,1);
        for(i=1; i<len; i++){
            for(int j=0; j<i; j++){
                if(v[i] >= v[j]){
                    d[i] = max(d[i], d[j]+1);
                }
            }
        }
        int result = 0;
        for(i=0; i<len; i++){
            result = max(d[i],result);
        }
        printf("%d\n",result);

        return 0;
    }

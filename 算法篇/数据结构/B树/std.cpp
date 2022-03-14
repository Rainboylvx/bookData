#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


vector<int> v;
int n;
void print(){

    sort(v.begin(),v.end());
    for (const auto& e : v) {
        std::cout << e << " " ;
    }
    std::cout << '\n' ;

}
int main(){
    std::cin >> n;
    for(int i=1;i<=n;++i){
        int o,x;
        std::cin >> o;
        if( o == 3 ) {
            sort(v.begin(),v.end());
            for (const auto& e : v) {
                std::cout << e << " " ;
            }
            std::cout << '\n' ;
        }
        else if (o == 1){
            std::cin >> x;
            v.push_back(x);
            print();
        }
        else {
            std::cin >> x;
            if( v.size() == 0){
                std::cout <<"The three is empty\n";
                continue;
            }

            for( auto it = v.begin(); it != v.end() ; ++it){
                if( *it == x){
                    v.erase(it);
                    break;
                }
            }
            print();
        }
    }
    return 0;
}

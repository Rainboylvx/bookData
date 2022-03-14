#include <bits/stdc++.h>
#include "Btree.hpp"
using namespace std;

void mywrite(int n,std::string & c){
    std::string name = to_string(n) + ".dot"; std::fstream fs(name,fstream::in | fstream::out | fstream::trunc);
    //fs.open(name.c_str());
    if( !fs.is_open()) {
        std::cout << "not open" << std::endl;
    }
    fs << c;
    fs.close();
}

int main(){
    {
    int n;
    BTree<int,3> t;
    std::cin >> n;
    for(int i=1;i<=n;++i){
        int o,x;
        std::cin >> o;
        //std::cout << o << " " ;
        if( o == 3 ) {
	        t.traverse();
            std::cout << '\n' ;
            //std::cout << t.to_dot() << std::endl;
        }
        else if (o == 1){
            //if( i == n-1)
            //std::cout << t.to_dot() << std::endl;
            std::cin >> x;
            //std::cout << x << '\n' ;
            t.insert(x);
	        t.traverse();
            std::cout << '\n' ;

        }
        else {
            //if( i == n-1)
            //std::cout << t.to_dot() << std::endl;
            std::cin >> x;
            //std::cout << x << '\n' ;
            t.remove(x);
	        t.traverse();
            std::cout << '\n' ;
        }
        std::string ans = t.to_dot();
        mywrite(i,ans);
    }
    }
    //std::cout << t.to_dot() << std::endl;

	//t.insert(1);
	//t.insert(3);
	//t.insert(7);
	//t.insert(10);
	//t.insert(11);
	//t.insert(13);
	//t.insert(14);
	//t.insert(15);
	//t.insert(18);
	//t.insert(16);
	//t.insert(19);
	//t.insert(24);
	//t.insert(25);
	//t.insert(26);
	//t.insert(21);
	//t.insert(4);
	//t.insert(5);
	//t.insert(20);
	//t.insert(22);
	//t.insert(2);
	//t.insert(17);
	//t.insert(12);
	//t.insert(6);

	//cout << "Traversal of tree constructed is\n";
	//t.traverse();
	//cout << endl;

    ////t.remove(11);
    ////t.remove(13);
    ////t.remove(12);
    //t.remove(24);
	//std::cout << t.to_dot() ;

	//t.remove(6);
	//cout << "Traversal of tree after removing 6\n";
	//t.traverse();
	//cout << endl;

	//t.remove(13);
	//cout << "Traversal of tree after removing 13\n";
	//t.traverse();
	//cout << endl;

	//t.remove(7);
	//cout << "Traversal of tree after removing 7\n";
	//t.traverse();
	//cout << endl;

	//t.remove(4);
	//cout << "Traversal of tree after removing 4\n";
	//t.traverse();
	//cout << endl;

	//t.remove(2);
	//cout << "Traversal of tree after removing 2\n";
	//t.traverse();
	//cout << endl;

	//t.remove(16);
	//cout << "Traversal of tree after removing 16\n";
	//t.traverse();
	//cout << endl;
    return 0;
}

#include <iostream>
#include <memory>
#include <iterator>

struct Node{
    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> child_a;
    std::shared_ptr<Node> child_b;
    int value;

    Node(const int&value): value(value){};

    ~Node(){
        std::cout << "delete" << value << std::endl;
        ~value;
    };

};

class S{
    public:
        std::shared_ptr<Node> m;
        std::shared_ptr<Node> n;

        S(const int& value){
            m = std::make_shared<Node>(value);
            n = m;
        };
        
        int& get_value() {
            std::cout << n -> value << std::endl;
            return n -> value;};
            
        
        void right(){
            n = n -> child_b;
        };

        void left() {
            n = n -> child_a;
        };

        void up(){
            n = (n -> parent);
        };
        
                void B(const int& val) {
            n -> child_b = std::make_shared<Node>(val);
            n -> child_b -> parent = std::shared_ptr<Node>(n);
        };
        
        void A(const int& val) {
            n -> child_b = std::make_shared<Node>(val);
            n -> child_a -> parent = std::shared_ptr<Node>(n);
        };

};

int main(){
    S tree(2);
    tree.A(7);
    tree.B(4);
    tree.left();
    tree.A(3);
    tree.B(16);
    tree.up();
    tree.get_value();
    tree.A(8);
    tree.get_value();
    tree.up();
    tree.up();
    tree.get_value();
};

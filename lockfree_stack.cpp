#include <iostream>
#include <atomic>
using namespace std;

template<typename T> class LockFreeStack{

    private:
    
    struct Node{
        T data;
        Node* next;

        // Default Constructor
        Node(T val) : data(val), next(nullptr){}
    };

    // To solve ABA problem - use Tagged pointer
    struct TaggedPtr{
        Node* ptr;
        uint64_t tag;
    };

    // atomic<Node*> head;   ->  Before Solving ABA Problem

    atomic<TaggedPtr> head;   // To Solve ABA Problem
    
    
    public:

    // Default Constructor
    // LockFreeStack() : head(nullptr) {}  ->  Before Solving ABA Problem

    // Default Constructor - updated to solve ABA Problem
    LockFreeStack(){
        TaggedPtr init;
        init.ptr = nullptr;
        init.tag = 0;
        head.store(init);
    }

    // Push Operation
    void push(T value){

        Node* newNode = new Node(value);

        // newNode->next = head.load(memory_order_relaxed);
        // while(!head.compare_exchange_weak(
        //     newNode->next,
        //     newNode,
        //     memory_order_release,
        //     memory_order_relaxed
        // )){
        //     // If CAS Fails:
        //     // newNode->next is updated with head automatically
        // }

        TaggedPtr oldHead = head.load(memory_order_relaxed);
        TaggedPtr newHead;

        do{
            newNode->next = oldHead.ptr;

            newHead.ptr = newNode;
            newHead.tag = oldHead.tag + 1;
        } while(!head.compare_exchange_weak(
            oldHead,
            newHead,
            memory_order_release,
            memory_order_relaxed
        ));
    }

    // Pop operation
    bool pop(T& result){

        // Node* oldHead = head.load(memory_order_relaxed);

        // while(oldHead && !head.compare_exchange_weak(
        //     oldHead,
        //     oldHead->next,
        //     memory_order_acquire,
        //     memory_order_relaxed
        // )){
        //     // retry
        // }

        // if(!oldHead) { return false; }

        // result = oldHead->data;
        // delete oldHead;
        // return true;



        // To solve ABA Problem
        TaggedPtr oldHead = head.load(memory_order_relaxed);
        TaggedPtr newHead;

        do{
            if(!oldHead.ptr){
                return false;
            }

            newHead.ptr = oldHead.ptr->next;
            newHead.tag = oldHead.tag + 1;
        } while(!head.compare_exchange_weak(
            oldHead,
            newHead,
            memory_order_acquire,
            memory_order_relaxed
        ));

        result = oldHead.ptr->data;
        delete oldHead.ptr;
        return true;
    }

    // Is empty
    bool empty() const {
        // return head.load(memory_order_acquire) == nullptr;

        return head.load(memory_order_acquire).ptr == nullptr;
    }

    // Destructor
    ~LockFreeStack(){
        // // Cleanup remaining nodes
        // Node* node = head.load();

        // while(node){
        //     Node* next = node->next;
        //     delete node;
        //     node = next;
        // }

        T temp;
        while(pop(temp));
    }
};

int main(){

    LockFreeStack<int> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Is stack empty?: " << (stack.empty()? "True" : "False") << endl;

    cout << "Popped values: ";

    int value;

    while(stack.pop(value)){
        cout << value << " "; 
    }

    cout << endl << "Is stack empty?: " << (stack.empty()? "True" : "False") << endl;

    return 0;
}


// Platform limitation occurs because Windows + MinGW ≠ good environment for lock-free 128-bit CAS.
// Run: g++ Lockfree_stack.cpp -O3 -latomic -o Lockfree_stack

// After runnig this with -latomic: 
// 1. Not truly lock-free & performance meaningless
// 2. It may emulate atomics with locks
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Node struct
struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr){}
};

// NodeData struct
struct NodeData{
    int height;
    int diameter;

    NodeData(int h, int dia) : height(h), diameter(dia){}
};

// Binary Tree class
class BinaryTree{
    int idx = -1;
    
    public: 

    // Build Binary Tree
    Node* binaryTree(vector<int> nodes){
        idx++;

        if(nodes[idx] == -1){
            return nullptr;
        }

        Node* newNode = new Node(nodes[idx]);
        newNode->left = binaryTree(nodes);
        newNode->right = binaryTree(nodes);

        return newNode;
    }

    // Print Binary Tree (Preorder traversal)
    void preorderPrint(Node* rootNode){
        if(rootNode == nullptr){
            cout << "-1 ";
            return;
        }

        cout << rootNode->data << " ";
        preorderPrint(rootNode->left);
        preorderPrint(rootNode->right);
    }

    // Print Binary Tree (Inorder Traversal)
    void inorderPrint(Node* rootNode){
        if(rootNode == nullptr){
            cout << "-1 ";
            return;
        }

        inorderPrint(rootNode->left);
        cout << rootNode->data << " ";
        inorderPrint(rootNode->right);
    }

    // Print Binary Tree (Postorder Traversal)
    void postorderPrint(Node* rootNode){
        if(rootNode == nullptr){
            cout << "-1 ";
            return;
        }

        postorderPrint(rootNode->left);
        postorderPrint(rootNode->right);
        cout << rootNode->data << " ";
    }

    // Print Binary Tree (Levelorder Traversal - BFS)
    void levelorderPrint(Node* rootNode){
        if(rootNode == nullptr){
            return;
        }

        queue<Node*> nodes;

        nodes.push(rootNode);
        nodes.push(nullptr);

        while(!nodes.empty()){
            Node* currNode = nodes.front();
            nodes.pop();

            if(currNode == nullptr){
                cout << endl;

                if(nodes.empty()){
                    break;
                }
                else{
                    nodes.push(nullptr);
                }
            }
            else{
                cout << currNode->data << " ";
                
                if(currNode->left != nullptr){
                    nodes.push(currNode->left);
                }
                if(currNode->right != nullptr){
                    nodes.push(currNode->right);
                }
            }
        }
    }

    // Count of nodes
    int countOfNodes(Node* rootNode){
        if(rootNode == nullptr){
            return 0;
        }

        int leftNodes = countOfNodes(rootNode->left);
        int rightNodes = countOfNodes(rootNode->right);

        return (leftNodes + rightNodes + 1);
    }

    // Sum of Nodes
    int sumOfNodes(Node* rootNode){
        if(rootNode == nullptr){
            return 0;
        }

        int leftSum = sumOfNodes(rootNode->left);
        int rightSum = sumOfNodes(rootNode->right);

        return (leftSum + rightSum + rootNode->data);
    }

    // Height of tree
    int heightOfTree(Node* rootNode){
        if(rootNode == nullptr){
            return 0;
        }

        int leftHeight = heightOfTree(rootNode->left);
        int rightHeight = heightOfTree(rootNode->right);

        return max(leftHeight, rightHeight) + 1;
    }

    // Diameter of tree - Time Complexity (O(n^2))
    int diameterOfTreeApproach1(Node* rootNode){
        if(rootNode == nullptr){
            return 0;
        }

        int leftDiameter = diameterOfTreeApproach1(rootNode->left);
        int rightDiameter = diameterOfTreeApproach1(rootNode->right);
        int rootDiameter = heightOfTree(rootNode->left) + heightOfTree(rootNode->right) + 1;

        return max(max(leftDiameter, rightDiameter), rootDiameter);
    }

    // Diameter of tree - Time Complexity (O(n))
    NodeData diameterOfTreeApproach2(Node* rootNode){
        if(rootNode == nullptr){
            return NodeData(0, 0);
        }

        NodeData leftData = diameterOfTreeApproach2(rootNode->left);
        NodeData rightData = diameterOfTreeApproach2(rootNode->right);

        int rootHeight = max(leftData.height, rightData.height) + 1;
        int rootDiameter = max((leftData.height + rightData.height + 1), max(leftData.diameter, rightData.diameter));
        NodeData rootData(rootHeight, rootDiameter);

        return rootData;
    }

    // Lowest Common Ancestor
    Node* LCA(Node* rootNode, Node* p, Node* q){
        if(rootNode == nullptr){
            return nullptr;
        }

        if(rootNode->data == p->data || rootNode->data == q->data){
            return rootNode;
        }

        Node* leftLCA = LCA(rootNode->left, p, q);
        Node* rightLCA = LCA(rootNode->right, p, q);

        if(leftLCA != nullptr && rightLCA != nullptr){
            return rootNode;
        }
        else if(leftLCA != nullptr){
            return leftLCA;
        }
        else {
            return rightLCA;
        }
    }
};


// Binary Search Tree
class BinarySearchTree{
    int prevOrder = 0;

    public:

    // Reset PrevOrder to 0
    void resetPrevOrder(){
        prevOrder = 0;
    }

    // Build BST
    Node* buildBST(vector<int> nodes){
        Node* root = nullptr;

        for(int node : nodes){
            root = insertNode(root, node);
        }

        return root;
    }

    // Insert Node
    Node* insertNode(Node* root, int val){
        if(root == nullptr){
            return new Node(val);
        }

        if(val < root->data){
            root->left = insertNode(root->left, val);
        }
        else{
            root->right = insertNode(root->right, val);
        }

        return root;
    }

    // Inorder Traversal
    void inorderTraversal(Node* rootNode){
        if(rootNode == nullptr){
            return;
        }

        inorderTraversal(rootNode->left);
        cout << rootNode->data << " ";
        inorderTraversal(rootNode->right);
    }

    // Search BST - Time Complexity (O(Height))
    bool searchBST(Node* root, int key){
        if(root == nullptr){
            return false;
        }

        if(root->data == key){
            return true;
        }

        if(root->data > key){
            return searchBST(root->left, key);
        }
        else{
            return searchBST(root->right, key);
        }
    }

    // Delete Node in BST
    Node* deleteNode(Node* rootNode, int key){
        if(rootNode == nullptr){
            return nullptr;
        }

        if(rootNode->data > key){
            rootNode->left = deleteNode(rootNode->left, key);
        }
        else if(rootNode->data < key){
            rootNode->right = deleteNode(rootNode->right, key);
        }
        else{ // rootNode->data == key
            if(rootNode->left == nullptr){
                Node* temp = rootNode->right;
                delete rootNode;
                return temp;
            }
            else if(rootNode->right == nullptr){
                Node* temp = rootNode->left;
                delete rootNode;
                return temp;
            }
            else{ // 2 children case
                Node* IS = getInorderSuccessor(rootNode->right);
                rootNode->data = IS->data;
                rootNode->right = deleteNode(rootNode->right, IS->data);

            }
        }

        return rootNode;
    }

    // Get InorderSuccessor
    Node* getInorderSuccessor(Node* rootNode){
        while(rootNode != nullptr && rootNode->left != nullptr){
            rootNode = rootNode->left;
        }

        return rootNode;
    }

    // Kth Smallest Element in BST
    int kthSmallest(Node* root, int k){
        if(root == nullptr){
            return -1;
        }

        if(root->left != nullptr){
            int leftVal = kthSmallest(root->left, k);
            if(leftVal != -1){
                return leftVal;
            }
        }

        if(prevOrder + 1 == k){
            return root->data;
        }
        prevOrder++;

        if(root->right != nullptr){
            int rightVal = kthSmallest(root->right, k);
            if(rightVal != -1){
                return rightVal;
            }
        }

        return -1;
    }
};

int main(){
    
    // // Binary Tree
    // {
    //     vector<int> nodes = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};  // Preorder

    //     BinaryTree bt = BinaryTree();
    //     Node* rootNode = bt.binaryTree(nodes);

    //     cout << "Root Node: " << rootNode->data << endl;
    //     cout << "Left Node of Root Node: " << rootNode->left->data << endl;
    //     cout << "Right Node of Root Node: " << rootNode->right->data << endl;

    //     cout << endl << "Preorder: ";
    //     bt.preorderPrint(rootNode);
    //     cout << endl;

    //     cout << endl << "Inorder: ";
    //     bt.inorderPrint(rootNode);
    //     cout << endl;

    //     cout << endl << "Postorder: ";
    //     bt.postorderPrint(rootNode);
    //     cout << endl;

    //     cout << endl << "Levelorder: " << endl;
    //     bt.levelorderPrint(rootNode);
    //     cout << endl;

    //     cout << "Number of Nodes: " << bt.countOfNodes(rootNode) << endl;
    //     cout << "Sum of Nodes: " << bt.sumOfNodes(rootNode) << endl;
    //     cout << "Height of Tree: " << bt.heightOfTree(rootNode) << endl;
    //     cout << "Diameter of Tree (Approach 1): " << bt.diameterOfTreeApproach1(rootNode) << endl;
    //     cout << "Diameter of Tree (Approach 2): " << bt.diameterOfTreeApproach2(rootNode).diameter << endl;

    //     cout << "Lowest Common Ancestor of 4 & 6 is: " << bt.LCA(rootNode, new Node(4), new Node(6))->data << endl;
    //     cout << "Lowest Common Ancestor of 4 & 5 is: " << bt.LCA(rootNode, new Node(4), new Node(5))->data << endl;
    // }



    // Binary Search Tree
    {
        vector<int> nodes = {6, 5, 4, 8, 7, 9};

        BinarySearchTree bst = BinarySearchTree();
        Node* root = bst.buildBST(nodes);

        cout << "Root node: " << root->data << endl;
        cout << "Inorder Traversal: ";
        bst.inorderTraversal(root);
        cout << endl;

        cout << "3rd smallest element in BST: " << bst.kthSmallest(root, 3) << endl;

        cout << "Is 7 exists? " << (bst.searchBST(root, 7)? "True" : "False") << endl;
        cout << "Is 4 exists? " << (bst.searchBST(root, 4)? "True" : "False") << endl;

        root = bst.deleteNode(root, 5);
        cout << "Inorder Traversal: ";
        bst.inorderTraversal(root);
        cout << endl;

        bst.resetPrevOrder();
        cout << "3rd smallest element in BST: " << bst.kthSmallest(root, 3) << endl;
    }

    return 0;
}
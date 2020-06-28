#include <fstream>

class HtreeNode{
public:
    int prob;
    std::string chSt, code;
    HtreeNode* left;
    HtreeNode* right;
    HtreeNode* next;
    
    HtreeNode(std::string data, int p, std::string c, HtreeNode* l, HtreeNode* r, HtreeNode* n){
        this->chSt = data;
        this->prob = p;
        this->code = c;
        this->left = l;
        this->right = r;
        this->next = n;
    }
    HtreeNode(){
        this->chSt = "";
        this->code = "";
        this->prob = 0;
        this->left = nullptr;
        this->right = nullptr;
        this->next = nullptr;
    }
    
    void printNode(std::ofstream& file1){
        if(this == nullptr){
            file1<<"NULL";
        }else{
            file1<<"("<<this->chSt<<", "<<this->prob<<", "<<this->code;
            if(this->next != nullptr){
                file1<<this->next->chSt<<", ";
            }else{
                file1<<"NULL, ";
            }
            if(this->left != nullptr){
                file1<<this->left->chSt<<", ";
            }else{
                file1<<"NULL, ";
            }
            if(this->right != nullptr){
                file1<<this->right->chSt<<", ";
            }else{
                file1<<"NULL,";
            }
            file1<<")->";
        }
    }
};

class linkedList{
public:
    HtreeNode* listHead;
    linkedList(HtreeNode* h, std::ifstream& inFile, std::ofstream& outFile){
        this->listHead = h;
        int prob;
        std::string ch;
        while(inFile>>ch && inFile>>prob){
            HtreeNode* newNode = new HtreeNode(ch, prob, "", nullptr, nullptr, nullptr);
            listInsert(this->listHead, newNode);
            printList(this->listHead, outFile);
        }
    }
    void listInsert(HtreeNode* h, HtreeNode* nn){
        HtreeNode* spot = findSpot(h, nn);
        if(spot != nullptr){
            nn->next = spot->next;
            spot->next = nn;
        }
    }
    HtreeNode* findSpot(HtreeNode* h, HtreeNode* nn){
        HtreeNode* spot = h;
        while(spot->next != nullptr && spot->next->prob < nn->prob){
            spot = spot->next;
        }
        return spot;
    }
    void printList(HtreeNode* h, std::ofstream& file1){
        HtreeNode* walker = h;
        file1<<"listHead->";
        while(walker->next != nullptr){
            walker->printNode(file1);
            walker = walker->next;
        }
    }
};

class HuffmanBinaryTree{
public: 
    HtreeNode* listHead;   
    HuffmanBinaryTree(linkedList* list, std::ofstream& outFile){
        this->listHead = list->listHead;
        while(listHead->next->next != nullptr){
        
            HtreeNode* newNode = new HtreeNode();
            newNode->prob = listHead->next->prob + listHead->next->next->prob;
            newNode->chSt = listHead->next->chSt + listHead->next->next->chSt;
            newNode->left = listHead->next;
            newNode->right = listHead->next->next;
            newNode->next = nullptr; 
        
            list->listInsert(listHead, newNode);
            listHead->next = listHead->next->next->next;
            list->printList(listHead, outFile);
        }
    }
    void constructCharCode(HtreeNode* T, std::string code, std::ofstream& outFile){
        if(isLeaf(T)){
            T->code = code;
            outFile<<T->chSt<<T->code<<"\n";
        }else{
            constructCharCode(T->left, code+"0", outFile);
            constructCharCode(T->right, code+"1", outFile);
        }    
    }
    
    void inOrderTraversal(HtreeNode* T, std::ofstream& outFile){
        if(isLeaf(T)){
            T->printNode(outFile);
        }else{
            inOrderTraversal(T->left, outFile);
            T->printNode(outFile);
            inOrderTraversal(T->right, outFile);
        }
    }
    void preOrderTraversal(HtreeNode* T, std::ofstream& outFile){
        if(isLeaf(T)){
            T->printNode(outFile);
            
        }else{
            T->printNode(outFile);
            preOrderTraversal(T->left, outFile);
            preOrderTraversal(T->right, outFile);
        }
    }
    void postOrderTraversal(HtreeNode* T, std::ofstream& outFile){
        if(isLeaf(T)){
            T->printNode(outFile);
        }else{
            postOrderTraversal(T->left, outFile);
            postOrderTraversal(T->right, outFile);
            T->printNode(outFile);
        }    
    }
    bool isLeaf(HtreeNode* T){
        return (T->left == nullptr && T->right == nullptr);
    }
};

int main(int argc, char* argv[]){
    std::ifstream inFile(argv[1]);
    std::ofstream outFile1(argv[2]), outFile2(argv[3]), outFile3(argv[4]);
    
    HtreeNode* listHead = new HtreeNode("dummy", 0, "", nullptr, nullptr, nullptr);
    linkedList* ll = new linkedList(listHead, inFile, outFile3);
    
    outFile2<<"LinkedList\n";
    ll->printList(listHead, outFile2);
    outFile2<<"Null\n";
    
    HuffmanBinaryTree* tree = new HuffmanBinaryTree(ll, outFile3);
    HtreeNode* root = tree->listHead->next;
    
    outFile2<<"preOrderTraversal\n";
    tree->preOrderTraversal(root, outFile2);
    outFile2<<"Null\n";
    
    outFile2<<"inOrderTraversal\n";
    tree->inOrderTraversal(root, outFile2);
    outFile2<<"Null\n";
    
    outFile2<<"postOrderTraversal\n";
    tree->postOrderTraversal(root, outFile2);
    outFile2<<"Null\n";
    
    inFile.close();
    outFile1.close();
    outFile2.close();
    outFile3.close();
    return 0;
}

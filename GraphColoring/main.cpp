#include <iostream>
#include <fstream>
#include <stdexcept>
class hashTable{
private:
    int numberOfVertecies;
    int* colorOfNodeAry;
    bool** hashTableAry;
    //Auxilarry methods for method 1 of coloring
    int getUncoloredNode()const{
        for(int i = 1; i <= numberOfVertecies; i++){
            if(colorOfNodeAry[i] <= 0){
                return i;
            }
        }
       return -1;
    }
    int getColor()const{
        try{
            for(int i = 1; i <= numberOfVertecies; i++){
                if(hashTableAry[i][i] == false){
                    return i;
                }
            }
            throw(-1);
        }catch(int x){
            std::cout<<"Major Error in getColor(). Negative Color\n";
            exit(1);
        }

        return -1;
    }
    bool validColor(const int c, const int n)const{
        for(int i = 1; i <= numberOfVertecies; i++){
            if(i != n){
                bool tempNode = hashTableAry[n][i];
                if(tempNode and colorOfNodeAry[i] == c){
                    return false;
                }
            }
        }
        return true;
    }

    //Aux methods for method2 of coloring
    void markColorsUsed(const int n){
        int tempColor;
        for(int i = 1; i <= numberOfVertecies; i++){
            if(i != n){
                bool tempNode = hashTableAry[n][i];
                if(tempNode and colorOfNodeAry[i] > 0){
                    tempColor = colorOfNodeAry[i];
                    hashTableAry[tempColor][tempColor] = true;
                }
            }
        }
    }
    void assignColorToNode(const int node) const{
        int i = 1;
        while(hashTableAry[i][i]){
            ++i;
        }
        colorOfNodeAry[node] = i;
    }
    void initializeColorUsedAry(bool** ary){
        for(int i = 0; i <= numberOfVertecies; i++){
            ary[i][i] = false;
        }
    }
    void debug(std::ofstream& file) const{
        file<<"colorOfNodeAry"<<"\n";
        for(int i = 0; i <= numberOfVertecies; i++){
            file<<colorOfNodeAry[i]<<" ";
        }
        file<<"\n";

        file<<"colorUsedAry"<<"\n";
        for(int i = 0; i <= numberOfVertecies; i++){
            if(hashTableAry[i][i]){
                file<<"True  ";
            }else{
                file<<"False ";
            }
        }
        file<<"\n";

        file<<"hashTableAry"<<"\n";
        tablePrint(file);
        file<<"\n";
    }

public:
    hashTable(std::ifstream& inFile){
        int startNode, endNode;
        inFile>>numberOfVertecies;
        colorOfNodeAry = new int[numberOfVertecies+1];
        hashTableAry = new bool*[numberOfVertecies+1];
        for(int i = 0; i <= numberOfVertecies; i++){
            hashTableAry[i] = new bool[numberOfVertecies+1];
            colorOfNodeAry[i] = 0;
        }
        for(int r = 0; r <= numberOfVertecies; r++){
            for(int c = 0; c <= numberOfVertecies; c++){
                hashTableAry[r][c] = false;
            }
        }
        while(inFile>>startNode>>endNode){
            hashTableAry[startNode][endNode] = true;
            hashTableAry[endNode][startNode] = true;
        }
    }
    ~hashTable(){
        delete[] colorOfNodeAry;
        for(int i = 0; i <= numberOfVertecies; i++){
            delete[] hashTableAry[i];
        }
        delete[] hashTableAry;
    }
    //1st method of graph coloring
    void graphColoring1(std::ofstream& debugFile){
        int uncoloredNode, newColor;
        uncoloredNode = getUncoloredNode();
        while(uncoloredNode > 0){
            newColor = getColor();
            hashTableAry[newColor][newColor] = true;
            colorOfNodeAry[uncoloredNode] = newColor;
            for(int i = uncoloredNode+1; i <= numberOfVertecies; i++){
                if(colorOfNodeAry[i] <= 0 and validColor(newColor, i)){
                    colorOfNodeAry[i] = newColor;
                }
            }
            uncoloredNode = getUncoloredNode();
            debug(debugFile);
        }
    }

    //2nd Method of Graph Coloring
    void graphColoring2(std::ofstream& debugFile){
        for(int i = 1; i <= numberOfVertecies; i++){
            markColorsUsed(i);
            assignColorToNode(i);
            initializeColorUsedAry(hashTableAry);
            debug(debugFile);
        }
    }

    void printToFile1(std::ofstream& file)const{
        file<<numberOfVertecies<<"\n";
        for(int i = 1; i <= numberOfVertecies; i++){
            file<<i<<" "<<colorOfNodeAry[i]<<"\n";
        }
    }
    void tablePrint(std::ofstream& file) const{
        for(int r = 1; r <= numberOfVertecies; r++){
            for(int c = 1; c <= numberOfVertecies; c++){
                if(hashTableAry[r][c]){
                    file<<"True  ";
                }else{
                    file<<"False ";
                }
            }
            file<<"\n";
        }
        file<<"\n";
    }
};

int main(int argc, char** argv) {
	int temp;
    try{
        if(argc < 2){
            throw std::invalid_argument("No input File detetced");
        }else if(argc < 3){
            throw std::invalid_argument("No method detected");
        }else{
            temp = atoi(argv[2]);
            if(temp != 1 && temp != 2){
                throw std::invalid_argument("Pick Method 1 or 2");
            }
        }
    }catch(std::invalid_argument &ex){
        std::cout<<ex.what()<<"\n";
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);
    const int whichMethod = temp;

    const std::string fileName1 = "output 1 method" + std::to_string(whichMethod) + " " + argv[1];
    const std::string fileName2 = "output 2 method" + std::to_string(whichMethod) + " " + argv[1];
    const std::string fileName3 = "debug file " + std::to_string(whichMethod) + " " + argv[1];

    std::ofstream output1(fileName1);
    std::ofstream output2(fileName2);
    std::ofstream output3(fileName3);

    hashTable table = hashTable(input);

    switch(whichMethod){
        case(1):{
            table.graphColoring1(output3);
            break;
        }
        case(2):{
            table.graphColoring2(output3);
            break;
        }
        default:{
            try{
                throw std::exception();
            }
            catch(...){
                std::cout<<"Error. See switch\n";
                input.close();
                output1.close();
                output2.close();
                output3.close();
                return 1;
            }
            break;
        }
    }

    output1<<whichMethod<<"\nBelow is the result of the color assignments\n\n";
    table.printToFile1(output1);
    table.tablePrint(output2);

    input.close();
    output1.close();
    output2.close();
    output3.close();

    return 0;
}

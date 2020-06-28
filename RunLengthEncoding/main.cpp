#include <fstream>
#include <iostream>
class runLength{
private:
    int numRows, numCols, minVal, maxVal, row, col, length, currVal, nextVal;
public:    
    runLength(std::ifstream& inFile, std::ofstream& outFile, int method){
        inFile>>numRows>>numCols>>minVal>>maxVal;
        outFile<<numRows<<' '<<numCols<<' '<<minVal<<' '<<maxVal<<"\n"<<method<<"\n";
        row = 0;
        col = 0;
    }
    //encode all zeros, no wrap around
    void encodeMethod01(std::ifstream& inFile, std::ofstream& outFile){
        outFile<<row<<" "<<col<<" ";
        inFile>>currVal;
        while(row < numRows){
            col = 0;
            length = 1;
            while(col < numCols){
                ++col;
                inFile>>nextVal;
                if(currVal == nextVal){
                    ++length;
                }else{
                    outFile<<currVal<<" "<<length<<" \n";
                    currVal = nextVal;
                    length = 1;
                    if(col < numCols){
                        outFile<<row<<" "<<col<<" ";
                    }
                }
            }
            ++row;
            if(length > 1){
                outFile<<currVal<<" "<<length-1<<" \n";
            }
            if(row < numRows){
                outFile<<row<<" 0 ";
            }
        }
    }
    void encodeMethod02(std::ifstream& inFile, std::ofstream& outFile){
        int zeroCnt;
        row = 0; col = -1; length = 1;
        currVal = skipZero02(inFile, row, col, zeroCnt);
        while(currVal != 0 && row < numRows){
            currVal = skipZero02(inFile, row, col, zeroCnt);
        }
    }
    
    int skipZero02(std::ifstream& file, int& r, int& c, int& z){
        if(++c == numCols){
            c = 0;
            ++r;
            return 0;
        }
        int pixelVal;
        while(file>>pixelVal && pixelVal == 0){
            z++; 
            if(++c == numCols){
                c = 0;
                row++;
                return 0;
            }
        }
        return pixelVal;
    }
    
    
    //don't encode zeors, and wrap around
    void encodeMethod04(std::ifstream& inFile, std::ofstream& outFile){
        int zeroCnt;
        row = 0, col = -1, length = 1;
        currVal = skipZero01(inFile, row, col, zeroCnt);
        outFile<<row<<' '<<col<<' '<<currVal<<' ';
        while(row < numRows){
            nextVal = skipZero01(inFile, row, col, zeroCnt);
            if(zeroCnt > 0){
                currVal = 0;
            }
            if(nextVal == currVal){
                ++length;
            }else{
                currVal = nextVal;
                outFile<<length<<"\n"<<row<<' '<<col<<' '<<currVal<<' ';
                length = 1;
            }
        }
        outFile<<--length;
    } 

    int skipZero01(std::ifstream& file, int& r, int& c, int& z){
        z = 0;
        if(++c == numCols){
            c = 0;
            ++r;
        }
        int pixelVal;
        while(file>>pixelVal && pixelVal == 0){
            z++; 
            if(++c == numCols){
                c = 0;
                row++;
            }
        }
        return pixelVal;
    }
};

int main(int argc, char* argv[]){
	std::ifstream inFile1(argv[1]);
    int method = atoi(argv[2]);

    std::string fileName = argv[1];
    std::string nameEncodeFile = fileName.substr(0, fileName.length()-4); 
    nameEncodeFile += "_EncodeMethod" + std::to_string(method) + ".txt";
    std::ofstream encodeFile(nameEncodeFile);
    
    runLength* image = new runLength(inFile1, encodeFile, method);

    if(method == 1){
        image->encodeMethod01(inFile1, encodeFile);
    }else if(method == 4){
        image->encodeMethod04(inFile1, encodeFile);
    }else{
        return -9999;
        return -1;
    }
    //delete image;
    inFile1.close();
    encodeFile.close();
    return 0;
}

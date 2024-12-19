#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstdint>
using namespace std;
#pragma pack(push, 1)
struct head{
    uint16_t header_crs;
    uint8_t header_type;
    uint16_t header_flags;
    uint16_t header_size;
};
struct mainHead{
    uint16_t hughPosAv;
    uint32_t posAV;
    uint8_t encryptVer;
};
struct fileHead{
    uint32_t packSize;
    uint32_t unpSize;
    uint8_t hostOS;
    uint32_t fileCRC;
    uint32_t gileTime;
    uint8_t unpVer;
    uint8_t method;
    uint16_t nameSize;
    uint32_t fileAttr;
};

#pragma pack(pop)
void readarc(vector<char> x){
    int index = 14 + 6;
    while(true){
        head * p_header = reinterpret_cast<head*> (&x[index]);
        index += 7;
        if(int(p_header -> header_type) != 116){ // 74 из 16-й в 10-ю
            break;
        }
        else{
            fileHead* f_header = reinterpret_cast<fileHead*> (&x[index]);
            index += 25;
                for (int i = index; i< index + int(f_header -> nameSize); i++){
                    cout << x[i];
                }
                cout << endl;
                index -= 25;
                index -= 7;
                index += int(f_header -> packSize);
                index += p_header -> header_size;
            }
            cout << "\n" << endl;
        }
}
int main()
{
    vector<string> path = {"Example.rar"};
    ifstream file("Example.rar", ios::binary);
    if (file.is_open()){
        cout << "File is open!" << "\n" << endl;}
    file.seekg(0, ios::end);
    int size = file.tellg();
    file.seekg(0, ios::beg);
    vector<char> arr(size,0);
    file.read(arr.data(), size);

}

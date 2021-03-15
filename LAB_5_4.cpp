#include <fstream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Label {
    string name;
    int value;
};

int main() {
    ifstream fin("quack.in");
    ofstream fout("quack.out");

    vector <string> Vector;
    vector <Label> Lab;
    queue <unsigned short int> Que;
    unsigned short int Regist[26];
    for (int i = 0; i < 26; i++)
        Regist[i] = 0;
    while (!fin.eof()) {
        string com;
        fin >> com;
        Vector.push_back(com);
        if (com[0] == ':') {
            string name = com;
            name.erase(0, 1);
            Lab.push_back({ name, (int)Vector.size() - 1 });
        }
    }

    for (int count = 0; count < Vector.size(); count++) {
        if (Vector[count][0] == '-') {  
            unsigned short int x = Que.front();
            Que.pop();
            unsigned short int y = Que.front();
            Que.pop();
            Que.push((x - y) % 65536); 
        }
        else if (Vector[count][0] == '*') {
            unsigned short int x = Que.front();
            Que.pop();
            unsigned short int y = Que.front();
            Que.pop();
            Que.push((x * y) % 65536);
        }
        else if (Vector[count][0] == '+') {
            unsigned short int x = Que.front();
            Que.pop();
            unsigned short int y = Que.front();
            Que.pop();
            Que.push((x + y) % 65536);
        }
        else if (Vector[count][0] == '/')  {
            unsigned short int x = Que.front();
            Que.pop();
            unsigned short int y = Que.front();
            Que.pop();
            if (y == 0)
                Que.push(0);
            else
                Que.push(x / y);
        }
        else if (Vector[count][0] == '%') {
            unsigned short int x = Que.front();
            Que.pop();
            unsigned short int y = Que.front();
            Que.pop();
            if (y == 0)
                Que.push(0);
            else
                Que.push(x % y);
        }
        else if (Vector[count][0] == '>') {
            unsigned short int x = Que.front();
            Que.pop();
            Regist[(int)Vector[count][1] - (int)'a'] = x;
        }
        else if (Vector[count][0] == '<') {
            Que.push(Regist[(int)Vector[count][1] - (int)'a']);
        }
        else if (Vector[count][0] == 'P') {
            if (Vector[count].size() == 1) {
                fout << Que.front() << "\n";
                Que.pop();
            }
            else {
                fout << Regist[(int)Vector[count][1] - (int)'a'] << "\n";
            }
        }
        else if (Vector[count][0] == 'C')  {
            if (Vector[count].size() == 1) {
                fout << (char)(Que.front() % 256);
                Que.pop();
            }
            else {
                fout << (char)(Regist[(int)Vector[count][1] - (int)'a'] % 256);
            }
        }
        else if (Vector[count][0] == 'Z') {
            if (Regist[(int)Vector[count][1] - (int)'a'] == 0) {
                string str = Vector[count];
                str.erase(0, 2);
                for (int k = 0; k < Lab.size(); k++)
                    if (Lab[k].name == str) {
                        count = Lab[k].value;
                        break;
                    }
            }
        }
        else if (Vector[count][0] == 'J') {
            string str = Vector[count];
            str.erase(0, 1);
            for (int k = 0; k < Lab.size(); k++)
                if (Lab[k].name == str) {
                    count = Lab[k].value;
                    break;
                }
        }
        else if (Vector[count][0] == 'E') {
            if (Regist[(int)Vector[count][1] - (int)'a'] == Regist[(int)Vector[count][2] - (int)'a']) {
                string str = Vector[count];
                str.erase(0, 3);
                for (int k = 0; k < Lab.size(); k++)
                    if (Lab[k].name == str) {
                        count = Lab[k].value;
                        break;
                    }
            }
        }
        else if (Vector[count][0] == 'G') {
            if (Regist[(int)Vector[count][1] - (int)'a'] > Regist[(int)Vector[count][2] - (int)'a']){
                string str = Vector[count];
                str.erase(0, 3);
                for (int k = 0; k < Lab.size(); k++)
                    if (Lab[k].name == str) {
     
                        count = Lab[k].value;
                        break;
                    }
            }
        }
        else if (Vector[count][0] == 'Q')
            break;
        else if (Vector[count][0] >= '0' && Vector[count][0] <= '9') {
            unsigned short int element = 0;
            for (int k = 0; k < Vector[count].size(); k++)
                element = element * 10 + (int)Vector[count][k] - (int)'0';
            Que.push(element);
        }
    }
    fin.close();
    fout.close();
    return 0;
}

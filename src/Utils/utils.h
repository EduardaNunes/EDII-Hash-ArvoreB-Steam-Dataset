#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Utils{
    public:
        Utils(){};
    
        vector<string> split(const string& str, char delimitador) {
            vector<string> tokens;
            string token;
            stringstream ss(str);
            while (getline(ss, token, delimitador)) {
                // Remove espaços em branco extras
                size_t start = token.find_first_not_of(" ");
                size_t end = token.find_last_not_of(" ");
                if (start != string::npos && end != string::npos)
                    tokens.push_back(token.substr(start, end - start + 1));
                else if (!token.empty())
                    tokens.push_back(token);
            }
            return tokens;
        }

};

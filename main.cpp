// SecureHuff.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <iomanip>
#include <random>
#include <functional>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

// ========== Huffman Classes ========== //
class node {
public:
    char ch;
    int freq;
    node* left;
    node* right;

    node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }

    struct compare {
        bool operator()(node* a, node* b) {
            return a->freq > b->freq;
        }
    };
};

class Huffman_encoder {
private:
    string text;
    unordered_map<char, int> freq_map;
    unordered_map<char, string> codes;
    string encoded_str;
    node* root;

    void build_frequency_map() {
        for (char c : text) freq_map[c]++;
    }

    void build_Huffman_tree() {
        priority_queue<node*, vector<node*>, node::compare> pq;

        for (auto pair : freq_map) {
            pq.push(new node(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            node* Left = pq.top(); pq.pop();
            node* Right = pq.top(); pq.pop();
            node* Merged = new node('\0', Left->freq + Right->freq);
            Merged->left = Left;
            Merged->right = Right;
            pq.push(Merged);
        }

        root = pq.top();
    }

    void build_codes(node* n, string code) {
        if (n == nullptr) return;
        if (n->left == nullptr && n->right == nullptr) codes[n->ch] = code;
        build_codes(n->left, code + '0');
        build_codes(n->right, code + '1');
    }

    void encode_text() {
        for (auto c : text) encoded_str += codes[c];
    }

public:
    Huffman_encoder(string t) {
        text = t;
        build_frequency_map();
        build_Huffman_tree();
        build_codes(root, "");
        encode_text();
    }

    void display_codes() {
        cout << "\nHuffman Codes:\n";
        for (auto pair : codes) {
            cout << pair.first << " : " << pair.second << endl;
        }
    }

    void save_to_file(const string& file_name) {
        ofstream out(file_name);
        if (out.fail()) {
            cerr << "Error Writing to file!" << endl;
            return;
        }

        out << encoded_str << "\n";
        for (auto pair : codes) {
            out << (int)pair.first << " " << pair.second << "\n";
        }
        out.close();
    }

    void show_packing_density() {
        double original_size = text.size() * 8;
        double compressed_size = encoded_str.size();
        double density = (compressed_size / original_size) * 100;
        cout << fixed << setprecision(2);
        cout << "\nPacking Density: " << density << "%" << endl;
    }
};

class Huffman_decoder {
private:
    unordered_map<string, char> reverse_codes;
    string encoded_str;

public:
    Huffman_decoder(const string& encoded_file_name) {
        ifstream in(encoded_file_name);
        if (!in) {
            cerr << "Error reading file!" << endl;
            return;
        }

        getline(in, encoded_str);
        int ascii;
        string code;
        while (in >> ascii >> code) {
            reverse_codes[code] = (char)ascii;
        }
        in.close();
    }

    void decode() {
        string current_code = "", decoded_text = "";
        for (char bit : encoded_str) {
            current_code += bit;
            if (reverse_codes.find(current_code) != reverse_codes.end()) {
                decoded_text += reverse_codes[current_code];
                current_code = "";
            }
        }
        cout << "\nDecoded Text: " << decoded_text << endl;
    }
};

// ========== Login System ========== //
class login_signup {
private:
    unordered_map<string, pair<string, string>> user_Database;

    string generate_salt(size_t length = 7) {
        static const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        mt19937 generator(steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<> dist(0, charset.size() - 1);
        string salt;
        for (int i = 0; i < length; i++) salt += charset[dist(generator)];
        return salt;
    }

    string generate_Hash(const string& password, const string& salt) {
        hash<string> hasher;
        size_t hash_Value = hasher(password + salt);
        stringstream ss;
        ss << hex << hash_Value;
        return ss.str();
    }

public:
    bool register_User(const string& username, const string& password, const string& file_name) {
        if (user_Database.find(username) != user_Database.end()) return false;
        string salt = generate_salt();
        string hashedPassword = generate_Hash(password, salt);
        user_Database[username] = make_pair(salt, hashedPassword);
        save_to_file(file_name);
        return true;
    }

    bool verify_Login(const string& username, const string& password) {
        auto it = user_Database.find(username);
        if (it == user_Database.end()) return false;
        string salt = it->second.first;
        string storedHash = it->second.second;
        string computedHash = generate_Hash(password, salt);
        return computedHash == storedHash;
    }

    void save_to_file(const string& file_name) {
        ofstream file(file_name);
        if (!file) {
            cerr << "Error opening file: " << file_name << endl;
            return;
        }
        for (const auto& entry : user_Database) {
            file << entry.first << ":" << entry.second.first << ":" << entry.second.second << endl;
        }
    }

    void load_from_file(const string& file_name) {
        ifstream file(file_name);
        if (!file) {
            cerr << "Error opening file: " << file_name << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            size_t colon_1 = line.find(':');
            size_t colon_2 = line.find(':', colon_1 + 1);
            if (colon_1 != string::npos && colon_2 != string::npos) {
                string username = line.substr(0, colon_1);
                string salt = line.substr(colon_1 + 1, colon_2 - colon_1 - 1);
                string hashed_password = line.substr(colon_2 + 1);
                user_Database[username] = make_pair(salt, hashed_password);
            }
        }
    }
};

// ========== Main Program ========== //
int main() {
    login_signup user;
    const string file_name = "user_data.txt";
    user.load_from_file(file_name);

    cout << "========== Huff Puff ==========\n";
    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose: ";
        int opt;
        cin >> opt;
        cin.ignore();

        if (opt == 1) {
            string uname, pass;
            cout << "Username: "; getline(cin, uname);
            cout << "Password: "; getline(cin, pass);
            if (user.register_User(uname, pass, file_name))
                cout << "Registered Successfully!\n";
            else cout << "Username already exists!\n";
        }

        else if (opt == 2) {
            string uname, pass;
            cout << "Username: "; getline(cin, uname);
            cout << "Password: "; getline(cin, pass);
            if (user.verify_Login(uname, pass)) {
                cout << "Login successful! Welcome, " << uname << "\n";
                while (true) {
                    cout << "\n1. Encode Message\n2. Decode Message\n3. Logout\nChoose: ";
                    int choice;
                    cin >> choice;
                    cin.ignore();

                    if (choice == 1) {
                        string input_text, encoded_file_name;
                        cout << "Enter message: ";
                        getline(cin, input_text);
                        cout << "Save encoded message to (e.g. encoded.txt): ";
                        getline(cin, encoded_file_name);
                        Huffman_encoder encoder(input_text);
                        encoder.display_codes();
                        encoder.save_to_file(encoded_file_name);
                        encoder.show_packing_density();
                    }
                    else if (choice == 2) {
                        string fname;
                        cout << "Enter file to decode: ";
                        getline(cin, fname);
                        Huffman_decoder decoder(fname);
                        decoder.decode();
                    }
                    else break;
                }
            } else {
                cout << "Login failed!\n";
            }
        }

        else break;
    }

    user.save_to_file(file_name);
    return 0;
}

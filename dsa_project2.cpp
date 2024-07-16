#include <bits/stdc++.h>

using namespace std;

class tree{
    public:
        int freq;
        char ch;
        bool is_end;
        tree* zero;     //0;
        tree* one;      //1;
        tree(){
            freq=0;
            is_end = false;
            zero = NULL;
            one = NULL;
            ch = '=';
        }
};

tree* make_tree(priority_queue<pair<int, char>> heap){
    tree* head = new tree();
    tree* traverse = head;
    while(!heap.empty()){
        auto it = heap.top();
        heap.pop();
        if(!heap.empty()){
            tree* next = new tree();
            next->freq = it.first;
            next->ch = it.second;
            next->is_end = true;
            traverse->zero = next;
            tree* next1 = new tree();
            traverse->one = next1;
            traverse = next1;
        }
        else{
            traverse->freq = it.first;
            traverse->ch = it.second;
            traverse->is_end = true;
        }
    }
    return head;
}

string compressor(string& text, tree* head){
    string needed = "";
    tree* tem = head;
    for(char c : text){
        string sr = "";
        while(tem->zero && tem->zero->ch!=c){
            tem = tem->one;
            sr += '1';
        }
        if(tem->zero && tem->zero->ch==c){
            sr += '0';
        }
        else if(tem->ch==c){

        }
        needed += sr;
        tem = head;
    }
    return needed;
}

string decompressor(string& text, tree* head){
    tree* tem = head;
    string needed = "";
    for(char c : text){
        if(c=='1'){
            tem = tem->one;
        }
        else if(c=='0'){
            tem = tem->zero;
        }
        if(!tem->zero && !tem->one){
            needed += tem->ch;
            tem = head;
        }
    }
    return needed;
}

int main(){
    string text;
    cout<<"ENTER THE TEXT YOU WANT TO COMPRESS"<<endl;
    getline(cin, text);
    vector<int> freq(108, 0);
    for(auto ch : text){
        freq[ch-' ']++;
    }
    priority_queue<pair<int, char>> heap;
    for(int i=0;i<107;i++){
        if(freq[i]){
            heap.push({freq[i], i+' '});
        }
    }
    tree* head = make_tree(heap);
    string compressed = compressor(text, head);
    cout<<"THE COMPRESSED FILE IS "<<compressed<<endl;
    string gen_text = decompressor(compressed, head);
    cout<<"THE DECOMPRESSED FILE OF THE RECIEVED COMPRESSED FILE IS "<<gen_text<<endl;
    cout<<"THANK YOU FOR USING PLEASE DROP A FEEDBACK"<<endl;
    return 0;
}
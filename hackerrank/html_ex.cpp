#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <sstream>

class Tag {
    public:
        std::string tagName;
        std::unordered_map<std::string, std::string> attrs;
        std::vector<Tag*> subtags;
        Tag *parentTag{nullptr};
        Tag() {}
        
        void addAttrs(std::string name, std::string value){
            attrs.emplace(std::pair(name, value));
        }
        void printAttrs(){
            for(auto pair: attrs){
                std::cout<<pair.first<<" : "<< pair.second;
            }
        }
        void addSubtag(Tag *tag){
            subtags.emplace_back(tag);
            tag->parentTag = this;
        }

        void addName(std::string name){
            tagName = name;
        }

        void printName(){
            std::cout<<tagName<<'\n';
        }

        void printTag(){
            printName();
            for(auto i : subtags)
                i->printTag();
        }

        ~Tag(){
            for(auto i:subtags)
                delete i;
        }
};

class hrlm_parser {
    public:
        hrlm_parser(){
        }
        
        int numLines;
        int numQueries;
        std::vector<std::string> lines;
        std::
        void readInput()
        {
            std::string inputString;
            char ch;
            std::cin >> numLines >> numQueries;
            std::cin.ignore(); // Ignore the newline character after reading numLines and numQueries
            std::cout << numLines << ' ' << numQueries << '\n';
            for (int i = 0; i < numLines + numQueries; i++) {
                std::getline(std::cin, inputString);
                lines.push_back(inputString);
            }
            for (auto i : lines){
                std::cout<<inputString<<'\n';
            }
        }

        Tag *parseTagLine(int l){
            if(std::string::npos != lines[l].find('/'))
                return nullptr;
            Tag *tag = new Tag;
            std::string str = lines[l].substr(1, lines[l].length() -2);
            std::stringstream ss{str};
            std::string tagName, attrName, attrEqual, attrValue;
            ss >> tagName;
            tag->addName(tagName);
            std::cout<<tagName<<'\n';
            while(ss >> attrName >> attrEqual >> attrValue){
                std::cout<<"Attributes: "<<attrName<<attrEqual<<attrValue<<'\n';
                tag->addAttrs(attrName, attrValue.substr(1, attrValue.length() - 2));
            }
            return tag;
        }

        void parseInput(Tag *tag) {
            static int l = 0;
            l++;
            std::cout<<"Line No.:"<<l<<'\n';
            if(l < numLines){
                
                Tag *tag1 = parseTagLine(l);
                if(tag1 == nullptr){
                    if(tag->parentTag != nullptr)
                        parseInput(tag->parentTag);
                }
                else{
                    tag->addSubtag(tag1);
                    parseInput(tag1);
                }
            }
        }

        void search_query(std::vector<std::string>& list_of_tags, std::string& attr_name){
            
        }
        void parseQuery(int lineNo) {
            std::string substr;
            std::vector<std::string> listOfTags;
            std::istringstream iss(lines[lineNo].substr(0, lines[lineNo].find_first_of('~')));
            std::string attrName = lines[lineNo].substr(lines[lineNo].find_first_of('~'));
            std::cout<<"List of tags in Q: "<< lines[lineNo].substr(0, lines[lineNo].find_first_of('~'))<<'\n';
            std::cout<< "attribute name: " << attrName<<'\n';
            while(std::getline(iss, substr, '.')){
                listOfTags.emplace_back(substr);
            }
            std::cout<<"List of Tags\n";
            for(auto i : listOfTags){
                std::cout<<"i: "<<i<<'\n';
            }
        }

        void parseAllQueries(){
            for(auto l = numLines; l < (numLines + numQueries); l++){
                parseQuery(l);
            } 

        }
};
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    hrlm_parser hrlp{};
    Tag *tag;
    hrlp.readInput();
    tag = hrlp.parseTagLine(0);
    hrlp.parseInput(tag);
    tag->printTag();
    std::cout<<"Parsing all queries\n";
    hrlp.parseAllQueries();
    return 0;
}
/*
6 3
<tag1 value = "value">
<tag2 name = "name">
</tag2>
<tag3 another = "another" final = "final">
</tag3>
</tag1>
tag1.tag2~name
tag1~name
tag1~value
*/
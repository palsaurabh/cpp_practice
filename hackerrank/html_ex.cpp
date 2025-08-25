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
                //std::cout<<pair.first<<" : "<< pair.second;
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

        void printTagNameAndAttributes(){
            std::cout<<tagName<<'\n';
            if (!attrs.empty()){
                for(auto i : attrs){
                    std::cout<<i.first<<":"<<i.second<<"\n";
                }
            }
        }

        void printTag(){
            // printName();
            printTagNameAndAttributes();
            for(auto i : subtags)
                i->printTag();
        }

        Tag* searchChildren(const std::string& tagName) {
            for (auto i : subtags)
            {
                if(i->tagName == tagName)
                    return i;
            }
            
            return nullptr;
        }

        Tag* findTag(const std::string& tagName) {
            // std::cout<<"Looking for Tag: "<<tagName<<'\n';
            if(this->tagName == tagName){
                // std::cout<<"Found tag: "<<tagName<<"\n";
                return this;
            }
            else{
                for(auto i : subtags){
                    // std::cout<<"Looking for Tag inside subtags: "<<tagName<<'\n';
                    Tag* tag = i->findTag(tagName);
                    if(tag != nullptr){
                        return tag;
                    }
                }
            }
            return nullptr;
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
        std::vector<Tag*> tags;
        int vector_tag = 0;
        int numLines;
        int numQueries;
        std::vector<std::string> lines;
        void readInput()
        {
            std::string inputString;
            std::cin >> numLines >> numQueries;
            std::cin.ignore(); // Ignore the newline character after reading numLines and numQueries
            lines.reserve(numLines + numQueries);
            for (int i = 0; i < numLines + numQueries; i++) {
                std::getline(std::cin, inputString);
                lines.emplace_back(inputString);
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
            while(ss >> attrName >> attrEqual >> attrValue){
                tag->addAttrs(attrName, attrValue.substr(1, attrValue.length() - 2));
            }
            return tag;
        }

        void parseInput(Tag *parentTag) {
            static int l = -1;
            l++;
            if(l < numLines){
                Tag *tag1 = parseTagLine(l);
                if(tag1 != nullptr){
                    // std::cout<<"tag1 is not null\n";
                    if(parentTag == nullptr)
                    {
                        // std::cout<<"Parent tag is null\n";
                        tags.push_back(tag1);
                        parseInput(tag1);
                    }
                    else 
                    {
                        // std::cout<<"Parent tag is not null, adding as subtag\n";
                        parentTag->addSubtag(tag1);
                        parseInput(tag1);
                    }
                }
                else{
                    if(parentTag->parentTag != nullptr)
                    {
                        // std::cout<<"tag1 is null, parent->parent is not null\n";
                        parseInput(parentTag->parentTag);
                    }
                    else{
                        // std::cout<<"tag1 is null, parent->parent is null\n";
                        parseInput(nullptr);
                    }
                }
            }
        }

        void search_query(const std::vector<std::string>& list_of_tags, const std::string& attr_name){
            Tag* primaryTag = nullptr;
            
            for(auto i : tags){
                if(i->tagName == list_of_tags[0]){
                    primaryTag = i;
                    break;
                }
            }
            if(primaryTag == nullptr)
            {
                std::cout<<"Not Found!"<<'\n';
                return;
            }
            Tag* tempTag = primaryTag;
            if(list_of_tags.size() > 1){
                for(int i = 1; i < list_of_tags.size(); i++)
                {
                    tempTag = tempTag->searchChildren(list_of_tags[i]);
                    if(!tempTag){
                        std::cout<<"Not Found!"<<'\n';
                        break;
                    }
                }
            }
            if(tempTag){
                auto it = tempTag->attrs.find(attr_name);
                if(it != tempTag->attrs.end()){
                    std::cout<<it->second<<"\n";
                }
                else
                    std::cout<<"Not Found!"<<'\n';
            }

        }
        void parseQuery(int lineNo) {
            std::string substr;
            std::vector<std::string> listOfTags;
            size_t split_pos =  lines[lineNo].find_first_of('~');
            std::istringstream iss(lines[lineNo].substr(0, split_pos));
            std::string attrName = lines[lineNo].substr(split_pos+1);
            while(std::getline(iss, substr, '.')){
                listOfTags.emplace_back(substr);
            }
            search_query(listOfTags, attrName);
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
    hrlp.readInput();
    hrlp.parseInput(nullptr);
    hrlp.parseAllQueries();
    return 0;
}
/*
8 3
<tag0 value0 = "value">
</tag0>
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
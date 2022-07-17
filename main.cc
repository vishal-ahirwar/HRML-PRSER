#include <iostream>
#include <map>
#include <string>
#include <vector>
#include<string.h>
struct HRML
{
    std::string attribute{}, value{};
    HRML() = default;
    HRML(const std::string &att, const std::string &value) : attribute(att), value(value){};
};
class HParser
{
    std::string text{};
    std::map<std::string, std::vector<struct HRML>> parser{};

public:
    HParser(const std::string&hrml_text):text(hrml_text){};
    HParser(FILE*);
    HParser()=delete;
    std::map<std::string, std::vector<HRML>> &InitParser();
};
HParser::HParser(FILE*file)
{
    if(file)
    {
        char c{};
        while((c=getc(file))!=EOF)
        {
            this->text+=c;
        }
    }else
    {
        puts("[error] failed to open file!");
    }
};
std::map<std::string, std::vector<HRML>> &HParser::InitParser()
{
    puts("[message] Parsing has been started!");
    auto begin = text.begin();
    auto end = text.end();
    while (begin != end)
    {
        std::string tag{}, attr{}, value{};
        std::vector<HRML> temp{};
        // puts("getting tag ...");
        while (*begin != ' ' && begin != end)
        {
            if (*begin == '<')
                ++begin;
            tag += (*begin);
            ++begin;
            if(*begin=='>')break;
        };

        auto getAttr = [&]()
        {//puts("getting attribute ...");
        while (*begin != '='&&begin!=end)
        {

            attr += (*begin);
            ++begin;
            if(*begin=='>')break;
        }; };
        getAttr();
        auto getValue = [&]()
        {//puts("getting value ...\n");
        while (*begin != '>'&&begin!=end)
        {
            if (*begin == '=')
                ++begin;
            value += (*begin);
            ++begin;
         if(*begin=='>')
            {
                temp.push_back(HRML(attr,value));
                break;
            };
            if(*begin==' '&&begin!=end)
            {
                temp.push_back(HRML(attr,value));
                value={};
                attr={};
                getAttr();
                //puts("getting value ...\n");
        while (*begin != '>'&&begin!=end)
        {
            if (*begin == '=')
                ++begin;
            value += (*begin);
            ++begin;
            if(*begin=='>')
            {
                temp.push_back(HRML(attr,value));
                break;
            };
            if(*begin==' '&&begin!=end)
            {
                temp.push_back(HRML(attr,value));
                value={};
                attr={};
                getAttr();
                
            };
        };
                
            };
        }; };
        getValue();
        // std::cout << tag << " " << attr << " " << value << "\n";
        if (temp.size() == 0)
            temp.push_back(HRML(attr, value));
        parser.insert({tag, temp});
    };
    return parser;
};

int main()
{
/*
    std::string text{};
    std::map<std::string, std::vector<struct HRML>> parser{};
    unsigned short n{}, q{};
    std::cin >> n >> q;
    std::cin.clear();
    std::cin.ignore();
    for (; n;)
    {
        std::string temp_text{};
        std::getline(std::cin, temp_text);
        // printf("%s\n", temp_text.c_str());
        text.append(temp_text + "\n");
        --n;
        // printf("%u, ", n);
    };
*/

    FILE*file;
    file=fopen("info.hrml","r");
    HParser hrml(file);
    auto parser=hrml.InitParser();
    puts("HRML Parser : ");
    for (const auto &ref : parser)
    {
        std::cout << ref.first << " : \n\t";
        for (const auto &hrml : ref.second)
        {
            std::cout << hrml.attribute << " " << hrml.value << "\n";
        };
    };
    puts("end!");
    return 0;
}
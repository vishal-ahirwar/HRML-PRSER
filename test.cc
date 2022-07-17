#include <string>
#include <iostream>
int main()
{
    std::string text{};
    std::map<std::string, HRML> parser{};
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

    std::cout << text;

    return 0;
}
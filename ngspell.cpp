#include <fstream>
#include <iostream>
#include <map>

void string_to_tries ()
{

}

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: programm launch is: ./ngspell <dict_file_path>";
        return 1;
    }
    std::ifstream file_stream(argv[1]);
    if (!file_stream)
    {
        std::cerr << "Error: cant open dictionary";
        return 1;
    }
    // короче, читаем слова по строчно, удаляем \n, разбиваем на 3 граммы, ищем в словаре, если нет, добавляем
    // если есть, то + 1, потом просто проходимся при каком-то вводе и ищем внутри большее количество вхождений сохраняя последний
    // но если их несколько? то надо сохранить все
    // сделать map которая сохраняет все одинаковые сравнивать её, в конце очищать
    std::string str;
}
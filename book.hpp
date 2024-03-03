#include <string>
#include <sstream>

class Book
{
public:
    Book(int keyV = -1, std::string isbn = "", std::string name = "", std::string genre = "", bool availableV = false)
        : key{keyV}, available{availableV} {
        setIsbn(isbn);
        setName(name);
        setGenre(genre);
    }

    void setKey(int num)
    {
        this->key = num;
    }
    int getKey() const
    {
        return key;
    }

    void setName(std::string bookName)
    {
        size_t length = bookName.size();
        length = length < 100 ? length : 99;
        bookName.copy(name, length);
        name[length] = '\0';
    }
    std::string getName() const
    {
        std::string bookName{name};
        return bookName;
    }

    void setGenre(std::string bookGenre)
    {
        size_t length = bookGenre.size();
        length = length < 30 ? length : 29;
        bookGenre.copy(genre, length);
        genre[length] = '\0';
    }
    std::string getGenre() const
    {
        std::string bookGenre{genre};
        return bookGenre;
    }

    void setIsbn(std::string isbnum)
    {
        size_t length = isbnum.size();
        length = length < 14 ? length : 13;
        isbnum.copy(isbn, length);
        isbn[length] = '\0';
    }
    std::string getIsbn() const
    {
        std::string bookIsbn{isbn};
        return bookIsbn;
    }

    bool getAvailable() const
    {
        return available;
    }

    std::string getDetails() const
    {
        std::ostringstream output;
        output << getKey() << ' ' << getName() << ' ' << getIsbn() << ' ' << getGenre() << ' ' << getAvailable();

        return output.str();
    }
private:
    int key;
    char isbn[14];
    char name[100];
    char genre[30];
    bool available;
};
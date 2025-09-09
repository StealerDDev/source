#include <iostream>
#include <unordered_map>
#include <unordered_set>

struct Student {
    std::string name;
    std::unordered_set<std::string> borrowings;
};

struct Book {
    std::string title;
    bool available = true;
};

std::unordered_map<std::string, Student> students;
std::unordered_map<std::string, Book> books;

void
assignStudent(const std::string& id, const std::string& name) {
    students.emplace(id, Student{name});
}

void
editStudent(const std::string& id, const std::string& newName) {
    auto student = students.find(id);

    if (student == students.end()) {
        std::cout << "Não foi possível achar o estudante!\n";
        return;
    }

    std::cout << "O nome do estudante " << student->second.name << " foi alterado para " << newName << "\n"; 
    student->second.name = newName;
}

void
removeStudent(const std::string& id) {
    auto student = students.find(id);

    if (student == students.end()) {
        std::cout << "Não foi possível achar o estudante!\n";
        return;
    }

    std::cout << "O estudante " << student->second.name << " foi apagado com sucesso!\n";

    for (auto const& id : student->second.borrowings) {
        
        auto const& book = books.find(id);

        if (book == books.end()) {
            continue;
        }
        book->second.available = true;

    }

    student->second.borrowings.clear();
    students.erase(student);
}

void
visualizeStudents() {
    if (students.empty()) {
        std::cout << "Não há nenhum estudante para vizualizar!\n";
        return;
    }

    for (auto const& entry : students) {
        std::cout << "ID: " << entry.first << "\n"
                  << "NOME: " << entry.second.name << "\n";
    }
}

void
assignBook(const std::string& id, const std::string& title) {
    books.emplace(id, Book{title, true});
}

void
editBook(const std::string& id, const std::string& newTitle) {
    auto book = books.find(id);

    if (book == books.end()) {
        std::cout << "O livro não existe!\n";
        return;
    }

    book->second.title = newTitle;
}

void
removeBook(const std::string& id) {
    auto book = books.find(id);

    if (book == books.end()) {
        std::cout << "O livro não existe!\n";
        return;
    }

    for (auto& entry : students) {
        
        auto borrowedIt = entry.second.borrowings.find(id);

        if (borrowedIt == entry.second.borrowings.end()) {
            continue;
        }
        entry.second.borrowings.erase(id);

    }

    books.erase(book);
}

void
visualizeBooks() {
    if (books.empty()) {
        std::cout << "Não existem livros para vizualizar!\n";
        return;
    }

    for (auto const& entry : books) {
        std::cout << "ID: " << entry.first << "\n"
                  << "TITULO: " << entry.second.title << "\n"
                  << "DISPONIVEL: " << (entry.second.available ? "Sim" : "Não") << "\n";
    }
}

void 
borrowBook(const std::string& bookId, const std::string& studentId) {
    auto student = students.find(studentId);

    if (student == students.end()) {
        std::cout << "O estudante não existe!\n";
        return;
    }
    
    if (student->second.borrowings.find(bookId) != student->second.borrowings.end()) {
        std::cout << "O estudante ja está com este livro!\n";
        return;
    }

    auto book = books.find(bookId);

    if (book == books.end()) {
        std::cout << "O livro não existe!\n";
        return;
    }

    if (book->second.available == false) {
        std::cout << "O livro ja foi emprestado!\n";
        return;
    }

    book->second.available = false;
    student->second.borrowings.insert(bookId);
}

void 
returnBook(const std::string& bookId, const std::string& studentId) {
    auto student = students.find(studentId);

    if (student == students.end()) {
        std::cout << "O estudante não existe!\n";
        return;
    }
    
    if (student->second.borrowings.find(bookId) == student->second.borrowings.end()) {
        std::cout << "O estudante não está com este livro!\n";
        return;
    }

    auto book = books.find(bookId);

    if (book == books.end()) {
        std::cout << "O livro não existe!\n";
        return;
    }

    book->second.available = true;
    student->second.borrowings.erase(bookId);
}

void
visualizeBorrowings() {
    for (auto& entry : students) {

        if (entry.second.borrowings.empty()) {
            continue;
        }

        std::cout << "ESTUDANTE: " << entry.second.name << "\n";
        
        for (auto const& id : entry.second.borrowings) {

            auto const& book = books.find(id);
            
            if (book == books.end()) {
                continue;
            }

            std::cout << "ID: " << book->first << "\n"
                      << "TITULO: " << book->second.title << "\n";
        }

    }
}

int main() {
    return 0;
}

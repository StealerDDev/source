#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

struct Book {
    string title = "";
    bool available = true;
};
struct Students {
    string name = "";
};


unordered_map<string, Book> books = {};
unordered_map<string, Students> students = {};
unordered_map<string, unordered_set<string>> borrowings = {};

void registerStudent(string name, string id) {
    students[id].name = name;
}

void editStudent(string newName, string id) {

    if (!students.count(id)) {
        cout << "Não foi possível achar o estudante!\n";
        return;
    }

    students[id].name = newName;
}

void removeStudent(string id) {

    auto student = students.find(id);

    if (student == students.end()) {
        cout << "Este aluno não existe!";
        return;
    }

    auto borrowIt = borrowings.find(id);
    if (borrowIt != borrowings.end()) {
        for (const auto& bookID : borrowIt->second) {
            auto book = books.find(bookID);
            if (book != books.end()) {
                book->second.available = true;
            }
        }
        borrowings.erase(borrowIt);
    }

    students.erase(student);

}

void visualizeStudents() {
    for (const auto &entry:students) {
        cout << "[" << entry.first << "]." << entry.second.name << "\n";
    };
}

void registerBook(string title, string id) {
    books[id] = {title, true};
}

void removeBook(string id) {

    auto book = books.find(id);
    if (book == books.end()) {
        cout << "O livro não exite!\n";
        return;
    }

    for (auto& [studentID, borrowed] : borrowings) {
        borrowed.erase(id);
        if (borrowed.empty()) {
            borrowings.erase(studentID);
        }
    }

    books.erase(book);

}

void editBook(string newTitle, string id) {

    if (!books.count(id)) {
        cout << "Não foi possível achar o livro!\n";
        return;
    }
    books[id].title = newTitle;

}

void visualizeBooks() {
    for (const auto &entry:books) {
        cout <<"\nID de Serie: " << entry.first 
            << "\nTitulo: " << entry.second.title
            << "\nDisponivel: " << (entry.second.available ? "Sim" : "Não")
            << "\n";
        
    };
}

void borrowBook(string bookID, string studentID) {

    auto book = books.find(bookID);
    if (book == books.end()) {
        cout << "Não foi possível achar o livro!\n";
        return;
    }

    auto student = students.find(studentID);
    if (student == students.end()) {
        cout << "Não foi possível achar o estudante!\n";
        return;
    }

    auto borrowIt = borrowings.find(studentID);

    if (borrowings[studentID].count(bookID)) {
        cout << "O estudante ja está com esse livro!\n";
        return;
    }

    if (!book->second.available) {
        cout << "O livro não está disponível!\n";
        return;
    }

    borrowings[studentID].insert(bookID);
    book->second.available = false;

}

void returnBook(string bookID, string studentID) {

    auto book = books.find(bookID);
    if (book == books.end()) {
        cout << "Não foi possível achar o livro!\n";
        return;
    }

    auto student = students.find(studentID);
    if (student == students.end()) {
        cout << "Não foi possível achar o estudante!\n";
        return;
    }

    auto borrowIt = borrowings.find(studentID);

    if (borrowIt == borrowings.end()) {
        cout << "O estudante nunca pegou livros!\n";
        return;
    };

    auto borrowedBook = borrowIt->second.find(bookID);
    
    if (borrowedBook == borrowIt->second.end()) {
        cout << "Este aluno não tem este livro!\n";
        return;
    }

    borrowings[studentID].erase(bookID);
    book->second.available = true;
    if (borrowings[studentID].size() <= 0) {
        borrowings.erase(studentID);
    }
}

void visualizeBorrowings() {
    for (const auto& entry : borrowings) {
        const auto& studentID = entry.first;
        
        const auto& student = students.find(studentID);
        if (student == students.end()) {
            continue;
        }
        cout << "Aluno [" << studentID << "] " << student->second.name << ":\n";

        for (const string& bookID : entry.second) {
            const auto& book = books.find(bookID);

            if (book == books.end()) {
                continue;
            }

            cout << "   - Livro [" << bookID << "] " << book->second.title << "\n";
        }
    }
}

int main() {
    int option;
    do {
        cout << "1. Cadastrar Aluno\n";
        cout << "2. Editar Aluno\n";
        cout << "3. Remover Aluno\n";
        cout << "4. Visualizar Alunos\n";
        cout << "5. Cadastrar Livro\n";
        cout << "6. Editar Livro\n";
        cout << "7. Remover Livro\n";
        cout << "8. Visualizar Livros\n";
        cout << "9. Emprestar Livro\n";
        cout << "10. Devolver Livro\n";
        cout << "11. Visualizar Emprestimos\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> option;

        string id, name, title, studentID;
        switch (option) {
            case 1:
                cout << "ID do aluno: ";
                cin >> id;
                cout << "Nome: ";
                cin.ignore();
                getline(cin, name);
                registerStudent(name, id);
                break;
            case 2:
                cout << "ID do aluno: ";
                cin >> id;
                cout << "Novo nome: ";
                cin.ignore();
                getline(cin, name);
                editStudent(name, id);
                break;
            case 3:
                cout << "ID do aluno: ";
                cin >> id;
                removeStudent(id);
                break;
            case 4:
                visualizeStudents();
                break;
            case 5:
                cout << "ID do livro: ";
                cin >> id;
                cout << "Titulo: ";
                cin.ignore();
                getline(cin, title);
                registerBook(title, id);
                break;
            case 6:
                cout << "ID do livro: ";
                cin >> id;
                cout << "Novo titulo: ";
                cin.ignore();
                getline(cin, title);
                editBook(title, id);
                break;
            case 7:
                cout << "ID do livro: ";
                cin >> id;
                removeBook(id);
                break;
            case 8:
                visualizeBooks();
                break;
            case 9:
                cout << "ID do livro: ";
                cin >> id;
                cout << "ID do aluno: ";
                cin >> studentID;
                borrowBook(id, studentID);
                break;
            case 10:
                cout << "ID do livro: ";
                cin >> id;
                cout << "ID do aluno: ";
                cin >> studentID;
                returnBook(id, studentID);
                break;
            case 11:
                visualizeBorrowings();
                break;
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida!\n";
        }
    } while (option != 0);

    return 0;
}

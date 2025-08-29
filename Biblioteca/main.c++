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

unordered_map<string, Book> books = {};
unordered_map<string, string> students = {};
unordered_map<string, unordered_set<string>> borrowings = {};

void registerStudent(string name, string id) {
    students[id] = name;
}

void editStudent(string newName, string id) {

    if (!students.count(id)) {
        return;
    }

    students[id] = newName;
}

void removeStudent(string id) {

    if (!students.count(id)) {
        return;
    }
    students.erase(id);

}

void visualizeStudents() {
    for (const auto &entry:students) {
        printf(
            "\n[%s]. %s",
            entry.first.c_str(),
            entry.second.c_str()
        );
    };
}

void registerBook(string title, string id) {
    books[id] = {title, true};
}

void removeBook(string id) {

    if (!books.count(id)) {
        return;
    }
    books.erase(id);

}

void editBook(string newTitle, string id) {

    if (!books.count(id)) {
        return;
    }
    books[id] = {newTitle};

}

void visualizeBooks() {
    for (const auto &entry:books) {
        printf(
            "\nID de serie: %s\nTitulo: %s\nDisponivel: %s",
            entry.first.c_str(),
            entry.second.title.c_str(),
            entry.second.available ? "Sim" : "Não"
        );
    };
}

void borrowBook(string bookID, string studentID) {

    if (!books.count(bookID)) {
        return;
    }
    if (!students.count(studentID)) {
        return;
    }
    if (!books[bookID].available) {
        return;
    }

    borrowings[studentID].insert(bookID);
    books[bookID].available = false;

}

void returnBook(string bookID, string studentID) {

    if (!books.count(bookID)) {
        return;
    }
    if (!students.count(studentID)) {
        return;
    }

    borrowings[studentID].erase(bookID);
    books[bookID].available = true;
}

void visualizeBorrowings() {
    for (const auto& entry : borrowings) {
        string studentID = entry.first;
        cout << "Aluno [" << studentID << "] " << students[studentID] << ":\n";

        for (const string& bookID : entry.second) {
            cout << "   - Livro [" << bookID << "] " << books[bookID].title << "\n";
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

        string id, name, title;
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
                cin >> name;
                borrowBook(id, name);
                break;
            case 10:
                cout << "ID do livro: ";
                cin >> id;
                cout << "ID do aluno: ";
                cin >> name;
                returnBook(id, name);
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
        cout << "\n";
    } while (option != 0);

    return 0;
}

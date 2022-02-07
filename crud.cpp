#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <fstream>
using std::ifstream;
using std::ofstream;

void titulo();
void adicionar();
void listar();
void editar();
void remover();
void carregar(ifstream&);
void salvar(ofstream&);

struct dado {
	string nome;
	double valor;
};

dado dados[100];

int top  = -1;

int main() {
	ifstream ifs;
	ofstream ofs;
	int opcao;
	
	titulo();
	
	do {
		cout << "Escolha uma opcao:\n"
		     << "\t1 - Adicionar" << "\t5 - Carregar\n"
			 << "\t2 - Listar" << "\t6 - Salvar\n"
			 << "\t3 - Editar" << "\t7 - Sair\n"
			 << "\t4 - Remover\n\n"			 
			 << "Sua escolha: ";
			 
		cin >> opcao;
		
		switch (opcao) {			
			case 1: adicionar(); break;
			case 2: listar(); break;
			case 3: editar(); break;
			case 4: remover(); break;
			case 5: carregar(ifs); break;
			case 6: salvar(ofs); break;
			default: cout << "Valor invalido";
		}
	} while (opcao != 7);	
}

void adicionar() {
	char opcao;
	
	do {
		string nome_;
		double valor_;
		
		cout << "Insira o nome: ";
		cin >> nome_;
		cout << "Insira o valor: ";
		cin >> valor_;	
		
		dados[++top].nome = nome_;		
		dados[top].valor = valor_;
		
		cout << "Deseja incluir mais algum dado? (S/N): ";		
		cin >> opcao;
	} while(opcao == 's' || opcao == 'S');
	
	system("cls");
	titulo();
}

void listar() {	
	system("cls");
	titulo();
	
	for (int i = 0; i <= top; i++) {
		cout << (i + 1) << " - " << dados[i].nome << ": " << dados[i].valor << "\n";
	}
	
	cout << "\n";
}

void editar() {
	char opcao;
	
	do {
		int indice;
		int atributo;
		char novoNome[16];
		double novoValor;
		
		listar();
		cout << "Insira o indice do dado a ser editado: ";
		cin >> indice;
		
		cout << "\nInsira o indice do atributo a ser editado\n\t1 - nome\n\t2 - valor\n\n"
			 << "Sua escolha: ";
		cin >> atributo;
		
		switch (atributo) {
			case 1: 
				cout << "Insira o novo nome: ";
				cin >> novoNome;
				dados[indice - 1].nome = novoNome;
				break;
			case 2:
				cout << "Insira o novo valor: ";
				cin >> novoValor;
				dados[indice - 1].valor = novoValor;
				break;
			default: cout << "Valor invalido";
		}
		
		listar();
		cout << "Deseja editar mais algum dado? (S/N): ";		
		cin >> opcao;
	} while (opcao == 's' || opcao == 'S');
	
	system("cls");
	titulo();
}

void remover() {
	char opcao;
	
	do {
		int indice;
		
		listar();
		cout << "Insira o indice do dado a ser removido: ";
		cin >> indice;
		
		for (int i = indice; i <= top; i++) {
			dados[i - 1] = dados[i];
		}
		
		top--;
		
		listar();
		cout << "Deseja incluir mais algum dado? (S/N): ";
		cin >> opcao;
	} while(opcao == 's' || opcao == 'S');
	
	system("cls");
	titulo();
}

void titulo() {
	cout << "***********CRUD************\n"
		 << "***Administre seus dados***\n\n";
}

void carregar(ifstream& in) {
	in.open("dados.dat");	
	
	if (!in) {
		cerr << "Arquivo nao encontrado\n";
		system("pause");
	} else {
		in >> top;
		
		for (int i = 0; i <= top; i++) {
			in >> dados[i].nome;
			in >> dados[i].valor;
		}
		
		in.close();
		
		listar();		
		system("pause");
	}
	
	system("cls");
	titulo();
}

void salvar(ofstream& out) {
	out.open("dados.dat");
	out << top << endl;
	
	for (int i = 0; i <= top; i++) {
		out << dados[i].nome << " " << dados[i].valor << endl;
	}
	
	out.close();
	system("cls");
	titulo();
}
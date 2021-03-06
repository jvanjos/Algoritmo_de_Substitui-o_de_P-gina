// Algoritmo_de_Substituição_de_Página.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<sstream>
#include<stdio.h>

//Estrutura dos dados de entrada

std::ifstream arquivo;
std::vector<int> dados; // vetor com todos os dados
std::vector<int> quadros; // vetor com os quadros que estão pra serem utilizados
std::vector<int> zero; // vetor nulo do tamanho de quadros que eh usado para zera-lo


// encontra o indice do dado menos recentimente usado, dentre os que estao nos quadros
int indiceMenRecUsado(int posição) {
	int minRec = 0;
	int tempo = 0;
	int indiceMin = 0;
	for (int i = 0; i < quadros.size(); i++) {
		for (int j = posição; j >= 0; j--) {
			if (dados[j] != quadros[i]) {
				tempo++;
			}
			else if (dados[j] == quadros[i])
				break;
		}
		if (minRec < tempo) {
			minRec = tempo;
			indiceMin = i;
		}
		tempo = 0;
	}
	return indiceMin;
}

//Encontra o indice do dado que demorará mais para ser usado dentre os que ja estão nos quadros
int indiceDemora(int posição) {
	int demora = 0;
	int maxDemora = 0;
	int indiceMax = 0;
	for (int i = 0; i < quadros.size(); i++) {
		for (int j = posição; j < dados.size(); j++) {
			if (dados[j] == quadros[i]) {
				if (maxDemora < demora) {
					maxDemora = demora;
					indiceMax = i;
				}
				demora = 0;
				break;
			}
			if (j + 1 == dados.size() && dados[j] != quadros[i]) {
				return i;
			}
			demora++;
		}
	}
	return indiceMax;
}

/* Procura se o dado se encontra em algum quadro se sim retorna 1, se nao retorna 0*/
bool procurarQuadros(int a) {								
	for (int j = 0; j < quadros.size(); j++) {
		if (a == quadros[j]) {
			return 1;
		}
	}
	return 0;
}

int fifo() {																//algoritmo de paginação First-In,First-Out
	int indice = 0;
	int faltas = 0;
	for (int i = 0; i < dados.size(); i++) {
		if (!procurarQuadros(dados[i])) {
			faltas++;
			quadros[indice] = dados[i];
			indice = (indice + 1) % (quadros.size());
		}
	}
	return faltas;
}

int otimo() {																//algoritmo ótimo de paginação
	int faltas = 0;
	int j = 0;
	for (int i = 0; i < dados.size(); i++) {
		if (quadros[quadros.size()-1] == -1) {
			if (!procurarQuadros(dados[i])) {
				faltas++;
				quadros[j] = dados[i];
				j++;
			}
		}
		else if (!procurarQuadros(dados[i])) {
			faltas++;
			quadros[indiceDemora(i)] = dados[i];
		}
	}
	return faltas;
}
int lru() {																	/*algoritmo de paginação Least Recently Used*/
	int faltas = 0;
	int j = 0;
	for (int i = 0; i < dados.size(); i++) {
		if (quadros[quadros.size() - 1] == -1) {
			if (!procurarQuadros(dados[i])) {
				faltas++;
				quadros[j] = dados[i];
				j++;
			}
		}
		else if (!procurarQuadros(dados[i])) {
			faltas++;
			quadros[indiceMenRecUsado(i)] = dados[i];
		}
	}
	return faltas;
}

int main()
{
	int numQuadros;
	std::string arquivoname;
	std::cout << "Digite o nome do arquivo(ex. exemplo.txt): ";
	std::cin >> arquivoname;
	arquivo.open(arquivoname.data());
	if (!arquivo.is_open()) {
		system("pause");
		return -1;
	}
	std::string stringer;

	std::getline(arquivo, stringer);
	quadros.resize(std::stoi(stringer));
	while (!arquivo.eof()) {
		std::getline(arquivo, stringer);
		dados.push_back(std::stoi(stringer));											// adiciona o dado no vetor dados
	}
	for (int i = 0; i < quadros.size(); i++) {
		quadros[i] = -1;
	}
	zero = quadros;
	printf("FIFO %d\n", fifo());
	quadros = zero;
	printf("OTM %d\n", otimo());
	quadros = zero;
	printf("LRU %d\n", lru());
	system("pause");
	return 0;
}



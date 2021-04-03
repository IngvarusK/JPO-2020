// Projekt.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
#include <sstream>
#include <algorithm>    // std::sort
#include <stdlib.h >
#include "classes.h"
#include <iomanip>

bool comparedistr(Candidate i1, Candidate i2);

int main(){

    std::vector<Candidate> cand;// odczyt wszytskich kandydatów
    std::vector<Citizen> citize;// odczyt wszystkich wyborcow
    std::map<std::string, int> winners;// odczyt wynikow wyborow

    std::string name;
    std::string surname;
    std::string pesel;
    int date;
    int month;
    int year;
    int vote_dystr;
    //candidates
    std::string party;
    std::string placeorigin;
    int district;
    //citizens
    bool voted;
    std::string ID;

    std::ifstream file("files/candidates.txt");

    //opening candidates
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream ss(line);
            ss >> name;
            ss >> surname;
            ss >> pesel;
            ss >> date;
            ss >> month;
            ss >> year;
            ss >> vote_dystr;
            ss >> party;
            ss >> placeorigin;
            ss >> district;
            cand.push_back(Candidate(name, surname, pesel, date, month, year, vote_dystr, party, placeorigin, district));
        }
        std::cout << "Znaleziono " << cand.size() << " kandydatow!" << std::endl;
        //nowe
        file.close(); // koniecznie pamiętajmy o zamknięciu otwartego pliku
    }
    else {
        std::cout << "Nie udalo sie odczytac kandydatow" << std::endl;
    }
    std::ifstream file2("files/citizens.txt");

    //opening citizens
    if (file2.is_open()) {
        std::string line;

        while (std::getline(file2, line)) {
            std::istringstream ss(line);
            ss >> name;
            ss >> surname;
            ss >> pesel;
            ss >> date;
            ss >> month;
            ss >> year;
            ss >> vote_dystr;
            ss >> voted;
            ss >> ID;
            citize.push_back(Citizen(name, surname, pesel, date, month, year, vote_dystr, voted, ID));
        }
        std::cout << "Znaleziono " << citize.size() << " wyborcow!" << std::endl;
        file2.close();
    }
    else {
        std::cout << "Nie udalo sie odczytac obywateli" << std::endl;
    }


    std::string menu;

    system("cls");
    while (1) {
        std::cout << "Witaj w menu!" << std::endl;
        std::cout << "Wpisz 'dodaj kandydata' aby dodac nowego kandydata" << std::endl;
        std::cout << "Wpisz 'pokaz kandydatow' aby zobaczyc obecnych kandydatow" << std::endl;
        std::cout << "Wpisz 'glosuj' aby zaglosowac" << std::endl;
        std::cout << "Wpisz 'oblicz wyniki' aby wybrac posla!" << std::endl;//nowe
        std::cout << "Wpisz 'exit' aby wyjsc z programu" << std::endl << std::endl;
        std::getline(std::cin, menu);
        system("cls");
        //-------------------------------dodaj kandydata-------------------------------
        if (menu == "dodaj kandydata") {
            std::cout << "Wpisz 'wroc' aby wyjsc z podmenu" << std::endl << std::endl;
            while (1) {
                std::cout << "Podaj imie i nazwisko: ";
                std::cin >> name;
                if (name == "wroc") break;
                std::cin >> surname;
                std::cin >> pesel;
                std::cout << "Podaj dzien urodzenia: ";
                std::cin >> date;
                std::cout << "Podaj miesiac urodzenia: ";
                std::cin >> month;
                std::cout << "Podaj rok urodzenia: ";
                std::cin >> year;
                std::cout << "Podaj okreg zamieszkania: ";
                std::cin >> vote_dystr;
                std::cout << "Podaj przynaleznosc partyjna ";
                std::cin >> party;
                std::cout << "Podaj miejsce urodzenia ";
                std::cin >> placeorigin;
                std::cout << "Podaj okreg kandydowania: ";
                std::cin >> district;
            }
        }
        //-------------------------------pokaz kandydatow-------------------------------
        else if (menu == "pokaz kandydatow") {
            std::sort(cand.begin(), cand.end(), comparedistr);
            std::cout << "Wpisz 'wroc' aby wyjsc z podmenu" << std::endl << std::endl;
            for (unsigned int i = 0; i < cand.size(); i++) {
                std::cout << cand[i].get_fname() << " " << cand[i].get_surname() << " partia: "
                    << cand[i].get_party() << " Okreg: " << cand[i].get_district() << std::endl;
            }
            std::cin >> menu;
            if (name == "wroc") break;
        }
        //-----------------------------------glosuj----------------------------------
        else if (menu == "glosuj") {
            system("cls");
            std::sort(cand.begin(), cand.end(), comparedistr);
            std::cout << "Wpisz 'wroc' aby wyjsc z podmenu" << std::endl << std::endl;
            while (1) {
                int retur = 0;
                std::cout << "Podaj numer swojego dowodu osobistego: " << std::endl;
                std::cin >> ID;
                if (ID == "wroc") break;
                for (unsigned int i = 0; i < (citize.size()+1); i++) {
                    if (i >= citize.size()) {
                        std::cout << "Podaj poprawny numer dowodu oosbistego!" << std::endl;
                    }
                    else {
                        if (citize[i].get_ID() == ID) {
                            std::cout << std::endl << "Witaj " << citize[i].get_fname() << std::endl;
                            std::cout << "Znajdujesz sie w okregu wyborczym nr." << citize[i].get_vote_district() << std::endl;
                            if (citize[i].get_voted()) {
                                std::cout << "Juz zagloswales/as!" << std::endl;
                                break;
                            }
                            else {
                                std::cout << std::endl << "Kandydaci:" << std::endl;
                                std::map<int, std::string> temp;// <num,pesel>
                                int num_cand = 0;
                                for (unsigned int j = 0; j < cand.size(); j++) {
                                    if (citize[i].get_vote_district() == cand[j].get_district()) {
                                        temp[num_cand] = cand[j].get_pesel();
                                        std::cout << num_cand+1 << ". " << cand[j].get_fname() << " " << cand[j].get_surname() << ", partia: "
                                            << cand[j].get_party() << ", Urodzony w " << cand[j].get_placeorigin() << ", Okreg: " << cand[j].get_district() << std::endl;
                                        num_cand++;
                                    }
                                }
                                while (1) {
                                    std::cout << "Na kogo zaglosujesz? (podaj numer)" << std::endl;
                                    std::cin >> menu;
                                    if (ID == "wroc") break;
                                    num_cand = stoi(menu);
                                    
                                    if (temp.find(num_cand-1) != temp.end()) {
                                        std::cout << "Zaglosowano!!!" << std::endl;
                                        std::string pesl = temp[num_cand - 1];
                                        citize[i].set_voted(1);
                                        if (winners.find(pesl) == winners.end()) {
                                            winners[pesl] = 1;
                                        }
                                        else {
                                            winners[pesl]++;
                                        }
                                        //-----------------
                                        //for (std::pair<std::string, int > element : winners) {
                                        //    std::string word = element.first;
                                        //    int count = element.second;
                                        //    std::cout << word << " :: " << count << std::endl;
                                        //}
                                        //---------------------
                                        retur = 1;
                                        break;
                                    }
                                    else {
                                        std::cout << "Podaj poprawny numer!" << std::endl;
                                        
                                    }
                                    
                                }
                            }
                        }
                    }
                    if (retur) break;
                }
                while (1) {
                    std::cout << std::endl << "Wpisz 'wroc' aby wyjsc z podmenu " << std::endl;
                    std::cin >> menu;
                    if (menu == "wroc") break;
                }
            }
        }
        //--------------------------------oblicz wyniki-------------------------------
        else if (menu == "oblicz wyniki") {
            std::sort(cand.begin(), cand.end(), comparedistr);

            std::fstream plik3;
            plik3.open("results.txt", std::ios::out | std::ios::trunc);

            for (int i = 0; i < cand[cand.size() - 1].get_district(); i++) {
                std::cout << "W okregu nr." << (i+1) << " osiagnieto nastepujace wyniki:" <<std::endl;
                std::vector<Votes> votes;
                int total_votes = 0;
                int freq = 0;
                for (unsigned int j = 0; j < cand.size(); j++) {
                    int vote = 0;
                    std::string name;
                    std::string surname;
                    if (cand[j].get_district() == (i+1)) {
                        name = cand[j].get_fname();
                        surname = cand[j].get_surname();
                        if (winners.find(cand[j].get_pesel()) == winners.end()) {
                            vote = 0;
                        }
                        else {
                            vote = winners[cand[j].get_pesel()];
                            total_votes += vote;
                        }
                        votes.push_back(Votes(name, surname, vote));
                    }
                }
                for (unsigned int j = 0; j < citize.size(); j++) {
                    if (citize[j].get_vote_district() == (i + 1)) freq++;
                }
                for (unsigned int j = 0; j < votes.size(); j++) {
                    std::cout << votes[j].get_fname() << " " << votes[j].get_surname() << " " << votes[j].get_votes() << std::endl;
                }
                // wyswietlanie wynikow
                float fr = 100 * (float)total_votes / (float)freq;
                std::cout << "Oddanno glosow " << total_votes << " z " << freq << " wszytskich mozliwych" << std::endl;
                std::cout << std::setprecision(4) << "Frekwencja: " << fr << "%" << std::endl;
                std::cout << "------------------------------------------------" << std::endl << std::endl;

                //zapis wynikow
                if (plik3.good())
                {
                    plik3 << "W okregu nr." << (i + 1) << " osiagnieto nastepujace wyniki:\n";
                    for (unsigned int j = 0; j < votes.size(); j++) {
                        plik3 << votes[j].get_fname() << " " << votes[j].get_surname() << " " << votes[j].get_votes() << "\n";
                    }
                    plik3 << "Oddanno glosow " << total_votes << " z " << freq << " wszytskich mozliwych\n";
                    plik3 << "Frekwencja: " << fr << "%\n";
                    plik3 << "------------------------------------------------\n\n";
                }
                else std::cout << "Nie udalo sie odczytac zapisac wynikow" << std::endl;
            }
            plik3.close();
        }
        //-----------------------------------wyjscie----------------------------------
        else if (menu == "exit") break;
        else if (menu.size()) std::cout << "Wpisz poprawna komende" << std::endl;
    }
    return 0;
}

//funckja do sortowania kandydatow po kolejnosci okregow
bool comparedistr(Candidate i1, Candidate i2){
    return (i1.get_district() < i2.get_district());
}

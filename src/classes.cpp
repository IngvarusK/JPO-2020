#include "classes.h"

//------------------------------------------class Person------------------------------------------
Person::Person(std::string fname = "default", std::string surname = "default", std::string pesel = "default",
    int day = 1, int month = 1, int year = 1, int vote_dystr = 0)
    : m_fname{ fname }, m_surname{ surname }, m_pesel{ pesel }, m_dayofbirth{ day },
    m_monthofbirth{ month }, m_yeafofbirth{ year }, m_vote_district{ vote_dystr }{
}

std::string Person::get_fname(void) const { return m_fname; }
std::string Person::get_surname(void) const { return m_surname; }
std::string Person::get_pesel(void) const { return m_pesel; }
int Person::get_vote_district(void) const { return m_vote_district; }

std::string Person::get_birth(void) const{
    std::string day = std::to_string(m_dayofbirth);
    std::string month = std::to_string(m_monthofbirth);
    std::string year = std::to_string(m_yeafofbirth);
    return day + "." + month + "." + year;
}

//-----------------------------------------class Candidate-----------------------------------------
Candidate::Candidate(std::string fname, std::string surname, std::string pesel, int day, int month, int year,
    int vote_dystr, std::string party, std::string placeorigin, int district)
    : Person(fname, surname, pesel, day, month, year, vote_dystr), m_party(party), m_placeorigin(placeorigin), m_district(district) {
}
std::string Candidate::get_party(void) const { return m_party; }
std::string Candidate::get_placeorigin(void) const { return m_placeorigin; }
int Candidate::get_district(void) const { return m_district; }

//------------------------------------------class Citizen------------------------------------------
Citizen::Citizen(std::string fname, std::string surname, std::string pesel, int day, int month, int year,
    int vote_dystr, bool voted, std::string ID)
    : Person(fname, surname, pesel, day, month, year, vote_dystr), m_voted(voted), m_ID(ID) {
}
bool Citizen::get_voted(void) const { return m_voted; }
void Citizen::set_voted(bool voted) { m_voted = voted; }
std::string Citizen::get_ID(void) const { return m_ID; }

//-------------------------------------------class voted-------------------------------------------
Votes::Votes(std::string fname, std::string surname, int votes)
    : m_fname{ fname }, m_surname{ surname }, m_votes{ votes }{
}
std::string Votes::get_fname(void) const { return m_fname; }
std::string Votes::get_surname(void) const { return m_surname; }
int Votes::get_votes(void) const { return m_votes; }
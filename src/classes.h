#pragma once

#include <iostream>
#include <string>

class Person {
private:
    std::string m_fname;
    std::string m_surname;
    std::string m_pesel;
    int m_dayofbirth;
    int m_monthofbirth;
    int m_yeafofbirth;
    int m_vote_district;
public:
    Person(std::string , std::string, std::string,
        int, int, int, int);
    std::string get_fname(void) const;
    std::string get_surname(void) const;
    std::string get_pesel(void) const;
    int get_vote_district(void) const;
    std::string get_birth(void) const;
};

class Candidate : public Person {
private:
    std::string m_party;
    std::string m_placeorigin;
    int m_district;
public:
    Candidate(std::string, std::string, std::string, int, int, int,
        int, std::string, std::string, int);
    std::string get_party(void) const;
    std::string get_placeorigin(void) const;
    int get_district(void) const;
};

class Citizen : public Person {
private:
    bool m_voted;
    std::string m_ID;
public:
    Citizen(std::string, std::string, std::string, int, int, int,
        int, bool, std::string);
    bool get_voted(void) const;
    void set_voted(bool);
    std::string get_ID(void) const;
};

class Votes {
private:
    std::string m_fname;
    std::string m_surname;
    int m_votes;
public:
    Votes(std::string, std::string, int);
    std::string get_fname(void) const;
    std::string get_surname(void) const;
    int get_votes(void) const;
};
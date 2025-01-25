#pragma once
#include <string>
class Person
{
private:
    int yearOfBirth;
    std::string firstName;
    std::string lastName;
    float height;
    float weight;

public:

    Person() : yearOfBirth(0), firstName(""), lastName(""), height(0), weight(0) {}

    Person(int n) : yearOfBirth(n), firstName(""), lastName(""), height(0), weight(0) {}

    Person(int yearOfBirth, const std::string& firstName, const std::string& lastName, float height, float weight)
        : yearOfBirth(yearOfBirth), firstName(firstName), lastName(lastName), height(height), weight(weight) {}

    Person(const Person& other)
        : yearOfBirth(other.yearOfBirth), firstName(other.firstName), lastName(other.lastName), height(other.height), weight(other.weight) {}

    int GetYearOfBirth() const { return this->yearOfBirth; }

    std::string GetFirstname() const { return this->firstName; }

    std::string GetLastname() const { return this->lastName; }

    std::string GetFullName() const { return this->firstName + " " + this->lastName; }

    int GetWeight() const { return this->weight; }

    int GetHeight() const { return this->height; }

    struct YearOfBirthComparator
    {
        bool operator()(const Person& a, const Person& b) const
        {
            return a.yearOfBirth < b.yearOfBirth;
        }
    };

    struct LastnameComparator
    {
        bool operator()(const Person& a, const Person& b) const
        {
            return a.lastName < b.lastName;
        }
    };

    struct FirstnameComparator
    {
        bool operator()(const Person& a, const Person& b) const
        {
            return a.firstName < b.firstName;
        }
    };

    struct WeightComparator
    {
        bool operator()(const Person& a, const Person& b) const
        {
            return a.weight < b.weight;
        }
    };

    struct HeightComparator
    {
        bool operator()(const Person& a, const Person& b) const
        {
            return a.height < b.height;
        }
    };

    bool operator==(const Person& other) const
    {
        return (this->yearOfBirth == other.yearOfBirth &&
            this->firstName == other.firstName &&
            this->lastName == other.lastName &&
            this->height == other.height &&
            this->weight == other.weight);
    }

    bool operator<(const Person& other) const 
    {
        return yearOfBirth < other.yearOfBirth;
    }
};
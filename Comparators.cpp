
#include "Person.h"

bool compInt(int const & first, int const & second)
{
    return (first < second);
}

bool compPerson(Person const & first, Person const & second)
{
    return first.GetYearOfBirth() <  second.GetYearOfBirth();
}
#include "examDetails.h"
#include <iostream>
#include <string>

/* 
* @brief A boolean fucntion that checks if a given number is integer
*
* @param dbl
*/
static bool isInteger(double dbl)
{
    return (std::abs(dbl - (int)dbl) < DOUBLE_COMPARE);
}

/* 
* @brief A boolean fucntion that checks if a given time includes half an hour
*
* @param time
*/
static bool isHalfHour(double time)
{
    return (std::abs(time - HALF_AN_HOUR - (int)time) < DOUBLE_COMPARE);
}

ExamDetails::ExamDetails(double course_number, double month, double day, double time, double length, std::string link) :
    course_number(course_number),
    month(month),
    day(day),
    time(time),
    length(length),
    link(link)
{
    if(month <= 0 || month > 12 || !isInteger(month) ||
       (day <= 0 || day > 30) || !isInteger(day))
    {
        throw InvalidDateException();
    }
    if(time < 0 || time > 24 || (!isInteger(time) && !isHalfHour(time)))
    {
        throw InvalidTimeException();
    }
    if(std::abs(length - (int)length) > DOUBLE_COMPARE)
    {
        throw InvalidArgsException();
    }
}


ExamDetails::~ExamDetails() {}  //there's nothing to be deleted really

ExamDetails::ExamDetails(const ExamDetails &exam) :
    course_number(exam.course_number),
    month(exam.month),
    day(exam.day),
    time(exam.time),
    length(exam.length),
    link(exam.link)
{
}

ExamDetails& ExamDetails::operator=(const ExamDetails &exam){
    if(this == &exam)
    {
        return *this;
    }
    course_number = exam.course_number;
    month = exam.month;
    day = exam.day;
    time = exam.time;
    length = exam.length;
    link = exam.link; 

    return *this;
}

std::string ExamDetails::getLink() const {
    return this->link;
}

void ExamDetails::setLink(const std::string& new_link) {
    this->link = new_link;
}

int ExamDetails::operator-(const ExamDetails& exam) {

    int date_in_days1 = this->month * 30 + this->day;
    int date_in_days2 = exam.month * 30 + exam.day;

    return date_in_days1 - date_in_days2;
}

bool ExamDetails::operator<(const ExamDetails& exam) const {
    if(this->month != exam.month)
    {
        return (this->month < exam.month);
    }
    if(this->day != exam.day)
    {
        return (this->day < exam.day);
    }
    if(this->time != exam.time)
    {
        return (this->time < exam.time);
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const ExamDetails& exam){
    os << "Course Number: " << (int)exam.course_number << std::endl;
    os << "Time: " << (int)exam.day << "." << exam.month;
    if(isHalfHour(exam.time))
    {
        os << " at " << (int)(exam.time) << ":30" << std::endl;
    }
    else
    {
        os << " at " << (int)(exam.time) << ":00" << std::endl;
    }
    os << "Duration: " << (int)exam.length << ":00" << std::endl;
    os << "Zoom Link: " << exam.link << std::endl;

    return os;
}


ExamDetails ExamDetails::makeMatamExam(){
    return ExamDetails(234124, 7, 28, 13.0, 3, "https://tinyurl.com/59hzps6m");
}


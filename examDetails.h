#ifndef EXAMDETAILS_EXAMDETAILS_H
#define EXAMDETAILS_EXAMDETAILS_H
#include <iostream>
#include <string>
#include <cmath>

#define DOUBLE_COMPARE std::pow(10,-6)
#define HALF_AN_HOUR 0.5

class ExamDetails {
private:
    double course_number;
    double month;
    double day;
    double time;
    double length;
    std::string link;

public:
    class InvalidDateException {};
    class InvalidTimeException {};
    class InvalidArgsException {};

    /* 
     * @brief the constructor method of ExamDetails
     *
     * @param course_number
     * @param month
     * @param day
     * @param time
     * @param length
     * @param link 
     */
    ExamDetails(double course_number, double month, double day, double time, double length, std::string link = "");
    
    /* 
     * @brief the destructor method of ExamDetails
     */
    ~ExamDetails();

    /* 
     * @brief the copy constructor method of ExamDetails
     *
     * @param exam
     */
    ExamDetails(const ExamDetails& exam);

    /* 
     * @brief operator= of ExamDetails
     *
     * @param exam
     */
    ExamDetails& operator=(const ExamDetails& exam);

    /* 
     * @brief fucntion that gets the exam link of ExamDetails
     */
    std::string getLink() const;

    /* 
     * @brief fucntion that sets the exam link of ExamDetails
     *
     * @param new_link
     */
    void setLink(const std::string& new_link);

    /* 
     * @brief operator- of ExamDetails, finds the difference bewteen two given exams
     *
     * @param exam
     * 
     * @return difference between the two exams
     */    
    int operator-(const ExamDetails& exam);

    /* 
     * @brief operator< of ExamDetails
     *
     * @param exam
     * 
     * @return true if first exam occurs before second, otherwise false
     */
    bool operator<(const ExamDetails& exam) const;

    /* 
     * @brief operator<< of ExamDetails, overload of std::operator<<
     *
     * @param os
     * @param exam
     */
    friend std::ostream& operator<<(std::ostream& os, const ExamDetails& exam);

    /* 
     * @brief static constructor of ExamDetails - makes an exam with specific values
     */
    static ExamDetails makeMatamExam();

};

#endif //EXAMDETAILS_EXAMDETAILS_H

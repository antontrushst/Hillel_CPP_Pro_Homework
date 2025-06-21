#include "calculatormodel.h"

calculatormodel::calculatormodel(QString Celsius_val, QString Fahrenheit_val, QString Kelvin_val, QObject *parent)
    : field_Celsius(Celsius_val), field_Fahrenheit(Fahrenheit_val), field_Kelvin(Kelvin_val), QObject{parent}
{}

QString calculatormodel::get_field_Celsius()
{
    return this->field_Celsius;
}

void calculatormodel::set_field_Celsius(QString Celsius_val)
{
    this->field_Celsius = Celsius_val;
    emit this->field_Celsius_changed(this->field_Celsius);
}

QString calculatormodel::get_field_Fahrenheit()
{
    return this->field_Fahrenheit;
}

void calculatormodel::set_field_Fahrenheit(QString Fahrenheit_val)
{
    this->field_Fahrenheit = Fahrenheit_val;
    emit this->field_Fahrenheit_changed(this->field_Fahrenheit);
}

QString calculatormodel::get_field_Kelvin()
{
    return this->field_Kelvin;
}

void calculatormodel::set_field_Kelvin(QString Kelvin_val)
{
    this->field_Kelvin = Kelvin_val;
    emit this->field_Kelvin_changed(this->field_Kelvin);
}

#include "calculatorcontroller.h"

calculatorcontroller::calculatorcontroller(calculatormodel* model, QObject *parent)
    : model(model), QObject{parent}
{}

// void calculatorcontroller::convert(QString what_field)
// {
//     if(what_field == "Celsius")
//     {
//         this->model->set_field_Fahrenheit(QString::number(model->get_field_Celsius().toDouble() * 1.8 + 32));
//         this->model->set_field_Kelvin(QString::number(model->get_field_Celsius().toDouble() + 273.15));
//     }
//     else if(what_field == "Fahrenheit")
//     {
//         this->model->set_field_Celsius(QString::number((model->get_field_Fahrenheit().toDouble() - 32) / 1.8));
//         this->model->set_field_Kelvin(QString::number((model->get_field_Fahrenheit().toDouble() + 459.67) / 1.8));
//     }
//     else if(what_field == "Kelvin")
//     {
//         this->model->set_field_Celsius(QString::number(model->get_field_Kelvin().toDouble() - 273.15));
//         this->model->set_field_Fahrenheit(QString::number(model->get_field_Kelvin().toDouble() * 1.8 - 459.67));
//     }
// }

QString calculatorcontroller::get_field_Celsius()
{
    return this->model->get_field_Celsius();
}

void calculatorcontroller::set_field_Celsius(QString Celsius_val)
{
    this->model->set_field_Celsius(Celsius_val);
    this->model->set_field_Fahrenheit(QString::number(model->get_field_Celsius().toDouble() * 1.8 + 32));
    this->model->set_field_Kelvin(QString::number(model->get_field_Celsius().toDouble() + 273.15));
}

QString calculatorcontroller::get_field_Fahrenheit()
{
    return this->model->get_field_Fahrenheit();
}

void calculatorcontroller::set_field_Fahrenheit(QString Fahrenheit_val)
{
    this->model->set_field_Fahrenheit(Fahrenheit_val);
    this->model->set_field_Celsius(QString::number((model->get_field_Fahrenheit().toDouble() - 32) / 1.8));
    this->model->set_field_Kelvin(QString::number((model->get_field_Fahrenheit().toDouble() + 459.67) / 1.8));
}

QString calculatorcontroller::get_field_Kelvin()
{
    return this->model->get_field_Kelvin();
}

void calculatorcontroller::set_field_Kelvin(QString Kelvin_val)
{
    this->model->set_field_Kelvin(Kelvin_val);
    this->model->set_field_Celsius(QString::number(model->get_field_Kelvin().toDouble() - 273.15));
    this->model->set_field_Fahrenheit(QString::number(model->get_field_Kelvin().toDouble() * 1.8 - 459.67));
}

#ifndef CALCULATORCONTROLLER_H
#define CALCULATORCONTROLLER_H

#include <QObject>

#include "calculatormodel.h"

class calculatorcontroller : public QObject
{
    Q_OBJECT
public:
    explicit calculatorcontroller(calculatormodel* model, QObject *parent = nullptr);
    // Q_INVOKABLE void convert(QString what_field);
    Q_INVOKABLE QString get_field_Celsius();
    Q_INVOKABLE void set_field_Celsius(QString Celsius_val);
    Q_INVOKABLE QString get_field_Fahrenheit();
    Q_INVOKABLE void set_field_Fahrenheit(QString Fahrenheit_val);
    Q_INVOKABLE QString get_field_Kelvin();
    Q_INVOKABLE void set_field_Kelvin(QString Kelvin_val);

private:
    calculatormodel* model;
};

#endif // CALCULATORCONTROLLER_H

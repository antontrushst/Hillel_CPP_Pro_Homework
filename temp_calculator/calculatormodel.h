#ifndef CALCULATORMODEL_H
#define CALCULATORMODEL_H

#include <QObject>

class calculatormodel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString field_Celsius READ get_field_Celsius WRITE set_field_Celsius NOTIFY field_Celsius_changed)
    Q_PROPERTY(QString field_Fahrenheit READ get_field_Fahrenheit WRITE set_field_Fahrenheit NOTIFY field_Fahrenheit_changed)
    Q_PROPERTY(QString field_Kelvin READ get_field_Kelvin WRITE set_field_Kelvin NOTIFY field_Kelvin_changed)
public:
    explicit calculatormodel(QString Celsius_val, QString Fahrenheit_val, QString Kelvin_val, QObject *parent = nullptr);

    QString get_field_Celsius();
    void set_field_Celsius(QString Celsius_val);

    QString get_field_Fahrenheit();
    void set_field_Fahrenheit(QString Fahrenheit_val);

    QString get_field_Kelvin();
    void set_field_Kelvin(QString Kelvin_val);

signals:
    void field_Celsius_changed(QString Celsius_val);
    void field_Fahrenheit_changed(QString Fahrenheit_val);
    void field_Kelvin_changed(QString Kelvin_val);

private:
    QString field_Celsius;
    QString field_Fahrenheit;
    QString field_Kelvin;
};

#endif // CALCULATORMODEL_H

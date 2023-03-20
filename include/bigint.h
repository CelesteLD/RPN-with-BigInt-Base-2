/**
 * @file bigint.h
 * @author Celeste Luis Díaz (alu0101321660@ull.edu.es)
 * @brief Clase BigInt<Base> diseñada para la segunda práctica de 
 * Algoritmos y Estructuras de Datos Avanazadas 2022-2023
 * 
 *         ** Impementación de la especialización para la base 2
 *         ** Cambios de tipo incluidos.
 *         ** Se realizan las operaciones mediante una calculadora RPN
 * 
 * @version 0.1
 * @date 2023-03-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
 
#include <iostream>
#include <vector>
#include <regex>
#include <math.h>

template <size_t Base>
class BigInt;

// Flow Operators
template <size_t Base> std::ostream &operator<<(std::ostream &, const BigInt<Base> &);
template <size_t Base> std::istream &operator>>(std::istream &, BigInt<Base> &);

// Comparison Operators
template <size_t Base> bool operator==(const BigInt<Base>&, const BigInt<Base>&);
template <size_t Base> bool operator>(const BigInt<Base>&, const BigInt<Base>&);
template <size_t Base> bool operator<(const BigInt<Base>&, const BigInt<Base>&);

// Arithmetic Operators
template <size_t Base> BigInt<Base> operator+(const BigInt<Base>&, const BigInt<Base>&);
template <size_t Base> BigInt<Base> operator/(const BigInt<Base>&, const BigInt<Base>&);

// Pow
template <size_t Base> BigInt<Base> pow(const BigInt<Base>&, const BigInt<Base>&);

// Espcialización de la clase BigInt para la base 2

template <> std::ostream &operator<<(std::ostream &, const BigInt<2> &);
template <> std::istream &operator>>(std::istream &, BigInt<2> &);
template <> bool operator==(const BigInt<2>&, const BigInt<2>&);
template <> bool operator>(const BigInt<2>&, const BigInt<2>&);
template <> bool operator<(const BigInt<2>&, const BigInt<2>&);
template <> BigInt<2> operator+(const BigInt<2>&, const BigInt<2>&);
template <> BigInt<2> operator/(const BigInt<2>&, const BigInt<2>&);
template <> BigInt<2> pow(const BigInt<2>&, const BigInt<2>&);

template <>
class BigInt<2> {

    private:
        std::vector<bool> digits_;
        int sign_ = 0;

    public:
        BigInt(long value = 0);
        BigInt(std::string& value);
        BigInt(const char* value);
        BigInt(const BigInt<2>& value);
        BigInt(std::vector<bool> digits);
        ~BigInt() = default;

        // Asignment Operators
        BigInt<2>& operator=(const BigInt<2>& num);

        // Flow Operators
        friend std::ostream &operator<<(std::ostream &, const BigInt<2> &);
        friend std::istream &operator>>(std::istream &, BigInt<2> &);

        // Accesor Methods
        int sign() const; 
        char operator[](int) const; 
        std::vector<bool> digits() const;
        void setSign(int sign);
        void setDigits(std::vector<bool> digits);
        void setPosition(int position, bool value);

        // Comparison Operators
        friend bool operator==(const BigInt<2>& num1, const BigInt<2>& num2);
        bool operator!=(const BigInt<2>& num) const;
        friend bool operator>(const BigInt<2>& num1, const BigInt<2>& num2);
        bool operator>=(const BigInt<2>& num) const;
        friend bool operator< (const BigInt<2>& num1, const BigInt<2>& num2);
        bool operator<=(const BigInt<2>& num) const;

        // Increment and Decrement Operators
        BigInt<2>& operator++(); 
        BigInt<2> operator++(int value); 
        BigInt<2>& operator--(); 
        BigInt<2> operator--(int value); 

        // Arithmetic Operators
        friend BigInt<2> operator+(const BigInt<2>&, const BigInt<2>&);
        BigInt<2> operator-(const BigInt<2> &) const;
        BigInt<2> operator-() const;
        BigInt<2> operator*(const BigInt<2>&) const;
        friend BigInt<2> operator/(const BigInt<2>&, const BigInt<2>&);
        BigInt<2> operator%(const BigInt<2>&) const;

        // Pow
        friend BigInt<2> pow(const BigInt<2>&, const BigInt<2>&);

        BigInt<2> complementTwo() const;
        BigInt<2> abs() const;

        template<size_t Base> operator BigInt<Base>() const;

        //ToString
        std::string toString() const;

        // Binary to Octal
        std::string binaryToOctal(std::string binaryStr);
};

BigInt<2>::BigInt(long value) {}

BigInt<2>::BigInt(std::string& value) {

    if (value[0] == '0') {
        sign_ = 0;
        value = value.substr(1);
    } else {
        sign_ = 1;
        value = value.substr(1);
    }

    for (int i = value.size() - 1; i >= 0; i--) {
        if (value[i] == '0') {
            digits_.push_back(false);
        } else {
            digits_.push_back(true);
        }
    }

}

BigInt<2>::BigInt(const char* value) {

    if (value[0] == '0') {
        sign_ = 0;
        // Eliminar esa posicion
        value = value + 1;
    } else {
        sign_ = 1;
        // Eliminar esa posicion
        value = value + 1;
    }

    for (int i = strlen(value) - 1; i >= 0; i--) {
        if (value[i] == '0') {
            digits_.push_back(false);
        } else {
            digits_.push_back(true);
        }
    }
}

BigInt<2>::BigInt(const BigInt<2>& value) {
    digits_ = value.digits_;
    sign_ = value.sign_;
}

// Asignment Operators
BigInt<2>& BigInt<2>::operator=(const BigInt<2>& num) {
    digits_ = num.digits_;
    sign_ = num.sign_;

    return *this;
}

// Accesor Methods
int BigInt<2>::sign() const {
    return sign_;
}

char BigInt<2>::operator[](int index) const {
    return digits_[index];
}

std::vector<bool> BigInt<2>::digits() const {
    return digits_;
}

void BigInt<2>::setSign(int sign) {
    sign_ = sign;
}

void BigInt<2>::setDigits(std::vector<bool> digits) {
    digits_ = digits;
}

void BigInt<2>::setPosition(int position, bool value) {
    digits_[position] = value;
}

// Comparison Operators
bool operator==(const BigInt<2>& num1, const BigInt<2>& num2) {

    if (num1.sign_ != num2.sign_) {
        return false;
    }

    if (num1.digits_.size() != num2.digits_.size()) {
        for (int i = 0; i < num1.digits_.size(); i++) {
            for (int j = 0; j < num2.digits_.size(); j++) {
                if (num1.digits_[i] == false && num2.digits_[j] == false) {
                    return true;
                }
            }
        }
        return false;
    }

    for (int i = 0; i < num1.digits_.size(); i++) {
        if (num1.digits_[i] != num2.digits_[i]) {
            return false;
        }
    }

    return true;
}

bool BigInt<2>::operator!=(const BigInt<2>& num) const {
    return !(*this == num);
}

bool operator>(const BigInt<2>& num1, const BigInt<2>& num2) {

    // Comprobar que los dos números tengan el mismo número de dígitos
    int size1 = num1.digits_.size();
    int size2 = num2.digits_.size();

    BigInt<2> aux1 = num1;
    BigInt<2> aux2 = num2;

    if (size1 > size2) {
        for (int i = 0; i < size1 - size2; i++) {
            aux2.digits_.push_back(false);
        }
    } else if (size1 < size2) {
        for (int i = 0; i < size2 - size1; i++) {
            aux1.digits_.push_back(false);
        }
    }

    // Comprobar el signo
    if (num1.sign_ == 1 && num2.sign_ == 0) {
        return true;
    } else if (num1.sign_ == 0 && num2.sign_ == 1) {
        return false;
    }

    // Comprobar los dígitos
    for (int i = aux1.digits_.size() - 1; i >= 0; i--) {
        if (aux1.digits_[i] == true && aux2.digits_[i] == false) {
            return true;
        } else if (aux1.digits_[i] == false && aux2.digits_[i] == true) {
            return false;
        }
    }

    return false;
}

bool operator<(const BigInt<2>& num1, const BigInt<2>& num2) {
    return !(num1 > num2 || num1 == num2);
}

bool operator>=(const BigInt<2>& num1, const BigInt<2>& num2) {
    return (num1 > num2 || num1 == num2);
}

bool operator<=(const BigInt<2>& num1, const BigInt<2>& num2) {
    return (num1 < num2 || num1 == num2);
}

// Increment and Decrement Operators
BigInt<2>& BigInt<2>::operator++() {
    *this = *this + BigInt<2>("01");
    return *this;
}

BigInt<2> BigInt<2>::operator++(int) {
    BigInt<2> aux = *this;
    ++(*this);
    return aux;
}

BigInt<2>& BigInt<2>::operator--() {
    *this = *this - BigInt<2>("01");
    return *this;
}

BigInt<2> BigInt<2>::operator--(int) {
    BigInt<2> aux = *this;
    --(*this);
    return aux;
}

// Arithmetic Operators

BigInt<2> operator+(const BigInt<2>& num1, const BigInt<2>& num2) {


    int size1 = num1.digits_.size();
    int size2 = num2.digits_.size();

    BigInt<2> aux1 = num1;
    BigInt<2> aux2 = num2;

    
    BigInt<2> result;
    result.digits_.resize(std::max(size1, size2), false);

    bool carry = false;

    if (aux1.sign_ == 0 && aux2.sign_ == 0) {

        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(false);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(false);
            }
        }

        for(int i = 0; i < result.digits_.size(); i++) {
            if (aux1.digits_[i] == false && aux2.digits_[i] == false) {
                if (carry == true) {
                    result.digits_[i] = true;
                    carry = false;
                } else {
                    result.digits_[i] = false;
                }
            } else if (aux1.digits_[i] == true && aux2.digits_[i] == true) {
                if (carry == true) {
                    result.digits_[i] = true;
                } else {
                    result.digits_[i] = false;
                    carry = true;
                }
            } else {
                if (carry == true) {
                    result.digits_[i] = false;
                } else {
                    result.digits_[i] = true;
                }
            }
        }
        if (carry == true) {
            result.digits_.push_back(true);
        }
    } else if (aux1.sign_ == 1 && aux2.sign_ == 1) {

        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(true);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(true);
            }
        }

        result = aux1.abs() + aux2.abs();

        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;

    } else if (aux1.sign_ == 0 && aux2.sign_ == 1) {

        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(true);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(false);
            }
        }

        if (aux1 > aux2.abs()) {

            result = aux1 - aux2.abs();

        } else {
            result = aux2.abs() - aux1;
            result = result.complementTwo();
            result.digits_[result.digits_.size()] = true;
            result.sign_ = 1;

        }
    } else if (aux1.sign_ == 1 && aux2.sign_ == 0) {

        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(false);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(true);
            }
        }

        if (aux1.abs() > aux2) {

            result = aux1.abs() - aux2;
            result = result.complementTwo();
            result.digits_[result.digits_.size()] = true;
            result.sign_ = 1;

        } else if (aux1.abs() < aux2) {
            result = aux2 - aux1.abs();
        }
    }

    return result;
}

BigInt<2> BigInt<2>::operator-(const BigInt<2> &num) const {

    int size1 = digits_.size();
    int size2 = num.digits_.size();

    BigInt<2> aux1 = *this;
    BigInt<2> aux2 = num;

    
    BigInt<2> result;

    result.digits_.resize(std::max(size1, size2), false);

    if (aux1.sign_ == 1 && aux2.sign_ == 1) {
        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(true);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(true);
            }
        }

        result = aux1.abs() + aux2.abs();

        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;

    } else if (aux1.sign_ == 0 && aux2.sign_ == 0) {

        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(false);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(false);
            }
        }

        if (aux1 > aux2) {

            bool carry = false;
            for(int i = 0; i < result.digits_.size(); i++) { 
                if (aux1.digits_[i] == false && aux2.digits_[i] == false) { // 0 - 0 -> Carry = 0
                    if (carry == true) {
                        result.digits_[i] = true;
                        carry = true;
                    } else {
                        result.digits_[i] = false;
                    }
                } else if (aux1.digits_[i] == true && aux2.digits_[i] == true) { // 1 - 1 -> Carry = 0
                    if (carry == true) {
                        result.digits_[i] = true;
                        carry = true;
                    } else {
                        result.digits_[i] = false;
                    }
                } else if (aux1.digits_[i] == false && aux2.digits_[i] == true) { // 0 - 1 -> Carry = 1
                    if (carry == true) {
                        result.digits_[i] = false;
                        carry = true;
                    } else {
                        result.digits_[i] = true;
                        carry = true;
                    }
                } else { // 1 - 0 -> Carry = 0
                    if (carry == true) {
                        result.digits_[i] = false;
                        carry = false;
                    } else {
                        result.digits_[i] = true;
                    }
                }
            }

            if (carry == true) {
                result.digits_.push_back(true);
            }

        } else {


            aux2 = aux2.complementTwo();
            aux2.digits_[aux2.digits_.size()] = true;
            aux2.setSign(1);

            result = aux1 + aux2;
        }

    } else if (aux1.sign_ == 0 && aux2.sign_ == 1) {
        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(true);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(false);
            }
        }

        result = aux1 + aux2.abs();

    } else if (aux1.sign_ == 1 && aux2.sign_ == 0) {

        if (size1 > size2) {
            for (int i = 0; i < size1 - size2; i++) {
                aux2.digits_.push_back(false);
            }
        } else if (size1 < size2) {
            for (int i = 0; i < size2 - size1; i++) {
                aux1.digits_.push_back(true);
            }
        }

        result = aux1.abs() + aux2;
        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;
    }

    return result;
}

BigInt<2> BigInt<2>::complementTwo() const {

    if (this->sign_ == 1) {
        return *this;
    }

    BigInt<2> result;

    result.digits_.resize(this->digits_.size(), false);

    BigInt<2> aux = *this;
    aux.setPosition(aux.digits_.size(), true);

    int i = 0; 
    for (i = 0; i < this->digits_.size() + 1; i++) {
        if (aux.digits_[i]) {
            result.digits_[i] = true;
            break;
        } else {
            result.digits_[i] = false;
        }
    }

    // Invertir los dígitos
    for (i = i + 1; i < this->digits_.size() + 1; i++) {
        if (aux.digits_[i]) {
            result.digits_[i] = false;
        } else {
            result.digits_[i] = true;
        }
    }

    return result;
}

BigInt<2> BigInt<2>::abs() const {

    if (this->sign_ == 0) {
        return *this;
    }

    BigInt<2> result;

    result.digits_.resize(this->digits_.size(), false);

    int i = 0;
    for (i = 0; i < this->digits_.size(); i++) {
        if (this->digits_[i]) {
            result.digits_[i] = true;
            break;
        } else {
            result.digits_[i] = false;
        }
    }

    // Invertir los demas

    for (i = i + 1; i < this->digits_.size(); i++) {
        if (this->digits_[i]) {
            result.digits_[i] = false;
        } else {
            result.digits_[i] = true;
        }
    }

    return result;

}



BigInt<2> BigInt<2>::operator-() const {
    if(this->sign_ == 0) {
        BigInt<2> result = *this;
        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;
        return result;
    } else {
        BigInt<2> result = *this;
        result = result.abs();
        result.sign_ = 0;
        return result;
    }
}

BigInt<2> BigInt<2>::operator*(const BigInt<2>& num) const {
    BigInt<2> result;
    BigInt<2> aux1 = *this;
    BigInt<2> aux2 = num;

    if (aux1.sign_ == 1) {
        aux1 = aux1.abs(); // Convertir a positivo
    }

    if (aux2.sign_ == 1) {
        aux2 = aux2.abs(); // Convertir a positivo
    }

    int size1 = aux1.digits_.size();
    int size2 = aux2.digits_.size();

    if (size1 > size2) {
        for (int i = 0; i < size1 - size2; i++) {
            aux2.digits_.push_back(false);
        }
    } else if (size1 < size2) {
        for (int i = 0; i < size2 - size1; i++) {
            aux1.digits_.push_back(false);
        }
    }

    result.digits_.resize(size1 + size2, false);

    // 0 x 0 = 0
    // 0 x 1 = 0
    // 1 x 0 = 0
    // 1 x 1 = 1 

    for (int i = 0; i < aux1.digits_.size(); i++) {
        bool carry = false;
        for (int j = 0; j < aux2.digits_.size(); j++) {
            bool product = aux1.digits_[i] && aux2.digits_[j];
            bool sum = result.digits_[i+j] ^ product ^ carry;
            carry = (result.digits_[i+j] && product) || (result.digits_[i+j] && carry) || (product && carry);
            result.digits_[i+j] = sum;
        }
        if (carry) {
            result.digits_[i+aux2.digits_.size()] = true;
        }
    }


    if (this->sign_ == 1 && num.sign_ == 0) {
        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;
        
    } else if (this->sign_ == 0 && num.sign_ == 1) {
        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;
    }


    return result;
}


BigInt<2> operator/(const BigInt<2>& dividend, const BigInt<2>& divisor) {

    BigInt<2> result;

    BigInt<2> aux1 = dividend;

    if(dividend.sign_ == 1) {
        aux1 = aux1.abs();
    }

    BigInt<2> aux2 = divisor;

    if(divisor.sign_ == 1) {
        aux2 = aux2.abs();
    }

    int size1 = aux1.digits_.size();
    int size2 = aux2.digits_.size();

    if (size1 > size2) {
        for (int i = 0; i < size1 - size2; i++) {
            aux2.digits_.push_back(false);
        }
    } else if (size1 < size2) {
        for (int i = 0; i < size2 - size1; i++) {
            aux1.digits_.push_back(false);
        }
    }

    result.digits_.resize(size1 + size2, false);

    // 0 / 0 = 0
    // 0 / 1 = 0
    // 1 / 0 = 0
    // 1 / 1 = 1

    while (aux1 > aux2) {
        aux1 = aux1 - aux2;
        result = result + BigInt<2>("01");
    }

    if (aux1 == aux2) {
        result = result + BigInt<2>("01");
    }

    // Si los signos son diferentes el resultado es negativo

    if (dividend.sign_ == 1 && divisor.sign_ == 0) {
        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;
    } else if (dividend.sign_ == 0 && divisor.sign_ == 1) {
        result = result.complementTwo();
        result.digits_[result.digits_.size()] = true;
        result.sign_ = 1;
    }

    return result;

}

BigInt<2> BigInt<2>::operator%(const BigInt<2>& num) const {
    BigInt<2> result;
    BigInt<2> aux;
    // Dividir hasta que el resto sea menor que el divisor
    if (num.sign() == 1) {
        aux = num.abs();
    } else {
        aux = num;
    }

    if (this->sign() == 1) {
        result = this->abs();
    } else {
        result = *this;
    }

    if (result < aux) {
        return result;
    }

    while (result > aux) {
        result = result - aux;
    }

    return result;
}


// Flow Operators
std::ostream &operator<<(std::ostream &os, const BigInt<2> &num) {

    // Imprimir el signo
    if (num.sign_ == 1) {
        os << "1";
    } else {
        os << "0";
    }


    for (int i = num.digits_.size(); i >= 0; i--) {
        if (num.digits_[i]) {
            os << "1";
        } else {
            os << "0";
        }
    }

    return os;
}

// Cambio de tipo

template <size_t Base>
BigInt<2>::operator BigInt<Base>() const {

    BigInt<Base> result;
    BigInt<2> aux = *this;

    switch (Base) {
        case 2:
            return *this;
            break;

        case 8:
            {
                if (aux.sign_ == 1) {
                    aux = aux.abs();
                } 


                // Comprobar que aux tiene un numero de digitos multiplo de 3
                if (aux.digits_.size() % 3 != 0) {
                    for (int i = 0; i < 3 - (aux.digits_.size() % 3); i++) {
                        aux.digits_.push_back(false);
                    }
                }

                std::string digitsOctal;

                // Recorrer los digitos de aux de 3 en 3
                for (int i = 0; i < aux.digits_.size(); i += 3) {
                    int sum = 0;
                    for (int j = 0; j < 3; j++) {
                        sum += aux.digits_[i+j] * std::pow(2, j);
                    }
                    digitsOctal += std::to_string(sum);
                }

                // Invertir el string
                std::reverse(digitsOctal.begin(), digitsOctal.end());

                // Eliminar los ceros a la izquierda
                while (digitsOctal[0] == '0') {
                    digitsOctal.erase(0, 1);
                }

                result = BigInt<Base>(digitsOctal);

                if (sign_ == 1) {
                    result.setSign(-1);
                }

                return result;

                break;
                
            }
            
        case 10:
            {
                if (aux.sign_ == 1) {
                    aux = aux.abs();
                } 

                for (int i = 0; i < aux.digits_.size(); ++i) {
                    if (aux.digits_[i]) {
                        result = result + BigInt<Base>(std::pow(2, i));
                    }
                }

                if (sign_ == 1) {
                    result.setSign(-1);
                }

                return result;

                break;
            }

        case 16:
            {
                if (aux.sign_ == 1) {
                    aux = aux.abs();
                } 

                // Comprobar que aux tiene un numero de digitos multiplo de 4
                if (aux.digits_.size() % 4 != 0) {
                    for (int i = 0; i < 4 - (aux.digits_.size() % 4); i++) {
                        aux.digits_.push_back(false);
                    }
                }

                std::string digitsHex;

                // Recorrer los digitos de aux de 4 en 4
                for (int i = 0; i < aux.digits_.size(); i += 4) {
                    int sum = 0;
                    for (int j = 0; j < 4; j++) {
                        sum += aux.digits_[i+j] * std::pow(2, j);
                    }
                    switch (sum) {
                        case 10:
                            digitsHex += "A";
                            break;
                        case 11:
                            digitsHex += "B";
                            break;
                        case 12:
                            digitsHex += "C";
                            break;
                        case 13:
                            digitsHex += "D";
                            break;
                        case 14:
                            digitsHex += "E";
                            break;
                        case 15:
                            digitsHex += "F";
                            break;
                        default:
                            digitsHex += std::to_string(sum);
                            break;
                    }
                }

                // Invertir el string
                std::reverse(digitsHex.begin(), digitsHex.end());

                // Eliminar los ceros a la izquierda
                while (digitsHex[0] == '0') {
                    digitsHex.erase(0, 1);
                }

                result = BigInt<Base>(digitsHex);

                if (sign_ == 1) {
                    result.setSign(-1);
                }

                return result;

                break;
            }
        default:
            return *this;
            break;
    }

}




template <size_t Base = 10>
class BigInt {

    private:
        bool checkBase();
        bool checkDigits(char digit);

        std::vector<char> digits_;
        int sign_;

    public:
        BigInt(long value = 0);
        BigInt(std::string& value);
        BigInt(const char* value);
        BigInt(const BigInt<Base>& value);
        ~BigInt();

        // Asignment Operators
        BigInt<Base>& operator=(const BigInt<Base>& num);

        // Flow Operators
        friend std::ostream &operator<<<Base>(std::ostream &, const BigInt<Base> &);
        friend std::istream &operator>><Base>(std::istream &, BigInt<Base> &);

        // Accesor Methods
        int sign() const; 
        char operator[](int) const; 

        //Setters
        void setSign(int sign);

        // Comparison Operators
        friend bool operator==<Base>(const BigInt<Base>& num1, const BigInt<Base>& num2);
        bool operator!=(const BigInt<Base>& num) const;
        friend bool operator><Base>(const BigInt<Base>& num1, const BigInt<Base>& num2);
        bool operator>=(const BigInt<Base>& num) const;
        friend bool operator< <Base>(const BigInt<Base>& num1, const BigInt<Base>& num2);
        bool operator<=(const BigInt<Base>& num) const;

        // Increment and Decrement Operators
        BigInt<Base>& operator++(); 
        BigInt<Base> operator++(int value); 
        BigInt<Base>& operator--(); 
        BigInt<Base> operator--(int value); 

        // Arithmetic Operators
        friend BigInt<Base> operator+<Base>(const BigInt<Base>&, const BigInt<Base>&);
        BigInt<Base> operator-(const BigInt<Base> &) const;
        BigInt<Base> operator-() const;
        BigInt<Base> operator*(const BigInt<Base>&) const;
        friend BigInt<Base> operator/<Base>(const BigInt<Base>&, const BigInt<Base>&);
        BigInt<Base> operator%(const BigInt<Base>&) const;

        // Pow
        friend BigInt<Base> pow<Base>(const BigInt<Base>&, const BigInt<Base>&);

        // Type Conversion

        operator BigInt<2>() {

            BigInt<2> result;

            switch (Base) {
                case 2:
                    result = *this;
                    break;
                case 8:
                    {
                        std::string binaryDigits;

                        if (sign_ == -1) {
                            binaryDigits += "1";
                        } else {
                            binaryDigits += "0";
                        }

                        // Recorrer todos los digitos de this empezando por el final
                        for (int i = digits_.size() - 1; i >= 0; --i) {
                            // Convertir el digito octal a binario
                            switch (digits_[i]) {
                                case '0':
                                    binaryDigits += "000";
                                    break;
                                case '1':
                                    binaryDigits += "001";
                                    break;
                                case '2':
                                    binaryDigits += "010";
                                    break;
                                case '3':
                                    binaryDigits += "011";
                                    break;
                                case '4':
                                    binaryDigits += "100";
                                    break;
                                case '5':
                                    binaryDigits += "101";
                                    break;
                                case '6':
                                    binaryDigits += "110";
                                    break;
                                case '7':
                                    binaryDigits += "111";
                                    break;
                            }
                        }

                        result = BigInt<2>(binaryDigits);

                        return result;

                        break;
                    }
                case 10:
                    {
                        BigInt<Base> num(*this);

                        if (sign_ == -1) {
                            num = -num;
                        }

                        BigInt<Base> two(2L);
                        BigInt<Base> zero(0L);

                        std::vector<bool> digits;

                        while(num > two) {
                            if(num % two == zero) {
                                digits.push_back(false);
                            } else {
                                digits.push_back(true);
                            }
                            num = num / two;
                        }
                        
                        if (num < two) {
                            digits.push_back(true);
                        }

                        if (num == two) {
                            digits.push_back(false);
                            digits.push_back(true);
                        }

                        digits.push_back(false); // Signo

                        // Recorrer digits desde el final e introducirlo en un string
                        std::string binaryDigits;

                        for (int i = digits.size() - 1; i >= 0; --i) {
                            if (digits[i]) {
                                binaryDigits += "1";
                            } else {
                                binaryDigits += "0";
                            }
                        }

                        if (sign_ == -1) {
                            result = BigInt<2>(binaryDigits);
                            result = result.complementTwo();
                            result.setSign(1);

                            return result;

                        } else {
                            result = BigInt<2>(binaryDigits);
                            return result;
                        }

                        return result = BigInt<2>("00");

                    }

                case 16:
                    {
                        std::string binaryDigits;

                        if (sign_ == -1) {
                            binaryDigits += "1";
                        } else {
                            binaryDigits += "0";
                        }

                        // Recorrer todos los digitos de this empezando por el final
                        for (int i = digits_.size() - 1; i >= 0; --i) {
                            // Convertir el digito hexadecimal a binario
                            switch (digits_[i]) {
                                case '0':
                                    binaryDigits += "0000";
                                    break;
                                case '1':
                                    binaryDigits += "0001";
                                    break;
                                case '2':
                                    binaryDigits += "0010";
                                    break;
                                case '3':
                                    binaryDigits += "0011";
                                    break;
                                case '4':
                                    binaryDigits += "0100";
                                    break;
                                case '5':
                                    binaryDigits += "0101";
                                    break;
                                case '6':
                                    binaryDigits += "0110";
                                    break;
                                case '7':
                                    binaryDigits += "0111";
                                    break;
                                case '8':
                                    binaryDigits += "1000";
                                    break;
                                case '9':
                                    binaryDigits += "1001";
                                    break;
                                case 'A':
                                    binaryDigits += "1010";
                                    break;
                                case 'B':
                                    binaryDigits += "1011";
                                    break;
                                case 'C':
                                    binaryDigits += "1100";
                                    break;
                                case 'D':
                                    binaryDigits += "1101";
                                    break;
                                case 'E':
                                    binaryDigits += "1110";
                                    break;
                                case 'F':
                                    binaryDigits += "1111";
                                    break;
                            }
                        }

                        result = BigInt<2>(binaryDigits);

                        return result;

                        break;
                    }

                default:
                    return BigInt<2>("00");
                    break;
            }

            return result = BigInt<2>("00");
            
        }


};

// Check Methods

template <size_t Base>
bool BigInt<Base>::checkBase() {
    if (Base == 2 || Base == 8 || Base == 10 || Base == 16)
        return true;

    return false;
}

template <size_t Base>
bool BigInt<Base>::checkDigits(char digit) {
    switch(Base) {
        case 2:     
            if (digit == '0' || digit == '1')
                return true;
            break;
        case 8:
            if (digit >= '0' && digit <= '7')
                return true;
            break;
        case 10:
            if (digit >= '0' && digit <= '9')
                return true;
            break;
        case 16:
            if ((digit >= '0' && digit <= '9') || (digit >= 'A' && digit <= 'F'))
                return true;
            break;
        default:
            break;
    }
    return false;
}

// Constructors

template <size_t Base>
BigInt<Base>::BigInt(long value) {
    if(checkBase()) {
        if (value < 0) {
            sign_ = -1;
            value = -value;
        } else {
            sign_ = 1;
        }
    } else {
        std::cout << "Base is not supported" << std::endl;
        exit(EXIT_FAILURE);
    }

    while(value > 0) {
        if(checkDigits(value % 10 + '0')) 
            digits_.push_back(value % 10 + '0');
        else {
            std::cout << "Digit is not supported" << std::endl;
            exit(EXIT_FAILURE);
        }
        value /= 10;
    }
}

template <size_t Base>
BigInt<Base>::BigInt(std::string& value) {
    if (checkBase()) {
        if (value[0] == '-') {
            sign_ = -1;
            value = value.substr(1);
        } else if (value[0] == '+') {
            sign_ = 1;
            value = value.substr(1);
        } else if (regex_match(std::string(1, value[0]), std::regex("[0-9A-F]"))) {
            sign_ = 1;
        } else {
            std::cout << "Invalid number" << std::endl;
            exit(EXIT_FAILURE);
        }
    } else {
        std::cout << "Base is not supported" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (int i = value.size() - 1; i >= 0; i--) {
        if (checkDigits(value[i]))
            digits_.push_back(value[i]);
        else {
            std::cout << "Digit is not supported" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

template <size_t Base>
BigInt<Base>::BigInt(const char* value) {
    // Convert char* to string
    std::string str(value);
    BigInt<Base> temp(str);
    digits_ = temp.digits_;
    sign_ = temp.sign_;
}

template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& value) {
    digits_ = value.digits_;
    sign_ = value.sign_;
}

template <size_t Base>
BigInt<Base>::~BigInt() {
    digits_.clear();
    sign_ = 0;
}

// Asignment Operators

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator=(const BigInt<Base>& num) {
    digits_ = num.digits_;
    sign_ = num.sign_;
    return *this;
}

// Flow operators
template <size_t Base>
std::ostream &operator<<(std::ostream &os, const BigInt<Base> &n) {
  if (n.sign_ == -1)
    os << "-";
  for (int i = n.digits_.size() - 1; i >= 0; i--)
    os << n.digits_[i];
  return os;
}

template <size_t Base>
std::istream &operator>>(std::istream &is, BigInt<Base> &n) {
  std::string str;
  is >> str;
  n = BigInt<Base>(str);
  return is;
}

// Accesor Methods

template <size_t Base>
int BigInt<Base>::sign() const {
    return sign_;
}

template <size_t Base>
char BigInt<Base>::operator[](int index) const {
    int size = digits_.size();
    if (index < 0 || index >= size) {
        std::cout << "Index out of range" << std::endl;
        exit(EXIT_FAILURE);
    }
    return digits_[index];
}

// Setters

template <size_t Base>
void BigInt<Base>::setSign(int sign) {
    sign_ = sign;
}


// Comparison Operators

template <size_t Base>
bool operator==(const BigInt<Base>& num1, const BigInt<Base>& num2) {

    bool num1_zero = true;
    bool num2_zero = true;

    for (int i = 0; i < num1.digits_.size(); i++) {
        if (num1.digits_[i] != '0') {
            num1_zero = false;
            break;
        }
    }

    for (int i = 0; i < num2.digits_.size(); i++) {
        if (num2.digits_[i] != '0') {
            num2_zero = false;
            break;
        }
    }

    if (num1_zero && num2_zero)
        return true;
    
    if (num1.sign_ != num2.sign_)
        return false;

    if (num1.digits_.size() != num2.digits_.size())        
        return false;

    for (int i = 0; i < num1.digits_.size(); i++) {
        if (num1.digits_[i] != num2.digits_[i])
            return false;
    }
    return true;
}

template <size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& num) const {
    return !(*this == num);
}

template <size_t Base>
bool operator>(const BigInt<Base>& num1, const BigInt<Base>& num2) {
    if (num1.sign_ == -1 && num2.sign_ == 1)
        return false;
    if (num1.sign_ == 1 && num2.sign_ == -1)
        return true;
    if (num1.sign_ == 1 && num2.sign_ == 1) {
        if (num1.digits_.size() > num2.digits_.size())
            return true;
        else if (num1.digits_.size() < num2.digits_.size())
            return false;
        else {
            for (int i = num1.digits_.size() - 1; i >= 0; i--) {
                if (num1[i] > num2[i])
                    return true;
                else if (num1[i] < num2[i])
                    return false;
            }
        }
    }
  return false;
}

template <size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base>& num) const {
    return (*this > num || *this == num);
}

template <size_t Base>
bool operator<(const BigInt<Base> &num1, const BigInt<Base> &num2) {
  return !(num1 >= num2);
}

template <size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base>& num) const {
    return (*this < num || *this == num);
}

// Increment and Decrement Operators

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator++() {
    BigInt<Base> one(1);
    *this = *this + one;
    return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator++(int) {
    BigInt<Base> temp(*this);
    ++(*this);
    return temp;
}

template <size_t Base>
BigInt<Base>& BigInt<Base>::operator--() {
    BigInt<Base> one(1);
    *this = *this - one;
    return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator--(int) {
    BigInt<Base> temp(*this);
    --(*this);
    return temp;
}

// Arithmetic Operators

template <size_t Base>
BigInt<Base> operator+(const BigInt<Base> &n1, const BigInt<Base> &n2) {
  BigInt<Base> result;

  size_t carry = 0;
  size_t i = 0;
  size_t j = 0;

  if (n1.sign() == -1 && n2.sign() == -1)
  {
    result.sign_ = -1;
    while (i < n1.digits_.size() || j < n2.digits_.size())
    {
      int num1, num2;
      if (i < n1.digits_.size())
      {
        if (n1[i] >= '0' && n1[i] <= '9')
          num1 = n1[i] - '0';
        else if (n1[i] >= 'A' && n1[i] <= 'F')
          num1 = n1[i] - 'A' + 10;
        i++;
      }
      else
        num1 = 0;

      if (j < n2.digits_.size())
      {
        if (n2[j] >= '0' && n2[j] <= '9')
          num2 = n2[j] - '0';
        else if (n2[j] >= 'A' && n2[j] <= 'F')
          num2 = n2[j] - 'A' + 10;
        j++;
      }
      else
        num2 = 0;

      int sum = num1 + num2 + carry;
      carry = sum / Base;
      sum = sum % Base;

      if (sum >= 0 && sum <= 9)
        result.digits_.push_back(sum + '0');
      else if (sum >= 10 && sum <= 15)
        result.digits_.push_back(sum - 10 + 'A');
    }
    if (carry > 0)
      result.digits_.push_back(carry + '0');
  }
  else if (n1.sign() == 1 && n2.sign() == 1)
  {
    result.sign_ = 1;
    while (i < n1.digits_.size() || j < n2.digits_.size())
    {
      int num1, num2;
      if (i < n1.digits_.size())
      {
        if (n1[i] >= '0' && n1[i] <= '9')
          num1 = n1[i] - '0';
        else if (n1[i] >= 'A' && n1[i] <= 'F')
          num1 = n1[i] - 'A' + 10;
        i++;
      }
      else
        num1 = 0;

      if (j < n2.digits_.size())
      {
        if (n2[j] >= '0' && n2[j] <= '9')
          num2 = n2[j] - '0';
        else if (n2[j] >= 'A' && n2[j] <= 'F')
          num2 = n2[j] - 'A' + 10;
        j++;
      }
      else
        num2 = 0;

      int sum = num1 + num2 + carry;
      carry = sum / Base;
      sum = sum % Base;

      if (sum >= 0 && sum <= 9)
        result.digits_.push_back(sum + '0');
      else if (sum >= 10 && sum <= 15)
        result.digits_.push_back(sum - 10 + 'A');
    }
    if (carry > 0)
      result.digits_.push_back(carry + '0');
  }
  else if (n1.sign() == -1 && n2.sign() == 1)
  {
    BigInt<Base> n1_copy(n1);
    n1_copy.sign_ = 1;
    result = n2 - n1_copy;
  }
  else if (n1.sign() == 1 && n2.sign() == -1)
  {
    BigInt<Base> n2_copy(n2);
    n2_copy.sign_ = 1;
    result = n1 - n2_copy;
  }

  return result;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base> &other) const {
  BigInt<Base> result;

  size_t carry = 0;
  size_t i = 0;
  size_t j = 0;

  if (sign() == -1 && other.sign() == -1)
  {
    BigInt<Base> n1_copy(*this);
    n1_copy.sign_ = 1;
    BigInt<Base> n2_copy(other);
    n2_copy.sign_ = 1;
    result = n2_copy - n1_copy;
  }
  else if (sign() == 1 && other.sign() == 1)
  {
    BigInt<Base> n1_copy(*this);
    BigInt<Base> n2_copy(other);
    if (n1_copy < n2_copy)
    {
      result = n2_copy - n1_copy;
      result.sign_ = -1;
    }
    else
    {
      result.sign_ = 1;
      while (i < n1_copy.digits_.size() || j < n2_copy.digits_.size())
      {
        int num1, num2;
        if (i < n1_copy.digits_.size())
        {
          if (n1_copy[i] >= '0' && n1_copy[i] <= '9')
            num1 = n1_copy[i] - '0';
          else if (n1_copy[i] >= 'A' && n1_copy[i] <= 'F')
            num1 = n1_copy[i] - 'A' + 10;
          i++;
        }
        else
          num1 = 0;

        if (j < n2_copy.digits_.size())
        {
          if (n2_copy[j] >= '0' && n2_copy[j] <= '9')
            num2 = n2_copy[j] - '0';
          else if (n2_copy[j] >= 'A' && n2_copy[j] <= 'F')
            num2 = n2_copy[j] - 'A' + 10;
          j++;
        }
        else
          num2 = 0;

        int sum = num1 - num2 - carry;
        if (sum < 0)
        {
          sum += Base;
          carry = 1;
        }
        else
          carry = 0;

        if (sum >= 0 && sum <= 9)
          result.digits_.push_back(sum + '0');
        else if (sum >= 10 && sum <= 15)
          result.digits_.push_back(sum - 10 + 'A');
      }
    }
  }
  else if (sign() == -1 && other.sign() == 1)
  {
    BigInt<Base> n1_copy(*this);
    n1_copy.sign_ = 1;
    result = n1_copy + other;
    result.sign_ = -1;
  }
  else if (sign() == 1 && other.sign() == -1)
  {
    BigInt<Base> n2_copy(other);
    n2_copy.sign_ = 1;
    result = *this + n2_copy;
  }

  if (result.digits_[result.digits_.size() - 1] == '0')
    result.digits_.pop_back();

  return result;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator-() const
{
  BigInt<Base> result(*this);
  result.sign_ = -result.sign_;
  return result;
}


template <size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base> &rhs) const
{
  BigInt<Base> result;
  result.sign_ = sign_ * rhs.sign_;

  BigInt<Base> n1 = *this;
  BigInt<Base> n2 = rhs;

  if (n1.sign() == -1)
    n1 = -n1;
  if (n2.sign() == -1)
    n2 = -n2;

  BigInt<Base> sum;

  for (size_t i = 0; i < n2.digits_.size(); i++)
  {
    BigInt<Base> temp;
    int carry = 0;
    for (size_t j = 0; j < n1.digits_.size(); j++)
    {
      int num1 = n1[j] >= '0' && n1[j] <= '9' ? n1[j] - '0' : n1[j] - 'A' + 10;
      int num2 = n2[i] >= '0' && n2[i] <= '9' ? n2[i] - '0' : n2[i] - 'A' + 10;
      int prod = num1 * num2 + carry;
      carry = prod / Base;
      prod = prod % Base;
      temp.digits_.push_back(prod >= 10 ? prod - 10 + 'A' : prod + '0');
    }
    if (carry > 0)
      temp.digits_.push_back(carry >= 10 ? carry - 10 + 'A' : carry + '0');
    for (size_t j = 0; j < i; j++)
      temp.digits_.insert(temp.digits_.begin(), '0');
    sum = sum + temp;
  }

  if (result.sign() == -1)
    result = -sum;
  else
    result = sum;

  return result;
}

template <size_t Base>
BigInt<Base> operator/(const BigInt<Base> &dividend, const BigInt<Base> &divider) {

    BigInt<Base> result;
    BigInt<Base> n1 = dividend;
    BigInt<Base> n2 = divider;
    
    if (n1.sign() == -1)
        n1 = -n1;
    if (n2.sign() == -1)
        n2 = -n2;

    if (n1 < n2) {

        return BigInt<Base>("0");
    }
        
    
    BigInt<Base> temp;
    for (int i = (int)n1.digits_.size() - 1; i >= 0; i--) {
        temp.digits_.insert(temp.digits_.begin(), n1[i]);
        int count = 0;
        while (temp >= n2)
        {
        temp = temp - n2;
        count++;
        }
        result.digits_.insert(result.digits_.begin(), (count >= 10) ? count - 10 + 'A' : count + '0');
    }
    
    if (dividend.sign() == -1 && divider.sign() == -1)
        result.sign_ = 1;
    else if (dividend.sign() == -1 || divider.sign() == -1)
        result.sign_ = -1;

    // Si hay algun cero al final, se elimina
    if (result.digits_[result.digits_.size() - 1] == '0')
        result.digits_.pop_back();
    
    return result;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base> &rhs) const
{
  BigInt<Base> result;
  BigInt<Base> n1 = *this;
  BigInt<Base> n2 = rhs;

  if (n1.sign() == -1)
    n1 = -n1;
  if (n2.sign() == -1)
    n2 = -n2;

  if (n1 < n2)
    return n1;

  BigInt<Base> temp;
  for (int i = (int)n1.digits_.size() - 1; i >= 0; i--)
  {
    temp.digits_.insert(temp.digits_.begin(), n1[i]);
    int count = 0;
    while (temp >= n2)
    {
      temp = temp - n2;
      count++;
    }
  }

  if (sign() == -1)
    result = -temp;
  else
    result = temp;

  return result;
}

template <size_t Base>
BigInt<Base> pow(const BigInt<Base> &a, const BigInt<Base> &b)
{
  if (b < BigInt<Base>(0L))
  {
    std::cerr << "Error: el exponente no puede ser negativo." << std::endl;
    return BigInt<Base>();
  }
  BigInt<Base> res(1L);
  for (BigInt<Base> i(0L); i < b; i = i + BigInt<Base>(1L))
    res = res * a;

  return res;
}


////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>


namespace xi {

//==============================================================================
// Free functions -- helpers
//==============================================================================

// TODO: if you need any free functions, add their definitions here.

//==============================================================================
// class PlusOp
//==============================================================================

int PlusOp::operation(char op, int a, int b, int /*c*/) {
    if (op != '+')
        throw std::logic_error("Operation other than Plus (+) are not supported");

    // here we just ignore unused operands
    return a + b;
}

IOperation::Arity PlusOp::getArity() const {
    return arDue;
}

//==============================================================================
// class MinusOp
//==============================================================================

int MinusOp::operation(char op, int a, int b, int /*c*/) {
    if (op != '-')
        throw std::logic_error("Operation other than Minus (-) are not supported");
    return a - b;
}

IOperation::Arity MinusOp::getArity() const {
    return arDue;
}

//==============================================================================
// class MultOp
//==============================================================================

    int MultOp::operation(char op, int a, int b, int /*c*/) {
        if (op != '*')
            throw std::logic_error("Operation other than Mult (*) are not supported");
        return a * b;
    }

    IOperation::Arity MultOp::getArity() const {
        return arDue;
    }

//==============================================================================
// class AssignOp
//==============================================================================

    int AssignOp::operation(char op, int a, int /*b*/, int /*c*/) {
        if (op != '=')
            throw std::logic_error("Operation other than Assign (=) are not supported");
        return a;
    }

    IOperation::Arity AssignOp::getArity() const {
        return arUno;
    }


//==============================================================================
// class StackMachine
//==============================================================================

    void StackMachine::registerOperation(char symb, xi::IOperation *oper) {
        SymbolToOperMapConstIter it = _opers.find(symb);
        if (it != _opers.end())
            throw std::logic_error("An operation (" + std::string(1, symb) + ") is already registered");
        _opers[symb] = oper;
    }

    IOperation* StackMachine::getOperation(char symb) {
        SymbolToOperMapConstIter it = _opers.find(symb);
        if (it == _opers.end())
            throw std::logic_error("An operation (" + std::string(1, symb) + ") didn't register");
        else
            return it->second;
    }

    int StackMachine::calculate(const std::string &expr, bool clearStack) {
        if (clearStack)
            _s.clear();
        std::string exprpart;

        std::istringstream iss(expr);
        std::vector<std::string> exprVector;
        while (iss >> exprpart) {
            exprVector.push_back(exprpart);
        }
        for(int i = 0; i < exprVector.size(); i++) {
            std::stringstream stream(exprVector[i]);
            int x;
            if (!(stream >> x)) {
                if (exprVector[i] == "+" || exprVector[i] == "-" || exprVector[i] == "*" || exprVector[i] == "=") {
                    xi::IOperation *operation = getOperation(exprVector[i][0]);
                    char symb = exprVector[i][0];
                    if (operation->getArity() == operation->arUno) {
                        int res = operation->operation(symb, _s.pop());
                        _s.push(res);
                    } else {
                        if (symb == '+') {
                            int b = _s.pop();
                            int a = _s.pop();
                            int res = operation->operation(symb, a, b);
                            _s.push(res);
                        }
                        if (symb == '-') {
                            int b = _s.pop();
                            int a = _s.pop();
                            int res = operation->operation(symb, a, b);
                            _s.push(res);
                        }
                        if (symb == '*') {
                            int b = _s.pop();
                            int a = _s.pop();
                            int res = operation->operation(symb, a, b);
                            _s.push(res);
                        }
                    }
                } else {
                    throw std::logic_error("Ivalid value or operator!");
                }
            } else {
                _s.push(x);
            }
        }
        return _s.top();
    }
}//namespace xi
